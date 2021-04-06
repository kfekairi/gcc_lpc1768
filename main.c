#include "LPC17xx.h"
#include "lpc17xx_gpio.h"
#include "FreeRTOS.h"
#include "task.h"

#define LED1  (1<<18)
#define LED2  (1<<20)


void vTask1(void *pvParameters);
void vTask2(void *pvParameters);
void vIdealTask(void *pvParameters);

int main(void){
    
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
