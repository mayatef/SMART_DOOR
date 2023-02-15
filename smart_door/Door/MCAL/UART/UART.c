#include "UART.h"
#define BAUD_PRESCALE ((F_CPU / (UART_BAUDRATE * 8UL))-1)
void USART_Init (void)					// function for initialization the UART
{
	UCSRA = (1<<U2X);     // Enable Double speed mode

	/*
	 * Disable for RX complete interrupt
	 * Disable for TX complete interrupt
	 * Disable for UDR empty register interrupt
	 * RXB8 & TXB not Used
	 */
	UCSRB = (1<<RXEN) | (1<<TXEN); // Enable receiver (RXEN = 1) and Enable Transmitter (TXEN = 1)


	/*
	 * URSEL = 1 to select UCSRC register
	 * URSEL = 0 for Asynchronous
	 * UPM0:1 = 00 (Disable Parity)
	 * USBS = 0 for 1 stop bit
	 * UCSZ1:0 = 1 (8-Bit data length)
	 * UCPOL = 0  (Used with Synchronous mode Only)
	 */

	UCSRC = (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1);

	// Set value of UBRR register with the baud rate (9600)
	UBRRH = BAUD_PRESCALE >> 8;
	UBRRL = BAUD_PRESCALE;

}

void USART_sendByte (u8 data)			// Function for sending data byte
{
	while (BIT_IS_CLEAR(UCSRA,UDRE));	//Polling until UDR register is empty and ready to accept data
	UDR = data;						    //move the data to UDR register

}

u8 USART_receiveByte (void)				// Function for receiving data byte
{
	while (BIT_IS_CLEAR(UCSRA,RXC));	//Polling until UDR register is full with data
	return UDR;							// Return the data from UDR register
}

void USART_sendString (const u8 *str)	// Function for sending string
{
	u8 i = 0;

	while (str[i] != '\0')
	{
		USART_sendByte(str[i]);
		i++;
	}
}

void USART_receiveString (u8 *str)		// function for receiving string
{

	u8 i = 0;
	str[i] = USART_receiveByte();
	while (str[i] != "#")
	{
		i++;
		str[i] =USART_receiveByte();
	}
	str[i] = '\0';
}
