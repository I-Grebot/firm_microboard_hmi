/* -----------------------------------------------------------------------------
 * microBoard - HMI
 * I-Grebot HMI interface
 * -----------------------------------------------------------------------------
 * File        : microBoard_hmi.c
 * Language    : C
 * Author      : Paul M.
 * Creation    : 2015-03-01
 * -----------------------------------------------------------------------------
 * Description:
 *   This board is a Human-Machine-Interface (HMI) allowing the user to
 *   interract with the system. It provides:
 *   - 2x navigation switches for "OK" and "Return"
 *   - 1x Quadrature Encoder for menu up/down or value +/-
 *   - 1x 128x64 OLED screen using the SSD1306 controller
 *   - 1x RGB Leds with current ratings up to 20 mA (mosfet controlled)
 *   - 4x Classic LEDs for general purpose feedbacks
 *   - 1x micro SD-Card slot for data retrieve/storage
 *   - 1x Sounder for making horrible noises (or play the so called "music")
 *   - 1x CAN Interface for compliance with the Igrebot's Legacy board
 *   - 1x Debug Interface
 * -----------------------------------------------------------------------------
 * Hardware Resources Usage:
 *   - SPI1 (master) is used for the OLED & SD-Card (2 different chip-selects)
 *   - INT0 and SPI2 (slave) are used for the board control
 *                   (only with microBoards system)
 *   - ECAN1 is used for the board control (only Igrebot's Legacy boards)
 *   - UART1 for Debug Interface
 *   - PWM1 for LED1 and LED2
 *   - PWM4 for LED3 and LED4
 *   - PWM2 and PWM3 for the RGB LED
 *   - PWM5 for the Sounder PWM
 *   - INT1 and INT2 are used for the "OK" and "RET" navigation switches
 *   - QEI1 is used for the navigation scrolling
 * -----------------------------------------------------------------------------
 * Versionning informations
 * Repository: http://svn2.assembla.com/svn/paranoid_android/
 * -----------------------------------------------------------------------------
 * $Rev:: 1396                                                                 $
 * $LastChangedBy:: Ldoppea                                                    $
 * $LastChangedDate:: 2015-10-15 22:23:32 +0200 (jeu., 15 oct. 2015)           $
 * -----------------------------------------------------------------------------
 * Version     Comment                                   Author       Date
 * 1.0         Initial release                           Paul M.      2015-03-01
 * -----------------------------------------------------------------------------
 */

#include "microBoard_hmi.h"

menu_action_e menu_action;

// Temp
extern uint16_t spi2_rx;
reg_config_t reg_config;

// -----------------------------------------------------------------------------
// CONFIGURATION
// -----------------------------------------------------------------------------

// Disable JTAG pins and use PGEC1/PGED1 pins for config
_FICD(JTAGEN_OFF & ICS_PGD1);

// Disable BOR, Do not use alternate I2C pins and setup WDT window to 50%
_FPOR(BOREN_OFF & ALTI2C1_OFF & ALTI2C2_OFF & WDTWIN_WIN50)

// Watchdog is enabled/disabled by software control
// When used, the WDT period is 256ms (128 * 64 / 32kHz)
// Enable the PLL source lock
_FWDT(FWDTEN_OFF & WINDIS_OFF & WDTPRE_PR128 & WDTPOST_PS64 & PLLKEN_ON);

// Configure POSC in HS mode and enable clock switching.
// Also enable multiple remapping.
_FOSC(POSCMD_HS & OSCIOFNC_OFF & IOL1WAY_OFF & FCKSM_CSECME);

// Oscillator startup configuration, on internal fast RC
// Remove PWM Lock for IOCONx and FCLCONx registers
_FOSCSEL(FNOSC_FRC & PWMLOCK_OFF);

// Configure General Segment Write protection (write-protect & code-protect)
_FGS(GWRP_OFF & GCP_OFF)

// Configure User-IDS
_FUID0(0x1234);
_FUID1(0x0000);
_FUID2(0x0000);
_FUID3(0x0000);

// -----------------------------------------------------------------------------
// GLOBALS
// -----------------------------------------------------------------------------

