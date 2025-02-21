/**
******************************************************************************
* @file         types.h                                                                                           
* @version      V1.0                          
* @date         2018-06-18                       
* @brief        常用类型重定义
*        
* @company      深圳炜世科技有限公司
* @information  WIZnet W5100s官方代理商，全程技术支持，价格优势大！
* @website      www.wisioe.com
* @forum        www.w5100s.com
* @qqGroup      579842114                                                     
******************************************************************************
*/
#ifndef _TYPE_H_
#define _TYPE_H_

#define MAX_SOCK_NUM 4 // Maxmium number of socket

typedef unsigned char uint8_t;

typedef char int8;

typedef volatile char vint8;

typedef unsigned char uint8;

typedef volatile unsigned char vuint8;

typedef int int16;

typedef unsigned short uint16;

typedef long int32;

typedef unsigned long uint32;

typedef uint8  u_char;    /**< 8-bit value */
typedef uint8  SOCKET;
typedef uint16 u_short;   /**< 16-bit value */
typedef uint16 u_int;     /**< 16-bit value */
typedef uint32 u_long;    /**< 32-bit value */

typedef union _un_l2cval 
{
 u_long lVal;
 u_char cVal[4];
}un_l2cval;

typedef union _un_i2cval 
{
 u_int iVal;
 u_char cVal[2];
}un_i2cval;

#endif /* _TYPE_H_ */
