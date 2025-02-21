/**
******************************************************************************
* @file         ftpc.h                                         
* @version      V1.0                          
* @date         2018-06-18                 
* @brief        ftpc.c的头文件        
*
* @company      深圳炜世科技有限公司
* @information  WIZnet W5100S官方代理商，全程技术支持，价格优势大！
* @website      www.wisioe.com     
* @forum        www.w5100s.com
* @qqGroup      579842114                                                     
******************************************************************************
*/
#ifndef _FTPC_H_
#define _FTPC_H_

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdarg.h>
#include "stdio_private.h"
#include "socket.h"

#define F_APP_FTPC

/* If your target support a file system, you have to activate this feature and implement. */
//#define F_FILESYSTEM

/* Change to your Chipset Uart function, you have to activate this feature and implement.
 * Change!! -> Board_UARTGetCharBlocking()
 * Below is an example of a function of lpc_chip library. */
//#define ftp_getc()  Board_UARTGetCharBlocking()

#ifdef F_FILESYSTEM
#include "ff.h"
#endif

//#ifndef  ftp_getc()
#define Need_UARTGetCharBlocking_func
//#else
/* Change library
 * Change!! -> board_api.h,
 * Below is an example of a function of lpc_chip library. */
//#include "board_api.h"
//#endif


#define LINELEN    100
#ifndef F_FILESYSTEM
#define _MAX_SS    512
#endif

#define CTRL_SOCK  2
#define DATA_SOCK  3

/* FTP Responses */
#define R_150  150    // File status ok; opening data conn 
#define R_200  200    // 'Generic' command ok 
#define R_220  220    // Service ready for new user. 
#define R_221  221    // 服务正在关闭
#define R_225  225    // 数据连接打开
#define R_226  226    // Closing data connection.  File transfer/abort successful 
#define R_227  227    // Entering passive mode (h1,h2,h3,h4,p1,p2) 
#define R_230  230    // User logged in, proceed 
#define R_250  250    // 请求文件操作已完成
#define R_257  257    // 路径创建成功
#define R_331  331    // User name okay, need password. 

#define TransferAscii    'A'
#define TransferBinary   'I'

enum ftpc_type {
  ASCII_TYPE,
  IMAGE_TYPE,
};

enum ftpc_datasock_state{
  DATASOCK_IDLE,
  DATASOCK_READY,
  DATASOCK_START
};

enum ftpc_datasock_mode{
  PASSIVE_MODE,
  ACTIVE_MODE
};
enum CommandFirst {
  f_nocmd,
  f_dir,
  f_put,
  f_get,
};
enum CommandSecond {
  s_nocmd,
  s_dir,
  s_put,
  s_get,
};
struct Command {
  enum CommandFirst First;
  enum CommandSecond Second;
};
struct ftpc {
  uint8_t control;      // Control stream 
  uint8_t data;         // Data stream 

  enum ftpc_type type;  // Transfer type 

  enum ftpc_datasock_state dsock_state;
  enum ftpc_datasock_mode dsock_mode;

  char workingdir[LINELEN];
  char filename[LINELEN];

#ifdef F_FILESYSTEM
  FIL fil;     // FatFs File objects
  FRESULT fr;  // FatFs function common result code
#endif
};

void ftpc_init(uint8_t * src_ip);
uint8_t ftpc_run(uint8_t * dbuf);
char proc_ftpc(char * buf);
int pportc(char * arg);
uint8_t* User_Keyboard_MSG(void);
void ftp_cmd(uint8_t cmd,char* sbuf,char*dbuf);
#endif // _FTPC_H_
