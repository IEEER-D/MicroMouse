#include <avr/io.h>
#include "Encoder.h"
#include "Motor.h"


void Motor_init(){
	DDRB |= (1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB4); // the pins attached to the driver to control the motors // we made it as an output.
}
void PWM_init(){
	//PWM0
	TCCR0 |=(1<<WGM01) | (1<<WGM00); // enable fast PWM
	TCCR0 |=(1<<COM01); // Clear OC0 on compare match, set OC0 at BOTTOM.
	TCCR0 |=(1<<CS01) ;  // set PRE-scaling with /2
	
	DDRB |= (1<<PB3); //make this pin as an output so the PWM0 can be generated.
	PORTB |= (1<<PB3);
		
	
	//PWM1
	TCCR1A |=(1<<COM1A1); // Clear OC1A on compare match (Set output to low level)
	TCCR1A |=(1<<WGM12) | (1<<WGM10); //Fast PWM, 8-bit
	TCCR1B |=(1<<CS10);  // set PRE-scaling with /2
	
	DDRD |= (1<<PD5); //make this pin as an output so the PWM1 can be generated.
	PORTD |= (1<<PD5);
}
void set_Left_Speed(uint8_t speed){
	/*
	speed in range 0 -> 255
	*/
	OCR1A = speed;
}
void set_Right_Speed(uint8_t speed){
	/*
	speed in range 0 -> 255
	*/
	OCR0 = speed;
}

void Stop_Motors(){
	PORTB &= ~ ((1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB4)); //clear the pins so the motors stop.
}
void Move_Forword(uint8_t speed_L,uint8_t speed_R ){
	//1001      0 1 2 4
	PORTB = ((1<<PB0)|(1<<PB4));
	PORTB &= ~ ((1<<PB1)|(1<<PB2));
	
	set_Left_Speed(speed_L);
	set_Right_Speed(speed_R);
}
void Move_Right(uint8_t speed){
	set_Left_Speed(speed);
	set_Right_Speed(speed);
	uint16_t Desired_countL = Left_Counter+20;  //current = Left_counter and desired = current + 20 #means Quarter cycle
	uint16_t Desired_countR = Right_Counter+20; //current = Right_counter and desired = current + 20 #means Quarter cycle
	
	while((Left_Counter == Desired_countL )&& (Right_Counter == Desired_countR)){
		//0101      0 1 2 4
	PORTB = ((1<<PB1)|(1<<PB4));
	PORTB &= ~ ((1<<PB0)|(1<<PB2));	
	}
	Stop_Motors();
}
void Move_Left(uint8_t speed){
	set_Left_Speed(speed);
	set_Right_Speed(speed);
	uint16_t Desired_countL = Left_Counter+20;  //current = Left_counter and desired = current + 20 #means Quarter cycle
	uint16_t Desired_countR = Right_Counter+20; //current = Right_counter and desired = current + 20 #means Quarter cycle
	
	while((Left_Counter == Desired_countL )&& (Right_Counter == Desired_countR)){
		//1010      0 1 2 4
	PORTB = ((1<<PB0)|(1<<PB2));
	PORTB &= ~ ((1<<PB1)|(1<<PB4));
	}
Stop_Motors();
	
}
void U_Turn(uint8_t speed){
	//1010 //1010 
	set_Left_Speed(speed);
	set_Right_Speed(speed);
	uint16_t Desired_countL = Left_Counter+40;  //current = Left_counter and desired = current + 40 #means Half cycle
	uint16_t Desired_countR = Right_Counter+40; //current = Right_counter and desired = current + 40 #means Half cycle
	
	while((Left_Counter == Desired_countL )&& (Right_Counter == Desired_countR)){
		//1010      0 1 2 4
		PORTB = ((1<<PB0)|(1<<PB2));
		PORTB &= ~ ((1<<PB1)|(1<<PB4));
	}
	Stop_Motors();	
}
