/* -----------------------------------------------------------------------------
 * microBoard - HMI
 * I-Grebot HMI interface
 * -----------------------------------------------------------------------------
 * File        : oscillator.c
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
 * $Rev:: 1370                                                                 $
 * $LastChangedBy:: Ldoppea                                                    $
 * $LastChangedDate:: 2015-05-12 17:52:01 +0200 (mar., 12 mai 2015)            $
 * -----------------------------------------------------------------------------
 * Version     Comment                                   Author       Date
 * 1.0         Initial release                           Paul M.      2015-03-01
 * -----------------------------------------------------------------------------
 */

#include "microBoard_hmi.h"

// -----------------------------------------------------------------------------
// OSCILLATOR
// -----------------------------------------------------------------------------

void osc_init(void) {

    // dsPIC33E PLL Setup:
    // Setup PLL to obtain FCY = 32 MHz (FOSC = 64 MHz)
    // POSCCLK = 16MHz,
    // FOSC = (FIN/N1) * M / N2
    // However frequency ranges must be respected as the different nodes,
    // so that :
    // 0.8  <= FIN/N1       <= 8 MHz
    // 120  <= (FIN/N1) * M <= 340 MHz
    // 15   <= FOSC         <= 140 MHz (120 MHz if Temp >= 85°C)
    //
    // So we can pick:
    // N1 = 2,  (FIN/N1)   = 8 MHz
    // M  = 16, (FIN/N1)*M = 128 MHz
    // N2 = 2,        FOSC =  64 MHz, FCY = 32 MHz

    CLKDIVbits.PLLPRE  =  0; // N1 = 2
    PLLFBDbits.PLLDIV  = 14; // M  = 16
    CLKDIVbits.PLLPOST =  0; // N2 = 2
    CLKDIVbits.DOZE    =  0; // FP = FCY

    RCONbits.SWDTEN = 0; // Software watchdog disabled

    // Initiate Clock Switch to Primary Oscillator with PLL (NOSC = 0b011)
    __builtin_write_OSCCONH(0x03);
    __builtin_write_OSCCONL(0x01);

    // FIXME: program blocked here
    while (OSCCONbits.COSC != 3) ; // Wait until HSPLL mode is set
    while (OSCCONbits.LOCK != 1) ; // Wait until PLL is lock

}
