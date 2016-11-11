/* -----------------------------------------------------------------------------
 * microBoard - HMI
 * I-Grebot HMI interface
 * -----------------------------------------------------------------------------
 * File        : nav.c
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
 * $Rev:: 1346                                                                 $
 * $LastChangedBy:: Ldoppea                                                    $
 * $LastChangedDate:: 2015-05-07 18:57:27 +0200 (jeu., 07 mai 2015)            $
 * -----------------------------------------------------------------------------
 * Version     Comment                                   Author       Date
 * 1.0         Initial release                           Paul M.      2015-03-01
 * -----------------------------------------------------------------------------
 */

#include "microBoard_hmi.h"

extern uint8_t sw_irq;

void nav_init(void) {

  // All navigation switches are inputs
  NAV_A_TRIS = 1;
  NAV_B_TRIS = 1;
  NAV_OK_TRIS = 1;
  NAV_RET_TRIS = 1;

  // Setup INTx interrupts for OK & RET switches
  NAV_OK_RPIR = NAV_OK_RPN;
  NAV_RET_RPIR = NAV_RET_RPN;

  // Setup QEIA associated with the NAV_A/NAV_B switches
  NAV_A_RPIR = NAV_A_RPN;
  NAV_B_RPIR = NAV_B_RPN;

  // Configure the QEI for navigation
  _QEIEN = 0 ; // Disabled during configuration
  _CCM = 0 ; // Quadrature encoder mode
  _PIMOD = 0; // Index input does not affect position counter
  _IMV = 0 ;
  QEI1IOCbits.FLTREN = 1 ; // Input pin digital filter is enabled
  QEI1IOCbits.QFDIV = 0; // 1:1 QEIA / QEIB input clock divide
  POS1CNTH = 0; // Reset position counter
  POS1CNTL = 0;  

  _QEIEN = 1 ; // Enable QEI

  // Interrupt on negative edges (i.e. button get pushed down, not released)
  _INT1EP = 1;
  _INT2EP = 1;

  // Clean up and enable ISRs
  _INT1IF = 0;
  _INT2IF = 0;
  //_QEI1IF = 0;
  //_QEI1IE = 1; // NAV UP/DN
  _INT1IE = 1; // NAV_OK
  _INT2IE = 1; // NAV_RET

}

// Get the absolute position of the navigation's encoder
int32_t nav_get_pos(void) {
  return (int32_t) (((int32_t) POS1CNTH) << 16) + POS1CNTL;
}

void nav_set_pos(int32_t value) {
  POS1CNTH = (value >> 16) & 0xFFFF;
  POS1CNTL = value & 0x0000FFFF;
}

// Reset the navigation's encoder position
void nav_reset_pos(void) {
  POS1CNTH = 0;
  POS1CNTL = 0;
}

// NAV_OK interrupt
_ISR_NO_AUTO_PSV _INT1Interrupt(void) {
  sw_irq |= IRQ_NAV_OK;
  _INT1IF = 0;
}

// NAV_RET interrupt
_ISR_NO_AUTO_PSV _INT2Interrupt(void) {
  sw_irq |= IRQ_NAV_RET;
  _INT2IF = 0;
}

/*_ISR_NO_AUTO_PSV _QEI1Interrupt(void) {
  sw_irq |= IRQ_NAV_UP_DN;
  _QEI1IF = 0;
}*/