// Some pictures for the OLED screen
extern const uint8_t igrebot_logo[];
extern const uint8_t robocop_logo[];

extern uint8_t display_buffer[OLED_NB_PAGES][OLED_WIDTH];

// Sofware interrupts
uint8_t sw_irq;

// Demo-mode
uint8_t demo_mode;

//void uart_init(void) {
//
//    UNLOCK_PPS
//    // Init UART peripheral
//    DEBUG_UART_RX_TRIS = 1;
//    DEBUG_UART_TX_TRIS = 0;
//    DEBUG_UART_RX_RPN = DEBUG_UART_RX_PIN;
//    DEBUG_UART_TX_RPN = DEBUG_UART_TX_PIN;
//
//    U1MODEbits.STSEL = 0; // 1 Stop bits
//    U1MODEbits.PDSEL = 0; // 8 Data bits and no parity
//    U1MODEbits.ABAUD = 0; // Auto-baud disabled
//    U1MODEbits.BRGH = 0; // Low speed flag
//    U1BRG = DEBUG_UART_BRG; // Baud-rate config
//
//    U1MODEbits.UARTEN = 1; // Enable UART
//    U1STAbits.UTXEN = 1; // Enable TX on UART
//
//    LOCK_PPS
//}

// -----------------------------------------------------------------------------
// MAIN
// -----------------------------------------------------------------------------

#define DATA_FIFO_SIZE  (127 - 3*(SSD1306_FONT_WIDTH+1))

int main() {

  uint32_t delay;
  uint8_t nb_char;
  char oled_string[OLED_NB_CHAR_PER_LINE * OLED_NB_PAGES];
  int16_t cnt;
  int8_t cnt_inc;

  int16_t nav_value;
  int16_t nav_value_prev;
  
  ssd1306_int16_plot_t plot;

  FRESULT res;
  
  // Initialize all I/Os as digital
  ANSELA = 0x0000;
  ANSELB = 0x0000;
  ANSELC = 0x0000;

  // Modules initialization
  osc_init();
  spi1_init();
  ctrl_if_init();
  ssd1306_init();
  nav_init();
  led_init();
  //pwm_init();

  uart_init(DEBUG_UART_BRG);
  fatfs_init();
  buzzer_init();

  led_rgb_set_intensity(0, 0, 0);
  

  sw_irq = 0;

  reg_config.red_brightness = 0;
  reg_config.green_brightness = 0;
  reg_config.blue_brightness = 0;

  reg_config.buzzer_frequency = 0;
  reg_config.buzzer_duty = 0;
  reg_config.oled_contrast = 200;
//
//  microboardhmi_can_init();
  //can_set_mode(CAN_MODE_LOOPBACK);
//  can_set_mode(CAN_MODE_LISTEN);

  
  // Power-up the OLED screen and adjust the contrast
  ssd1306_power_up();
  ssd1306_set_contrast(reg_config.oled_contrast);
  //ssd1306_display_picture(igrebot_logo);

  menu_init();
  menu_build();

  buzzer_set_frequency((uint16_t) reg_config.buzzer_frequency);
  buzzer_set_duty_cycle((uint8_t) reg_config.buzzer_duty);

  menu_draw();

  //play_song("Music/zeldan64.wav");
  
  while(1) {

    menu_action_e menu_action;

    for(delay=100000; delay; delay--);

    // Default action
    menu_action = MENU_ACTION_NOTHING;

    // Retreive navigation switch position
    nav_value = ((int16_t) nav_get_pos());

    if(sw_irq & IRQ_NAV_OK) {
      sw_irq &= ~IRQ_NAV_OK;
      menu_action = MENU_ACTION_ENTER;
      //menu_manage(MENU_ACTION_ENTER);
    }

    else if(sw_irq & IRQ_NAV_RET) {
      sw_irq &= ~IRQ_NAV_RET;
      menu_action = MENU_ACTION_RETURN;
      //menu_manage(MENU_ACTION_RETURN);
    }

    else if(nav_value - nav_value_prev > MENU_SCROLL_THRESHOLD) {
      menu_action = MENU_ACTION_NEXT;
      //menu_manage(MENU_ACTION_NEXT);
      nav_value_prev = nav_value;
    }

    else if(nav_value_prev - nav_value > MENU_SCROLL_THRESHOLD) {
      menu_action = MENU_ACTION_PREV;
      //menu_manage(MENU_ACTION_PREV);
      nav_value_prev = nav_value;
    }

    // Always manage the menu
    menu_manage(menu_action);

  }


  // OLD  --------------
  sprintf(plot.title, "NAVIGATION");
  //plot.var = &nav_value;
  //plot.var = &cnt;
  plot.var = (int16_t*) &spi2_rx;
  plot.color = 0;
  plot.y_axis_auto = 1;
  plot.disp_axis_values = 0;

  ssd1306_int16_plot_init(&plot);
  cnt = 0;
  cnt_inc = 0;

  while(1) {
    for(delay=100000; delay; delay--);

    nav_value = ((int16_t) nav_get_pos());

    // Ping-pong with amplitude controller!
    if(cnt <= -30*nav_value)
      cnt_inc = 1;
    else if(cnt >= 30*nav_value)
      cnt_inc = -1;
    
    cnt = cnt + 5*cnt_inc*nav_value;
    
    ssd1306_int16_plot_process(&plot);
    
  }
  
  //while(1);
  //draw_electrical_monitoring();

//  //show_demo();
  //browse_menu();
  //SD CARD
//  fatfs_main();

} // main

