/**
 ****************************************************************************************************
 * @file        delay.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2021-10-14
 * @brief       ʹ��SysTick����ͨ����ģʽ���ӳٽ��й���(֧��ucosii)
 *              �ṩdelay_init��ʼ�������� delay_us��delay_ms����ʱ����
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� ̽���� F407������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 * �޸�˵��
 * V1.0 20211014
 * ��һ�η���
 *
 ****************************************************************************************************
 */
 
#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f4xx.h"
#ifdef __cplusplus
extern "C"
{
#endif


void delay_init(uint16_t sysclk);           /* ��ʼ���ӳٺ��� */
void delay_ms(uint16_t nms);                /* ��ʱnms */
void delay_us(uint32_t nus);                /* ��ʱnus */
uint32_t millis();//����
uint32_t micros();//΢��
//#if (!SYS_SUPPORT_OS)                       /* û��ʹ��Systick�ж� */
//    void HAL_Delay(uint32_t Delay);         /* HAL�����ʱ������SDIO����Ҫ�õ� */
//#endif
/*______________________���������������________________:*/

#ifdef __cplusplus
}
#endif
#endif

