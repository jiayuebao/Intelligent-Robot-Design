#include <project.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

extern const uint8 CYCODE LCD_Char_customFonts[];//载入传统字体
#define PI 3.1416
#define r 35//mm
#define d 162//mm 轮间距

/**********PID调速变量*****************/
int16 expected_speed1=0;//期望转速
int16 expected_speed2=0;

int16 speed1 = 0,speed2=0;//转速，r/min

uint16 FIFO1[100],FIFO2[100];//FIFO数组，存放100个转速值


int8 flag=1;     //初始化正交解码器的标志位
int16 All_speed1=0,All_speed2=0;
int16 num1=0,num2=0;
int8 i=0;//指向FIFO中的数据位置


/**********红外变量*****************/
//中间红外传感器
uint32 IR_M = 0;  //AD转换值
float distM;
int disM;

//右侧红外传感器  
uint32 IR_R = 0;  //AD转换值
float distR;
int disR;

/*************LCD显示****************/
char outputStr1[12],outputStr2[12],outputStr3[12];
char outputStrx[12],outputStry[12],outputStrz[12];

/**********PWM变量*****************/
int PWM1=4700;          //左轮
int PWM2=4800;          //右轮
int stop1=4700;         //中间值1
int stop2=4800;         //中间值2
int forward1=600;       //前进，可调，速度快慢 
int forward2=250;                          
int backward1=450;      //后退 
int backward2=950;     
int rotate1;       //用于顺时针转 
int rotate2;       //用于逆时针转

int state=0;   //状态

int fflag=0;   //函数切换标记

int delayFlag=0; //延时标记

/**********位姿变量*****************/
int16 Pos[3]={0,0,0};//机器人的位姿x,y,sita
int16 Pos_Previous[3]={0,0,0};

double ins[3]={0,0,0};


/*************相关函数****************/
void Initialize_Components();  
void IntToString(char *str, int number);
void LCD_Display();

void Servo_PWM();
void Position();         //位姿计算

void Rotate_CW();        //小车顺时针旋转
void Rotate_CCW();       //小车逆时针旋转
void Move_Forward();     //小车前进
void Move_Backward();    //小车后退

void State_Verify();//判断小车状态
void Speed_Verify();//确认小车动作


/*******************************************获取红外传感器读数**********************************************/
void get_IR_dis()     
{
    AMux_Select(0);//中间读数
    CyDelay(1);
    ADC_SAR_Seq_StartConvert(); 
    ADC_SAR_Seq_IsEndConversion(ADC_SAR_Seq_WAIT_FOR_RESULT); 
    IR_M = ADC_SAR_Seq_GetResult16(0);
        
    AMux_Select(1);//右边读书
    CyDelay(1);
    ADC_SAR_Seq_StartConvert(); 
    ADC_SAR_Seq_IsEndConversion(ADC_SAR_Seq_WAIT_FOR_RESULT); 
    IR_R = ADC_SAR_Seq_GetResult16(0); 
        
    if(IR_M >0x7FFF) IR_M=0;
    if(IR_R >0x7FFF) IR_R=0;
        
    if(IR_M>0)//中间距离
    {
        distM=0.5/(0.00002*IR_M -0.00045)-2;
        disM=(int)distM;
    }
    if(IR_R>0)//右边距离
    {
        distR=0.5/(0.00002*IR_R -0.00045)-2;
        disR=(int)distR;
    }
}

