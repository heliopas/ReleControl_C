#include <atmel_start.h>
#include <port.h>
#include <util/delay.h>
#include <avr/interrupt.h>


#define setBit(reg, bit)    (reg = reg | (1 << bit))
#define clearBit(reg, bit)  (reg = reg & ~(1 << bit))
#define toggleBit(reg, bit) (reg = reg ^ (1 << bit))
#define clearFlag(reg, bit) (reg = reg | (1 << bit))

#define F_CPU				16000000
#define BOUD				9600
#define BRC					((F_CPU/16/BOUD) - 1)
#define BUFFER_SIZE		    128	

char serialBUFFER[BUFFER_SIZE];
char serialBUFFERrx[BUFFER_SIZE];
char releAct = 0;

uint8_t serialReadPos = 0;
uint8_t serialWritePos = 0;
uint8_t serialReadPosRX = 0;

char receiveDataSerial();
char getDataSerial();
int  releAtivated(char aux);

int main(void)
{
	configSerialCOMM(); // iniciliza porta COM
	sei(); // habilita interrupções

	//serialWriter("\nDigite 1\n\r");

	DDRD |= 0xFC; // seta de PD2 a PD7 como OUTPUT
	DDRB |= 0x1F; // seta de PB0 a PB4 como OUTPUT
	//DDRC |= 0x7F;

	char aux = 0;
	//int count = 0;
	int setReleControl = 0; 

	while(1)
	{		
		aux = getDataSerial();
		
		setReleControl = releAtivated(aux);
		if(setReleControl == 1)
		{
		    if(aux == '1')
			{
				setReleEnable(1);
				clearBUFFERrx();
			}
			else if(aux == '2')
			{
				setReleEnable(2);
				clearBUFFERrx();
			}
			else if(aux == '3')
			{
				setReleEnable(3);
				clearBUFFERrx();
			}
			else if(aux == '4')
			{
				setReleEnable(4);
				clearBUFFERrx();
			}
			else if(aux == '5')
			{
				setReleEnable(5);
				clearBUFFERrx();
			}
			else if(aux == '6')
			{
				setReleEnable(6);
				clearBUFFERrx();
			}
			else if(aux == '7')
			{
				setReleEnable(7);
				clearBUFFERrx();
			}
			else if(aux == '8')
			{
				setReleEnable(8);
				clearBUFFERrx();
			}
			else if(aux == '9')
			{
				setReleEnable(9);
				clearBUFFERrx();
			}
			else if(aux == 'A')
			{
				setReleEnable(10);
				clearBUFFERrx();
			}
			else if(aux == 'B')
			{
				setReleEnable(11);
				clearBUFFERrx();
			}
			else if(aux == 'C')
			{
				setReleEnable(12);
				clearBUFFERrx();
			}
			else if(aux == 'D')
			{
				setReleEnable(13);
				clearBUFFERrx();
			}
			else if(aux == 'E')
			{
				setReleEnable(14);
				clearBUFFERrx();
			}
			else if(aux == 'F')
			{
				setReleEnable(15);
				clearBUFFERrx();
			}
			else if(aux == 'G')
			{
				setReleEnable(16);
				clearBUFFERrx();
			}
			else if(aux == 'H')
			{
				setReleEnable(17);
				clearBUFFERrx();
			}
		}
		

		/*if (aux > 1 && aux <= 18)
		{
			
			for(count; count<=8 ; count++)
			{
				setReleEnable(count);
				serialWriter("\nLigando LED!!!!\n");
				_delay_ms(2000);
				setReleDisable(count);
				serialWriter("\nDesligando LED!!!!\n");
				_delay_ms(2000);
			}
			
			count = 0;

		}*/
		
	}
} 

int releAtivated(char aux)
{
	if (releAct == '0')
	{
		releAct = aux;
		return 1;
	}else
	if (releAct == aux)
	{
		releAct = '0';
		return 1;
	}else
	if (releAct != aux)
	{
		return 0;
	}
}


void clearBUFFERrx()
{
	memset(serialBUFFERrx , 0, BUFFER_SIZE);
}

void configSerialCOMM()
{
	// SET BOUDRATE 9600
	UBRR0H = (BRC >> 8);
	UBRR0L = BRC;
	/*Enable receiver and transmitter  and interruptions*/
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0)|(1<<TXCIE0);
	/* Set frame format: 8data, 1stop bit */
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
}

