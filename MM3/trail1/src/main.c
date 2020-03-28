
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "Sensors.h"
#include "Encoder.h"
#include "Motor.h"


int main (void)
{
	
	Motor_init();
	PWM_init();
	ADC_init(); // initialize the ADC
	INT_init();

	while(1){}
}
	

