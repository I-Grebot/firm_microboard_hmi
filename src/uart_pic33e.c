/*------------------------------------------------------------------------/
/  UART control module for PIC24F                          (C)ChaN, 2010
/-------------------------------------------------------------------------/
/
/  Copyright (C) 2010, ChaN, all right reserved.
/
/ * This software is a free software and there is NO WARRANTY.
/ * No restriction on use. You can use, modify and redistribute it for
/   personal, non-profit or commercial products UNDER YOUR RESPONSIBILITY.
/ * Redistributions of source code must retain the above copyright notice.
/
/-------------------------------------------------------------------------*/

#include "uart_pic33e.h"

#include "board_cfg.h"

#define BUFFER_SIZE 128


static volatile int TxRun;		/* Tx running flag */
static volatile int TxRobotRun;		/* Tx running flag */
static volatile struct {
	int		ri, wi, ct;			/* Read index, Write index, Data counter */
	BYTE	buff[BUFFER_SIZE];	/* FIFO buffer */
} TxFifo, RxFifo, TxRobotFifo, RxRobotFifo;




/* UART1 Rx interrupt ISR */

void __attribute__((interrupt, auto_psv)) _U1RXInterrupt (void)
{
	BYTE d;
	int i;


	d = (BYTE)U1RXREG;			/* Get received data */
	_U1RXIF = 0;				/* Clear Rx interrupt flag */
	i = RxFifo.ct;				/* Number of bytes in the FIFO */
	if (i < BUFFER_SIZE) {		/* Skip if FIFO is full */
		RxFifo.ct = ++i;
		i = RxFifo.wi;
		RxFifo.buff[i++] = d;	/* Store data into the FIFO */
		RxFifo.wi = i % BUFFER_SIZE;	/* Next write ptr */
	}
}



/* UART1 Tx interrupt ISR */

void __attribute__((interrupt, auto_psv)) _U1TXInterrupt (void)
{
	int i;


	_U1TXIF = 0;		/* Clear Tx interrupt flag */

	i = TxFifo.ct;		/* Number of data in the FIFO */
	if (i) {			/* If any data is available, pop a byte and send it. */
		TxFifo.ct = --i;
		i = TxFifo.ri;
		U1TXREG = TxFifo.buff[i++];		/* Send a byte */
		TxFifo.ri = i % BUFFER_SIZE;	/* Next read ptr */
	} else {			/* No data in the Tx FIFO */
		TxRun = 0;		/* Stop transmission sequense */
	}
}

/* UART2 Rx interrupt ISR */

void __attribute__((interrupt, auto_psv)) _U2RXInterrupt (void)
{
    static uint8_t ff_counter = 0;
    static uint8_t trame_start = 0;
    static uint8_t read_data = 0;
	BYTE d;
	int i;


	d = (BYTE)U2RXREG;			/* Get received data */

        if(0xFF == d)
        {
            ff_counter++;
            if(2 == ff_counter)
            {
                uint8_t count = RxRobotFifo.ct;

                //calcul CRC
                

                //flush in other buffer
                read_data = 0;
                trame_start = 1;
                RxRobotFifo.ct = 0;
            }
        }
        else
        {
            ff_counter = 0;
            if(1 == trame_start)
            {
                read_data = 1;
                //read_data_number = 0;
                trame_start = 0;
            }
        }

        if(1 == read_data)
        {
            i = RxRobotFifo.ct;				/* Number of bytes in the FIFO */
            if (i < BUFFER_SIZE) {		/* Skip if FIFO is full */
                    RxRobotFifo.ct = ++i;
                    i = RxRobotFifo.wi;
                    RxRobotFifo.buff[i++] = d;	/* Store data into the FIFO */
                    RxRobotFifo.wi = i % BUFFER_SIZE;	/* Next write ptr */
            }
        }

        _U2RXIF = 0;				/* Clear Rx interrupt flag */
}



/* UART2 Tx interrupt ISR */

void __attribute__((interrupt, auto_psv)) _U2TXInterrupt (void)
{
	int i;


	_U2TXIF = 0;		/* Clear Tx interrupt flag */

	i = TxRobotFifo.ct;		/* Number of data in the FIFO */
	if (i) {			/* If any data is available, pop a byte and send it. */
		TxRobotFifo.ct = --i;
		i = TxRobotFifo.ri;
		U2TXREG = TxRobotFifo.buff[i++];		/* Send a byte */
		TxRobotFifo.ri = i % BUFFER_SIZE;	/* Next read ptr */
	} else {			/* No data in the Tx FIFO */
		TxRobotRun = 0;		/* Stop transmission sequense */
	}
}



/* Check number of bytes in the Rx FIFO */

int uart_test (void)
{
    return RxFifo.ct;	/* Returns number of bytes in the Rx FIFO */
}



