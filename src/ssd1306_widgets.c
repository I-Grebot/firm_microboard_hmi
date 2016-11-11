/* -----------------------------------------------------------------------------
 * microBoard - HMI
 * I-Grebot HMI interface
 * -----------------------------------------------------------------------------
 * File        : ssd1306_widgets.c
 * Language    : C
 * Author      : Paul M.
 * Creation    : 2016-02-28
 * -----------------------------------------------------------------------------
 * Description:
 *   This module contains widgets (= graphical features) for the SSD1306 library
 *   Each widget get the following things:
 *     - A configuration/processing structure that contains all variables
 *     - An initializer function
 *     - A processing function (non-blocking) that is used for refreshing the
 *       widget's state
 * -----------------------------------------------------------------------------
 * Versionning informations
 * Repository: http://svn2.assembla.com/svn/paranoid_android/
 * -----------------------------------------------------------------------------
 * $Rev:: 1369                                                                 $
 * $LastChangedBy:: Ldoppea                                                    $
 * $LastChangedDate:: 2015-05-12 13:29:03 +0200 (mar., 12 mai 2015)            $
 * -----------------------------------------------------------------------------
 * Version     Comment                                   Author       Date
 * 1.0         Creation - split from ssd1306.c           Paul M.      2016-02-28
 * -----------------------------------------------------------------------------
 */

#include "microBoard_hmi.h"

// -----------------------------------------------------------------------------
// PRIVATE PROTOTYPES
// -----------------------------------------------------------------------------

static uint32_t log2(uint32_t v);

// -----------------------------------------------------------------------------
// PLOT 1D_TIME WIDGET
// -----------------------------------------------------------------------------

// Initialize a signed 16b 2D plot
void ssd1306_int16_plot_init(ssd1306_int16_plot_t* plot) {

  uint8_t nb_char;
  char str[OLED_NB_CHAR_PER_LINE];

  // Allocate memory for the data fifo
  plot->data_fifo = fifo_new(SSD1306_PLOT_FIFO_SIZE, sizeof(int16_t));

  // Could not allocate memory
  if(!plot->data_fifo)
    return;

  // Initialize plot variables
  plot->min = INT16_MAX; // So the 1st "min" function will always update correctly
  plot->max = INT16_MIN;
  plot->avg = 0;
  plot->acc = 0;

  if(plot->y_axis_auto) {
    plot->y_axis_max = plot->max + 1;
    plot->y_axis_min = plot->min - 1;
  }

  // Initialize graphics
  ssd1306_clear_screen();

  // Draw Y axis vertical line (it is removed du to printf()
  ssd1306_draw_vertical_line(SSD1306_PLOT_X_DATA_START+1,
                             SSD1306_PLOT_Y_DATA_START, SSD1306_PLOT_Y_DATA_END, 1);

  // Draw X axis upper and lower horizontal lines
  ssd1306_draw_horizontal_line(0, SSD1306_PLOT_X_DATA_END,
                               SSD1306_PLOT_Y_DATA_START, 1);
  ssd1306_draw_horizontal_line(SSD1306_PLOT_X_DATA_START, SSD1306_PLOT_X_DATA_END,
                               SSD1306_PLOT_Y_DATA_END, 1);

  // Print-out plot's title
  nb_char = sprintf(str, "%s", plot->title);
  if(nb_char > SSD1306_PLOT_NAME_SIZE)
    nb_char = SSD1306_PLOT_NAME_SIZE;

  ssd1306_printf(str, nb_char, 0, SSD1306_PLOT_Y_TITLE, SSD1306_PLOT_X_TITLE);

  // Print-out Min/Max/Avg texts
  nb_char = sprintf(str, " Min  ");
  ssd1306_printf(str, nb_char, 1, SSD1306_PLOT_Y_MIN_TEXT, SSD1306_PLOT_X_DATA);
  nb_char = sprintf(str, " Avg  ");
  ssd1306_printf(str, nb_char, 1, SSD1306_PLOT_Y_AVG_TEXT, SSD1306_PLOT_X_DATA);
  nb_char = sprintf(str, " Max  ");
  ssd1306_printf(str, nb_char, 1, SSD1306_PLOT_Y_MAX_TEXT, SSD1306_PLOT_X_DATA);

}

