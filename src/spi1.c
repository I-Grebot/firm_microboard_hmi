/* -----------------------------------------------------------------------------
 * microBoard - HMI
 * I-Grebot HMI interface
 * -----------------------------------------------------------------------------
 * File        : spi1.c
 * Language    : C
 * Author      : Paul M.
 * Creation    : 2015-03-01
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
 * 1.0         Initial release                           Paul M.      2015-03-01
 * -----------------------------------------------------------------------------
 */

#include "microBoard_hmi.h"

// Init SPI1 in Master Mode for OLED & SD_CARD slaves
// Not interrupt-driven - active polling mode
void spi1_init(void) {

  // Define TRIS registers
  SPI1_SCK_TRIS = 0;
  SPI1_MISO_TRIS = 1;
  SPI1_MOSI_TRIS = 0;

  // Configure SPI1 to operate in Master mode @ FCY / 8 MHz (= 10 MHz)
  SPI1STATbits.SPIEN  = 0; // Disable SPI during configuration
  IFS0bits.SPI1IF     = 0; // Clear the Interrupt flag
  IEC0bits.SPI1IE     = 0; // Disable the interrupt  
  SPI1CON1bits.PPRE   = 2; // Primary prescaler = 4:1
  SPI1CON1bits.SPRE   = 6; // Secondary prescaler = 2:1
  SPI1CON1bits.DISSCK = 0; // Internal serial clock is enabled
  SPI1CON1bits.DISSDO = 0; // SDOx pin is controlled by the module
  SPI1CON1bits.MODE16 = 0; // Communication is byte_wide (8 bits)
  SPI1CON1bits.SMP    = 0; // Input data is sampled at the middle of data output time
  SPI1CON1bits.CKP    = 1; // Idle state for clock is a high-level;
  SPI1CON1bits.CKE    = 0; // Serial output data changes on transition from
                           // Idle clock state to active clock state  
  SPI1CON1bits.MSTEN  = 1; // Master Mode
  SPI1STATbits.SPIEN  = 1; // Enable SPI module

  // Configure SPI1 Interrupt
  _SPI1IF = 0; // Clear the Interrupt flag
  //_SPI1IE = 1; // Enable the interrupt
  
}

// Emit a byte and return the received byte
uint8_t spi1_tx_rx(uint8_t tx_byte) {

  uint8_t rx_byte;

  while(SPI1STATbits.SPITBF);
  SPI1BUF = tx_byte & 0x00FF;
  while(!SPI1STATbits.SPIRBF);
  rx_byte = SPI1BUF;

  return rx_byte;
}

// SPI1 ISR (unused)
_ISR_NO_AUTO_PSV _SPI1Interrupt(void) {
  
  // Clear Interrupt
  _SPI1IF = 0;
  
}