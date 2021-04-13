/****************************************Copyright (c)****************************************************
**                                 http://www.OpenMCU.com
**--------------File Info---------------------------------------------------------------------------------
** File name:           uart.c
** Last modified Date:  2014-04-10
** Last Version:        V1.1
** Descriptions:        
**
**--------------------------------------------------------------------------------------------------------
** Created by:          OpenMCU
** Created date:        2010-05-10
** Version:             V1.07
** Descriptions:        ��дʾ������
**
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "uart.h"

#define FOSC                        12000000           /* ����Ƶ��*/                 

#define FCCLK                      (FOSC  * 8)         /* ��ʱ��Ƶ��<=100Mhz*/        
                                                       /* FOSC��������*/               
#define FCCO                       (FCCLK * 3)         /* PLLƵ��(275Mhz~550Mhz)*/     
                                                       /* ��FCCLK��ͬ���������ż����*/ 
#define FPCLK                      (FCCLK / 4)         /* ����ʱ��Ƶ��,FCCLK��1/2��1/4*/
                                                       /* ����FCCLK��ͬ*/               

//#define UART0_BPS     115200                         /* ����0ͨ�Ų�����*/             
//#define UART2_BPS     115200                         /* ����2ͨ�Ų�����*/            
/*********************************************************************************************************
** Function name:       UART0_Init
** Descriptions:        ��Ĭ��ֵ��ʼ������0�����ź�ͨѶ����������Ϊ8λ����λ��1λֹͣλ������żУ��
** input parameters:    ������
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void UART0_Init (uint32_t UART0_BPS)
{
	uint16_t usFdiv;
   
    LPC_PINCON->PINSEL0 |= (1 << 4);            /* Pin P0.2 used as TXD0 (Com0)*/ 
    LPC_PINCON->PINSEL0 |= (1 << 6);            /* Pin P0.3 used as RXD0 (Com0) */
  
  	LPC_UART0->LCR  = 0x83;                     /* 8������λ��1��ֹͣλ������żУ���������ʳ���������*/               

		usFdiv = (FPCLK / 16) / UART0_BPS;          /* ���ò�����*/                   
    LPC_UART0->DLM  = usFdiv / 256;				      /* д������������λ*/
    LPC_UART0->DLL  = usFdiv % 256; 			      /* д������������λ*/
    LPC_UART0->LCR  = 0x03;                     /* ��ֹ���ʳ���������*/                  
    LPC_UART0->FCR  = 0x07; 				            /* ����FIFO�����UART0 RxFIFO ��TxFIFO*/
}

/*********************************************************************************************************
** Function name:       UART0_SendByte
** Descriptions:        ����0��������
** input parameters:    ucdata
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
int UART0_SendByte (int ucData)
{
	while (!(LPC_UART0->LSR & 0x20));           /*��bit5 0 Ϊ�����ݣ�1 Ϊ�������*/
    return (LPC_UART0->THR = ucData);
}


/*********************************************************************************************************
** Function name:      UART0_GetChar
** Descriptions:       �Ӵ���0��ȡ�ַ�
** input parameters:   ��
** output parameters:  ��
** Returned value:     RBR
*********************************************************************************************************/
int UART0_GetChar (void) 
{
  	while (!(LPC_UART0->LSR & 0x01));	       /*��bit0 0 Ϊ�գ�1 Ϊ���յ�����*/
  	return (LPC_UART0->RBR);			    
}

/*********************************************************************************************************
** Function name:       UART0_SendString 
** Descriptions:        �Ӵ���0��������
** input parameters:    s: Ҫ���͵��ַ���ָ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void UART0_SendString (unsigned char *s) 
{
  	while (*s != 0) 
	{
   		UART0_SendByte(*s++);
	}
}

/*********************************************************************************************************
** Function name:       UART2_Init
** Descriptions:        ��Ĭ��ֵ��ʼ������2�����ź�ͨѶ����������Ϊ8λ����λ��1λֹͣλ������żУ��
** input parameters:    ������
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void UART2_Init (uint32_t UART2_BPS)
{
	uint16_t usFdiv;
  
    LPC_PINCON->PINSEL0 |= (1 << 20);             /* Pin P0.10 used as TXD2 (Com2)*/ 
    LPC_PINCON->PINSEL0 |= (1 << 22);             /* Pin P0.11 used as RXD2 (Com2)*/

   	LPC_SC->PCONP = LPC_SC->PCONP|(1<<24);	      /*ʹ��UART2*/	          

    LPC_UART2->LCR  = 0x83;                       /* �������ò�����*/  	
    usFdiv = (FPCLK / 16) / UART2_BPS;            /*���ò�����*/                   
    LPC_UART2->DLM  = usFdiv / 256;
    LPC_UART2->DLL  = usFdiv % 256; 
    LPC_UART2->LCR  = 0x03;                       /* ����������*/                   
    LPC_UART2->FCR  = 0x07;
}

/*********************************************************************************************************
** Function name:       UART2_SendByte
** Descriptions:        �Ӵ���2��������
** input parameters:    data: ���͵�����
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
int UART2_SendByte (int ucData)
{
	while (!(LPC_UART2->LSR & 0x20));
    return (LPC_UART2->THR = ucData);
}

/*----------------------------------------------------------------------------
  Read character from Serial Port   (blocking read)
 *----------------------------------------------------------------------------*/
/*********************************************************************************************************
** Function name:       UART2_GetChar
** Descriptions:        �Ӵ���2��ȡ����
** input parameters:    ��
** output parameters:   ��
** Returned value:      RBR
*********************************************************************************************************/
int UART2_GetChar (void) 
{
  	while (!(LPC_UART2->LSR & 0x01));
  	return (LPC_UART2->RBR);
}

/*********************************************************************************************************
** Function name:     UART2_SendString
** Descriptions:	    �򴮿�2�����ַ���
** input parameters:  s:   Ҫ���͵��ַ���ָ��
** output parameters: ��
** Returned value:    ��
*********************************************************************************************************/
void UART2_SendString (unsigned char *s) 
{
  	while (*s != 0) 
	{
   		UART2_SendByte(*s++);
	}
}

void UART0_SendChar(uint16_t disp)
{
	uint16_t dispbuf[4];
	uint8_t i;

	dispbuf[3] = disp%10 + '0';
	dispbuf[2] = disp/10%10 + '0';
	dispbuf[1] = disp/10/10%10 + '0';
	dispbuf[0] = disp/10/10/10%10 + '0';
	for(i=0;i<4;i++)
		UART0_SendByte(dispbuf[i]);	
}