// Process and redraw a 2D plot with a new incomming value
void ssd1306_int16_plot_process(ssd1306_int16_plot_t* plot) {

  uint8_t nb_char;
  char str[OLED_NB_CHAR_PER_LINE];
  uint8_t y_page;
  uint8_t page_idx;
  uint8_t fifo_idx;
  uint8_t buffer[SSD1306_PLOT_Y_DATA_NB_PAGES];
  int16_t data_value;
  uint8_t disp_data;
  volatile int16_t new_value;
  int32_t axis_trip ;
  float axis_factor;

  // Sample once and for all the new value (avoid disrumptices, might need to protect WR access! with mutex in some applications)
  new_value = *(plot->var);

  // If fifo is full, empty an old data
  if(FIFO_IS_FULL(plot->data_fifo)) {
    fifo_pull(plot->data_fifo, &data_value);
    plot->acc -= ((int32_t) data_value);
  }

  // Push a new value
  fifo_push(plot->data_fifo, ((void*) &new_value));
  plot->acc += ((int32_t) new_value);

  // Overflow might only happen for displays with more than 16384 columns...
  plot->avg = (int16_t) (plot->acc / plot->data_fifo->cnt);

  // Current value display: right-aligned on the same line of the title
  nb_char = sprintf(str, "%*d", 6, new_value);
  ssd1306_printf(str, nb_char, 0, SSD1306_PLOT_Y_CURRENT_VALUE, SSD1306_PLOT_X_CURRENT_VALUE);

  // Axis values display
  nb_char = sprintf(str, "%*d", 6, plot->max);
  ssd1306_printf(str, nb_char, 0, SSD1306_PLOT_Y_MAX_DATA, SSD1306_PLOT_X_DATA);
  nb_char = sprintf(str, "%*d", 6, plot->avg);
  ssd1306_printf(str, nb_char, 0, SSD1306_PLOT_Y_AVG_DATA, SSD1306_PLOT_X_DATA);
  nb_char = sprintf(str, "%*d", 6, plot->min);
  ssd1306_printf(str, nb_char, 0, SSD1306_PLOT_Y_MIN_DATA, SSD1306_PLOT_X_DATA);

  // Write to the display in horizontal addressing mode
  ssd1306_set_addressing_mode(SSD1306_ADDR_HORIZ);
  ssd1306_set_column_start_stop(SSD1306_PLOT_X_DATA_END + 1 - plot->data_fifo->cnt, SSD1306_PLOT_X_DATA_END);
  ssd1306_set_page_start_stop(SSD1306_PLOT_Y_DATA_START_PAGE, SSD1306_PLOT_Y_DATA_END_PAGE);

  // Handles Y axis auto-scale, depending on the current min/max value
  // We choose arbitrarly to pick the upper power of 2 as the axis min/max
  if(plot->y_axis_auto) {
    if(plot->min == 0) {
      plot->y_axis_min = 0;
    } else if(plot->min < 0) {
      plot->y_axis_min = -(1UL << (log2(-plot->min) + 1UL));
    } else {
      plot->y_axis_min =  (1UL << (log2(plot->min)));
    }

    if(plot->max == 0) {
      plot->y_axis_max = 0;
    } else if(plot->max < 0) {
      plot->y_axis_max = -(1UL << (log2(-plot->max)));
    } else {
      plot->y_axis_max =  (1UL << ((log2(plot->max) + 1UL)));
    }

  }

  // Compute some axis constants
  axis_trip = plot->y_axis_max - plot->y_axis_min;

  // Clamp axis trip to the display dynamic
  // Also prevent dividing by 0
  if(axis_trip < SSD1306_PLOT_Y_DATA_MAX) {
    axis_trip = SSD1306_PLOT_Y_DATA_MAX;
    plot->y_axis_max = plot->y_axis_min + (1 << (log2(SSD1306_PLOT_Y_DATA_MAX) + 1));
  }

  // Number of displayed pixels for 1 data LSB. This is always smaller than 1,
  // because we have clamped the axis trip's value.
  // Besides, it only requires a float mult operation for each data value.
  axis_factor = (float) SSD1306_PLOT_Y_DATA_MAX / axis_trip;

  // Re-init stats because it might not be up-to-date
  // (If we remove the max or min, we need to look up for a new one)
  plot->min = INT16_MAX;
  plot->max = INT16_MIN;

  // Re-draw all data, from oldest (fifo tail: left), to newest (fifo head: right)
  for(fifo_idx = 0; fifo_idx < plot->data_fifo->cnt; fifo_idx++) {
    data_value = *((int16_t*) fifo_get_element(plot->data_fifo, fifo_idx));

    // Compute min/max statistics
    if(data_value > plot->max)
      plot->max = data_value;
    if(data_value < plot->min)
      plot->min = data_value;

    // Clamp data-value if it is out of axis boundaries
    if(data_value > plot->y_axis_max)
      data_value = plot->y_axis_max;
    else if(data_value < plot->y_axis_min)
      data_value = plot->y_axis_min;

    // Scale data according to axis
    disp_data = (uint8_t) (((float) data_value - plot->y_axis_min) * axis_factor);

    // "0" is at the bottom by convention
    // We also need to shift by 1 in order not to overwrite the bottom H line
    disp_data = SSD1306_PLOT_Y_DATA_MAX - disp_data + SSD1306_PLOT_Y_DATA_OFFSET;

    // Calculate page of the data to display
    y_page = (disp_data >> 3);

    // Go through all pages to write the data
    for(page_idx = 0; page_idx < SSD1306_PLOT_Y_DATA_NB_PAGES; page_idx++) {
      if(page_idx == y_page) {
        buffer[page_idx] = 1 << (disp_data - (y_page << 3));
        if(plot->color)
          buffer[page_idx] = ~buffer[page_idx];
      } else {
        buffer[page_idx] = plot->color? 0xFF : 0x00;
      }
    } // for page_idx

    // Ensure H lines are not overwritten
    // Avoid flicker due to axis values
    if((fifo_idx > 7*SSD1306_FONT_WIDTH + 2) || !(plot->disp_axis_values)) {
      buffer[0] |= 0x01;
      buffer[SSD1306_PLOT_Y_DATA_NB_PAGES-1] |= 0x80;
    }

    // Write an entire data-column
    ssd1306_tx_rx(SSD1306_WR_DATA, buffer, SSD1306_PLOT_Y_DATA_NB_PAGES);

  } // for fifo_idx

  // Draw axis min/max values
  if(plot->disp_axis_values) {
    nb_char = sprintf(str, "%-*ld", 6, plot->y_axis_max);
    ssd1306_printf(str, nb_char, 0, SSD1306_PLOT_Y_MAX_AXIS, SSD1306_PLOT_X_AXIS + 1);
    nb_char = sprintf(str, "%-*ld", 6, plot->y_axis_min);
    ssd1306_printf(str, nb_char, 0, SSD1306_PLOT_Y_MIN_AXIS, SSD1306_PLOT_X_AXIS + 1);
  }

}

