#include "LPC17xx.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_uart.h"
#include "FreeRTOS.h"
#include "task.h"

#define LED1  (1<<18)
#define LED2  (0<<20)


void vTask1(void *pvParameters);
void vTask2(void *pvParameters);
void vIdealTask(void *pvParameters);

int main(void){

    // UART Configuration structure variable
	UART_CFG_Type UARTConfigStruct;
	// UART FIFO configuration Struct variable
	UART_FIFO_CFG_Type UARTFIFOConfigStruct;
	// Pin configuration for UART0
	PINSEL_CFG_Type PinCfg;

	uint32_t idx, len;
	__IO FlagStatus exitflag;
	uint8_t buffer[10];

	/*
	 * Initialize UART0 pin connect
	 */
	PinCfg.Funcnum = 1;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Pinnum = 2;
	PinCfg.Portnum = 0;
	PINSEL_ConfigPin(&PinCfg);//P0.2 TXD0
	PinCfg.Pinnum = 3;
	PINSEL_ConfigPin(&PinCfg);//P0.3 RXD0

	/* Initialize UART Configuration parameter structure to default state:
	 * Baudrate = 9600bps
	 * 8 data bit
	 * 1 Stop bit
	 * None parity
	 */
	UART_ConfigStructInit(&UARTConfigStruct);

	// Initialize UART0 peripheral with given to corresponding parameter
	UART_Init(LPC_UART0, &UARTConfigStruct);

	/* Initialize FIFOConfigStruct to default state:
	 * 				- FIFO_DMAMode = DISABLE
	 * 				- FIFO_Level = UART_FIFO_TRGLEV0
	 * 				- FIFO_ResetRxBuf = ENABLE
	 * 				- FIFO_ResetTxBuf = ENABLE
	 * 				- FIFO_State = ENABLE
	 */
	UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);

	// Initialize FIFO for UART0 peripheral
	UART_FIFOConfig(LPC_UART0, &UARTFIFOConfigStruct);

	// Enable UART Transmit
	UART_TxCmd(LPC_UART0, ENABLE);

	// print welcome screen
	

    
    GPIO_SetDir(1,LED1|LED2,1);

    xTaskCreate( vTask1, "Task1", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
    xTaskCreate( vTask2, "Task1", configMINIMAL_STACK_SIZE, NULL, 1, NULL );

    vTaskStartScheduler();
    while(1);  
}

void vTask1(void *pvParameters){

    while(1){
        GPIO_SetValue(1,LED1);
        vTaskDelay(500);
        //UART_SendByte(LPC_UART0,'o');
		UART_Send(LPC_UART0, "rx_char", 8, BLOCKING);
        GPIO_ClearValue(1,LED1);
        vTaskDelay(500);
    }
}


void vTask2(void *pvParameters){

    while(1){
        GPIO_ClearValue(1,LED2);
        vTaskDelay(500);
        GPIO_SetValue(1,LED2);
        vTaskDelay(500);
    }
}
