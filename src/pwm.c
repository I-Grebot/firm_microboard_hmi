/* -----------------------------------------------------------------------------
 * microBoard - HMI
 * I-Grebot HMI interface
 * -----------------------------------------------------------------------------
 * File        : buzzer.c
 * Language    : C
 * Author      : Paul M.
 * Creation    : 2015-03-09
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
 * 1.0         Initial release                           Paul M.      2015-03-09
 * -----------------------------------------------------------------------------
 */

#include "microBoard_hmi.h"


extern reg_config_t reg_config;

void pwm_init(void) {

 
  // BUZZER (5L)
  /*asm("mov #0xabcd,w10");  // Load first unlock key to w10 register
  asm("mov #0x4321,w11");  // Load second unlock key to w11 register
  asm("mov #0x4C00, w0");  // Load desired value of IOCONx register in w0
  asm("mov w10, PWMKEY");  // Write first unlock key to PWMKEY register
  asm("mov w11, PWMKEY");  // Write second unlock key to PWMKEY register
  asm("mov w0, IOCON5") ;  // Write desired value to IOCONx register*/

  BUZZER_TRIS = 0;

  // Disable PWMs during configuration
  pwm_disable();

  // Common PWM Configuration

  PTCON2bits.PCLKDIV = PWM_PCLKDIV; // General prescaler

  PWMCON1bits.MTBS   = 0;    // PWM generator uses the primary master time
  PWMCON1bits.ITB    = 1;    // PHASEx/SPHASEx provide the time base for PWMxH/PWMxL
  PWMCON1bits.CAM    = 0;    // Edge-Aligned mode
  PWMCON1bits.DTC    = 0b10; // Dead time function is disabled
  PWMCON1bits.XPRES  = 0;    // External pins do not affect PWM time base
  PWMCON1bits.IUE    = 0;    // Freq/Duty registers update is synchronized
  PWMCON1bits.FLTIEN = 0;    // Fault interrupt is disabled
  PWMCON1bits.CLIEN  = 0;    // Current-limit interrupt is disabled
  PWMCON1bits.TRGIEN = 0;    // Trigger interrupt is disabled

  PWMCON2 = PWMCON1;
  PWMCON3 = PWMCON1;
  PWMCON4 = PWMCON1;
  PWMCON5 = PWMCON1;
  PWMCON6 = PWMCON1;

  IOCON1bits.POLH   = 0;    // PWMxH is active High
  IOCON1bits.POLL   = 0;    // PWMxL is active High
  IOCON1bits.PMOD   = 0b11; // Use True Independent PWM mode
  IOCON1bits.SWAP   = 0;    // PWMxH / PWMxL unswapped

  IOCON2 = IOCON1;
  IOCON3 = IOCON1;
  IOCON4 = IOCON1;
  IOCON5 = IOCON1;
  IOCON6 = IOCON1;

  FCLCON1bits.CLMOD   = 0;    // Current-Limit mode is disabled
  FCLCON1bits.FLTMOD  = 0b11; // Fault input is disabled

  FCLCON2 = FCLCON1;
  FCLCON3 = FCLCON1;
  FCLCON4 = FCLCON1;
  FCLCON5 = FCLCON1;
  FCLCON6 = FCLCON1;

  // Specific PWM Configuration
  
  IOCON1bits.PENH = PWM1H_EN;
  IOCON1bits.PENL = PWM1L_EN;
  IOCON2bits.PENH = PWM2H_EN;
  IOCON2bits.PENL = PWM2L_EN;
  IOCON3bits.PENH = PWM3H_EN;
  IOCON3bits.PENL = PWM3L_EN;
  IOCON4bits.PENH = PWM4H_EN;
  IOCON4bits.PENL = PWM4L_EN;
  IOCON5bits.PENH = PWM5H_EN;
  IOCON5bits.PENL = PWM5L_EN;
  IOCON6bits.PENH = PWM6H_EN;
  IOCON6bits.PENL = PWM6L_EN;

  // LEDs period
  LEDR_PER = 10000;
  LEDG_PER = 10000;
  LEDB_PER = 10000;

  buzzer_set_frequency(500);
  buzzer_set_duty_cycle(5);

  // Finally enable PWM module
  pwm_enable();
  
  //buzzer_set_frequency(2000);
  //SPHASE5 = 10000;  // Buzzer
 // SDC5 = 2000;
  //buzzer_set_duty_cycle(10);

//  PTCONbits.PTEN     = 1; // Enable PWMs

}

void pwm_enable(void) {
  _PTEN = 1;
}

void pwm_disable(void) {
  _PTEN  = 0;
}


void buzzer_set_frequency(uint16_t frequency_hz) {

  // 0 means 'OFF'
  if(frequency_hz == 0) {
    BUZZER_PER = 1;
    BUZZER_DUTY = 0;
  } else {

    if(frequency_hz < PWM_FREQ_MIN)
      frequency_hz = PWM_FREQ_MIN;
    else if(frequency_hz > PWM_FREQ_MAX)
      frequency_hz = PWM_FREQ_MAX;
    
    BUZZER_PER = ((PWM_BASE_FREQ/frequency_hz)-1) ;
    //reg_config.buzzer_duty = 10;  // default duty
  }
  
}

void buzzer_set_duty_cycle(uint8_t duty_percent) {
  BUZZER_DUTY = (uint16_t) (((uint32_t) BUZZER_PER * duty_percent) / 100);
}

void led_rgb_set_intensity(uint8_t red_percent, uint8_t green_percent, uint8_t blue_percent) {

  if(red_percent <= 100) LEDR_DUTY = red_percent * 100;
  if(green_percent <= 100) LEDG_DUTY = green_percent * 100;
  if(blue_percent <= 100) LEDB_DUTY = blue_percent * 100;

}
