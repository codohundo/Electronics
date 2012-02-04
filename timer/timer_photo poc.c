#pragma config FOSC = ECH
#pragma config LVP = OFF
#pragma config MCLRE = ON
#pragma config STVREN = ON


#include <p18cxxx.h>
#include <delays.h>

const int A = 0;
const int B = 1;
const int C = 2;

#define PIN0 1
#define PIN1 2
#define PIN2 4
#define PIN3 8
#define PIN4 16
#define PIN5 32
#define PIN6 64
#define PIN7 128

const int A_A0 = PIN4;
const int A_LCDRESET = PIN2;
const int B_CS1B = PIN6;
const int B_SCL = PIN5;
const int B_SDA = PIN4;
const int A_PHOTO1 = PIN0;
const int A_PHOTO2 = PIN1;

void init( );
void setPin(int aPort, int aPin);
void clearPin(int aPort, int aPin);
void delay( );

void setPin(int aPort, int aPin){
	if( aPort == A ){
		if( aPin & PIN0 ) LATAbits.LATA0 = 1;
		if( aPin & PIN1 ) LATAbits.LATA1 = 1;
		if( aPin & PIN2 ) LATAbits.LATA2 = 1;
//		if( aPin & PIN3 ) LATAbits.LATA3 = 1;
		if( aPin & PIN4 ) LATAbits.LATA4 = 1;
		if( aPin & PIN5 ) LATAbits.LATA5 = 1;
	}
	if( aPort == B ){
		if( aPin & PIN4 ) LATBbits.LATB4 = 1;
		if( aPin & PIN5 ) LATBbits.LATB5 = 1;
		if( aPin & PIN6 ) LATBbits.LATB6 = 1;
		if( aPin & PIN7 ) LATBbits.LATB7 = 1;
	}
	if( aPort == C ){
		if( aPin & PIN0 ) LATCbits.LATC0 = 1;
		if( aPin & PIN1 ) LATCbits.LATC1 = 1;
		if( aPin & PIN2 ) LATCbits.LATC2 = 1;
		if( aPin & PIN3 ) LATCbits.LATC3 = 1;
		if( aPin & PIN4 ) LATCbits.LATC4 = 1;
		if( aPin & PIN5 ) LATCbits.LATC5 = 1;
		if( aPin & PIN6 ) LATCbits.LATC6 = 1;
		if( aPin & PIN7 ) LATCbits.LATC7 = 1;
	}	
}

void clearPin(int aPort, int aPin){
	if( aPort == A ){
		if( aPin & PIN0 ) PORTAbits.RA0 = 0;
		if( aPin & PIN1 ) PORTAbits.RA1 = 0;
		if( aPin & PIN2 ) PORTAbits.RA2 = 0;
		if( aPin & PIN3 ) PORTAbits.RA3 = 0;
		if( aPin & PIN4 ) PORTAbits.RA4 = 0;
		if( aPin & PIN5 ) PORTAbits.RA5 = 0;
	}
	if( aPort == B ){
		if( aPin & PIN4 ) PORTBbits.RB4 = 0;
		if( aPin & PIN5 ) PORTBbits.RB5 = 0;
		if( aPin & PIN6 ) PORTBbits.RB6 = 0;
		if( aPin & PIN7 ) PORTBbits.RB7 = 0;
	}
	if( aPort == C ){
		if( aPin & PIN0 ) PORTCbits.RC0 = 0;
		if( aPin & PIN1 ) PORTCbits.RC1 = 0;
		if( aPin & PIN2 ) PORTCbits.RC2 = 0;
		if( aPin & PIN3 ) PORTCbits.RC3 = 0;
		if( aPin & PIN4 ) PORTCbits.RC4 = 0;
		if( aPin & PIN5 ) PORTCbits.RC5 = 0;
		if( aPin & PIN6 ) PORTCbits.RC6 = 0;
		if( aPin & PIN7 ) PORTCbits.RC7 = 0;
	}	
}


void init( ){
	PORTA = 0;
	PORTB = 0;
	PORTC  = 0;
	ANSEL = 0;

	TRISA = 0x03; //pin a0 and a1 for photo interrupters with interrupts
	TRISB = 0;
	TRISC = 0xff; 
}

void delay(){
	char i = 0;
	for( i = 0; i < 10; i++ )
	{
 		Delay10KTCYx(41);   // Delay of 320 000 cycles
	}
}

void main(void)
{
	int state = 0;
	init ();
			
	while (1){
		if( PORTAbits.RA0 == 1 ){
			clearPin( A, A_A0 );
		}
		else{
			setPin( A, A_A0 );
		}
		if( PORTAbits.RA1 == 1 ){
			clearPin( A, A_LCDRESET );
		}
		else{
			setPin( A, A_LCDRESET ); 
		}

		if( state == 0 ){
			state = 1;
			setPin( B, B_CS1B );
		}
		else{
			state = 0;
			clearPin( B, B_CS1B );
		}
		delay();
	}
}