int setReleEnable(int pinNumber)
{
	
	/*if(pinNumber<=6)
	{
		DDRD |= 0xFC; // seta de PD2 a PD7 como OUTPUT
	}else if ( pinNumber>6 || pinNumber <= 11)
	{	
		DDRB |= 0x1F; // seta de PB0 a PB4 como OUTPUT
	}else
	{
		DDRC |= 0x7F;
	}*/

	switch(pinNumber)
	{
		case 1:
			if(PORTD_get_pin_level(PD2) == true)
			{
				PORTD_set_pin_level(PD2, false);
				serialWriter("\n\rRELE ON\n\r");
			}
			else
			{
				PORTD_set_pin_level(PD2, true);
				serialWriter("\n\rRELE OFF\n\r");
			}
		break;
		case 2:
			if(PORTD_get_pin_level(PD3) == true)
			{
				PORTD_set_pin_level(PD3, false);
				serialWriter("\n\rRELE ON\n\r");
			}
			else
			{
				PORTD_set_pin_level(PD3, true);
				serialWriter("\n\rRELE OFF\n\r");
			}
		break;
		case 3:
			if(PORTD_get_pin_level(PD4) == true)
			{
				PORTD_set_pin_level(PD4, false);
				serialWriter("\n\rRELE ON\n\r");
			}
			else
			{
				PORTD_set_pin_level(PD4, true);
				serialWriter("\n\rRELE OFF\n\r");
			}
		break;
		case 4:
			if(PORTD_get_pin_level(PD5) == true)
			{
				PORTD_set_pin_level(PD5, false);
				serialWriter("\n\rRELE ON\n\r");
			}
			else
			{
				PORTD_set_pin_level(PD5, true);
				serialWriter("\n\rRELE OFF\n\r");
			}
		break;
		case 5:
			if(PORTD_get_pin_level(PD6) == true)
			{
				PORTD_set_pin_level(PD6, false);
				serialWriter("\n\rRELE ON\n\r");
			}
			else
			{
				PORTD_set_pin_level(PD6, true);
				serialWriter("\n\rRELE OFF\n\r");
			}
		break;
		case 6:
			if(PORTD_get_pin_level(PD7) == true)
			{
				PORTD_set_pin_level(PD7, false);
				serialWriter("\n\rRELE ON\n\r");
			}
			else
			{
				PORTD_set_pin_level(PD7, true);
				serialWriter("\n\rRELE OFF\n\r");
			}
		break;
		case 7:
			if(PORTB_get_pin_level(PB0) == true)
			{
				PORTB_set_pin_level(PB0, false);
				serialWriter("\n\rRELE ON\n\r");
			}
			else
			{
				PORTB_set_pin_level(PB0, true);
				serialWriter("\n\rRELE OFF\n\r");
			}
		break;
		case 8:
			if(PORTB_get_pin_level(PB1) == true)
			{
				PORTB_set_pin_level(PB1, false);
				serialWriter("\n\rRELE ON\n\r");
			}
			else
			{
				PORTB_set_pin_level(PB1, true);
				serialWriter("\n\rRELE OFF\n\r");
			}
		break;
		case 9:
			if(PORTB_get_pin_level(PB2) == true)
			{
				PORTB_set_pin_level(PB2, false);
				serialWriter("\n\rRELE OFF\n\r");
			}
			else
			{
				PORTB_set_pin_level(PB2, true);
				serialWriter("\n\rRELE ON\n\r");
			}
		break;
		case 10:
			if(PORTB_get_pin_level(PB3) == true)
			{
				PORTB_set_pin_level(PB3, false);
				serialWriter("\n\rRELE OFF\n\r");
			}
			else
			{
				PORTB_set_pin_level(PB3, true);
				serialWriter("\n\rRELE ON\n\r");
			}
		break;
		case 11:	
			if(PORTB_get_pin_level(PB4) == true)
			{
				PORTB_set_pin_level(PB4, false);
				serialWriter("\n\rRELE OFF\n\r");
			}
			else
			{
				PORTB_set_pin_level(PB4, true);
				serialWriter("\n\rRELE ON\n\r");
			}
		break;
		case 12:
			if(PORTC_get_pin_level(PC0) == true)
			{
				PORTC_set_pin_level(PC0, false);
				serialWriter("\n\rRELE OFF\n\r");
			}
			else
			{
				PORTC_set_pin_level(PC0, true);
				serialWriter("\n\rRELE ON\n\r");
			}
		break;
		case 13:
			if(PORTC_get_pin_level(PC1) == true)
			{
				PORTC_set_pin_level(PC1, false);
				serialWriter("\n\rRELE OFF\n\r");
			}
			else
			{
				PORTC_set_pin_level(PC1, true);
				serialWriter("\n\rRELE ON\n\r");
			}
		break;
		case 14:
			if(PORTC_get_pin_level(PC2) == true)
			{
				PORTC_set_pin_level(PC2, false);
				serialWriter("\n\rRELE OFF\n\r");
			}
			else
			{
				PORTC_set_pin_level(PC2, true);
				serialWriter("\n\rRELE ON\n\r");
			}
		break;
		case 15:
			if(PORTC_get_pin_level(PC3) == true)
			{
				PORTC_set_pin_level(PC3, false);
				serialWriter("\n\rRELE OFF\n\r");
			}
			else
			{
				PORTC_set_pin_level(PC3, true);
				serialWriter("\n\rRELE ON\n\r");
			}
		break;
		case 16:
			if(PORTC_get_pin_level(PC4) == true)
			{
				PORTC_set_pin_level(PC4, false);
				serialWriter("\n\rRELE OFF\n\r");
			}
			else
			{
				PORTC_set_pin_level(PC4, true);
				serialWriter("\n\rRELE ON\n\r");
			}
		break;
		case 17:
			if(PORTC_get_pin_level(PC5) == true)
			{
				PORTC_set_pin_level(PC5, false);
				serialWriter("\n\rRELE OFF\n\r");
			}
			else
			{
				PORTC_set_pin_level(PC5, true);
				serialWriter("\n\rRELE ON\n\r");
			}
		break;
		case 18:
			if(PORTC_get_pin_level(PC6) == true)
			{
				PORTC_set_pin_level(PC6, false);
				serialWriter("\n\rRELE OFF\n\r");
			}
			else
			{
				PORTC_set_pin_level(PC6, true);
				serialWriter("\n\rRELE ON\n\r");
			}
		break;
		default:
			return 1;
		break;
	}

}

