/* -----------------------------------------------------------------------------
 * microBoard - HMI
 * I-Grebot HMI interface
 * -----------------------------------------------------------------------------
 * File        : nav_menu.c
 * Language    : C
 * Author      : Paul M.
 * Creation    : 2016-02-06
 * -----------------------------------------------------------------------------
 * Description:
 *   See main module file for the full description.
 * -----------------------------------------------------------------------------
 * Versionning informations
 * Repository: http://svn2.assembla.com/svn/paranoid_android/
 * -----------------------------------------------------------------------------
 * $Rev:: 1369                                                                 $
 * $LastChangedBy:: Ldoppea                                                    $
 * $LastChangedDate:: 2015-05-12 13:29:03 +0200 (mar., 12 mai 2015)            $
 * -----------------------------------------------------------------------------
 * Version     Comment                                   Author       Date
 * 1.0         Initial release                           Paul M.      2016-01-06
 * -----------------------------------------------------------------------------
 */

#include "microBoard_hmi.h"

// -----------------------------------------------------------------------------
// GLOBALS
// -----------------------------------------------------------------------------

menu_cfg_t nav_menu_cfg;
menu_t nav_menu;
extern uint8_t sw_irq;

extern reg_config_t reg_config;

// -----------------------------------------------------------------------------
// INITIALIZERS
// -----------------------------------------------------------------------------

void menu_init(void) {

  // Initialize navigation menu configuration
  nav_menu_cfg.scroll_speed = 1; // Divider (2th power)
  nav_menu_cfg.scroll_blank = 30;

  // Initialize the root item
  nav_menu.root.id = 0;
  sprintf(nav_menu.root.name, MENU_ROOT_TITLE);
  nav_menu.root.parent = NULL;
  nav_menu.root.leaf_callback = NULL;

  nav_menu.root.nb_sub = 0;
  nav_menu.root.next = NULL;
  nav_menu.root.prev = NULL;
  nav_menu.root.sub_head = NULL;
  nav_menu.root.sub_tail = NULL;

  // Initialize the rest of the main menu structure
  nav_menu.nb_items = 1; // There is root!
  nav_menu.nav_idx = 0; // Initialized index to the root item
  nav_menu.cur_h_scroll_state = MENU_H_SCROLL_BLANK_RIGHT;
  nav_menu.nav_h_scroll_idx = 0;
  nav_menu.current = &nav_menu.root;
}

// Build the menu structure
void menu_build(void) {

  menu_item_t* menu;
  menu_leaf_cfg_t* leaf_cfg;

  // Add a menu and some children
  menu = menu_add_item(&nav_menu.root, "LED Adjustments", NULL, NULL);

  // Adjust Green brightness
  leaf_cfg = menu_new_leaf_cfg();
  sprintf(leaf_cfg->dig_gauge_cfg.title, "Green brightness");
  leaf_cfg->dig_gauge_cfg.low_bound  = 0;
  leaf_cfg->dig_gauge_cfg.high_bound = 30;
  leaf_cfg->dig_gauge_cfg.inc        = 1;
  leaf_cfg->dig_gauge_cfg.var = &reg_config.green_brightness;
  menu_add_item(menu, "Green LED brightness", menu_widget_digital_gauge, leaf_cfg);

  // Adjust Red brightness
  leaf_cfg = menu_new_leaf_cfg();
  sprintf(leaf_cfg->dig_gauge_cfg.title, "Red brightness");
  leaf_cfg->dig_gauge_cfg.low_bound  = 0;
  leaf_cfg->dig_gauge_cfg.high_bound = 10;
  leaf_cfg->dig_gauge_cfg.inc        = 1;
  leaf_cfg->dig_gauge_cfg.var = &reg_config.red_brightness;
  menu_add_item(menu, "Red LED brightness", menu_widget_digital_gauge, leaf_cfg);

  // Adjust Blue brightness
  leaf_cfg = menu_new_leaf_cfg();
  sprintf(leaf_cfg->dig_gauge_cfg.title, "Blue brightness");
  leaf_cfg->dig_gauge_cfg.low_bound  = 0;
  leaf_cfg->dig_gauge_cfg.high_bound = 50;
  leaf_cfg->dig_gauge_cfg.inc        = 1;
  leaf_cfg->dig_gauge_cfg.var = &reg_config.blue_brightness;
  menu_add_item(menu, "Blue LED brightness", menu_widget_digital_gauge, leaf_cfg);

  menu = menu_add_item(&nav_menu.root, "OLED", NULL, NULL);
  leaf_cfg = menu_new_leaf_cfg();
  sprintf(leaf_cfg->dig_gauge_cfg.title, "OLED Brightness");
  leaf_cfg->dig_gauge_cfg.low_bound  = 0;
  leaf_cfg->dig_gauge_cfg.high_bound = 255;
  leaf_cfg->dig_gauge_cfg.inc        = 5;
  leaf_cfg->dig_gauge_cfg.var = &reg_config.oled_contrast;
  menu_add_item(menu, "OLED Brightness", menu_widget_digital_gauge, leaf_cfg);

  menu = menu_add_item(&nav_menu.root, "Sound System", NULL, NULL);
  leaf_cfg = menu_new_leaf_cfg();
  sprintf(leaf_cfg->dig_gauge_cfg.title, "Buzzer frequency");
  leaf_cfg->dig_gauge_cfg.low_bound  = 20;
  leaf_cfg->dig_gauge_cfg.high_bound = 8000;
  leaf_cfg->dig_gauge_cfg.inc        = 20;
  leaf_cfg->dig_gauge_cfg.var = &reg_config.buzzer_frequency;
  menu_add_item(menu, "Buzzer freq. (Hz)", menu_widget_digital_gauge, leaf_cfg);

  leaf_cfg = menu_new_leaf_cfg();
  sprintf(leaf_cfg->dig_gauge_cfg.title, "Buzzer duty");
  leaf_cfg->dig_gauge_cfg.low_bound  = 0;
  leaf_cfg->dig_gauge_cfg.high_bound = 100;
  leaf_cfg->dig_gauge_cfg.inc        = 5;
  leaf_cfg->dig_gauge_cfg.var = &reg_config.buzzer_duty;
  menu_add_item(menu, "Buzzer duty (%)", menu_widget_digital_gauge, leaf_cfg);

  menu = menu_add_item(&nav_menu.root, "This is a very long menu with a lot of sub items", NULL, NULL);
  menu_add_item(menu, "Draw Electrical", draw_electrical_monitoring, NULL);
  menu_add_item(menu, "Bumpy ride", menu_widget_plot2d, NULL);

  menu_add_item(menu, "Long menu item 0", NULL, NULL);
  menu_add_item(menu, "Long menu item 1", NULL, NULL);
  menu_add_item(menu, "Long menu item 2 with a super long text", NULL, NULL);
  menu_add_item(menu, "Long menu item 3", NULL, NULL);
  menu_add_item(menu, "Long menu item 4", NULL, NULL);
  menu_add_item(menu, "Long menu item 5 with a super long text", NULL, NULL);
  menu_add_item(menu, "Long menu item 6", NULL, NULL);
  menu_add_item(menu, "Long menu item 7", NULL, NULL);
  menu_add_item(menu, "Long menu item 8", NULL, NULL);
  menu_add_item(menu, "Long menu item 9", NULL, NULL);
  menu_add_item(menu, "Long menu item 10 with a super long text", NULL, NULL);
  menu_add_item(menu, "Long menu item 11", NULL, NULL);
  
  nav_menu.nav_item = nav_menu.root.sub_head;
  
}

