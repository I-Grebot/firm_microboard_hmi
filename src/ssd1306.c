/* -----------------------------------------------------------------------------
 * microBoard - HMI
 * I-Grebot HMI interface
 * -----------------------------------------------------------------------------
 * File        : ssd1306.c
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
 * 1.2         Added 2D plot feature                     Paul M.      2016-01-31
 * 1.1         Added H & V lines features                Paul M.      2016-01-24
 * 1.0         Initial release                           Paul M.      2015-03-01
 * -----------------------------------------------------------------------------
 */

#include "microBoard_hmi.h"

// -----------------------------------------------------------------------------
// GLOBALS
// -----------------------------------------------------------------------------

extern const uint8_t ssd1306_font[];
extern const uint8_t igrebot_logo[];

// Double buffering: local buffer to store display data
uint8_t display_buffer[OLED_NB_PAGES][OLED_WIDTH];

// Fast LUT for swapping uint8 bits (MSB:LSB becomes LSB:MSB)
static const uint8_t reversed_uint8[] = {
  0x00, 0x80, 0x40, 0xC0, 0x20, 0xA0, 0x60, 0xE0,
  0x10, 0x90, 0x50, 0xD0, 0x30, 0xB0, 0x70, 0xF0,
  0x08, 0x88, 0x48, 0xC8, 0x28, 0xA8, 0x68, 0xE8,
  0x18, 0x98, 0x58, 0xD8, 0x38, 0xB8, 0x78, 0xF8,
  0x04, 0x84, 0x44, 0xC4, 0x24, 0xA4, 0x64, 0xE4,
  0x14, 0x94, 0x54, 0xD4, 0x34, 0xB4, 0x74, 0xF4,
  0x0C, 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC,
  0x1C, 0x9C, 0x5C, 0xDC, 0x3C, 0xBC, 0x7C, 0xFC,
  0x02, 0x82, 0x42, 0xC2, 0x22, 0xA2, 0x62, 0xE2,
  0x12, 0x92, 0x52, 0xD2, 0x32, 0xB2, 0x72, 0xF2,
  0x0A, 0x8A, 0x4A, 0xCA, 0x2A, 0xAA, 0x6A, 0xEA,
  0x1A, 0x9A, 0x5A, 0xDA, 0x3A, 0xBA, 0x7A, 0xFA,
  0x06, 0x86, 0x46, 0xC6, 0x26, 0xA6, 0x66, 0xE6,
  0x16, 0x96, 0x56, 0xD6, 0x36, 0xB6, 0x76, 0xF6,
  0x0E, 0x8E, 0x4E, 0xCE, 0x2E, 0xAE, 0x6E, 0xEE,
  0x1E, 0x9E, 0x5E, 0xDE, 0x3E, 0xBE, 0x7E, 0xFE,
  0x01, 0x81, 0x41, 0xC1, 0x21, 0xA1, 0x61, 0xE1,
  0x11, 0x91, 0x51, 0xD1, 0x31, 0xB1, 0x71, 0xF1,
  0x09, 0x89, 0x49, 0xC9, 0x29, 0xA9, 0x69, 0xE9,
  0x19, 0x99, 0x59, 0xD9, 0x39, 0xB9, 0x79, 0xF9,
  0x05, 0x85, 0x45, 0xC5, 0x25, 0xA5, 0x65, 0xE5,
  0x15, 0x95, 0x55, 0xD5, 0x35, 0xB5, 0x75, 0xF5,
  0x0D, 0x8D, 0x4D, 0xCD, 0x2D, 0xAD, 0x6D, 0xED,
  0x1D, 0x9D, 0x5D, 0xDD, 0x3D, 0xBD, 0x7D, 0xFD,
  0x03, 0x83, 0x43, 0xC3, 0x23, 0xA3, 0x63, 0xE3,
  0x13, 0x93, 0x53, 0xD3, 0x33, 0xB3, 0x73, 0xF3,
  0x0B, 0x8B, 0x4B, 0xCB, 0x2B, 0xAB, 0x6B, 0xEB,
  0x1B, 0x9B, 0x5B, 0xDB, 0x3B, 0xBB, 0x7B, 0xFB,
  0x07, 0x87, 0x47, 0xC7, 0x27, 0xA7, 0x67, 0xE7,
  0x17, 0x97, 0x57, 0xD7, 0x37, 0xB7, 0x77, 0xF7,
  0x0F, 0x8F, 0x4F, 0xCF, 0x2F, 0xAF, 0x6F, 0xEF,
  0x1F, 0x9F, 0x5F, 0xDF, 0x3F, 0xBF, 0x7F, 0xFF
};



