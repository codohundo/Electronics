#include p18f13k22.inc

__config	_CONFIG1H , _FOSC_ECH_1H 
__config	_CONFIG4L , _LVP_ON_4L 



	main
	CLRF TRISA
    CLRF TRISB
	movlw 0xff 
    movlw TRISC
    movlw 0x02
	movwf PORTA
    movwf PORTB
    ;;movwf PORTC

	goto main

	end
