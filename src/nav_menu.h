#ifndef __LCD_MENU
#define __LCD_MENU

#include "microBoard_hmi.h"

// -----------------------------------------------------------------------------
// MENU DEFINITIONS & MACROS
// -----------------------------------------------------------------------------

// Maximum length of a name for the menu
#define MENU_NAME_MAX_SIZE       250    // 255 with 5 characters reserved

// Maximum amount of sub-menus per node
#define MENU_MAX_SUB_ITEMS       100

// Returns non-zero if a node (menu_item) is a leaf
#define MENU_IS_NODE_LEAF(_pn) ((_pn)->nb_sub == 0)

// Position after we start to scroll up/down in order to make next items visible
#define MENU_START_SCROLL_IDX     (OLED_NB_PAGES/2)

// Character to be used for current selection
#define MENU_SELECT_CHAR        ">"

// Number of navigation ticks that is required to move between menus
#define MENU_SCROLL_THRESHOLD   2

// Horizontal scrolling states for long texts
#define MENU_H_SCROLL_LEFT          0
#define MENU_H_SCROLL_RIGHT         1
#define MENU_H_SCROLL_BLANK_RIGHT   2
#define MENU_H_SCROLL_BLANK_LEFT    3

// -----------------------------------------------------------------------------
// MENU STRUCTURE & ENUMERATIONS
// -----------------------------------------------------------------------------

// Defines a menu item. An item is a node on the menu graph, it can be
// a parent with a given amount of children (sub-menus) or a leaf (end item).
// "Entering" a node menu triggers different actions:
//   - Browse to the corresponding sub-menus if the node is a parent
//   - Execute a callback function if the node is a leaf
// If a leaf's callback points to "NULL" function pointer, it is considered as
// dummy and nothing can happen (the menu browsing stay still).
typedef struct menu_item menu_item_t;

// Defines a menu item leaf configuration structure. This is required as leaf
// are linked to widgets/parameters that need to be passed to the corresponding
// handling menu function
typedef union {
    ssd1306_int16_plot_t plot_cfg;          // Plot 1D vs Time widget
    ssd1306_widg_dig_gauge_t dig_gauge_cfg; // Digital Gauge widget
} menu_leaf_cfg_t;

// Defines the "node" function callback prototype
// Each callback receive the parent node pointer as parameter.
// This allows to map different menu items on the same callback, which
// then forwards the menu-call to a different process.
typedef void (*menu_callback_f) (menu_item_t* item);

typedef struct menu_item {
    uint16_t            id;            // Unique ID
    char                name[MENU_NAME_MAX_SIZE];  // Name (displayed) of the menu item
    uint8_t             nb_sub;        // Number of sub-menus (children). =0 for a leaf
    menu_callback_f     leaf_callback; // Pointer to the leaf callback function
    menu_item_t*        parent;        // Pointer to the parent menu item (level above)
                                   // Only the root item does not have any parent
    menu_item_t*        prev;          // Pointer to the previous menu item at the same level
    menu_item_t*        next;          // Pointer to the next menu item at the same level
    menu_item_t*        sub_head;      // Pointer to 1st sub-menu item (level bellow)
    menu_item_t*        sub_tail;      // Pointer to last sub-menu item (level bellow)
    menu_leaf_cfg_t*    leaf_cfg;      // Leaf configuration parameters
};

// Menu configuration structure
typedef struct {
    uint8_t     scroll_speed;   // Scrolling speed for horizontal long texts
    uint16_t    scroll_blank;   // Blanking time for horizontal scrollings
} menu_cfg_t;

// Main place-holder for navigation menu variables
typedef struct {
    menu_item_t  root;               // Root item of the menu
    menu_item_t* current;            // Currently browsed parent menu item
    uint16_t     cur_h_scroll_idx;   // Name of current item H scroll index
    uint8_t      cur_h_scroll_state; // Used for Ping-Pong H scrolling!
    menu_item_t* nav_item;           // Navigation item (current position)
    uint8_t      nav_idx;            // Navigation index (current index position)
    uint16_t     nav_h_scroll_idx;   // Navigation index's title horizontal scrolling index
    uint16_t     nb_items;           // Total count of items (node & leaf)
} menu_t;

// Posible menu actions
typedef enum {
    MENU_ACTION_NOTHING,
    MENU_ACTION_NEXT,
    MENU_ACTION_PREV,
    MENU_ACTION_ENTER,
    MENU_ACTION_RETURN
} menu_action_e;

// -----------------------------------------------------------------------------
// PROTOTYPES
// -----------------------------------------------------------------------------

void menu_init(void);
void menu_build(void);
void menu_free(void);
menu_leaf_cfg_t* menu_new_leaf_cfg(void);
menu_item_t* menu_add_item(menu_item_t* parent, char* name, menu_callback_f callback, menu_leaf_cfg_t* leaf_cfg);
void menu_manage(menu_action_e action);

void draw_electrical_monitoring(menu_item_t* item);
void menu_widget_plot2d(menu_item_t* item);
void menu_widget_digital_gauge(menu_item_t* item);

// ------------------------ OLD --------------------------

/*typedef struct MenuStructure
{	const char *text;
	unsigned char num_menupoints;
	unsigned char up;
	unsigned char down;
	unsigned char enter;
  	void ( *fp )( void );
	// unsigned char value;
} MenuEntry;
*/

// ***********************************************************************
// Variable declarations
// ***********************************************************************
//extern const MenuEntry menu[];

// ***********************************************************************
// Main functions
// ***********************************************************************
//extern void show_menu(void);
//extern void browse_menu(void);


// ***********************************************************************
// Functions called by menus
// ***********************************************************************
/*
extern void show_sd_card_error(void);
extern void show_start_procedure(void);
extern void draw_arduino(void);
extern void draw_electrical_monitoring(void);
extern void draw_igrebot(void);
extern void send_can_motion_goto(void);
extern void send_can_motion_set_speed(void);
extern void send_can_clap_cmd_open(void);
extern void send_can_clap_cmd_close(void);*/

#endif // __LCD_MENU