// -----------------------------------------------------------------------------
// INITIALIZER
// -----------------------------------------------------------------------------

// OLED module initializer
// SPI1 Must be initialized before
void ssd1306_init(void) {

  // Define controls as outputs
  OLED_PWR_EN_TRIS = 0;
  OLED_CSN_TRIS = 0;
  OLED_DCN_TRIS = 0;
  OLED_RESN_TRIS = 0;

  // Default states
  OLED_PWR_EN = 0; // Active high
  OLED_CSN = 1; // Active low
  OLED_RESN = 1; // Active low
  OLED_DCN = 0;

}

// -----------------------------------------------------------------------------
// 4-WIRE SPI INTERFACE
// -----------------------------------------------------------------------------

// Frame nb_data as a command or data
void ssd1306_tx_rx(uint8_t data_cmd, uint8_t* data, uint8_t nb_data) {

  uint8_t data_idx;

  OLED_DCN = data_cmd;
  for(data_idx = 0; data_idx < nb_data; data_idx++) {
    OLED_CSN = 0;        
    spi1_tx_rx(data[data_idx]);    
    OLED_CSN = 1;    
  }
}

// -----------------------------------------------------------------------------
// HOOKUPS
// -----------------------------------------------------------------------------

// Set display ON or OFF
void ssd1306_set_display_on(uint8_t display_on) {
  uint8_t cmd;
  cmd = 0xAE | (display_on & 0x01);
  ssd1306_tx_rx(SSD1306_WR_CMD, &cmd, 1);
}

void ssd1306_set_contrast(uint8_t contrast) {
  uint8_t cmd[2];
  cmd[0] = 0x81; cmd[1] = contrast;
  ssd1306_tx_rx(SSD1306_WR_CMD, cmd, 2);
}

void ssd1306_set_addressing_mode(uint8_t mode) {
  uint8_t cmd[2];
  cmd[0] = 0x20; cmd[1] = mode & 0x03;
  ssd1306_tx_rx(SSD1306_WR_CMD, cmd, 2);
}

// Note: Only used in horizontal or vertical addressing mode
void ssd1306_set_column_start_stop(uint8_t start, uint8_t stop) {
  uint8_t cmd[3];
  
  if((start >= OLED_WIDTH) || (stop >= OLED_WIDTH) || (stop < start))
    return;

  cmd[0] = 0x21;
  cmd[1] = start;
  cmd[2] = stop;
  ssd1306_tx_rx(SSD1306_WR_CMD, cmd, 3);
}

// Note: Only used in horizontal or vertical addressing mode
void ssd1306_set_page_start_stop(uint8_t start, uint8_t stop) {
  uint8_t cmd[3];

  if((start >= OLED_NB_PAGES) || (stop >= OLED_NB_PAGES) || (stop < start))
    return;

  cmd[0] = 0x22;
  cmd[1] = start;
  cmd[2] = stop;
  ssd1306_tx_rx(SSD1306_WR_CMD, cmd, 3);
}

// Note: only used in page addressing mode
void ssd1306_set_page_address(uint8_t address) {
  uint8_t cmd;
  cmd = 0xB0 | (address & 0x07);
  ssd1306_tx_rx(SSD1306_WR_CMD, &cmd, 1);
}

// Note: only used in page addressing mode
void ssd1306_set_column_address(uint8_t address) {
  uint8_t cmd[2];
  cmd[0] = 0x10 | (address >> 4);
  cmd[1] = address & 0x0F;
  ssd1306_tx_rx(SSD1306_WR_CMD, cmd, 2);
}

void ssd1306_set_horizontal_scroll(uint8_t left_horiz, uint8_t start, uint8_t end, uint8_t speed) {
  uint8_t cmd[7];
  cmd[0] = 0x26 | (left_horiz & 0x01); // Right or Left scrolling
  cmd[1] = 0x00; // Dummy
  cmd[2] = start & 0x07 ; // Start page address
  cmd[3] = speed & 0x07 ; // Time interval
  cmd[4] = end   & 0x07 ; // End page address
  cmd[5] = 0x00; // Dummy
  cmd[6] = 0xFF; // Dummy
  ssd1306_tx_rx(SSD1306_WR_CMD, cmd, 7);  
}

