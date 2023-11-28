/**
*********************************************************************
*********
* @project_name :car0
* @file : MyUsart.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/6
*********************************************************************
*********
*/
//

#include "WString.h"
#include "MyUsart.h"
#include "MyGPIO.h"
#include "PinConfig.h"
#include "MyDMA.h"
#define MAXWait 0xffff
#define MAXUart 6
uint8_t BufferArray;
uint8_t openDMATransmit;
MyDMA myDma;

struct uartInfo{
    UART_HandleTypeDef UsartList[MAXUart]={0};//全局串口句柄
    uint8_t USARTx_IRQn[MAXUart]={0};
};
uartInfo  uartInfo;
void MyUsart::uart_init(UART_enum uart, uint32_t baudrate) {
    MyGPIO myGpio;
    Pin_enum uart_tx, uart_rx;
    uint8_t USARTx_IRQn;uint8_t Alternate=0;
    switch (uart)
    {
#ifdef HAVE_SERIAL1
        case UART_1:
            __HAL_RCC_USART1_CLK_ENABLE();
            uartInfo.UsartList[uart].Instance=USART1;
            Alternate=GPIO_AF7_USART1;
            uart_tx = (Pin_enum)UART1_TX, uart_rx = (Pin_enum)UART1_RX;
            memset((void *)&UART1_recbuf, 0, sizeof(UART1_recbuf));
            uartInfo.USARTx_IRQn[UART_1]=USARTx_IRQn = USART1_IRQn;
    break;
#endif
#ifdef HAVE_SERIAL2
        case UART_2:
            __HAL_RCC_USART2_CLK_ENABLE();
            uartInfo.UsartList[uart].Instance=USART2;
            Alternate=GPIO_AF7_USART2;
            uart_tx = (Pin_enum)UART2_TX, uart_rx = (Pin_enum)UART2_RX;
            memset((void *)&UART2_recbuf, 0, sizeof(UART2_recbuf));
            uartInfo.USARTx_IRQn[UART_2]=USARTx_IRQn = USART2_IRQn;
    break;
#endif
#ifdef HAVE_SERIAL3
        case UART_3:
            __HAL_RCC_USART3_CLK_ENABLE();
            uartInfo. UsartList[uart].Instance=USART3;
            Alternate=GPIO_AF7_USART3;
            uart_tx = (Pin_enum)UART3_TX, uart_rx = (Pin_enum)UART3_RX;
            memset((void *)&UART3_recbuf, 0, sizeof(UART3_recbuf));
            uartInfo.USARTx_IRQn[UART_3]=USARTx_IRQn = USART3_IRQn;
    break;
#endif
#ifdef HAVE_SERIAL4
        case UART_4:
            __HAL_RCC_UART4_CLK_DISABLE();
            uartInfo.UsartList[uart].Instance=UART4;
            Alternate=GPIO_AF8_UART4;
            uart_tx = (Pin_enum)UART4_TX, uart_rx = (Pin_enum)UART4_RX;
            memset((void *)&UART4_recbuf, 0, sizeof(UART4_recbuf));
            uartInfo.USARTx_IRQn[UART_4]=USARTx_IRQn = UART4_IRQn;
    break;
#endif
#ifdef HAVE_SERIAL5
        case UART_5:
            __HAL_RCC_UART5_CLK_ENABLE();
            uartInfo. UsartList[uart].Instance=UART5;
            Alternate=GPIO_AF8_UART5;
            uart_tx = (Pin_enum)UART5_TX, uart_rx = (Pin_enum)UART5_RX;
            memset((void *)&UART5_recbuf, 0, sizeof(UART5_recbuf));
            uartInfo.USARTx_IRQn[UART_5]=USARTx_IRQn = UART5_IRQn;
    break;
#endif
#ifdef HAVE_SERIAL6
        case UART_6:
            __HAL_RCC_USART6_CLK_ENABLE();
            uartInfo.UsartList[uart].Instance=USART6;
            Alternate=GPIO_AF8_USART6;
            uart_tx = (Pin_enum)UART6_TX, uart_rx = (Pin_enum)UART6_RX;
            memset((void *)&UART6_recbuf, 0, sizeof(UART6_recbuf));
            uartInfo.USARTx_IRQn[UART_6]= USARTx_IRQn = USART6_IRQn;
            break;
#endif
        default:
            return;
    }
    myGpio.gpio_init(uart_rx, GpioMode::af_pp,Alternate);
    myGpio.gpio_init(uart_tx, GpioMode::af_pp,Alternate);
    HAL_NVIC_EnableIRQ(IRQn_Type(USARTx_IRQn));                      /* 使能USART中断通道 */
    HAL_NVIC_SetPriority((IRQn_Type)USARTx_IRQn, 0, 0);              /* 抢占优先级3，子优先级3 */
      uartInfo. UsartList[uart].Init.BaudRate = baudrate;                    /* 波特率 */
      uartInfo. UsartList[uart].Init.WordLength = UART_WORDLENGTH_8B;        /* 字长为8位数据格式 */
      uartInfo. UsartList[uart].Init.StopBits = UART_STOPBITS_1;             /* 一个停止位 */
      uartInfo. UsartList[uart].Init.Parity = UART_PARITY_NONE;              /* 无奇偶校验位 */
      uartInfo. UsartList[uart].Init.HwFlowCtl = UART_HWCONTROL_NONE;        /* 无硬件流控 */
      uartInfo. UsartList[uart].Init.Mode = UART_MODE_TX_RX;                 /* 收发模式 */

    if (openDMATransmit){
        uart_dma_init(uart);
        HAL_UART_Init(& uartInfo.UsartList[uart]);
        HAL_UART_Receive_DMA(&uartInfo.UsartList[uart], &BufferArray, 1);
    }else{
        HAL_UART_Init(& uartInfo.UsartList[uart]);
        HAL_UART_Receive_IT(&uartInfo.UsartList[uart], &BufferArray, 1);
    }


}