// TODO: cleanup all menu (remove all elements except root)
void menu_free(void) {

}

// Allocate memory to create a new leaf configuration
menu_leaf_cfg_t* menu_new_leaf_cfg(void) {
  return malloc(sizeof(menu_leaf_cfg_t));
}

// Add an item to a parent. The item is added at the end of the list.
menu_item_t* menu_add_item(menu_item_t* parent, char* name, menu_callback_f callback, menu_leaf_cfg_t* leaf_cfg) {

  menu_item_t* new_menu_item;

  // Allocate memory for the new item
  new_menu_item = malloc(sizeof(menu_item_t));

  // Check to see if that was successful
  if(new_menu_item == NULL)
    return NULL;

  // Check to see if parent is not full
  if(parent->nb_sub >= MENU_MAX_SUB_ITEMS)
    return NULL;

  // Defines new item parameters
  new_menu_item->id = (++nav_menu.nb_items);
  new_menu_item->nb_sub = 0;

  // Fill-up the new item from inputs, clamp name length if required
  strncpy(new_menu_item->name, name, MENU_NAME_MAX_SIZE);
  new_menu_item->parent = parent;
  new_menu_item->leaf_callback = callback;
  new_menu_item->leaf_cfg = leaf_cfg;

  // Update the pointer structures of the parent,
  // last item and new item!

  // Check to see if this is the 1st child for the parent
  if(parent->nb_sub == 0) {
    parent->sub_head = new_menu_item;
    new_menu_item->prev = NULL; // We are the first in line
  } else {
    new_menu_item->prev = parent->sub_tail;
    parent->sub_tail->next = new_menu_item;
  }

  // In any cases, update tail and other pointers  
  new_menu_item->next = NULL; // Because we are the last in the list
  parent->sub_tail = new_menu_item;

  // Finally increment the number of subs for the parent
  parent->nb_sub++;

  // Finally returns the new item
  return new_menu_item;
}