// TODO: vertical scroll

void ssd1306_set_scroll_enable(uint8_t scroll_en) {
  uint8_t cmd;

  cmd = 0x02E | (scroll_en & 0x01);
  ssd1306_tx_rx(SSD1306_WR_CMD, &cmd, 1); 
}

// -----------------------------------------------------------------------------
// POWER-UP / POWER-DOWN FUNCTIONS
// -----------------------------------------------------------------------------

// Power-up sequence
void ssd1306_power_up(void) {
  uint32_t delay;
  uint8_t cmd[8];

  // VDD is stable

  // Reset
  OLED_RESN = 1;    
  for(delay=50000; delay; delay--); // Fixme: nasty
  OLED_RESN = 0;
  for(delay=50000; delay; delay--);
  OLED_RESN = 1;
  for(delay=50000; delay; delay--);

  // Send Display OFF cmd
  ssd1306_set_display_on(0);

    // Set OSC frequency
  cmd[0] = 0xD5; cmd[1] = 0x80;
  ssd1306_tx_rx(SSD1306_WR_CMD, cmd, 2);

  // Set Mux Ratio
  cmd[0] = 0xA8; cmd[1] = 0x3F;
  ssd1306_tx_rx(SSD1306_WR_CMD, cmd, 2);

  // Display offset
  cmd[0] = 0xD3; cmd[1] = 0x00;
  ssd1306_tx_rx(SSD1306_WR_CMD, cmd, 2);

  // Charge pump (off): external supply
  cmd[0] = 0x8D; cmd[1] = 0x10;
  ssd1306_tx_rx(SSD1306_WR_CMD, cmd, 2);

  // Display start line
  cmd[0] = 0x40;
  ssd1306_tx_rx(SSD1306_WR_CMD, cmd, 1);

  // Normal display
  cmd[0] = 0xA6;
  ssd1306_tx_rx(SSD1306_WR_CMD, cmd, 1);
  
  // Disable entire display on
  cmd[0] = 0xA4;
  ssd1306_tx_rx(SSD1306_WR_CMD, cmd, 1);

  // Segment re-map
  cmd[0] = 0xA1;
  ssd1306_tx_rx(SSD1306_WR_CMD, cmd, 1);

  // COM Output scan direction
  cmd[0] = 0xC8;
  ssd1306_tx_rx(SSD1306_WR_CMD, cmd, 1);

  // COM Pins
  cmd[0] = 0xDA; cmd[1] = 0x12;
  ssd1306_tx_rx(SSD1306_WR_CMD, cmd, 2);

  // Contrast control
  //cmd[0] = 0x81; cmd[1] = 0x9F;
  //ssd1306_tx_rx(SSD1306_WR_CMD, cmd, 2);

  // Pre-charge period
  cmd[0] = 0xD9; cmd[1] = 0x22;
  ssd1306_tx_rx(SSD1306_WR_CMD, cmd, 2);

  // VCOMH Deselect level
  cmd[0] = 0xDB; cmd[1] = 0x20;
  ssd1306_tx_rx(SSD1306_WR_CMD, cmd, 2);

  // Page addressing mode
  cmd[0] = 0x20; cmd[1] = 0x02; // page
  ssd1306_tx_rx(SSD1306_WR_CMD, cmd, 2);

  // Delay > 3us
  for(delay=50000; delay; delay--); // Fixme
  
    // Power-on
  OLED_PWR_EN = 1;

  // Cleanup GDRAM
  ssd1306_clear_screen();

  // Send Display ON cmd
  ssd1306_set_display_on(1);

}

// Power-down sequence
void ssd1306_power_down(void) {
  uint32_t delay;
  ssd1306_set_display_on(0);
  for(delay=50000; delay; delay--); // Fixme
  OLED_PWR_EN = 0;
}

// -----------------------------------------------------------------------------
// DISPLAY FUNCTIONS
// -----------------------------------------------------------------------------

