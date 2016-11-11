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
 * $LastChangedDate:: 2015-03-01 16:05:55 +0100 (Sun, 01 Mar 2015)             $
 * -----------------------------------------------------------------------------
 * Version     Comment                                   Author       Date
 * 1.0         Initial release                           Paul M.      2015-03-01
 * -----------------------------------------------------------------------------
 */

#include "microBoard_hmi.h"

/*
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

uint16_t melody_length = 36;

const uint16_t melotest[] = {
  NOTE_A4, 0, NOTE_A4, 0,
  NOTE_A4, 0, NOTE_F4, 0,
  NOTE_C5, 0, NOTE_A4, 0,
  NOTE_F4, 0, NOTE_C5, 0,
  NOTE_A4, 0, NOTE_E5, 0,
  NOTE_E5, 0, NOTE_E5, 0,
  NOTE_F5, 0, NOTE_C5, 0,
  NOTE_G5, 0, NOTE_F5, 0,
  NOTE_C5, 0, NOTE_A4, 0
};

const uint16_t melotest_tempo[] = {
  8, 6, 8, 6,
  8, 6, 7, 2,
  6, 2, 9, 4,
  7, 2, 6, 2,
  9, 10, 8, 6,
  8, 6, 8, 6,
  7, 2, 6, 2,
  9, 4, 7, 2,
  6, 2, 9, 7
};
*/
static FIL song_file_hwd;
static uint8_t song_finished;

// Initialize the Buzzer timers
void buzzer_init(void) {
    // Init Timer 2
    T2CONbits.TON   = 0     ;               // Disable Timer
    T2CONbits.TCS   = 0     ;               // Internal cycle clock selected
    T2CONbits.TCKPS = MUSIC_TIMER_TCKPS  ;  // Set prescaler
    TMR2            = 0     ;               // Clear Timer
    PR2             = MUSIC_TIMER_PERIOD;   // Select TIM2 Period

    _T2IF = 0; // Clear Timer1 Interrupt Flag
    _T2IE = 1; // Enable Timer1 interrupt
}

void play_song(const TCHAR* path) {

  static const UINT header_size = 44; /* 44 Bytes, decoding TODO*/
  
  BYTE* data;

  UINT cnt;

  // Open the wav file and seek for 1st actual data
  put_rc(f_open(&song_file_hwd, path, (BYTE) FA_READ));
  f_lseek(&song_file_hwd, header_size);

  long p1;
  p1 = f_size(&song_file_hwd);
  printf("Playing '%s' (size : %lu)\n", path, p1);

  if(p1 <= 44)
    return;
  
  // Setup buzzer PWM  
  buzzer_set_frequency(MUSIC_SAMPLING_RATE);
  BUZZER_DUTY = 0;
  song_finished = 0;

  // Now ready to read data bytes

  // Start music timer
  T2CONbits.TON = 1;

  while(!song_finished);

  SDC5 = 0;
  T2CONbits.TON = 0;
  f_close(&song_file_hwd);

  printf("End of song\n");

}


_ISR_NO_AUTO_PSV _T2Interrupt(void) {
  
  BYTE song_buff;
  uint16_t pwm_duty;
  UINT cnt;

  _T2IF = 0;
  
  // Read one Byte from SD
  f_read(&song_file_hwd, &song_buff, 1, &cnt);
  //printf("%u\n", song_buff);
  //LED2 = ~LED2;

  // Unsigned Wave Data decoding:
  //   0: Maximum negative Signal value
  // 128: No Signal
  // 255: Maximum positive Signal value
  // Scale value to the BUZZER_PER scale
  if(cnt) {

    pwm_duty = ((uint16_t) song_buff);
    
    BUZZER_DUTY = pwm_duty;
  } else {
    song_finished = 1;
  }
}


uint16_t elapsed_time = 0;
uint16_t current_note = 0;
uint8_t is_silence = 0;

void do_update_buzzer(void) {
    elapsed_time++;

   /* if(0 == is_silence && melotest_tempo[current_note] <= elapsed_time)
    {
        elapsed_time = 0;
        is_silence = 1;

        PR2 = 0;

        current_note++;

        if (current_note >= melody_length)
        {
            current_note = 0;
        }
    }
    else if (1 == is_silence && 1 <= elapsed_time)
    {
        elapsed_time = 0;
        is_silence = 0;

        PR2 = (FCY / 64) / (2 * melotest[current_note]);
    }*/
}

