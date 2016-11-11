#ifndef _BOARD_H_
#define _BOARD_H_

// This board is host on ROBOT1
#define __ROBOT1__

// Hardware main include
#include <p33Exxxx.h>

// Robot1 constants
//#include "robot1_system.h"

// Compiler related types
#include <stdint.h>
/*typedef unsigned char uint8_t ;
typedef signed   char int8_t ;
typedef signed   char sint8_t ;
typedef unsigned int  uint16_t;
typedef signed   int  int16_t;
typedef signed   int  sint16_t;
typedef unsigned long uint32_t;
typedef signed   long int32_t;
typedef signed   long sint32_t;*/

// -----------------------------------------------------------------------------
// FREQUENCIES DEFINITIONS
// -----------------------------------------------------------------------------

#define FOSC 64000000
#define FCY  (FOSC/2)

// -----------------------------------------------------------------------------
// PPS IO MACROS
// -----------------------------------------------------------------------------

#define UNLOCK_PPS {__builtin_write_OSCCONL(OSCCON & ~(1<<6)); \
                    while(OSCCONbits.IOLOCK);  }
#define LOCK_PPS   {__builtin_write_OSCCONL(OSCCON | (1<<6)); \
                    while(!OSCCONbits.IOLOCK); }

// -----------------------------------------------------------------------------
// BOARD & PERIPHERAL MAPPINGS
// -----------------------------------------------------------------------------

// SPI1 (master) SD Card & OLED Screen control (up to 25 MHz)
#define SPI1_SCK_TRIS    _TRISC3
#define SPI1_SCK         _LATC3

#define SPI1_MISO_TRIS   _TRISA9
#define SPI1_MISO        _RC3

#define SPI1_MOSI_TRIS   _TRISA4
#define SPI1_MOSI        _LATA4

// SPI2 (slave) Control interface from main board (up to 15 MHz)
#define SPI2_SCK_TRIS   _TRISB8     // CTRL_SCK -> RB8 (RP40)
#define SPI2_SSN_TRIS   _TRISB9     // CTRL_SSN -> RB9 (RP41)
#define SPI2_MISO_TRIS  _TRISB6     // CTRL_MISO -> RB6 (RP38)
#define SPI2_MOSI_TRIS  _TRISC5     // CTRL_MOSI -> RC5 (RPI53)

// IRQ GPIOs for Control interface
#define IRQ_IN_TRIS     _TRISB7     // CTRL_IRQ_IN  -> RB7 (RP39 / INT0)
#define IRQ_IN          _RB7

#define IRQ_OUT_TRIS    _TRISC8     // CTRL_IRQ_OUT -> RC8 (RP56)
#define IRQ_OUT         _LATC8

// CAN Interface for Legacy Igrebot's board
#define CAN_RX_TRIS     _TRISC7  // CAN_RX -> RC6
#define CAN_RX_RPIR     _C1RXR   // ECAN1 RX
#define CAN_RX_RPN      55       // RP54

#define CAN_TX_TRIS     _TRISC6  // CAN_RX -> RC7
#define CAN_TX_RPOR     _RP54R   // RP55
#define CAN_TX_PER      0x0E     // ECAN1 TX

//CAN as UART
#define DEBUG_CAN_UART_RX_TRIS _TRISA7   // UART_RX    mapped on RA8/RPI24
#define DEBUG_CAN_UART_RX_PIN  55
#define DEBUG_CAN_UART_TX_TRIS _TRISC6   // UART_TX    mapped on RB5/RP37
#define DEBUG_CAN_UART_TX_RPN  _RP54R

// Using UART1 for debug
#define DEBUG_CAN_UART_BAUDRATE 115200
#define DEBUG_CAN_UART_BRG ((FCY/16/DEBUG_UART_BAUDRATE)-1)
#define DEBUG_CAN_UART_TX_PIN 0b00011
#define DEBUG_CAN_UART_RX_RPN _U2RXR