// Draw entirely the menu
// Clearing the screen might be needed. In order to limit flickering, this flush
// must be handled in the calling function (menu_manage() mostly).
void menu_draw(void) {

  uint8_t nb_char;
  char item_name_substr[OLED_NB_CHAR_PER_LINE]; // -1 due to select char but +1 for NULL terminator
  char str[OLED_NB_CHAR_PER_LINE+1]; // +1 for NULL terminator
  menu_item_t* item;
  uint8_t line_idx;
  uint8_t line_offset;
  uint16_t h_scroll_idx_max;
  
  // Display current menu item's title
  memset(str, ' ', sizeof(str)-1);
  str[sizeof(str)-1] = 0;

  // Get the length of the item name
  nb_char = strlen(nav_menu.current->name);

  // Check if horizontal scrolling is necessary
  if(nb_char < OLED_NB_CHAR_PER_LINE) {
    sprintf(str, " %s", nav_menu.current->name);
    ssd1306_printf(str, OLED_NB_CHAR_PER_LINE, SSD1306_COLOR_WHITE, 0, 0);
  } else {

    // Maximum value that can be reached for the horizontal scroll index
    // This corresponds to the last character of the title aligned on the right
    // side of the screen.
    h_scroll_idx_max = (nb_char - OLED_NB_CHAR_PER_LINE) << nav_menu_cfg.scroll_speed;
    
    // Mini FSM for handling horizontal scrolling of a long title text
    switch(nav_menu.cur_h_scroll_state) {

      // Text is moving from the left (to the right)
      case MENU_H_SCROLL_LEFT:
        strncpy(str, nav_menu.current->name + (nav_menu.cur_h_scroll_idx >> nav_menu_cfg.scroll_speed), sizeof(str)-1);
        if(nav_menu.cur_h_scroll_idx == 0) {
          nav_menu.cur_h_scroll_state = MENU_H_SCROLL_BLANK_RIGHT;
        } else {
          nav_menu.cur_h_scroll_idx--;
        }        
        break;

      // Text is moving from the right (to the left)
      case MENU_H_SCROLL_RIGHT:
        strncpy(str, nav_menu.current->name + (nav_menu.cur_h_scroll_idx >> nav_menu_cfg.scroll_speed), sizeof(str)-1);
        if(nav_menu.cur_h_scroll_idx >= h_scroll_idx_max) {
          nav_menu.cur_h_scroll_state = MENU_H_SCROLL_BLANK_LEFT;
          nav_menu.cur_h_scroll_idx = 0;
        } else {
          nav_menu.cur_h_scroll_idx++;
        }        
        break;

      // Blank time (wait), before going to SCROLL_LEFT state
      case MENU_H_SCROLL_BLANK_LEFT:
        strncpy(str, nav_menu.current->name + (nb_char - OLED_NB_CHAR_PER_LINE), sizeof(str)-1);
        if(nav_menu.cur_h_scroll_idx >= nav_menu_cfg.scroll_blank) {
          nav_menu.cur_h_scroll_idx = h_scroll_idx_max;
          nav_menu.cur_h_scroll_state = MENU_H_SCROLL_LEFT;
        } else {
          nav_menu.cur_h_scroll_idx++;
        }        
        break;

      // Blank time (wait), before going to SCROLL_RIGHT state
      default:
      case MENU_H_SCROLL_BLANK_RIGHT:
        strncpy(str, nav_menu.current->name, sizeof(str)-1);
        if(nav_menu.cur_h_scroll_idx >= nav_menu_cfg.scroll_blank) {
          nav_menu.cur_h_scroll_idx = 0;
          nav_menu.cur_h_scroll_state = MENU_H_SCROLL_RIGHT;
        } else {
          nav_menu.cur_h_scroll_idx++;
        }        
        break;
    }
    str[sizeof(str)-1] = 0;
    
    ssd1306_printf(str, OLED_NB_CHAR_PER_LINE, SSD1306_COLOR_WHITE, 0, 0);
  }

  // Drawing the OLED_NB_PAGES -1 (due to title) sub items
  // Different cases arise:
  // 1. nav_menu.nav_idx < MENU_START_SCROLL_IDX:
  //    The index is within the 1st items and we haven't start to scroll.
  //    Draw all items from the 1st, up to OLED_NB_PAGES-1.
  // 2. MENU_START_SCROLL_IDX <= nav_menu.nav_idx < (nav_menu.current->nb_sub - MENU_START_SCROLL_IDX)
  //    The index is after the scrolling index so we have started to scroll
  //    (1st items in the list are not visible anymore), but the last visible item is
  //    not the last item in the list (there is more).
  //    In this case when scrolling up/down, the nav_idx does not move and stay at the
  //    same position until it goes to case 1) or 3)
  // 3. nav_menu.nav_idx >= (nav_menu.current->nb_sub - MENU_START_SCROLL_IDX)
  //    Last OLED_NB_PAGE-1 items are drawn.

  // 1st pass: look for 1st item in the list to be displayed
  item = nav_menu.current->sub_head;
  line_offset = 0;
  if(nav_menu.nav_idx < MENU_START_SCROLL_IDX) {
    // nothing
  } else if((nav_menu.nav_idx >= MENU_START_SCROLL_IDX)
    && (nav_menu.nav_idx < (nav_menu.current->nb_sub - MENU_START_SCROLL_IDX))) {
    while(line_offset <= nav_menu.nav_idx - MENU_START_SCROLL_IDX) {
      item = item->next;
      line_offset++;
    }
  } else if(nav_menu.nav_idx >= (nav_menu.current->nb_sub - MENU_START_SCROLL_IDX)) {
    while(line_offset <= nav_menu.current->nb_sub - OLED_NB_PAGES) {
      item = item->next;
      line_offset++;
    }
  }

  // 2nd pass: actual drawing of items subset
  line_idx = 0;
  while(item != NULL && (line_idx < OLED_NB_PAGES-1)) {

    // Print the select character or nothing
    ssd1306_printf((line_offset + line_idx == nav_menu.nav_idx)?MENU_SELECT_CHAR:" ", 1, SSD1306_COLOR_BLACK, line_idx+1, 0);

    // TODO: horizontal scrolling    
    strncpy(item_name_substr, item->name, sizeof(item_name_substr)); // -1 due to the select char
    item_name_substr[sizeof(item_name_substr)-1] = 0;
    
    ssd1306_printf(item_name_substr, OLED_NB_CHAR_PER_LINE-1, SSD1306_COLOR_BLACK, line_idx+1, 1);

    //nb_char = sprintf(str, "%c%s", (line_offset + line_idx == nav_menu.nav_idx)?MENU_SELECT_CHAR:' ', item_name_substr);

    
    //ssd1306_printf(str, nb_char, SSD1306_COLOR_BLACK, line_idx+1, 0);
    item = item->next;
    line_idx++;
  }
 
}