void MyUsart::uart_deinit(UART_enum uart) {
    HAL_UART_DeInit(&uartInfo.UsartList[uart]);
    HAL_NVIC_DisableIRQ( (IRQn_Type)uartInfo.USARTx_IRQn[uart]);
}

void MyUsart::uart_write_byte(UART_enum uart, uint8_t data) {
    HAL_UART_Transmit(&uartInfo.UsartList[uart], (uint8_t *)&data, 1, MAXWait);
}

void MyUsart::uart_write_buffer(UART_enum uart, const uint8_t *buf, int len) {
    HAL_UART_Transmit(&uartInfo.UsartList[uart], (uint8_t *)buf, len, MAXWait);
}

void MyUsart::uart_write_string(UART_enum uart, const char *str) {
    int len= strlen(str);
    HAL_UART_Transmit(&uartInfo.UsartList[uart], (uint8_t *)str, len, MAXWait);
}

uint16_t MyUsart::uart_rec_size(UART_enum uart) {
    auto uart_buf= selectBuff(uart);
    return uart_buf->data_size;
}

uint8_t MyUsart::uart_read_byte(UART_enum uart) {
    __rec_buf *uart_recbuf =selectBuff(uart);
    while (uart_recbuf->data_size == 0) //等待串口缓冲区接收到数据
        ;
    uint8_t res = uart_recbuf->buf[uart_recbuf->read_index++];
    uart_recbuf->data_size--;
    return res;
}

void MyUsart::uart_dma_init(UART_enum uart) {
    myDma.DMAInitIN(&uartInfo.UsartList[uart], uart,
                     (DMA_Stream_TypeDef *) DmaHandle[uart],
                     DMA_Channel[uart], DMA_IQRNNum[uart]);
    myDma.DMAInitOut(&uartInfo.UsartList[uart], uart,
                     (DMA_Stream_TypeDef *) DmaHandle[uart+1],
                     DMA_Channel[uart+1], DMA_IQRNNum[uart+1]);


}

void MyUsart::uart_dma_write_buffer(UART_enum uart, const uint8_t *buf, int len) {
    HAL_UART_Transmit_DMA(&uartInfo.UsartList[uart],buf,len);
}

