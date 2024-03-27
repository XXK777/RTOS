#ifndef NEEDLE_H
#define NEEDLE_H



#include "main.h"
#include "cmsis_os.h"
#include "adc.h"
#include "can.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include<string.h>


/*is aaa sa a */


extern SemaphoreHandle_t task_semaphr;
void Uart_init( uint8_t *pData, uint16_t Size);
#endif

