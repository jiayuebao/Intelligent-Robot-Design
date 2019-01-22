#include <project.h>
#include <stdio.h>
#include <string.h>

extern const uint8 CYCODE LCD_Char_customFonts[];//载入传统字体
//设定PID系数
#define KP   0.18   
#define KD 0.005
#define KI  0.0002

/**********PID调速变量*****************/
int16 speed1 = 0,speed2=0;//转速，r/min
uint16 FIFO1[100],FIFO2[100];//FIFO数组，存放100个转速值

int8 flag=1;     //初始化正交解码器的标志位
int16 All_speed1=0,All_speed2=0;//角度和
int16 num1=0,num2=0; //角度
int8 i=0;//指向FIFO中的数据位置

/*************LCD显示****************/
//转速显示
char outputStr1[12],outputStr2[12];
//位姿显示
char outputStrx[12],outputStry[12],outputStrz[12];

//ADC显示
char string_L[50]; 
char string_M[50];
char string_R[50];


/**********PWM变量*****************/
int16 PWM_1=4500;
int16 PWM_2=4500;

int turn=0;//转向偏差
int turn_1=0;
int turn_sum=0;
int turn_diff=0;

int state=0;

/***********ADC变量****************/

int ADC_Result[3]={0,0,0};
int ADC_Result_L = 0; //左
int ADC_Result_M = 0; //中
int ADC_Result_R = 0; //右


/**********位姿变量*****************/
int16 Pos[3]={1,2,3};//机器人的位姿x,t,sita


/*************相关函数****************/

void Initialize_Components();

void IntToString(char *str, int number);//int转string
double constrain(double lowerBoundary, double upperBoundary,double input);

void LCD_Display();
void ADC_Convert();

void PWM_Control();
void Servo_PWM();


/*************************************中断****************************************/
CY_ISR(InterruptHandler)//计时器中断
{
    Timer_ReadStatusRegister();//中断标志位重置
    if (flag==1)//不要再初始化的时候初始这个组件，会发生中断
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
    All_speed2=All_speed2+FIFO2[i];//累加
    
    ++i;
    if (i==100)
    {
        i=0;
    //左轮获得转速
    num1=All_speed1/(1); 
    speed1 = num1;
    All_speed1=0;
       
    //右轮获得转速
    num2=All_speed2/(1);
    speed2 = num2;
    All_speed2=0;
   
    
   
    }
}

/*************************************主函数****************************************/
int main()
{    
    Initialize_Components(); //初始化
    for(;;)
    {
      ADC_Convert();//巡线传感器读数AD转换
      
      PWM_Control();//速度控制
    
      Servo_PWM();//电机转动
      
    
      LCD_Display();//LCD输出
    
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
    ADC_SAR_Seq_Start(); //ADC使能
    
    PWM_1_Start();
    PWM_2_Start();
    PWM_1_WriteCompare(4500);
    PWM_2_WriteCompare(4500);
    Timer_Enable();
    Timer_Start();//最后启动时钟
    LCD_Char_ClearDisplay();	
	LCD_Char_Position(0,0);

}


/******************************************int转string****************************************/
void IntToString(char *str, int number)// 由数值变换为字符串的函数
{
    sprintf(str, "%d", number);
}
/******************************************constrain函数****************************************/
double constrain(double lowerBoundary, double upperBoundary,double input)//设置上下限
{
	if (input > upperBoundary)
		return upperBoundary;
	else if (input < lowerBoundary)
		return lowerBoundary;
	else
		return input;
}

/******************************************ADC转换********************************************/
void ADC_Convert()
{
    AMux_Select(0);//左
    CyDelay(1);
    ADC_SAR_Seq_StartConvert();
    ADC_SAR_Seq_IsEndConversion(ADC_SAR_Seq_WAIT_FOR_RESULT); //ADC的转换结束，存储结束前一直待机
    ADC_Result_L = ADC_SAR_Seq_GetResult16(0);  //结果存储
    IntToString(string_L, ADC_Result_L);
    
    AMux_Select(1);//中
    CyDelay(1);
    ADC_SAR_Seq_StartConvert();
    ADC_SAR_Seq_IsEndConversion(ADC_SAR_Seq_WAIT_FOR_RESULT); //ADC的转换结束，存储结束前一直待机
    ADC_Result_M = ADC_SAR_Seq_GetResult16(0);  //结果存储
    IntToString(string_M, ADC_Result_M);
    
    AMux_Select(2);//右
    CyDelay(1);
    ADC_SAR_Seq_StartConvert();
    ADC_SAR_Seq_IsEndConversion(ADC_SAR_Seq_WAIT_FOR_RESULT); //ADC的转换结束，存储结束前一直待机
    ADC_Result_R = ADC_SAR_Seq_GetResult16(0);  //结果存储
    IntToString(string_R, ADC_Result_R);
}


/******************************************参数显示********************************************/
void LCD_Display()
{
    
    LCD_Char_ClearDisplay();
    
    //巡线传感器数值输出
    LCD_Char_Position(0,0);
    LCD_Char_PrintString(string_L); 
    LCD_Char_Position(0,6);
    LCD_Char_PrintString(string_M);
    LCD_Char_Position(0,11);
    LCD_Char_PrintString(string_R);
    
    //转速输出
    LCD_Char_Position(1,0);
    sprintf(outputStr1,"%d",speed1);
    LCD_Char_PrintString(outputStr1);

    LCD_Char_Position(1,6);
    sprintf(outputStr2,"%d",speed2);
    LCD_Char_PrintString(outputStr2);
    
   CyDelay(50);
}


/******************************************PWM 控制 ********************************************/

void PWM_Control()
{    
   if(ADC_Result_M>2000)//中间为黑线，直走
    {
       
        PWM_1=4715-890;//左轮给定
       PWM_2=4800+600;//右轮给定
        
        state=1;
    }
    else if(ADC_Result_L>2000) //左边为黑线，左转,PWM1变小,PWM2不变
    {
        turn=ADC_Result_L-ADC_Result_M;//偏差量
        
       turn_sum=turn_sum+turn;//积分
       turn_diff=turn-turn_1;//差分
        
        
        PWM_1=4715-890+constrain(0,890,KP*turn+KD*turn_diff+KI*turn_sum);//左轮PID控制
        PWM_2=4800+600;//右轮给定
        
        turn_1=turn;//记录这一时刻偏差
        
        state=2;
    }
    else if(ADC_Result_R>2000)//右边为黑线，右转,PWM2变小，PWM1不变
    { 
        
        turn=ADC_Result_R-ADC_Result_M;//偏差量
        
        turn_sum=turn_sum+turn;//积分
        turn_diff=turn-turn_1;//差分
        PWM_1=4715-890;//左轮给定
        
        PWM_2=4800+600-constrain(0,600,KP*turn+KD*turn_diff+KI*turn_sum);//右轮PID控制
        
        turn_1=turn;//记录这一时刻偏差
        
        state=3;
    }

     
}

void Servo_PWM()
{
      PWM_1_WriteCompare(PWM_1); //PWM1调制结果传递
    
     PWM_2_WriteCompare(PWM_2); //PWM2调制结果传递
}