// Flush entirely the screen
void ssd1306_clear_screen(void) {

  uint16_t i;
  uint8_t data = 0x00;
  uint8_t* pBuffer = display_buffer;

  ssd1306_set_addressing_mode(SSD1306_ADDR_HORIZ);
  ssd1306_set_column_start_stop(0, OLED_WIDTH-1);
  ssd1306_set_page_start_stop(0, OLED_NB_PAGES-1);
  
  for(i = 0; i < OLED_WIDTH * OLED_NB_PAGES; i++, pBuffer++) {
      ssd1306_tx_rx(SSD1306_WR_DATA, &data, 1);
      *pBuffer = data;
  } // for i
}

void ssd1306_display_picture(const uint8_t pic[]) {

  uint16_t i;
  uint8_t j;
  uint8_t data;

  ssd1306_set_addressing_mode(SSD1306_ADDR_HORIZ);
  ssd1306_set_column_start_stop(0, OLED_WIDTH-1);
  ssd1306_set_page_start_stop(0, OLED_NB_PAGES-1);

  for(i = 0; i < 8; i++) {
    for(j = 0; j < 128; j++) {
      data = reversed_uint8[pic[128*i + j]] ^ 0xFF;
      ssd1306_tx_rx(SSD1306_WR_DATA, &data, 1);
    } // j
  } // i
}

void ssd1306_display_picture_from_bytes(const BYTE pic[]) {

  uint16_t i;
  uint8_t j;
  uint8_t data;

  ssd1306_set_addressing_mode(SSD1306_ADDR_HORIZ);
  ssd1306_set_column_start_stop(0, OLED_WIDTH-1);
  ssd1306_set_page_start_stop(0, OLED_NB_PAGES-1);

  for(i = 0; i < 8; i++) {
    for(j = 0; j < 128; j++) {
      data = reversed_uint8[pic[128*i + j]];
      ssd1306_tx_rx(SSD1306_WR_DATA, &data, 1);
    } // j
  } // i
}

// Draw a character at the given position
void ssd1306_draw_char(unsigned char c, uint8_t x, uint8_t line,  uint8_t bg) {

  uint8_t col_idx;
  uint8_t line_value;

  if((x + SSD1306_FONT_WIDTH+1 >= OLED_WIDTH)  || // Clip right
     (line >= OLED_NB_PAGES))                     // Clip bottom
    return;

  ssd1306_set_addressing_mode(SSD1306_ADDR_HORIZ);
  ssd1306_set_column_start_stop(x, x + SSD1306_FONT_WIDTH+1);
  ssd1306_set_page_start_stop(line, line);

  // Sweep the font horizontally
  for(col_idx = 0; col_idx <= SSD1306_FONT_WIDTH+1; col_idx++) {

    if(col_idx >= SSD1306_FONT_WIDTH) {
      line_value = 0;
    } else {
      line_value = ssd1306_font[(c*SSD1306_FONT_WIDTH) + col_idx];
    }
    
    // Invert background if flag is set
    if(bg) {
      line_value ^= 0xFF;
    }

    ssd1306_tx_rx(SSD1306_WR_DATA, &line_value, 1);

  } // for(col_idx) 
}

// Our own customized printf. Start to print where ever the pointer is
void ssd1306_printf(char* line_str, uint8_t len, uint8_t bg, uint8_t start_line, uint8_t start_col) {

  uint8_t idx_line;
  uint8_t idx_col;
  uint8_t idx_str;

  if(len > OLED_NB_PAGES * OLED_NB_CHAR_PER_LINE)
    return;

  if(start_line >= OLED_NB_PAGES)
    return;

  if(start_col >= OLED_NB_CHAR_PER_LINE)
    return;

  idx_col = start_col * (SSD1306_FONT_WIDTH+1);
  idx_line = start_line;

  for(idx_str = 0; idx_str < len; idx_str++) {

    // Handles carriage return
    if(line_str[idx_str] == '\n' || line_str[idx_str] == '\r') {
      if(idx_line < OLED_NB_PAGES) {

        // Cleanup the rest of the line
        while(idx_col+=(SSD1306_FONT_WIDTH+1) < OLED_NB_CHAR_PER_LINE) {
          ssd1306_draw_char(' ', idx_col, idx_line, bg);
        }
        
        idx_line++;
        idx_col = 0;
        
      // Cannot add any new line!
      } else {
        return;
      }

    // Normal print-out
    } else {
      ssd1306_draw_char(line_str[idx_str], idx_col, idx_line, bg);

      idx_col+=(SSD1306_FONT_WIDTH+1);

      // Handles automatic end-of-line
      if(idx_col > OLED_WIDTH - (SSD1306_FONT_WIDTH+1)) {
        idx_line++;
        idx_col = 0;
      }      
    }

  } // for idx_str

}