/*************************************中断****************************************/
CY_ISR(InterruptHandler)//计时器中断
{
    Timer_ReadStatusRegister();//中断标志位重置
    if (flag==1)
    {
        QuadDec_1_Start(); QuadDec_2_Start();
        QuadDec_1_TriggerCommand(QuadDec_1_MASK, QuadDec_1_CMD_RELOAD);
        QuadDec_2_TriggerCommand(QuadDec_2_MASK, QuadDec_2_CMD_RELOAD);
        QuadDec_1_WriteCounter(0);
        QuadDec_2_WriteCounter(0);
        flag=0;
    }
    FIFO1[i]=QuadDec_1_ReadCounter()-32768;//每1.67ms读取解码器的计数
    QuadDec_1_WriteCounter(0);//解码器计数清零
    All_speed1=All_speed1+FIFO1[i];
    
    FIFO2[i]=QuadDec_2_ReadCounter()-32768;//每1.67ms读取解码器的计数
    QuadDec_2_WriteCounter(0);//解码器计数清零
    All_speed2=All_speed2+FIFO2[i];
    
    ++i;
    if (i==100)
    {
        i=0;
  
      //左轮
    num1=All_speed1/(1);
    speed1 = num1*6*60/360;
    All_speed1=0;

    
    //右轮
    num2=All_speed2/(1);
    speed2 = num2*6*60/360;
    All_speed2=0;
        
    get_IR_dis();//红外测距
    Position();//计算位姿

    }
     
}

/*************************************主函数****************************************/
int main()
{
        
     Initialize_Components();//初始化
    
    
    for(;;)
    { 
      
        if(fflag==0)
             State_Verify();//状态判定
                   
        else if(fflag==1)
             Speed_Verify(); //速度控制              
      
        LCD_Display();//LCD显示
    
    }
    
    
    return 0;
}

/*******************************************初始化**********************************************/
void Initialize_Components()
{
    CyGlobalIntEnable;//允许全局中断
    
    //以下初始化中断组件
    isr_StartEx(InterruptHandler);
    
    LCD_Char_Start();
    
    PWM_1_Start();
    PWM_2_Start();
    PWM_1_WriteCompare(4715);
    PWM_2_WriteCompare(4800);
    Timer_Enable();
    Timer_Start();//最后启动时钟
     ADC_SAR_Seq_Start();
    LCD_Char_ClearDisplay();//清屏
	LCD_Char_Position(0,0);
}
/******************************************LCD显示********************************************/
void LCD_Display()
{
    
    LCD_Char_ClearDisplay();
    
    //显示状态
    LCD_Char_Position(0,0);
    sprintf(outputStr1,"%d",state);
    LCD_Char_PrintString(outputStr1);

    //显示红外测距传感器读数
    LCD_Char_Position(0,6);
   sprintf(outputStr2,"%d",disR);
   LCD_Char_PrintString(outputStr2);

    LCD_Char_Position(0,11);
   sprintf(outputStr3,"%d",disM);
   LCD_Char_PrintString(outputStr3);


   CyDelay(50);
}


/******************************************PWM********************************************/
void Servo_PWM()
{
         
     PWM_1_WriteCompare(PWM1); //改变PWM的值以改变转速
     
      PWM_2_WriteCompare(PWM2); //改变PWM的值以改变转速
}

/******************************************位姿********************************************/
void Position ()
{
   
    //x,y,sita位姿计算
   ins[0]=ins[0]+(1/3.4)*(1.0/600)*100*(35.0/2)*(abs(speed2)+abs(speed1))*(2.0*PI/60)*sin(ins[2]/(180.0/PI)+(1.0/600)*100*(35.0/190)*(abs(speed2)-abs(speed1))*(2.0*PI/60.0));//x
   ins[1]=ins[1]+(1/3.5)*(1.0/600)*100*(35.0/2)*(abs(speed2)+abs(speed1))*(2.0*PI/60)*cos(ins[2]/(180.0/PI)+(1.0/600)*100*(35.0/190)*(abs(speed2)-abs(speed1))*(2.0*PI/60.0));//y
   ins[2]=ins[2]+(1.0/600)*100*(35.0/162)*(abs(speed2)-abs(speed1))*60;//sita
    
    
    Pos[0]=ins[0];//小车位姿X坐标mm
    Pos[1]=ins[1];//小车位姿Y坐标mm
    Pos[2]=ins[2];//-360*(int)(ins[2]/360);//小车逆时针旋转角度°

    
}

/*******************************************顺时针(右转)**********************************************/
void Rotate_CW()       
{
   
    rotate1=80;
    
    PWM1=stop1-20*rotate1;  //左轮向前多 
    PWM2=stop2+2*rotate1;  //右轮向前少
    
    Servo_PWM();
    
}