void menu_manage(menu_action_e action) {

  uint32_t cnt;
  
  switch(action) {

    // Update current selection (if possible)
    case MENU_ACTION_NEXT:
      if(nav_menu.nav_idx < nav_menu.current->nb_sub-1) {
        nav_menu.nav_idx++;
        nav_menu.nav_item = nav_menu.nav_item->next;
      }
      break;

    case MENU_ACTION_PREV:
      if(nav_menu.nav_idx > 0) {
        nav_menu.nav_idx--;
        nav_menu.nav_item = nav_menu.nav_item->prev;        
      }
      break;

    case MENU_ACTION_ENTER:

      // Node, enter sub-menu
      if(nav_menu.nav_item->nb_sub > 0) {
        nav_menu.current = nav_menu.nav_item;
        nav_menu.nav_idx = 0;
        nav_menu.nav_item = nav_menu.current->sub_head;
        nav_menu.cur_h_scroll_state = MENU_H_SCROLL_BLANK_RIGHT;
                
      // Leaf with a callback
      } else if(nav_menu.nav_item->leaf_callback != NULL) {

        // Callback
        (nav_menu.nav_item->leaf_callback)(nav_menu.nav_item);

        // What to do when we return from it?
        // -- nothing!
      }
      // Else: leaf without callback, do nothing

      ssd1306_clear_screen();
      break;

    case MENU_ACTION_RETURN:
      // Only return when current item is not root
      if(nav_menu.current != &nav_menu.root) {
        nav_menu.current = nav_menu.current->parent;
        nav_menu.nav_idx = 0;
        nav_menu.nav_item = nav_menu.current->sub_head;
        nav_menu.cur_h_scroll_state = MENU_H_SCROLL_BLANK_RIGHT;
      }
      
      ssd1306_clear_screen();
      break;

    // Nothing to do!
    case MENU_ACTION_NOTHING:
    default:
      break;
  }

  if(action != MENU_ACTION_NOTHING) {
    //ssd1306_clear_screen();
    //menu_draw();
  }

  // Always re-draw (necessary for dynamic displays)
  menu_draw();

}

void draw_electrical_monitoring(menu_item_t* item) {
  int nb_char = 0;
  char oled_string[OLED_NB_CHAR_PER_LINE * OLED_NB_PAGES];

  //if (1 == must_redraw) {

        ssd1306_clear_screen();

        nb_char = sprintf(oled_string, "o---  ELECTRICAL ---o");
        ssd1306_printf(oled_string, nb_char, 1, 0, 0);

        nb_char = sprintf(oled_string, " BAT  ");
        ssd1306_printf(oled_string, nb_char, 1, 1, 0);
        nb_char = sprintf(oled_string, " %3d W  %1.2f A", 123,  4.56);
        ssd1306_printf(oled_string, nb_char, 0, 1, 7);

        nb_char = sprintf(oled_string, " C1/2 ");
        ssd1306_printf(oled_string, nb_char, 1, 2, 0);
        nb_char = sprintf(oled_string, "%1.2f V  %1.2f V", 3.81, 3.77);
        ssd1306_printf(oled_string, nb_char, 0, 2, 7);

        nb_char = sprintf(oled_string, " C3/4 ");
        ssd1306_printf(oled_string, nb_char, 1, 3, 0);
        nb_char = sprintf(oled_string, "%1.2f V  %1.2f V", 3.71, 3.97);
        ssd1306_printf(oled_string, nb_char, 0, 3, 7);

        nb_char = sprintf(oled_string, " C5/6 ");
        ssd1306_printf(oled_string, nb_char, 1, 4, 0);
        nb_char = sprintf(oled_string, "%1.2f V  %1.2f V", 4.01, 4.00);
        ssd1306_printf(oled_string, nb_char, 0, 4, 7);

        nb_char = sprintf(oled_string, "IP1/2 ");
        ssd1306_printf(oled_string, nb_char, 1, 5, 0);
        nb_char = sprintf(oled_string, "%1.2f A  %1.2f A", 5.55, 6.66);
        ssd1306_printf(oled_string, nb_char, 0, 5, 7);

        nb_char = sprintf(oled_string, "IP3   ");
        ssd1306_printf(oled_string, nb_char, 1, 6, 0);
        nb_char = sprintf(oled_string, "%1.2f A", 7.77);
        ssd1306_printf(oled_string, nb_char, 0, 6, 7);

        nb_char = sprintf(oled_string, "IM1/2 ");
        ssd1306_printf(oled_string, nb_char, 1, 7, 0);
        nb_char = sprintf(oled_string, "%1.2f A  %1.2f A", 8.88, 9.99);
        ssd1306_printf(oled_string, nb_char, 0, 7, 7);


        while(!(sw_irq & IRQ_NAV_RET));
        //must_redraw = 0;
    //}

}

