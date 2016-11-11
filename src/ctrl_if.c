/* -----------------------------------------------------------------------------
 * microBoard - HMI
 * I-Grebot HMI interface
 * -----------------------------------------------------------------------------
 * File        : ctrl_if.c
 * Language    : C
 * Author      : Paul M.
 * Creation    : 2016-01-28
 * -----------------------------------------------------------------------------
 * Description:
 *   See main module file for the full description.
 * -----------------------------------------------------------------------------
 * Versionning informations
 * Repository: http://svn2.assembla.com/svn/paranoid_android/
 * -----------------------------------------------------------------------------
 * $Rev:: 1247                                                                 $
 * $LastChangedBy:: paul.m                                                     $
 * $LastChangedDate:: 2015-03-01 16:05:55 +0100 (dim., 01 mars 2015)           $
 * -----------------------------------------------------------------------------
 * Version     Comment                                   Author       Date
 * 1.0         Initial release                           Paul M.      2016-01-28
 * -----------------------------------------------------------------------------
 */

#include "microBoard_hmi.h"

// Temporary
uint16_t spi2_rx;

// Init SPI2 in Slave Mode for board control from external master
// Also intialize IRQs I/Os
void ctrl_if_init(void) {

  spi2_rx = 0;
  
  // Define TRIS registers
  SPI2_SCK_TRIS  = 1;
  SPI2_SSN_TRIS  = 1;
  SPI2_MISO_TRIS = 0;
  SPI2_MOSI_TRIS = 1;
  IRQ_IN_TRIS    = 1;
  IRQ_OUT_TRIS   = 0;

  // Configure SPI2 to operate in SPI Slave @ FCY / 8 MHz (= 10 MHz)
  SPI2BUF             = 0;
  SPI2STATbits.SPIEN  = 0; // Disable SPI during configuration
  _SPI2IF             = 0; // Clear the Interrupt flag
  _SPI2IE             = 0; // Disable the interrupt
  SPI2CON1bits.PPRE   = 2; // Primary prescaler = 4:1
  SPI2CON1bits.SPRE   = 6; // Secondary prescaler = 2:1
  SPI2CON1bits.DISSCK = 0; // Internal serial clock is enabled
  SPI2CON1bits.DISSDO = 0; // SDOx pin is controlled by the module
  SPI2CON1bits.MODE16 = 1; // Communication is word_wide (16 bits)
  SPI2CON1bits.SMP    = 0; // Input data is sampled at the middle of data output time
  SPI2CON1bits.CKP    = 1; // Idle state for clock is a high-level;
  SPI2CON1bits.CKE    = 0; // Serial output data changes on transition from
                           // Idle clock state to active clock state
  SPI2CON1bits.MSTEN  = 0; // Slave Mode
  SPI2CON1bits.SSEN   = 1; // Using Slave Select Enable pin (framed mode)
  SPI2CON2bits.FRMEN  = 0; // Do not use frame mode
  SPI2CON2bits.SPIBEN = 1; // Use the Enhanced Buffer mode
  SPI2STATbits.SISEL  = 1; // Interrupt when SRMPT is set (data is received in RX buffer)
  SPI2STATbits.SPIROV = 0; // Clear RX Overflow Flag
  SPI2STATbits.SPIEN  = 1; // Enable SPI module

  // Configure SPI2 Interrupt
  _SPI2IF = 0; // Clear the Interrupt flag
  //_SPI2IP  // Configure priority
  _SPI2IE = 1; // Enable the interrupt
  

  // Configure IRQ_IN Interrupt
  _INT0IF = 0;
  //_INT0IP // Configure priority
  _INT0IE = 1;

}

// Emit a word and return the received word
uint16_t ctrl_if_tx_rx(uint16_t tx_byte) {

  uint16_t rx_word;

  while(SPI2STATbits.SPITBF);
  SPI2BUF = tx_byte;
  while(!SPI2STATbits.SPIRBF);
  rx_word = SPI2BUF;

  return rx_word;
}

// SPI2 ISR
_ISR_NO_AUTO_PSV _SPI2Interrupt(void) {

  // Check for # of bytes in the RX fifo
  // Must be 2 for CTRL + DATA words (2 x 16 bits words)
  //if(SPI2STATbits.SPIBEC >= 2)
  spi2_rx = SPI2BUF;

  LED2 = ~LED2;
  
  // Clear Interrupt
  _SPI2IF = 0;

}

// INT0 (IRQ_IN) ISR
_ISR_NO_AUTO_PSV _INT0Interrupt(void) {

  // DO something?
  
  // Clear IRQ
  _INT0IF = 0;
  
}