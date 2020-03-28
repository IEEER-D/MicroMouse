#include <avr/io.h>
#include <avr/interrupt.h>
#include "Encoder.h"


void INT_init(void){
	sei();
	MCUCR |=   (1<<ISC00);  // make INT 1 and  INT0 on toggle condition
	GICR |= (1<<INT1) | (1<<INT0);		//enable the interrupt 1 and 0
}
float Calculte_Distance(uint16_t Slots){
	// if 20 slots and 20 holes then one cycle
	//one cycle means 2*3pi
	float cycles = Slots/40;
	float Distance = cycles*2*3*22/7;
	return Distance;
}

ISR(INT0_vect){
	Right_Counter++;
}

ISR(INT1_vect){
	Left_Counter++;
}