void menu_widget_plot2d(menu_item_t* item) {
  ssd1306_int16_plot_t plot;
  int16_t cnt;
  int8_t cnt_inc;
  int16_t nav_value;
  uint32_t delay;
  
  sprintf(plot.title, "Plot Test");
  
  plot.var = (int16_t*) &nav_value;
  plot.color = 0;
  plot.y_axis_auto = 1;
  plot.disp_axis_values = 0;

  ssd1306_int16_plot_init(&plot);
  cnt = 0;
  cnt_inc = 0;

  while(1) {
    for(delay=100000; delay; delay--);

    if(sw_irq & IRQ_NAV_RET) {
      sw_irq = 0;
      return;
    }

    nav_value = ((int16_t) nav_get_pos());

    // Ping-pong with amplitude controller!
    if(cnt <= -30*nav_value)
      cnt_inc = 1;
    else if(cnt >= 30*nav_value)
      cnt_inc = -1;

    cnt = cnt + 5*cnt_inc*nav_value;

    ssd1306_int16_plot_process(&plot);

  }
}

void menu_widget_digital_gauge(menu_item_t* item) {
  uint32_t delay;
  ssd1306_widg_dig_gauge_t* gauge = &item->leaf_cfg->dig_gauge_cfg;
  
  ssd1306_widg_dig_gauge_init(gauge);
  nav_set_pos(*(gauge->var) / gauge->inc);

  while(1) {
    for(delay=100000; delay; delay--);

    if(sw_irq & IRQ_NAV_RET) {
      sw_irq = 0;
      *(gauge->var) = gauge->init_value;
      led_rgb_set_intensity(reg_config.green_brightness, reg_config.red_brightness, reg_config.blue_brightness);
      buzzer_set_frequency((uint16_t) reg_config.buzzer_frequency);
      buzzer_set_duty_cycle((uint8_t) reg_config.buzzer_duty);
      ssd1306_set_contrast(reg_config.oled_contrast);
      return;
    }

    else if(sw_irq & IRQ_NAV_OK) {
      sw_irq = 0;
      led_rgb_set_intensity(reg_config.green_brightness, reg_config.red_brightness, reg_config.blue_brightness);
      buzzer_set_frequency((uint16_t) reg_config.buzzer_frequency);
      buzzer_set_duty_cycle((uint8_t) reg_config.buzzer_duty);
      ssd1306_set_contrast(reg_config.oled_contrast);
      return;
    }

    *(gauge->var) = ((int16_t) nav_get_pos()) * gauge->inc;
    ssd1306_widg_dig_gauge_process(gauge);

    led_rgb_set_intensity(reg_config.green_brightness, reg_config.red_brightness, reg_config.blue_brightness);
    buzzer_set_frequency((uint16_t) reg_config.buzzer_frequency);
    buzzer_set_duty_cycle((uint8_t) reg_config.buzzer_duty);
    ssd1306_set_contrast(reg_config.oled_contrast);
  }
  
}

// --------------------  [ OLD ] ------------------------------