void show_demo() {

  uint8_t cnt;
  uint32_t idx;
  int32_t nav_value;
  uint8_t red_led, green_led, blue_led;
  char oled_string[OLED_NB_CHAR_PER_LINE * OLED_NB_PAGES];
  int nb_char;
  
  // Main demo-loop
  demo_mode = 0;

  while(0x2A) {

    // CAN RX Fifos
//    do_can_rx();

    nav_value = nav_get_pos();

    // Basic delay
    for(idx=100000; idx; idx--);

    //printf("TestYannick2\n");

    switch(demo_mode) {

      case 0:
        pwm_disable();
        //ssd1306_display_picture(igrebot_logo);
        ssd1306_display_picture(robocop_logo);
//        ssd1306_clear_screen();
//
//        nb_char = sprintf(oled_string, "SALUT");
//        if(nb_char > 0) ssd1306_printf(oled_string, nb_char, 0, 2, 0);

        //pwm_enable();
        //buzzer_set_duty_cycle(10);

        break;

      case 1:
        //can_send_motion_goto(0, 0, 0);
        pwm_disable();
        ssd1306_clear_screen();
        nb_char = sprintf(oled_string, "NAV = %ld\nCNT = %u", nav_value, cnt++);
        if(nb_char > 0) ssd1306_printf(oled_string, nb_char, 0, 0, 0);
        break;

      case 2:
        pwm_enable();
        ssd1306_clear_screen();
        nb_char = sprintf(oled_string, "Nav = %ld\nFreq = %.2f kHz\n", nav_value, ((double) nav_value)/10);
        if(nb_char > 0) ssd1306_printf(oled_string, nb_char, 0, 0, 0);
        buzzer_set_frequency(nav_value*100);
        //buzzer_set_frequency(2000);
        //buzzer_set_duty_cycle(200);
        //buzzer_set_duty_cycle(nav_value);

        break;

      case 3:
      case 4:
      case 5:
        pwm_enable();
        ssd1306_clear_screen();
        buzzer_set_frequency(0);
        nb_char = sprintf(oled_string, "Red = %u %%\nGreen = %u %%\nBlue = %u %%",
          red_led, green_led, blue_led);
        if(nb_char > 0) ssd1306_printf(oled_string, nb_char, 0, 0, 0);

        if(demo_mode == 3) red_led = (uint8_t) nav_value;
        if(demo_mode == 4) green_led = (uint8_t) nav_value;
        if(demo_mode == 5) blue_led = (uint8_t) nav_value;

        led_rgb_set_intensity(red_led, green_led, blue_led);
        break;

      // Reset to a correct value
      default:
        demo_mode = 0;
        break;
    } // switch

  } // while
}

//void show_menu() {
//}