/* Get a byte from Rx FIFO */

BYTE uart_getc (void)
{
    BYTE d;
    int i;


    while (!RxFifo.ct) ;		/* Wait while Rx FIFO empty */

    i = RxFifo.ri;				/* Get a byte from Rx FIFO */
    d = RxFifo.buff[i++];
    RxFifo.ri = i % BUFFER_SIZE;
    _DI();
    RxFifo.ct--;
    _EI();

    return d;
}



/* Put a byte into Tx FIFO */

void uart_putc (BYTE d)
{
    int i;


    while (TxFifo.ct >= BUFFER_SIZE) ;	/* Wait while Tx FIFO is full */

    i = TxFifo.wi;		/* Put a data into the Tx FIFO */
    TxFifo.buff[i++] = d;
    TxFifo.wi = i % BUFFER_SIZE;
    _DI();
    TxFifo.ct++;
    if (!TxRun) {		/* If transmission sequense is not running, start the tx sequense */
            TxRun = 1;
            _U1TXIF = 1;	/* Force trigger Tx interrupt */
    }
    _EI();
}



/* Initialize UART module */

void uart_init (DWORD bps)
{
//* PRINTF VERSION
    //UNLOCK_PPS
    // Init UART peripheral
    DEBUG_UART_RX_TRIS = 1;
    DEBUG_UART_TX_TRIS = 0;
    DEBUG_UART_RX_RPN = DEBUG_UART_RX_PIN;
    DEBUG_UART_TX_RPN = DEBUG_UART_TX_PIN;

    U1MODEbits.STSEL = 0; // 1 Stop bits
    U1MODEbits.PDSEL = 0; // 8 Data bits and no parity
    U1MODEbits.ABAUD = 0; // Auto-baud disabled
    U1MODEbits.BRGH = 0; // Low speed flag
    U1BRG = DEBUG_UART_BRG; // Baud-rate config

    U1STAbits.UTXISEL0 = 0; // Interrupt after one TX character is transmitted
    U1STAbits.UTXISEL1 = 0;
    IEC0bits.U1TXIE = 1; // Enable UART TX interrupt

    U1MODEbits.UARTEN = 1; // Enable UART
    U1STAbits.UTXEN = 1; // Enable TX on UART

    //LOCK_PPS
    //*/

    //Configure CAN pins as UART
    UNLOCK_PPS
    // Init UART peripheral
    DEBUG_CAN_UART_RX_TRIS = 1;
    DEBUG_CAN_UART_TX_TRIS = 0;
    DEBUG_CAN_UART_RX_RPN = DEBUG_CAN_UART_RX_PIN;
    DEBUG_CAN_UART_TX_RPN = DEBUG_CAN_UART_TX_PIN;

    U2MODEbits.STSEL = 0; // 1 Stop bits
    U2MODEbits.PDSEL = 0; // 8 Data bits and no parity
    U2MODEbits.ABAUD = 0; // Auto-baud disabled
    U2MODEbits.BRGH = 0; // Low speed flag
    U2BRG = DEBUG_CAN_UART_BRG; // Baud-rate config

    U2STAbits.UTXISEL0 = 0; // Interrupt after one TX character is transmitted
    U2STAbits.UTXISEL1 = 0;
    IEC1bits.U2TXIE = 1; // Enable UART TX interrupt

    U2STAbits.URXISEL0 = 0; // Interrupt after one RX character is received
    U2STAbits.URXISEL1 = 0;
    IEC1bits.U2RXIE = 1; // Enable UART RX interrupt

    U2MODEbits.UARTEN = 1; // Enable UART
    U2STAbits.UTXEN = 1; // Enable TX on UART

    //LOCK_PPS

/*
    // Init UART peripheral
    DEBUG_UART_RX_TRIS = 1;
    DEBUG_UART_TX_TRIS = 0;
    DEBUG_UART_RX_RPN = DEBUG_UART_RX_PIN;
    DEBUG_UART_TX_RPN = DEBUG_UART_TX_PIN;
    
    // Disable UART1 Tx/Rx interrupts
    _U1RXIE = 0;
    _U1TXIE = 0;

    // Initialize UART1
    U1BRG = DEBUG_UART_BRG;
    U1MODEbits.UARTEN = 1; // Enable UART
    U1STAbits.UTXEN = 1; // Enable TX on UART

    // Clear Tx/Rx FIFOs
    TxFifo.ri = 0; TxFifo.wi = 0; TxFifo.ct = 0;
    RxFifo.ri = 0; RxFifo.wi = 0; RxFifo.ct = 0;
    TxRun = 0;

    // Enable UART Tx/Rx interruptrs
    _U1RXIE = 1;
    _U1TXIE = 1;
//*/
}


