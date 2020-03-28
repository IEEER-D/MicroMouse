#include <avr/io.h>
#include <util/delay.h>

#define SegOne   0x01
#define SegTwo   0x02
#define SegThree 0x04
#define SegFour  0x08

uint16_t Right(void);
uint16_t Front_Right(void);

uint16_t Left(void);
uint16_t ADC_read(uint8_t n);

uint16_t Front_Left(void);


int main() {
	char seg_code[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
	int   temp,i;
	uint16_t num;
	
	/* Configure the ports as output */
	DDRB = 0xff; // Data lines
	DDRD = 0xff; // Control signal PORTD0-PORTD3
	
	
	ADMUX = (1<<REFS0); // AVCC with external capacitor at AREF pin
	ADCSRA |= (1 << ADEN); // Enable ADC
	ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); // pr-scaler = 128

	while (1)
	{
			for (i = 0; i < 100; i++)
			{
				num = Right();
				temp = num / 1000;
				num = num % 1000;
				PORTD = SegOne;
				PORTB = seg_code[temp];
				_delay_ms(1);

				temp = num / 100;
				num = num % 100;
				PORTD = SegTwo;
				PORTB = seg_code[temp];
				_delay_ms(1);

				temp = num / 10;
				PORTD = SegThree;
				PORTB = seg_code[temp];
				_delay_ms(1);

				temp = num % 10;
				PORTD = SegFour;
				PORTB = seg_code[temp];
				_delay_ms(1);
			}
			for (i = 0; i < 100; i++)
			{
				num = Left();
				temp = num / 1000;
				num = num % 1000;
				PORTD = SegOne;
				PORTB = seg_code[temp];
				_delay_ms(1);

				temp = num / 100;
				num = num % 100;
				PORTD = SegTwo;
				PORTB = seg_code[temp];
				_delay_ms(1);

				temp = num / 10;
				PORTD = SegThree;
				PORTB = seg_code[temp];
				_delay_ms(1);

				temp = num % 10;
				PORTD = SegFour;
				PORTB = seg_code[temp];
				_delay_ms(1);
			}
			for (i = 0; i < 100; i++)
			{
				num = Front_Left();
				temp = num / 1000;
				num = num % 1000;
				PORTD = SegOne;
				PORTB = seg_code[temp];
				_delay_ms(1);

				temp = num / 100;
				num = num % 100;
				PORTD = SegTwo;
				PORTB = seg_code[temp];
				_delay_ms(1);

				temp = num / 10;
				PORTD = SegThree;
				PORTB = seg_code[temp];
				_delay_ms(1);

				temp = num % 10;
				PORTD = SegFour;
				PORTB = seg_code[temp];
				_delay_ms(1);
			}
			for (i = 0; i < 100; i++)
			{
				num = Front_Right();
				temp = num / 1000;
				num = num % 1000;
				PORTD = SegOne;
				PORTB = seg_code[temp];
				_delay_ms(1);

				temp = num / 100;
				num = num % 100;
				PORTD = SegTwo;
				PORTB = seg_code[temp];
				_delay_ms(1);

				temp = num / 10;
				PORTD = SegThree;
				PORTB = seg_code[temp];
				_delay_ms(1);

				temp = num % 10;
				PORTD = SegFour;
				PORTB = seg_code[temp];
				_delay_ms(1);
			}
	}
	}

uint16_t ADC_read(uint8_t n)
{
	/*
	n is the number of the channel hence corresponding sensor
	n from 0 to 7 to make sure we have to AND it with 0b00000111
	*/
	n &= 0b00000111;  // AND operation with 7
	
	ADMUX = (ADMUX & 0xF8)|n;     // clears the bottom 3 bits before ORing
	
	ADCSRA |= (1<<ADSC);// start single conversion 
	
	while(ADCSRA & (1<<ADSC));// wait for conversion to complete ADSC becomes '0' again till then, run loop continuously
	
	return (ADC); //the result of conversion
}


uint16_t Front_Left(void) {
	uint16_t read1; //read1 With transmitters off and read2 With transmitters on
	//REC 3 is connected to	AD3
	read1=ADC_read(3); //noise signal
	return (read1);
}
uint16_t Front_Right(void) {
	uint16_t read1; //read1 With transmitters off and read2 With transmitters on
	//REC 1 is connected to	AD7
		read1=ADC_read(7); //noise signal
		return (read1);
	}

uint16_t Left(void) {
	uint16_t read1; //read1 With transmitters off and read2 With transmitters on
	//REC 4 is connected to	AD4
		read1=ADC_read(4); //noise signal
		return (read1);
	}

uint16_t Right(void) {
	uint16_t read1; //read1 With transmitters off and read2 With transmitters on
	//REC 2 is connected to	AD6
		read1=ADC_read(6); //noise signal
		return (read1);
	}
