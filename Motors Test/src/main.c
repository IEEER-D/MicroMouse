#include <avr/io.h>
#include <util/delay.h>
#include "Encoder.h"

#define F_CPU 8000000UL

void Motor_init(void);
void PWM_init(void);
void set_Left_Speed(uint8_t speed);
void set_Right_Speed(uint8_t speed);
void Stop_Motor(void);
void Move_Forword(uint8_t speed_L,uint8_t speed_R );
void Move_Right(uint8_t speed);
void Move_Left(uint8_t speed);
void U_Turn(uint8_t speed);
int Distance_to_slots(float distance);
void Move_Forword_For(uint16_t speed,float distance);


extern volatile uint16_t  Right_Counter;
extern volatile uint16_t Left_Counter;
int main(void){
	PWM_init();
	Motor_init();
	
	
	while(1){
		
		Move_Forword(200,200);
	}
	
	
}
void Motor_init(){
	DDRB |= (1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB4);
}
void PWM_init(){
	//PWM0
	TCCR0 |=(1<<WGM01) | (1<<WGM00); // enable fast PWM
	TCCR0 |=(1<<COM01) ;//| (1<<COM00) ; //Set OC0 on compare match, clear OC0 at BOTTOM
	TCCR0 |=(1<<CS00) ;//| (1<<CS02);  // set PRE-scaling with /1024
	
	DDRB |= (1<<PB3);
	PORTB |= (1<<PB3);
	
	//PWM1
	TCCR1A |=(1<<WGM10); //Fast PWM, 8-bit
	TCCR1A |=(1<<COM1A1); // Clear OC1A on compare match (Set output to low level)
	TCCR1B |=(1<<CS10);// | (1<<CS12);  // set PRE-scaling with /1024
	
	DDRD |= (1<<PD5);
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

void Stop_Motor(){
	PORTB &= ~ ((1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB4));
}
void Move_Forword_For(uint16_t speed,float distance){
	//1001      0 1 2 4
	int slots= Distance_to_slots(distance);
	set_Left_Speed(speed);
	set_Right_Speed(speed);
	uint16_t Desired_countL = Left_Counter+(slots);  //current = Left_counter and desired = current + slots
	uint16_t Desired_countR = Right_Counter+(slots); //current = Right_counter and desired = current + slots
	
	while((Left_Counter == Desired_countL )&& (Right_Counter == Desired_countR)){
		Move_Forword(speed,speed);
	}
	Stop_Motor();
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
	Stop_Motor();
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
Stop_Motor();
	
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
	Stop_Motor();	
}

int Distance_to_slots(float distance){
	
return ((int)((distance*7*40)/(2*3*22)));
}
