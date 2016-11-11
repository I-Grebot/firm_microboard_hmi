
#include "board_cfg.h"
#include "microBoard_hmi.h"
#include "ff.h"
#include <stdio.h>

//*****************************************************************************
// Defines the size of the buffers that hold the path, or temporary
// data from the SD card.  There are two buffers allocated of this size.
// The buffer size must be large enough to hold the longest expected
// full path name, including the file name, and a trailing null character.
//*****************************************************************************
#define PATH_BUF_SIZE   80

//*****************************************************************************
// Defines the size of the buffer that holds the command line.
//*****************************************************************************
#define CMD_BUF_SIZE    64

//*****************************************************************************
// This buffer holds the full path to the current working directory.
// Initially it is root ("/").
//*****************************************************************************
static char g_cCwdBuf[PATH_BUF_SIZE] = "/";

//*****************************************************************************
// A temporary data buffer used when manipulating file paths, or reading data
// from the SD card.
//*****************************************************************************
static char g_cTmpBuf[PATH_BUF_SIZE];

//*****************************************************************************
// The buffer that holds the command line.
//*****************************************************************************
static char g_cCmdBuf[CMD_BUF_SIZE];

//*****************************************************************************
// The following are data structures used by FatFs.
//*****************************************************************************
static FATFS g_sFatFs;
static DIR g_sDirObject;
static FILINFO g_sFileInfo;
static FIL g_sFileObject;


// ----

uint8_t sd_card_error_encountered = 0;
FIL FileLog[1]; /* File objects */
//DIR current_log_dir;
char current_log_dir_name[15];

uint8_t sd_card_error(void)
{
    return sd_card_error_encountered;
}

void create_new_log_file(void)
{
    if (NULL != &FileLog[0])
    {
        printf("close file\n");
        f_sync(&FileLog[0]);
    }

    FRESULT res;
    DIR dir;				/* Directory object */
    FILINFO Finfo;
    UINT file_number = 1;

    res = f_opendir(&dir, current_log_dir_name);
    if (res) { put_rc(res); sd_card_error_encountered = 1; return; }

    //count number of files in Logs
    for(;;) {
        res = f_readdir(&dir, &Finfo);
        if ((res != FR_OK) || !Finfo.fname[0]) break;
        if (Finfo.fattrib & AM_DIR) { //if attribute is folder
        } else { //if attribute is file
            file_number++;
        }
    }

    //generate new file name based on file_number
    char new_file_name[29];
    sprintf(new_file_name, "%s/log_%.5d.txt", current_log_dir_name, file_number);
    printf("new file : %s\n", new_file_name);

    //create file
    put_rc(f_open(&FileLog[0], new_file_name, (BYTE)FA_CREATE_NEW));
    printf("file created\n");

    //close file (save)
    f_close(&FileLog[0]);

    put_rc(f_open(&FileLog[0], new_file_name, (BYTE)FA_WRITE));

    //flush data in file
    f_sync(&FileLog[0]);
}

void create_new_log_folder(void)
{
    FRESULT res;
    DIR dir;				/* Directory object */
    FILINFO Finfo;
    UINT folder_number = 1;

    res = f_opendir(&dir, "Logs");
    if (res) { put_rc(res); sd_card_error_encountered = 1; return; }

    //count number of files in Logs
    for(;;) {
        res = f_readdir(&dir, &Finfo);
        if ((res != FR_OK) || !Finfo.fname[0]) break;
        if (Finfo.fattrib & AM_DIR) { //if attribute is folder
            folder_number++;
        } else { //if attribute is file
        }
    }

    //generate new folder name based on folder_number
    sprintf(current_log_dir_name, "Logs/log_%.5d", folder_number);
    printf("new folder : %s\n", current_log_dir_name);

    //create file
    put_rc(f_mkdir(current_log_dir_name));
    printf("folder created\n");

    create_new_log_file();
}

void log_string_no_sync(const TCHAR* str)
{
//    long file_size = f_size(&FileLog[0]);

//    f_lseek(&FileLog[0], file_size);

    f_puts(str, &FileLog[0]);
}

uint8_t delayed_count = 0;
void log_string_delayed(const TCHAR* str)
{
    log_string_no_sync(str);

    delayed_count+=1;
    if(10 <= delayed_count)
    {
        f_sync(&FileLog[0]);
        delayed_count = 0;
    }
}

void log_string(const TCHAR* str)
{
    log_string_no_sync(str);

    f_sync(&FileLog[0]);
}

void log_string_with_date(const TCHAR* str)
{
    char test[100];
    DWORD time = get_fattime();
    sprintf(test, "%d:%d:%d - %s", get_hours(), get_minutes(), get_seconds(), str);

    printf("result = %s", test);
    log_string_no_sync(test);

    f_sync(&FileLog[0]);
}

void get_picture(FIL* fp, BYTE* pict, const TCHAR* path)
{
    UINT bmp_header_size = 62;
    UINT bmp_lcd_size = 1024;

    BYTE Buff[4096];
    UINT cnt;

    put_rc(f_open(fp, path, (BYTE)FA_READ));

    f_lseek(fp, bmp_header_size);

    f_read(fp, Buff, bmp_lcd_size, &cnt);

    UINT i = 0;
    for(i = 0; i < bmp_lcd_size; i++)
    {
        pict[i] = Buff[i];
    }

    f_close(fp);
}
