/**
******************************************************************************
* @file         bsp_usart1.c                                                                                              
* @version      V1.0                          
* @date         2018-06-18                       
* @brief        配置串口与重定向C库函数
*        
* @company      深圳炜世科技有限公司
* @information  WIZnet W5100s官方代理商，全程技术支持，价格优势大！
* @website      www.wisioe.com 
* @forum        www.w5100s.com
* @qqGroup      579842114                                                     
******************************************************************************
*/
#include "bsp_usart1.h"

void USART1_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;  
  /* config USART1 clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
  
  /* USART1 GPIO config */
  /* Configure USART1 Tx (PA.09) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);    
  /* Configure USART1 Rx (PA.10) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;  
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;      
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;        
  NVIC_Init(&NVIC_InitStructure);  
  /* USART1 mode config */
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No ;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART1, &USART_InitStructure); 
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  USART_Cmd(USART1, ENABLE);
}

/*重定向c库函数printf到USART1*/
int fputc(int ch, FILE *f)
{
  /* 发送一个字节数据到USART1 */
  USART1->SR;
  USART_SendData(USART1, (uint8_t) ch);
  
  /* 等待发送完毕 */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);    
  
  return (ch);
}

/*重定向c库函数scanf到USART1*/
int fgetc(FILE *f)
{
  /* 等待串口1输入数据 */
  while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

  return (int)USART_ReceiveData(USART1);
}
/*********************************************END OF FILE**********************/
