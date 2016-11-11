/* -----------------------------------------------------------------------------
 * microBoard - HMI
 * I-Grebot HMI interface
 * -----------------------------------------------------------------------------
 * File        : ssd1306.h
 * Language    : C
 * Author      : Paul M.
 * Creation    : 2015-03-01
 * -----------------------------------------------------------------------------
 * Description:
 *   See main module file for the full description.
 *   TODO: This file should be moved in a dedicated library.
 * -----------------------------------------------------------------------------
 * Versionning informations
 * Repository: http://svn2.assembla.com/svn/paranoid_android/
 * -----------------------------------------------------------------------------
 * $Rev:: 1369                                                                 $
 * $LastChangedBy:: Ldoppea                                                    $
 * $LastChangedDate:: 2015-05-12 13:29:03 +0200 (mar., 12 mai 2015)            $
 * -----------------------------------------------------------------------------
 * Version     Comment                                   Author       Date
 * 1.0         Initial release                           Paul M.      2015-03-01
 * -----------------------------------------------------------------------------
 */

#ifndef _SSD1306_H
#define	_SSD1306_H

#include "board_cfg.h"


// -----------------------------------------------------------------------------
// CONTROLLER CONSTANTS
// -----------------------------------------------------------------------------

// Value on the DCN pin for data or command instruction
#define SSD1306_WR_CMD  0
#define SSD1306_WR_DATA 1

// Addressing modes
#define SSD1306_ADDR_VERT  0x00
#define SSD1306_ADDR_HORIZ 0x01
#define SSD1306_ADDR_PAGE  0x02

// Scrolling speeds (number of frames between each step)
#define SSD1306_SCROLL_SPEED_2   0b111
#define SSD1306_SCROLL_SPEED_3   0b100
#define SSD1306_SCROLL_SPEED_4   0b101
#define SSD1306_SCROLL_SPEED_5   0b000
#define SSD1306_SCROLL_SPEED_25  0b110
#define SSD1306_SCROLL_SPEED_64  0b001
#define SSD1306_SCROLL_SPEED_128 0b010
#define SSD1306_SCROLL_SPEED_256 0b011

// Scrolling enable flags
#define SSD1306_SCROLL_OFF  0x00
#define SSD1306_SCROLL_ON   0x01

// -----------------------------------------------------------------------------
// GRAPHICS DEFINITION
// -----------------------------------------------------------------------------

// Hight of 1 page in number of pixels
#define SSD1306_PAGE_HEIGHT 8

// Size of font characters defined in the ssd1306_const module
#define SSD1306_FONT_WIDTH  5
#define SSD1306_FONT_HEIGHT SSD1306_PAGE_HEIGHT

// Colors arbitrary values
#define SSD1306_COLOR_WHITE 1
#define SSD1306_COLOR_BLACK 0

// -----------------------------------------------------------------------------
// WIDGETS DEFINITION
// -----------------------------------------------------------------------------

// 1D Vs Time Plot
// ---------------

// Maximum length for a plot's title
#define SSD1306_PLOT_NAME_SIZE OLED_NB_CHAR_PER_LINE

// X data starts after 6 characters (enough for int16 data like "-32000)
#define SSD1306_PLOT_X_DATA_START (6*(SSD1306_FONT_WIDTH+1))
#define SSD1306_PLOT_X_DATA_END   (OLED_WIDTH-1)

// Y data starts after 1 line (enough to print the title)
#define SSD1306_PLOT_Y_DATA_START       SSD1306_FONT_HEIGHT
#define SSD1306_PLOT_Y_DATA_START_PAGE  1
#define SSD1306_PLOT_Y_DATA_END         (OLED_HEIGHT-1)
#define SSD1306_PLOT_Y_DATA_END_PAGE    (OLED_NB_PAGES-1)
#define SSD1306_PLOT_Y_DATA_MAX         (SSD1306_PLOT_Y_DATA_END - SSD1306_PLOT_Y_DATA_START - 2) // due to 2 top/bottom lines
#define SSD1306_PLOT_Y_DATA_OFFSET      1 // Make room for the bottom line
#define SSD1306_PLOT_Y_DATA_NB_PAGES    (SSD1306_PLOT_Y_DATA_END_PAGE - SSD1306_PLOT_Y_DATA_START_PAGE+1)

// Title position
#define SSD1306_PLOT_X_TITLE 1
#define SSD1306_PLOT_Y_TITLE 0

// Current value position
#define SSD1306_PLOT_X_CURRENT_VALUE 0
#define SSD1306_PLOT_Y_CURRENT_VALUE 1

// Data info positions
#define SSD1306_PLOT_X_DATA         0
#define SSD1306_PLOT_Y_MAX_TEXT     2
#define SSD1306_PLOT_Y_MAX_DATA     3
#define SSD1306_PLOT_Y_AVG_TEXT     4
#define SSD1306_PLOT_Y_AVG_DATA     5
#define SSD1306_PLOT_Y_MIN_TEXT     6
#define SSD1306_PLOT_Y_MIN_DATA     7

// Axis info positions
#define SSD1306_PLOT_X_AXIS         6
#define SSD1306_PLOT_Y_MAX_AXIS     1
#define SSD1306_PLOT_Y_MIN_AXIS     7


// The FIFO size depends on the width of screen (# of samples)
#define SSD1306_PLOT_FIFO_SIZE (SSD1306_PLOT_X_DATA_END - SSD1306_PLOT_X_DATA_START)


