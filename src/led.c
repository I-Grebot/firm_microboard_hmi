/* -----------------------------------------------------------------------------
 * microBoard - HMI
 * I-Grebot HMI interface
 * -----------------------------------------------------------------------------
 * File        : led.c
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

// Initialize the RGB led to use the PWMs
// TODO
void led_init(void) {
  
  LED1_TRIS = 0;
  LED2_TRIS = 0;
  LED3_TRIS = 0;
  LED4_TRIS = 0;

  LEDR_TRIS = 0;
  LEDG_TRIS = 0;
  LEDB_TRIS = 0;

  LED1 = LED_OFF;
  LED2 = LED_OFF;
  LED3 = LED_OFF;
  LED4 = LED_OFF;
  LEDR = 0;
  LEDG = 0;
  LEDB = 0;
  
}