// Define CAN pins
#define ECAN1_RX_PIN  55         // C1 RX Mapped on RP55 / RC7
#define ECAN1_RX_TRIS _TRISC7
#define ECAN1_TX_RPN  _RP54R     // C1 TX Mapped on RP54 / RC6
#define ECAN1_TX_TRIS _TRISC6

#define CAN_NODE_ID    CAN_NODE_ID_MICROBOARD_HMI
// -----------------------------------------------------------------------------
// CAN CONSTANTS
// -----------------------------------------------------------------------------

// Define the sizes of the software CAN FIFOs
#define CAN_RX_FIFO_SIZE 16
#define CAN_TX_FIFO_SIZE 16
//YCH

// UART
#define DEBUG_UART_RX_TRIS (TRISAbits.TRISA8)   // UART_RX    mapped on RA8/RPI24
#define DEBUG_UART_RX_PIN  24
#define DEBUG_UART_TX_TRIS (TRISBbits.TRISB5)   // UART_TX    mapped on RB5/RP37
#define DEBUG_UART_TX_RPN  (RPOR1bits.RP37R)

// Using UART1 for debug
#define DEBUG_UART_BAUDRATE 115200
#define DEBUG_UART_BRG ((FCY/16/DEBUG_UART_BAUDRATE)-1)
#define DEBUG_UART_TX_PIN 0b00001
#define DEBUG_UART_RX_RPN (RPINR18bits.U1RXR)

#define _DI()		__asm__ volatile("disi #0x3FFF")
#define _EI()		__asm__ volatile("disi #0")

// OLED Screen
#define OLED_CSN_TRIS    _TRISC0   // OLED_CSN -> RC0
#define OLED_CSN         _LATC0    // Output
#define OLED_DCN_TRIS    _TRISC1   // OLED_DCN -> RC1
#define OLED_DCN         _LATC1    // Output
#define OLED_RESN_TRIS   _TRISC2   // OLED_RESN -> RC2
#define OLED_RESN        _LATC2    // Output
#define OLED_PWR_EN_TRIS _TRISB10  // OLED_PWR_EN -> RB10
#define OLED_PWR_EN      _LATB10   // Output

// Navigation & Switches
#define NAV_A_TRIS    _TRISB0 // NAV_A -> RB0
#define NAV_A         (!_RB0) // Input
#define NAV_A_RPIR    _QEA1R  // QEI 1 Channel A
#define NAV_A_RPN     32      // RPI32
#define NAV_B_TRIS    _TRISA1 // NAV_B -> RA1
#define NAV_B         (!_RA1) // Input
#define NAV_B_RPIR    _QEB1R  // QEI 1 Channel B
#define NAV_B_RPN     17      // RPI17
#define NAV_OK_TRIS   _TRISB1 // NAV_OK -> RB1
#define NAV_OK        (!_RB1) // Input
#define NAV_OK_RPIR   _INT1R  // External Interrupt #1
#define NAV_OK_RPN    33      // RPI33
#define NAV_RET_TRIS  _TRISA0 // NAV_RET -> RA0
#define NAV_RET       (!_RA0) // Input
#define NAV_RET_RPIR  _INT2R  // External Interrupt #2
#define NAV_RET_RPN   16      // RPI16

// RGB LED
#define LEDR_TRIS   _TRISB12     // LEDR -> RB12  (PWM2H)
#define LEDR        _LATB12      // Output
#define LEDR_PER    PHASE2
#define LEDR_DUTY   PDC2

#define LEDG_TRIS   _TRISB13     // LEDG -> RB13  (PWM2L)
#define LEDG        _LATB13      // Output
#define LEDG_PER    SPHASE2
#define LEDG_DUTY   SDC2

#define LEDB_TRIS   _TRISB11     // LEDB -> RB11  (PWM3L)
#define LEDB        _LATB11      // Output
#define LEDB_PER    SPHASE3
#define LEDB_DUTY   SDC3

// Buzzer
#define BUZZER_TRIS  _TRISC9    // BUZZER_PWM -> RC9 (PWM5L)
#define BUZZER       _LATC9     // Output
#define BUZZER_PER   SPHASE5
#define BUZZER_DUTY  SDC5