// -----------------------------------------------------------------------------
// DIGITAL GAUGE WIDGET
// -----------------------------------------------------------------------------

void ssd1306_widg_dig_gauge_init(ssd1306_widg_dig_gauge_t* gauge) {

  uint8_t nb_char;
  char str[OLED_NB_CHAR_PER_LINE];

  // Save init value
  gauge->init_value = *(gauge->var);

  // Initialize graphics
  ssd1306_clear_screen();

  // Print-out gauge's title
  nb_char = sprintf(str, "%s", gauge->title);
  if(nb_char > SSD1306_WIDG_DIG_GAUGE_NAME_SIZE)
    nb_char = SSD1306_WIDG_DIG_GAUGE_NAME_SIZE;

  ssd1306_printf(str, nb_char, 0, SSD1306_WIDG_DIG_GAUGE_Y_TITLE, SSD1306_WIDG_DIG_GAUGE_X_TITLE);

  // Print-out save & cancel info buttons
  nb_char = sprintf(str, "ENTER:   Save");
  ssd1306_printf(str, nb_char, 0, SSD1306_WIDG_DIG_GAUGE_Y_ENTER, SSD1306_WIDG_DIG_GAUGE_X_ENTER);

  nb_char = sprintf(str, "RETURN:  Cancel");
  ssd1306_printf(str, nb_char, 0, SSD1306_WIDG_DIG_GAUGE_Y_RETURN, SSD1306_WIDG_DIG_GAUGE_X_RETURN);

  // Print the gauge bar frame
  ssd1306_draw_horizontal_line(SSD1306_WIDG_DIG_GAUGE_X_START_BAR-2, SSD1306_WIDG_DIG_GAUGE_X_END_BAR+2,
    SSD1306_WIDG_DIG_GAUGE_Y_BAR*SSD1306_PAGE_HEIGHT-2, SSD1306_COLOR_WHITE);
  ssd1306_draw_horizontal_line(SSD1306_WIDG_DIG_GAUGE_X_START_BAR-2, SSD1306_WIDG_DIG_GAUGE_X_END_BAR+2,
    (SSD1306_WIDG_DIG_GAUGE_Y_BAR+1)*SSD1306_PAGE_HEIGHT+1, SSD1306_COLOR_WHITE);
  ssd1306_draw_vertical_line(SSD1306_WIDG_DIG_GAUGE_X_START_BAR-2, SSD1306_WIDG_DIG_GAUGE_Y_BAR*SSD1306_PAGE_HEIGHT-2,
    (SSD1306_WIDG_DIG_GAUGE_Y_BAR+1)*SSD1306_PAGE_HEIGHT+1, SSD1306_COLOR_WHITE);
  ssd1306_draw_vertical_line(SSD1306_WIDG_DIG_GAUGE_X_END_BAR+2, SSD1306_WIDG_DIG_GAUGE_Y_BAR*SSD1306_PAGE_HEIGHT-2,
    (SSD1306_WIDG_DIG_GAUGE_Y_BAR+1)*SSD1306_PAGE_HEIGHT+1, SSD1306_COLOR_WHITE);
  
}

