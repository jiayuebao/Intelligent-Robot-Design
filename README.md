# Intelligent-Robot-Design
Implemented an intelligent robot which can achieve the following two functions:
- Line Tracking
	- Walking along the black guideline in the field    
	- Average time: 30 seconds/round 
- Maze Solving
	- Getting out a maze automatically (both entrance directions)
	- Average time: 90 seconds/round
## Programming Platform
- PSoC Creator 4.0
## Sensors on Robot
- Line-tracking sensor
- Collision sensor 
- Infrared ranging sensor
- Encoder
## Implementation
### Line-tracking

#### Functions
- ADC_Convert() 
- PWM_Control()
- Initialize_Components()
- LCD_Display()
- Servo_PWM()



### Maze-Solving

#### Functions
- State_Verify()
- Speed_Verify()
- Position()
- get_IR_dis()
- Rotate_CW()
- Rotate_CCW()
- Move_Forward()
- Move_Backward()