// Individual LEDs
#define LED1_TRIS _TRISB15     // LED1 -> RB15
#define LED1      _LATB15      // Output
#define LED2_TRIS _TRISB14     // LED2 -> RB14
#define LED2      _LATB14      // Output
#define LED3_TRIS _TRISA7      // LED3 -> RA7
#define LED3      _LATA7       // Output
#define LED4_TRIS _TRISA10     // LED4 -> RA10
#define LED4      _LATA10      // Output

#define LED_OFF     1
#define LED_ON      0

// PWMs usage (1 = PWM module, 0 = GPIO)
#define PWM1H_EN    0 // LED2
#define PWM1L_EN    0 // LED1
#define PWM2H_EN    1 // RGB_R
#define PWM2L_EN    1 // RGB_G
#define PWM3H_EN    0 // unused
#define PWM3L_EN    1 // RGB_B
#define PWM4H_EN    0 // LED4
#define PWM4L_EN    0 // LED3
#define PWM5H_EN    0 // unused
#define PWM5L_EN    1 // BUZZER
#define PWM6H_EN    0 // unused
#define PWM6L_EN    0 // unused


// -----------------------------------------------------------------------------
// SSD1306's SPECIFIC OLED DEFINITIONS
// -----------------------------------------------------------------------------

// We need to specify the size of our display since the SSD1306 is a generic controller
#define OLED_WIDTH   128
#define OLED_HEIGHT   64
#define OLED_NB_PAGES (OLED_HEIGHT/8) // 8 Bits (vertical) per page
#define OLED_NB_CHAR_PER_LINE OLED_WIDTH/(SSD1306_FONT_WIDTH+1)


// -----------------------------------------------------------------------------
// PWM DEFINITIONS
// -----------------------------------------------------------------------------

// High-Speed PWM Input clock prescaler (common to all PWMs)
// Ensure that the PWM can be adjusted in the [20 Hz; 20 kHz] range for buzzer
// PWM freq = FOSC / (PWM_PCLKDIV * SPHASEx), SPHASEx is a uint16
// PCLKDIV Decoding:
#define PWM_PCLKDIV_1   0b000
#define PWM_PCLKDIV_2   0b001
#define PWM_PCLKDIV_4   0b010
#define PWM_PCLKDIV_8   0b011
#define PWM_PCLKDIV_16  0b100
#define PWM_PCLKDIV_32  0b101
#define PWM_PCLKDIV_64  0b110

#define PWM_PCLKDIV     PWM_PCLKDIV_32
#define PWM_BASE_FREQ   (FOSC/32)

// PWM Freq Min = 16 Hz
// PWM Freq Max = 1  MHz
#define PWM_FREQ_MIN    16
#define PWM_FREQ_MAX    1000000

// -----------------------------------------------------------------------------
// BUZZER & MUSIC DEFINITIONS
// -----------------------------------------------------------------------------

// Music Sampling rate, in Hz
#define MUSIC_SAMPLING_RATE     8000

// Required Timer rate
#define MUSIC_TIMER_TCKPS      0b11    // Timer base = FCY/8
#define MUSIC_TIMER_PERIOD    ((FCY/256/MUSIC_SAMPLING_RATE)-1)

//#define TIMER_BUZZER_PERIOD    1512 //310Hz

//#define TIMER_BUZZER_PERIOD    512 //914Hz

//SD CARD
#define SD_CSN_TRIS    _TRISC4   // sd card_CSN -> RC4
#define SD_CSN         _LATC4    // Output


// -----------------------------------------------------------------------------
// USEFUL MACROS
// -----------------------------------------------------------------------------



// -----------------------------------------------------------------------------
// PROTOTYPES
// -----------------------------------------------------------------------------

// Shorthand for ISR with no_auto_psv attribute (default _ISR does not have it)
#define _ISR_NO_AUTO_PSV void __attribute__((__interrupt__, no_auto_psv))

#endif