void ssd1306_widg_dig_gauge_process(ssd1306_widg_dig_gauge_t* gauge) {

  uint8_t nb_char;
  char str[OLED_NB_CHAR_PER_LINE];
  uint8_t idx;
  float gauge_ratio;
  uint8_t gauge_value;

  // Clamp value if out of bounds
  
  if(*(gauge->var) > gauge->high_bound)
    *(gauge->var) = gauge->high_bound;
  else if(*(gauge->var) < gauge->low_bound)
    *(gauge->var) = gauge->low_bound;

  // Check for low/high bound sanity
  if(gauge->high_bound == INT16_MIN)
    gauge->high_bound = INT16_MIN + 1;

  if(gauge->low_bound == INT16_MAX)
    gauge->low_bound = INT16_MAX - 1;

  if(gauge->low_bound >= gauge->high_bound)
    gauge->low_bound = gauge->high_bound - 1;

  // Print-out low/high boundaries
  nb_char = sprintf(str, "%-5d", gauge->low_bound);
  ssd1306_printf(str, nb_char, 0, SSD1306_WIDG_DIG_GAUGE_Y_VALUE, SSD1306_WIDG_DIG_GAUGE_X_LOW_BOUND);
  nb_char = sprintf(str, "%5d", gauge->high_bound);
  ssd1306_printf(str, nb_char, 0, SSD1306_WIDG_DIG_GAUGE_Y_VALUE, SSD1306_WIDG_DIG_GAUGE_X_HIGH_BOUND);

  // Print-out gauge value
  nb_char = sprintf(str, "%5d", *(gauge->var));
  ssd1306_printf(str, nb_char, 0, SSD1306_WIDG_DIG_GAUGE_Y_VALUE, SSD1306_WIDG_DIG_GAUGE_X_VALUE);

    // Calculate gauge ratio: number of displayed pixels per input unit
  if(gauge->high_bound - gauge->low_bound) // should be OK
    gauge_ratio =    (SSD1306_WIDG_DIG_GAUGE_X_END_BAR - SSD1306_WIDG_DIG_GAUGE_X_START_BAR)
                  / ((float) (gauge->high_bound - gauge->low_bound));
  else
    gauge_ratio = 0;
  
  // Scale gauge value to the screen
  gauge_value = (uint8_t) (((float) *(gauge->var)) * gauge_ratio);
  
  // Print the gauge bar itself
  for(idx = 0; idx < SSD1306_PAGE_HEIGHT; idx++) {
    ssd1306_draw_horizontal_line(SSD1306_WIDG_DIG_GAUGE_X_START_BAR, SSD1306_WIDG_DIG_GAUGE_X_START_BAR + gauge_value,
      SSD1306_WIDG_DIG_GAUGE_Y_BAR*SSD1306_PAGE_HEIGHT+idx, SSD1306_COLOR_WHITE);
    ssd1306_draw_horizontal_line(SSD1306_WIDG_DIG_GAUGE_X_START_BAR + gauge_value + 1, SSD1306_WIDG_DIG_GAUGE_X_END_BAR ,
      SSD1306_WIDG_DIG_GAUGE_Y_BAR*SSD1306_PAGE_HEIGHT+idx, SSD1306_COLOR_BLACK);
  }
  
}

// -----------------------------------------------------------------------------
// PRIVATE TOOLBOX
// -----------------------------------------------------------------------------

uint32_t log2(uint32_t v) {

  register uint32_t r; // result of log2(v) will go here
  register uint32_t shift;

  r =     (v > 0xFFFF) << 4; v >>= r;
  shift = (v > 0xFF  ) << 3; v >>= shift; r |= shift;
  shift = (v > 0xF   ) << 2; v >>= shift; r |= shift;
  shift = (v > 0x3   ) << 1; v >>= shift; r |= shift;
                                          r |= (v >> 1);
  return r;
}