void delaySeconds(int sec)
{
	int aux = 0;
	while(aux <= sec)
	{
		while(!(TIFR0 & (1 << TOV0))) { }
		clearFlag(TIFR0, TOV0);
		aux += 1;
	}	
}

char receiveDataSerial()
{
	char ret = '\0';

	if(serialReadPosRX != serialReadPos)
	{
		ret = serialBUFFERrx[serialReadPosRX];
		serialReadPosRX++;

		if(serialReadPosRX >= BUFFER_SIZE){ serialReadPosRX = 0; }
	}
		
	return ret;
}

char getDataSerial()
{
	char ret = '\0';

	if(serialReadPosRX != serialReadPos)	{ ret = serialBUFFERrx[serialReadPosRX]; }
	
	serialReadPosRX++;

	if(serialReadPosRX >= BUFFER_SIZE){ serialReadPosRX = 0; }

	return ret;
}


void appendSerial(char c) // insere na fila os caracteres para serem enviados pela serial
{
	serialBUFFER[serialWritePos] = c;
	serialWritePos ++;

	if(serialWritePos >= BUFFER_SIZE){ serialWritePos = 0; }

}
void serialWriter(char c[]) // envia caracteres pela serial
{
	for(uint8_t i=0; i<strlen(c); i++)
	{
		appendSerial(c[i]);
	}
	
	if(UCSR0A & (1 << UDRE0)){ UDR0 = 0; } // Verifica se serial está livre para transmitir
}

ISR(USART_TX_vect)
{
	if(serialReadPos != serialWritePos) // ainda com informações para enviar
	{
		UDR0 = serialBUFFER[serialReadPos];
		serialReadPos++;

		if (serialReadPos >= BUFFER_SIZE){ serialReadPos = 0; }
	}
}

ISR(USART_RX_vect)
{
	serialBUFFERrx[serialReadPosRX] = UDR0;
	serialReadPosRX++;

	if(serialReadPosRX >= BUFFER_SIZE){ serialReadPosRX = 0; }

}



/*

	DDRD = 0x04; //Seta porta D2 como output
	initTimerMode_normal();
	PORTD_set_pin_dir(PD2, PORT_DIR_OUT);
	
	setBit(CLKPR, CLKPCE);
	setBit(CLKPR, CLKPS3);

	while(1)
	{
		
		PORTD_set_pin_level(PD2, true);
		delaySeconds(1);
		
		PORTD_set_pin_level(PD2, false);
		delaySeconds(1);

	}

*/