__rec_buf *MyUsart::selectBuff(UART_enum uart) {
    switch (uart) {
#ifdef HAVE_SERIAL1
        case UART_1:
            return &UART1_recbuf;
#endif
#ifdef HAVE_SERIAL2
        case UART_2:
            return &UART2_recbuf;
#endif
#ifdef HAVE_SERIAL3
        case UART_3:
            return &UART3_recbuf;
#endif
#ifdef HAVE_SERIAL4
        case UART_4:
            return &UART4_recbuf;
#endif
#ifdef HAVE_SERIAL5
        case UART_5:
            return &UART5_recbuf;
#endif
#ifdef HAVE_SERIAL6
        case UART_6:
            return &UART6_recbuf;
#endif
        default:
            return nullptr;
    }
}


/*******************************************串口中断*****************************************************/
#ifdef HAVE_SERIAL1
__rec_buf UART1_recbuf;
void USART1_IRQHandler(void)
{
    HAL_UART_IRQHandler(&uartInfo.UsartList[0]);
}
#endif

#ifdef HAVE_SERIAL2
__rec_buf UART2_recbuf;
void USART2_IRQHandler(void)
{
    HAL_UART_IRQHandler(&uartInfo.UsartList[1]);
}
#endif

#ifdef HAVE_SERIAL3
__rec_buf UART3_recbuf;
void USART3_IRQHandler(void)
{
    HAL_UART_IRQHandler(&uartInfo.UsartList[2]);
}
#endif

#ifdef HAVE_SERIAL4
__rec_buf UART4_recbuf;
void UART4_IRQHandler(void)
{
    HAL_UART_IRQHandler(&uartInfo.UsartList[3]);
}
#endif

#ifdef HAVE_SERIAL5
__rec_buf UART5_recbuf;
void UART5_IRQHandler(void)
{
    HAL_UART_IRQHandler(&uartInfo.UsartList[4]);
}
#endif
#ifdef HAVE_SERIAL6
__rec_buf UART6_recbuf;
void USART6_IRQHandler(void)
{
    HAL_UART_IRQHandler(&uartInfo.UsartList[5]);
}
#endif
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
    if (huart->Instance==USART1){
        if (UART1_recbuf.data_size>256) return;
        UART1_recbuf.buf[UART1_recbuf.write_index++]=BufferArray;
        UART1_recbuf.data_size++;
        if (openDMATransmit){
            HAL_UART_Receive_DMA(&uartInfo.UsartList[0],&BufferArray,1);
        } else{
            HAL_UART_Receive_IT(&uartInfo.UsartList[0],&BufferArray,1);
        }
    }
    if (huart->Instance==USART2){
        if (UART2_recbuf.data_size>256) return;
        UART2_recbuf.buf[UART2_recbuf.write_index++]=BufferArray;
        UART2_recbuf.data_size++;
        HAL_UART_Receive_IT(&uartInfo.UsartList[1],&BufferArray,1);
    }
    if (huart->Instance==USART3){
        if (UART3_recbuf.data_size>256) return;
            UART3_recbuf.buf[UART3_recbuf.write_index++]=BufferArray;
            UART3_recbuf.data_size++;

            HAL_UART_Receive_IT(&uartInfo.UsartList[2],&BufferArray,1);
    }
    if (huart->Instance==UART4){
        if (UART4_recbuf.data_size>256) return;
       UART4_recbuf.buf[UART4_recbuf.write_index++]=BufferArray;
       UART4_recbuf.data_size++;
        HAL_UART_Receive_IT(&uartInfo.UsartList[3],&BufferArray,1);
    }
    if (huart->Instance==UART5){
        if (UART5_recbuf.data_size>256) return;
        UART5_recbuf.buf[UART5_recbuf.write_index++]=BufferArray;
        UART5_recbuf.data_size++;
        HAL_UART_Receive_IT(&uartInfo.UsartList[4],&BufferArray,1);
    }
    if (huart->Instance==USART6){
        if (UART6_recbuf.data_size>256) return;
        UART6_recbuf.buf[UART6_recbuf.write_index++]=BufferArray;
        UART6_recbuf.data_size++;
        HAL_UART_Receive_IT(&uartInfo.UsartList[5],&BufferArray,1);
    }

}


/*****************************************************************************************************************************/