/*
#include "nav_menu.h"
#include "board_cfg.h"
#include "microBoard_hmi.h"
#include "ssd1306.h"
#include "ff.h"
#include <stdio.h>

static unsigned char selected = 1; // Start with first entry (apart from header)
uint8_t must_redraw = 1;
uint8_t draw_function = 0;
uint8_t btn_ok_pressed;
uint8_t btn_cancel_pressed;

extern const uint8_t igrebot_logo[];
extern const uint8_t arduino_logo[];

//for draw_igrebot()
uint8_t igrebot_year = 1;
int32_t igrebot_previous_nav_value = 0;


const char menu_first[] = " Igrebotlogo";  	// 0

const char menu_000[] = " IGREBOT";  	// 0
const char menu_001[] = "  Favorites";          // 1
const char menu_002[] = "  CAN messages";	// 2
const char menu_003[] = "  Robot maintenance";  // 3
const char menu_004[] = "  Funny actions";	// 4
const char menu_005[] = "  return";  		// 6

const char menu_100[] = " FAVORITES";              // 6
//const char menu_101[] = "  Clean wheels";           // 7
const char menu_101[] = "  Start procedure";        // 7
const char menu_102[] = "  Reset robot";            // 8
const char menu_103[] = "  Enable/Disable logs";    // 9
const char menu_104[] = "  return";                 // 10

const char menu_200[] = " CAN MESSAGES";      // 11
const char menu_201[] = "  motion_goto";  	// 12
const char menu_202[] = "  motion_set_speed";  	// 13
const char menu_203[] = "  clap_cmd open";  	        // 14
const char menu_204[] = "  clap_cmd close";  	// 15
const char menu_205[] = "  Option205";  	// 16
const char menu_206[] = "  Option206";  	// 17
const char menu_207[] = "  Option207";  	// 18
const char menu_208[] = "  return";  		// 19

const char menu_300[] = " ROBOT MAINTNANCE"; // 20
const char menu_301[] = "  Clean wheels";  	// 21
const char menu_302[] = "  return";  		// 22

const char menu_400[] = " FUNNY ACTIONS";     // 23
const char menu_401[] = "  Show IGrebot Logo";  // 24
const char menu_402[] = "  Show Arduino Logo";  // 25
const char menu_403[] = "  return";  		// 26


const MenuEntry menu[] =
{
    {menu_first, 1,  0,  0,  2,  draw_igrebot}, // 0

    {menu_000, 6,  0,  0,  0,  0}, // 1
    {menu_001, 6,  2,  3,  8,  0},
    {menu_002, 6,  2,  4, 13,  0},
    {menu_003, 6,  3,  5, 22,  0},
    {menu_004, 6,  4,  6, 25,  0},
    {menu_005, 6,  5,  6, 27,  0},

    {menu_100,  5, 0,  0,  0,  0}, // 7
    {menu_101,  5, 8,  9,  8,  draw_electrical_monitoring},//show_start_procedure},
    {menu_102,  5, 8,  10,  9,  0},
    {menu_103,  5, 9, 11,  10,  0},
    {menu_104,  5, 10, 11,  2,  0}, // 11

    {menu_200,  9,  0,  0,  0,  0}, // 12
    {menu_201,  9, 13, 14, 13,  send_can_motion_goto},
    {menu_202,  9, 13, 15, 14,  send_can_motion_set_speed},
    {menu_203,  9, 14, 16, 15,  send_can_clap_cmd_open},
    {menu_204,  9, 15, 17, 16,  send_can_clap_cmd_close},
    {menu_205,  9, 16, 18, 17,  0},
    {menu_206,  9, 17, 19, 18,  0},
    {menu_207,  9, 18, 20, 19,  0},
    {menu_208,  9, 19, 20,  3,  0}, // 20

    {menu_300,  3,  0,  0,  0,  0}, // 21
    {menu_301,  3, 22, 23, 22,  0},
    {menu_302,  3, 22, 23,  4,  0}, // 23

    {menu_400,  4,  0,  0,  0,  0}, // 24
    {menu_401,  4, 25, 26, 25,  draw_igrebot},
    {menu_402,  4, 25, 27, 26,  draw_arduino},
    {menu_403,  4, 26, 27,  5,  0}, // 27
};

// Draw the menu on screen
void show_menu(void)
{
    ssd1306_clear_screen();

    //OLED vars
    char oled_string[OLED_NB_CHAR_PER_LINE * OLED_NB_PAGES];
    int nb_char;

    //Menu vars
    unsigned char current_line;
    unsigned char from;
    unsigned char till = 0;

    unsigned char header_title_position;

     // Get beginning and end of current (sub)menu
    while (till <= selected)
    {
        till += menu[till].num_menupoints;
    }
    from = till - menu[selected].num_menupoints;
    till--;

    header_title_position = from;

    current_line = 1; //line 0 is for the header

    // Write header
    nb_char = sprintf(oled_string, "                    ");
    if(nb_char > 0)
    {
        ssd1306_printf(oled_string, nb_char, 1, 0, 0);
    }

    nb_char = sprintf(oled_string, menu[header_title_position].text);
    if(nb_char > 0)
    {
        ssd1306_printf(oled_string, nb_char, 1, 0, 0);
    }

    // Output formatting for selection somewhere in between (sub)menu top and bottom
    if ( (selected >= (from + UPPER_SPACE)) && (selected <= (till - LOWER_SPACE)) )
    {
        from = selected - (UPPER_SPACE - 1);
        till = from + (DISPLAY_ROWS - 2);

        for (from; from<=till; from++)
        {
            nb_char = sprintf(oled_string, menu[from].text);
            if(nb_char > 0) 
            {
                ssd1306_printf(oled_string, nb_char, 0, current_line, 0);
            }

            current_line++;
        }
	
        nb_char = sprintf(oled_string, SELECTION_CHAR);
        if(nb_char > 0) 
        {
            ssd1306_printf(oled_string, nb_char, 0, UPPER_SPACE, 0);
        }
    }

    // Output formatting for selection close to (sub)menu top and bottom
    // (distance between selection and top/bottom defined as UPPER- and LOWER_SPACE)
    else
    {
        // Top of (sub)menu
        if (selected < (from + UPPER_SPACE))
        {
            from += 1;

            if(till > from + (DISPLAY_ROWS - 2))
            {
                till = from + (DISPLAY_ROWS - 2);
            }

            for (from; from<=till; from++)
            {

                nb_char = sprintf(oled_string, menu[from].text);
                if(nb_char > 0) 
                {
                    ssd1306_printf(oled_string, nb_char, 0, current_line, 0);
                }

                if (from == selected)
                {
                    nb_char = sprintf(oled_string, SELECTION_CHAR);
                    if(nb_char > 0) 
                    {
                        ssd1306_printf(oled_string, nb_char, 0, current_line, 0);
                    }
                }

                current_line++;
            }
        }
        else if (selected > (till - LOWER_SPACE))
        {
            if (from < till - (DISPLAY_ROWS - 2))
            {
                from = till - (DISPLAY_ROWS - 2);
            }

            if (from <= header_title_position)
            {
                from = header_title_position + 1;
            }

            for (from; from<=till; from++)
            {

                nb_char = sprintf(oled_string, menu[from].text);
                if(nb_char > 0) 
                {
                    ssd1306_printf(oled_string, nb_char, 0, current_line, 0);
                }

                if (from == selected)
                {
                    nb_char = sprintf(oled_string, SELECTION_CHAR);
                    if(nb_char > 0) 
                    {
                        ssd1306_printf(oled_string, nb_char, 0, current_line, 0);
                    }
                }

                current_line++;
            }
        }
    }
}
FIL FileNav[2];
// Browse contains the main loop for managing menus
void browse_menu(void)
{
  uint32_t idx;
  int32_t nav_value;
  int32_t previous_nav_value;

  btn_ok_pressed = 0;
  btn_cancel_pressed = 0;

  pwm_disable();

  create_new_log_folder();
  log_string_with_date("test with date\n");
  log_string_with_date("test with date\n");

    for(idx=10000000; idx; idx--);
  log_string_with_date("test with date\n");
  log_string_with_date("test with date\n");
  log_string_with_date("test with date\n");
  log_string_with_date("test with date\n");
  log_string_with_date("test with date\n");
  log_string_with_date("test with date\n");
  log_string_with_date("test with date\n");
  log_string_with_date("test with date\n");
  log_string_with_date("test with date\n");
  log_string_with_date("test with date\n");
  log_string_with_date("test with date\n");
  log_string("test igrebot\n");
  log_string("test igrebot\n");
  log_string("test igrebot\n");
  log_string("test igrebot\n");
  log_string("test igrebot\n");
  log_string_delayed("test yannick\n");
  log_string("test igrebot\n");
  log_string_delayed("test yannick2\n");
  log_string("test igrebot2\n");
  log_string_delayed("test yannick3\n");

  create_new_log_file();
  log_string("test new file\n");
  log_string_delayed("test differed 1\n");
  log_string_delayed("test differed 2\n");
  log_string_delayed("test differed 3\n");
  log_string_delayed("test differed 4\n");
  log_string_delayed("test differed 5\n");
  log_string_delayed("test differed 6\n");
  log_string_delayed("test differed 7\n");
  log_string_delayed("test differed 8\n");
  log_string_delayed("test differed 9\n");
  log_string_delayed("test differed 10\n");
  log_string_delayed("test differed 11\n");
  log_string_delayed("test differed 12\n");
  //get_new_log_id();

  ssd1306_clear_screen();
  while(0x2A)
  {
      //printf("TestYannick2\n");
    nav_value = nav_get_pos();

    // CAN RX Fifos
    //do_can_rx();
    //do_uart_rx();

    do_update_buzzer();

    // Basic delay
    for(idx=100000; idx; idx--);

    if(previous_nav_value < nav_value - NAVIGATION_SENSITIVITY_REDUCE) // next
    {
        if (0 == draw_function)
        {
            selected = menu[selected].down;
        }

        previous_nav_value = nav_value;
        must_redraw = 1;
    }

    if(previous_nav_value > nav_value + NAVIGATION_SENSITIVITY_REDUCE) // previous
    {
        if (0 == draw_function)
        {
            selected = menu[selected].up;
        }
        
        previous_nav_value = nav_value;
        must_redraw = 1;
    }

    if(0 != btn_ok_pressed)
    {
        if (0 == draw_function)
        {
            btn_ok_pressed = 0;

            if (menu[selected].fp != 0 && 0 != selected)
            {
                draw_function = 1;
            }
            else
            {
                selected = menu[selected].enter;
            }
        }
        
        igrebot_year = 1;
        igrebot_previous_nav_value = nav_value;
        must_redraw = 1;
    }


    if(0 != btn_cancel_pressed)
    {
        btn_cancel_pressed = 0;
        must_redraw = 1;
        draw_function = 0;

        igrebot_year = 1;
        igrebot_previous_nav_value = nav_value;
    }

    if(menu[selected].fp != 0 && draw_function != 0 || 0 == selected)
    {
        //if(0 == sd_card_error())
        //{
            menu[selected].fp();
        //}
        //else
        //{
        //    show_sd_card_error();
        //}
    }
    else
    {
        if (1 == must_redraw)
        {
            //if(0 == sd_card_error())
            //{
                show_menu();
            }
            else
            {
                show_sd_card_error();
            }
//            get_new_log_id();

//            put_rc(f_open(&FileNav[0], "test.txt", (BYTE)FA_WRITE));
//            long p1;
//            p1 = f_size(&FileNav[0]);
//            //if (res != FR_OK) { put_rc(res); break; }
//
//            f_lseek(&FileNav[0], p1);
//
//            f_puts("test", &FileNav[0]);
//
//            xprintf("size : %lu\n", p1);
//
//            f_close(&FileNav[0]);

//            put_rc(f_open(&FileNav[0], "Pictures/igrebot_2016.bmp", (BYTE)FA_READ));
//            long p1;
//            p1 = f_size(&FileNav[0]);
//            printf("size : %lu", p1);
//
//            UINT bmp_header_size = 62;
//            UINT bmp_lcd_size = 1024;
//
//            f_lseek(&FileNav[0], bmp_header_size);
//
//            BYTE Buff[4096];
//            BYTE picture[1024];
//            UINT cnt;
//
//            f_read(&FileNav[0], Buff, bmp_lcd_size, &cnt);
////
//            printf("read bytes : %d\n", cnt);
//            UINT i = 0;
//            for(i = 0; i < bmp_lcd_size; i++)
//            {
//                picture[i] = Buff[i];
//                printf("byte %d : %d\n", i, Buff[i]);
//            }
////
//            f_close(&FileNav[0]);
//
//
//            ssd1306_clear_screen();
//
//            ssd1306_display_picture_from_bytes(picture);
////            ssd1306_display_picture(picture);
            
            must_redraw = 0;
        }
    }
  }
}



void show_sd_card_error(void)
{
    int nb_char = 0;
    char oled_string[OLED_NB_CHAR_PER_LINE * OLED_NB_PAGES];

    //ssd1306_clear_screen();

    //nb_char = sprintf(oled_string, "   Erreur Carte SD");
    //if(nb_char > 0) ssd1306_printf(oled_string, nb_char, 0, 2, 0);
}

uint8_t start_procedure_index = 0;
void show_start_procedure(void)
{
    if (1 == must_redraw)
    {
        int nb_char = 0;
        char oled_string[OLED_NB_CHAR_PER_LINE * OLED_NB_PAGES];

        ssd1306_clear_screen();

        //pagination
        if (0 != btn_ok_pressed)
        {
            start_procedure_index++;

            if(1<start_procedure_index)
            {
                start_procedure_index = 0;
            }
            btn_ok_pressed = 0;
        }

        switch(start_procedure_index)
        {
            case 0 :
                nb_char = sprintf(oled_string, "1 Positionner robot\n  dans la zone de\n  depart (calle)");
                if(nb_char > 0) ssd1306_printf(oled_string, nb_char, 0, 0, 0);

                nb_char = sprintf(oled_string, "2 Remettre la\n  puissance en\n  maintenant reset");
                if(nb_char > 0) ssd1306_printf(oled_string, nb_char, 1, 3, 0);

                nb_char = sprintf(oled_string, "...");
                if(nb_char > 0) ssd1306_printf(oled_string, nb_char, 0, 7, 0);
                break;

            case 1 :
                nb_char = sprintf(oled_string, "3 Choisir la couleur");
                if(nb_char > 0) ssd1306_printf(oled_string, nb_char, 0, 0, 0);

                nb_char = sprintf(oled_string, "4 Placer la tirette");
                if(nb_char > 0) ssd1306_printf(oled_string, nb_char, 1, 1, 0);

                nb_char = sprintf(oled_string, "...");
                if(nb_char > 0) ssd1306_printf(oled_string, nb_char, 0, 7, 0);
                break;
        }

        must_redraw = 0;
    }
}

void draw_arduino(void)
{
    if (1 == must_redraw)
    {
        ssd1306_clear_screen();
        ssd1306_display_picture(arduino_logo);

        must_redraw = 0;
    }
}


void draw_igrebot(void)
{
    if (1 == must_redraw)
    {
        int32_t nav_value;
        nav_value = nav_get_pos();

        if(igrebot_previous_nav_value < nav_value - NAVIGATION_SENSITIVITY_REDUCE) // next
        {
            igrebot_year++;
            if(2 < igrebot_year)
            {
                igrebot_year = 0;
            }
            igrebot_previous_nav_value = nav_value;
        }

        if(igrebot_previous_nav_value > nav_value + NAVIGATION_SENSITIVITY_REDUCE) // previous
        {
            igrebot_year--;

            if(0 > igrebot_year || 2 < igrebot_year)
            {
                igrebot_year = 2;
            }
            igrebot_previous_nav_value = nav_value;
        }

        BYTE picture[1024];

        if (igrebot_year == 1)
        {
            get_picture(&FileNav[0], picture, "Pictures/igrebot_2015.bmp");
        }
        else if (igrebot_year == 2)
        {
            get_picture(&FileNav[0], picture, "Pictures/igrebot_2016.bmp");
        }
        else
        {
            get_picture(&FileNav[0], picture, "Pictures/igrebot_2017.bmp");
        }

        ssd1306_clear_screen();

        ssd1306_display_picture_from_bytes(picture);

        must_redraw = 0;

        if(0 != btn_ok_pressed)
        {
            selected = menu[selected].enter;
            btn_ok_pressed = 0;
        }
    }
}

void send_can_motion_goto(void)
{
    //can_send_motion_goto(0, 0, 0);
    must_redraw = 1;
    draw_function = 0;
}

void send_can_motion_set_speed(void)
{
    if (1 == must_redraw)
    {
        ssd1306_clear_screen();

        int nb_char;
        char oled_string[OLED_NB_CHAR_PER_LINE * OLED_NB_PAGES];

        int32_t nav_value;
        nav_value = nav_get_pos();

        nb_char = sprintf(oled_string, "Value = %ld\n", nav_value);
        if(nb_char > 0) ssd1306_printf(oled_string, nb_char, 0, 0, 0);

        if(0 != btn_ok_pressed)
        {
            //can_send_motion_set_speed(nav_value,4);
            btn_ok_pressed = 0;
        }
    }
}

void send_can_clap_cmd_open(void)
{
    //can_send_clap_cmd(0x01, 0x01);
    must_redraw = 1;
    draw_function = 0;
}
void send_can_clap_cmd_close(void)
{
    //can_send_clap_cmd(0x02, 0x02);
    must_redraw = 1;
    draw_function = 0;
}
*/