// Draw an horizontal line between (x1, y) and (x2, y) points (included)
// x2 must be larger than x1. Line can be black or white, depending on 'color'.
// Can be used to draw a point if x1 = x2 (but this is very ineficient!)
void ssd1306_draw_horizontal_line(uint8_t x1, uint8_t x2, uint8_t y, uint8_t color) {

  uint8_t y_page;
  uint8_t col_idx = x1;
  uint8_t data;

  // Check for out-of-boudaries exceptions
  if((x1 > OLED_WIDTH) || ((x2 > OLED_WIDTH)) || (x2 < x1) || (y > OLED_HEIGHT) )
    return;

  // Calculate vertical page to address and local y value within the page
  y_page = y >> 3;        // Page index
  y = y - (y_page << 3);  // Modulo

  // Write to the display in horizontal addressing mode
  // Start to write at column adress x1
  ssd1306_set_addressing_mode(SSD1306_ADDR_HORIZ);
  ssd1306_set_column_start_stop(x1, x2);
  ssd1306_set_page_start_stop(y_page, y_page);

  // For each column, calculate data value based on the screen content
  for(col_idx = x1; col_idx <= x2; col_idx++) {

    // Fetch current data
    data = display_buffer[y_page][col_idx];

    // Depending on the color, force a '1' or a '0'
    if(color == SSD1306_COLOR_WHITE)
      data |= (1 << y);
    else
      data &= ~(1 << y);

    // Save new data
    display_buffer[y_page][col_idx] = data;
  }

  // Actual data write to the screen    
  ssd1306_tx_rx(SSD1306_WR_DATA, &display_buffer[y_page][x1], x2 - x1 +1);
}

// Similar than draw_horizontal_line, but vertical!
void ssd1306_draw_vertical_line(uint8_t x, uint8_t y1, uint8_t y2, uint8_t color) {

  uint8_t y1_page;
  uint8_t y2_page;
  uint8_t y_mask;
  uint8_t page_idx;
  uint8_t data;

  // Local page buffer because display_buffer is organized in columns
  uint8_t page_buffer[OLED_NB_PAGES];
  
  // Check for out-of-boudaries exceptions
  if((y1 > OLED_HEIGHT) || ((y2 > OLED_HEIGHT)) || (y2 < y1) || (x > OLED_WIDTH) )
    return;

  // Calculate vertical page range to address and local y values within the pages
  y1_page = y1 >> 3;
  y1 = y1 - (y1_page << 3);
  y2_page = y2 >> 3;
  y2 = y2 - (y2_page << 3);

  // Write to the display in horizontal addressing mode
  // Start to write at column adress x
  ssd1306_set_addressing_mode(SSD1306_ADDR_HORIZ);
  ssd1306_set_column_start_stop(x, x);
  ssd1306_set_page_start_stop(y1_page, y2_page);

  // For each column, calculate data value based on the screen content
  for(page_idx = y1_page; page_idx <= y2_page; page_idx++) {

    // Fetch current data
    data = display_buffer[page_idx][x];

    // We need to compute a data mask for the current page, because
    // starting and ending pages data can be partially written.

    // Special case: line is smaller than 1 page
    if(y1_page == y2_page) {

      // Set all bits to 1 except the 'y1' first LSBs
      y_mask = ~((1 << y1) - 1);

      // Clear all 'y2' last MSBs
      y_mask &= (1 << y2) - 1;

    // Starting page
    } else if(page_idx == y1_page) {
        y_mask = ~((1 << y1) - 1);

    // Ending page
    } else if(page_idx == y2_page) {
      y_mask = (1 << y2) - 1;

    // Internal pages: all values are written
    } else {
      y_mask = 0xFF;
    }
    
    // Depending on the color, force a '1' or a '0'
    if(color)
      data |= y_mask;
    else
      data &= ~y_mask;

    // Save new data
    display_buffer[page_idx][x] = data;
    page_buffer[page_idx] = data;
  }

  // Actual data write to the screen
  ssd1306_tx_rx(SSD1306_WR_DATA, &page_buffer[y1_page], y2_page - y1_page +1);

}