/*******************************************逆时针（左转）**********************************************/
void Rotate_CCW()        
{
   
    rotate2=40;
    
    PWM1=stop1+10*rotate2;  //左轮向后  
    PWM2=stop2+10*rotate2;  //右轮向前    
    Servo_PWM();
 
    
}

/*******************************************前进**********************************************/
void Move_Forward()    //PID控制 
{
    
    if(state==1) //跟着右前方走
    {
        PWM1=stop1-forward1-(disR-28)*10; //右前方距离P控制
        PWM2=stop2+forward2-(disR-28)*10; 
        Servo_PWM();
    }
   if(state==0)  //跟着正右方走
    {
        PWM1=stop1-forward1-(disM-11)*10;//正右方距离P控制
        PWM2=stop2+forward2-(disM-11)*10; 
        Servo_PWM();
    
    }
    
   
   
}

/*******************************************后退**********************************************/
void Move_Backward()       
{
    PWM1=stop1+backward1;//左轮反转
    PWM2=stop2-backward2; //右轮反转 
    Servo_PWM();
   
}
/*******************************************状态判断**********************************************/
void State_Verify()
{
    
    if(ButtonL_Read()==1&&ButtonR_Read()==1)  //若前方碰墙，逆时针转动90°
        {
            state=3;           
            
        }
        
     else if(ButtonL_Read()==1&&ButtonR_Read()==0)  //若左碰撞传感器碰墙
        {
            state=4;
      
        }
     else if(ButtonL_Read()==0&&ButtonR_Read()==1)//若右碰撞传感器碰墙
        {
            state=5;
              
        }
     else   //碰撞传感器未碰到
        {
            if(disM>=40) //右边有空隙
            {
                if(state==2) state=1;//不再进入state 2
                else
                state=2;
               
            }
           else
            {
                if(disR>=43) //斜前侧有空隙
                { if(state==1) state=0; 
                    else state=1; //不再进入state 0
                }
                else  state=1;                
            }                      
             
        }
        fflag=1;//进入speed control    
        delayFlag=1;//出延时
        Pos_Previous[2]=Pos[2];//记录转角 
        
}
       
/*******************************************速度控制**********************************************/
void Speed_Verify()  //根据给定线速度角速度，计算两轮期望转速
{   
   if(state==0)
{
     Move_Forward();//直走
    fflag=0; //进入state verify
  
}
    if(state==1)
    {
        Move_Forward(); //直走
        fflag=0;   //进入state verify       
    }    
    if(state==2) //先直走一段，再顺时针转90°
    {
         if(Pos_Previous[2]-Pos[2]>90) fflag=0;//进入state verify  
         else//右转 
               Rotate_CW();                
    }   
    if(state==3)    //前面撞到
    {   
        if(delayFlag==1) //先退后一段
            {
                Move_Backward();
                CyDelay(500);
                delayFlag=0;
                Pos_Previous[2]=Pos[2];
            }
        else
            {
                if(Pos[2]-Pos_Previous[2]>70) fflag=0;//进入state verify 
                
                else//左转
            
                     Rotate_CCW();            
            }       
    }
    if(state==4) //左边撞到，转大一点
    {
        if(delayFlag==1) //先退后一段
            {
                Move_Backward();
                CyDelay(500);
                delayFlag=0;
                Pos_Previous[2]=Pos[2];
            }
        else
            {
                 if(Pos[2]-Pos_Previous[2]>80)fflag=0;//进入state verify    
                else//左转
            
                Rotate_CCW();                             
            }                     
        }
          
    if(state==5)    //右边撞到，转小一点
    {
        if(delayFlag==1) //先退后一段
            {
                Move_Backward();
                CyDelay(500);
                delayFlag=0;
                Pos_Previous[2]=Pos[2];
            }
        else
            {
                 if(Pos[2]-Pos_Previous[2]>60) fflag=0;//进入state verify     
                else//左转            
                Rotate_CCW();             
            }       
    }
}
