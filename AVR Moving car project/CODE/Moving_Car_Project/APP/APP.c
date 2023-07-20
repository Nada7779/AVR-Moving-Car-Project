#include "APP.h"

/***********************************************************************************************************************
                                    GLOBAL VARIABLES 
*****************************************************************************************************************************/
// used in pwm
float g_time1;
float g_speed;
float g_time2;

// used in rotate_90degree_calculation
float rotation_per_circle;
float time_rotation_state ;
/***********************************************************************************************************************
                                   FUNCTION IMPLMENTATION
****************************************************************************************************************************/

/**DESCRIPTION:-
  this function is used to make pwm in pin pinb0
  **/
void pwm(float a_speed){
	 g_speed= a_speed/100;
	g_time1=  (g_speed * 256);
	 g_time2=256-g_time1;
	TIMER_0_pwm(g_time1);
	LED_ON(pinb0);
	
	TIMER_0_pwm(g_time2);
	LED_OFF(pinb0);
	
}

/********************************************************************************************/
/**DESCRIPTION:-
  this function is used for short side --> move with 30 % max speed for 2 seconds
  **/
void shortSide_start()
{
	//mode_ovf= 7813 ;
	LED_OFF(pinc0);
	mode_ovf= 19532; // 5 seconds for simulation test
	Car_Moving_FWD();
	LED_ON(pinc2);
	pwm(30);

}

/********************************************************************************************/
/**DESCRIPTION:-
  this function is used for short side --> move with 50 % max speed for 3 seconds
  **/

void longSide_start()
{
	//mode_ovf= 11719; 
	// timee of stage / .000256
	LED_OFF(pinc0);
	mode_ovf= 19532;  // 5 seconds for simulation test
	Car_Moving_FWD();
	LED_ON(pinc1);
	pwm(50);
}

void ready_State(void){
	
		mode_ovf= 19532;  // 5 seconds for simulation test
		Car_Stop();
}


/*****************************************************************************************************
**DESCRIPTION:-
this function calculates the time nedded of rotation to turn the car 90 degree*/

void rotate_90degree_calculation (void)
{
	//1-Rotation of wheels needed to make a circular path calculations:
	//(1.1)-the circumference of the circle of that the wheels make.
	//circle_circumference= PI*distance_between_wheels;
	//(1.2) the circumference of the wheel.
	//wheel_circumference= PI*wheel_diameter;
	//(1.3) total rotations needed for one circular path.
	//rotation_per_circle = circle_circumference/wheel_circumference;
	rotation_per_circle = ((PI*distance_between_wheels)/(PI*wheel_diameter));
	//2- Calculate the rotation of each wheel to rotate 90 degrees:
	//(2.1)  rotation per wheel= rotation_per_circle/0.25
	//(2.2) time needed for car to turn 90 degree= (rotation per wheel/maximum speed percentage)*60) in sec
	time_rotation_state= ((rotation_per_circle*0.25)/(max_speed*0.1))*60;
	
	
}




/****************************************************************************************************************************************
**DESCRIPTION:-
this function makes the car stop for 0.5 sec, LED 3 indicator for stopping phase*/
void car_stop_state (void) {
	
	LED_OFF(pinc1);
	LED_OFF(pinc2);
	LED_OFF(pinc3);
	LED_ON(pinc0);
	mode_ovf= 19532;  // 5 seconds for simulation test
	Car_Stop();

	
}
/*******************************************************************************************************************************************
**DESCRIPTION:-
this function makes the car stop for another 0.5 sec then rotate 90 degree to the right then stop for another 0.5 sec
LED four is the indicator of rotating phase*/

void rotate_90degree_state (void)
{
	LED_OFF(pinc0);
	rotate_90degree_calculation();
	mode_ovf= time_rotation_state/ 0.000256 ;  // 3.75 seconds for simulation test
	//mode_ovf= 15625 ;
	// Rotation state
	Car_Rotating();
	
	LED_ON(pinc3);
	pwm(10);

}
/*************************************************************************************************************************************************/




void app_Init(void){
	
	sei();
	
	LED_INIT(pinb0);	// pwm 
	LED_INIT(pind4);	// timer start
	LED_INIT(pind5);	// timer stop
	
	Button_INIT(pind2);
	EXI_Enable(EXT_INT_0);
	EXI_SetCallBack(EXT_INT_0,Car_Stop);
	EXI_Trigger(EXT_INT_0,LOW_LEVEL);
	
	Button_INIT(pind3); 
	EXI_Enable(EXT_INT_1);
	EXI_Trigger(EXT_INT_1,LOW_LEVEL);
		
	LED_INIT(pinc0);
	LED_INIT(pinc1);
	LED_INIT(pinc2);
	LED_INIT(pinc3);
	
	Car_Motors_init();
	
	TIMER_2_INT();
	
}

void app_Start(void){


	if(car_flag==1){
		
		LED_ON(pind4);  //  start timer
		LED_OFF(pind5);
			
			if (car_mode == 0)
			{
				ready_State();
			}
	
	
			else if(car_mode == 1){

				longSide_start();
		
			}
	
			// rotation
			else if (car_mode == 2)
			{
				//mode_ovf= 1954 ;
				car_stop_state();
			}
	
			else if (car_mode == 3)
			{
				
				rotate_90degree_state();
				
		
			}
	
			// rotation
			else if(car_mode == 4){
		
				//mode_ovf= 1954 ;
				car_stop_state();

			}
			else if(car_mode == 5){
				
				//mode_ovf= 1954 ;
				shortSide_start();

			}
			else if(car_mode == 6){
				
				//mode_ovf= 1954 ;
				car_stop_state();

			}
			else if (car_mode == 7)
			{
				
				rotate_90degree_state();				
				
			}
			
			else if (car_mode == 8)
			{
				
				car_stop_state();
				
				
			}
			
		}else{
			//rest timer
			LED_OFF(pind4); 
			LED_ON(pind5);

		}

	


}