// Digital Gauge
// -------------

#define SSD1306_WIDG_DIG_GAUGE_NAME_SIZE    OLED_NB_CHAR_PER_LINE

// Title position
#define SSD1306_WIDG_DIG_GAUGE_X_TITLE 1
#define SSD1306_WIDG_DIG_GAUGE_Y_TITLE 0

// Enter / Return positions
#define SSD1306_WIDG_DIG_GAUGE_X_ENTER   3
#define SSD1306_WIDG_DIG_GAUGE_Y_ENTER   6
#define SSD1306_WIDG_DIG_GAUGE_X_RETURN  3
#define SSD1306_WIDG_DIG_GAUGE_Y_RETURN  7

// Current value position
#define SSD1306_WIDG_DIG_GAUGE_X_LOW_BOUND      1
#define SSD1306_WIDG_DIG_GAUGE_X_VALUE          (OLED_NB_CHAR_PER_LINE/2 - 3)
#define SSD1306_WIDG_DIG_GAUGE_X_HIGH_BOUND     (OLED_NB_CHAR_PER_LINE - 6)
#define SSD1306_WIDG_DIG_GAUGE_Y_VALUE          2

// Gauge bar position
#define SSD1306_WIDG_DIG_GAUGE_X_START_BAR  6
#define SSD1306_WIDG_DIG_GAUGE_X_END_BAR    (OLED_WIDTH - SSD1306_WIDG_DIG_GAUGE_X_START_BAR)

#define SSD1306_WIDG_DIG_GAUGE_Y_BAR        4   // Page address

// -----------------------------------------------------------------------------
// WIDGET STRUCTURES & ENUMERATIONS
// -----------------------------------------------------------------------------

// Signed 16b 1D_Time plot structure
typedef struct {
    
    // Plot title
    char title[SSD1306_PLOT_NAME_SIZE];

    // Pointer on the data to monitor
    int16_t* var;
    
    // Plot options
    uint8_t y_axis_auto ;       // 1: axis will auto adjust
    int32_t y_axis_min  ;       // Min/Max value when manual
    int32_t y_axis_max  ;
    uint8_t x_axis_speed ;      // For future implementation with autonomous update from timer
    uint8_t disp_axis_values;   // Display axis min/max values (tends to flickers)
    uint8_t color;              // Plot color: 0 for black BG and white FG
    
    // Statistics in legacy units
    int16_t min ;
    int16_t max ;
    int16_t avg ;
    int32_t acc ; // Accumulated data_fifo value

    // Fifo to hold our int16 data
    fifo_t* data_fifo;
    
} ssd1306_int16_plot_t;

// Signed 16b digital gauge structure
typedef struct {

    // Gauge title
    char title[SSD1306_WIDG_DIG_GAUGE_NAME_SIZE];

    // Pointer on the gauge data to change (live update)
    int16_t* var;

    // Value when the gauge is created (useful for "cancel" action:
    // old value is put back)
    int16_t init_value;

    // Increment value (between each tick for 1 CW turn)
    int16_t inc;
    
    // Limits (new value cannot exceed these limits), low_bound <= high_bound
    int16_t low_bound;
    int16_t high_bound;

} ssd1306_widg_dig_gauge_t;

// -----------------------------------------------------------------------------
// PROTOTYPES
// -----------------------------------------------------------------------------

void ssd1306_init(void);
void ssd1306_tx_rx(uint8_t data_cmd, uint8_t* data, uint8_t nb_data);

// Hookups
void ssd1306_set_display_on(uint8_t display_on);
void ssd1306_set_contrast(uint8_t contrast);
void ssd1306_set_addressing_mode(uint8_t mode);
void ssd1306_set_column_start_stop(uint8_t start, uint8_t stop);
void ssd1306_set_page_start_stop(uint8_t start, uint8_t stop);
void ssd1306_set_page_address(uint8_t address);
void ssd1306_set_column_address(uint8_t address);
void ssd1306_set_horizontal_scroll(uint8_t left_horiz, uint8_t start, uint8_t end, uint8_t speed);
void ssd1306_set_scroll_enable(uint8_t scroll_en);

// Power up/down
void ssd1306_power_up(void);
void ssd1306_power_down(void);

// General display functions
void ssd1306_clear_screen(void);

// Picture display functions
void ssd1306_display_picture(const uint8_t pic[]);
void ssd1306_display_picture_from_bytes(const uint8_t pic[]);

// String display functions
void ssd1306_draw_char(unsigned char c, uint8_t x, uint8_t y, uint8_t bg);
void ssd1306_printf(char* line_str, uint8_t len, uint8_t bg, uint8_t start_line, uint8_t start_col);

// H & V Lines plot functions
void ssd1306_draw_horizontal_line(uint8_t x1, uint8_t x2, uint8_t y, uint8_t color);
void ssd1306_draw_vertical_line(uint8_t x, uint8_t y1, uint8_t y2, uint8_t color);

// Widgets
// -------

// 1D Vs Time plot
void ssd1306_int16_plot_init(ssd1306_int16_plot_t* plot);
void ssd1306_int16_plot_process(ssd1306_int16_plot_t* plot);

// Digital gauge
void ssd1306_widg_dig_gauge_init(ssd1306_widg_dig_gauge_t* gauge);
void ssd1306_widg_dig_gauge_process(ssd1306_widg_dig_gauge_t* gauge);

#endif	/* SSD1306_H */

