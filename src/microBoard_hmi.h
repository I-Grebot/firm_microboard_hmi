/* -----------------------------------------------------------------------------
 * microBoard - HMI
 * I-Grebot HMI interface
 * -----------------------------------------------------------------------------
 * File        : microBoard_hmi.h
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
 * $Rev:: 1396                                                                 $
 * $LastChangedBy:: Ldoppea                                                    $
 * $LastChangedDate:: 2015-10-15 22:23:32 +0200 (jeu., 15 oct. 2015)           $
 * -----------------------------------------------------------------------------
 * Version     Comment                                   Author       Date
 * 1.0         Initial release                           Paul M.      2015-03-01
 * -----------------------------------------------------------------------------
 */

#ifndef _MICROBOARD_HMI_H
#define	_MICROBOARD_HMI_H

// -----------------------------------------------------------------------------
// INCLUDES
// -----------------------------------------------------------------------------

// C libraries
#include <stdint.h>
#include <stdio.h>
//#include <stdarg.h>

// Program modules
#include "board_cfg.h"

// IgreBot libraries
//#include "igrecan.h"
#include "fifo.h"

#include "ssd1306.h"

#include "uart_pic33e.h"
#include "ff.h"
#include "xprintf.h"
#include "diskio.h"

#include "nav_menu.h"

#define MENU_ROOT_TITLE "IGREBOT HMI"

// Software IRQs

#define IRQ_NAV_OK      1
#define IRQ_NAV_RET     2
#define IRQ_NAV_UP_DN   4


#define BUZZER_OFF 0

// Temporary: registers are stored here
typedef struct {

    int16_t oled_contrast;
    
    int16_t red_brightness;
    int16_t green_brightness;
    int16_t blue_brightness;

    // Temp
    int16_t buzzer_frequency;
    int16_t buzzer_duty;


} reg_config_t;

// Oscillator
void osc_init(void);

// SPI1
void spi1_init(void);
uint8_t spi1_tx_rx(uint8_t tx_byte);

// Control Interface
void ctrl_if_init(void);
uint16_t ctrl_if_tx_rx(uint16_t tx_byte);

//// UART
//void uart_init(void);

// Navigation
void nav_init(void);
int32_t nav_get_pos(void);
void nav_reset_pos(void);
void nav_set_pos(int32_t value);

// PWMs (Buzzer & LEDs)
void pwm_init(void);
void pwm_enable(void);
void pwm_disable(void);
void buzzer_set_frequency(uint16_t frequency_hz);
void buzzer_set_duty_cycle(uint8_t duty_percent);

// LEDs
void led_init(void);

void led_rgb_set_intensity(uint8_t red_percent, uint8_t green_percent, uint8_t blue_percent);

// CAN module
// -----------

// Inits & processing
/*void microboardhmi_can_init(void);
void microboardhmi_can_rx(void);
void do_can_rx(void);
void do_can_tx(void);
void igg_process_can_rx(can_msg_t* msg);*/

// Motion
void can_send_motion_cmd(uint8_t flags, int16_t pos_reset_x, int16_t pos_reset_y,int16_t pos_reset_a);
void can_send_motion_goto(uint8_t type, int16_t pos_x,int16_t pos_y);
void can_send_motion_turnto(uint8_t type, int16_t pos_x,int16_t pos_y);
void can_send_motion_set_speed(int16_t speed_d, int16_t speed_a);

// Acutators
void can_send_spot_cmd(uint8_t left_builder, uint8_t right_builder, uint8_t bull_bar);
void can_send_pop_cmd(uint8_t left_pop, uint8_t right_pop);
void can_send_clap_cmd(uint8_t left_clap, uint8_t right_clap);
void can_send_cup_cmd(uint8_t left_cup, uint8_t right_cup);

// Menus
void show_demo();
//void show_menu();

// Buzzer
void do_update_buzzer(void);

// Fatfs
void fatfs_init (void);
void put_rc (FRESULT rc);
WORD get_seconds(void);
WORD get_minutes(void);
WORD get_hours(void);

// Fatfs logger
uint8_t sd_card_error(void);
void create_new_log_folder(void);
void create_new_log_file(void);
void log_string_no_sync(const TCHAR* str);
void log_string(const TCHAR* str);
void log_string_with_date(const TCHAR* str);
void log_string_delayed(const TCHAR* str);
void get_picture(FIL* fp, BYTE* pict, const TCHAR* path);

// Tests
int Cmd_ls(int argc, char *argv[]);

#endif	/* _MICROBOARD_HMI_H */

