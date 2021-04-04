#include "LPC17xx.h"
#include "lpc17xx_gpio.h"

#define LED1  (1<<18)


int main(void){
    
    GPIO_SetDir(1,LED1,1);
    GPIO_SetValue(1,LED1);

    while(1);
    
    return 0;
}

