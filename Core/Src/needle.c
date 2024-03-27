
/* is for use freeRTOS task */
#include "needle.h"

SemaphoreHandle_t task_semaphr;
uint16_t temp =0;
uint8_t arrys[5] = {0};
uint8_t arry0[4]={0};


uint16_t uart_recv_len = 1;
uint8_t uart_recv_data[100] ={0}; 

const osThreadAttr_t send_can_attributes = {
  .name = "send_can",
  .stack_size = 64 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
const osThreadAttr_t send_usart_attributes = {
  .name = "send_usart",
  .stack_size = 64 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

const osThreadAttr_t main_api_attributes = {
  .name = "main_api_attributes",
  .stack_size = 64 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
const osThreadAttr_t display_attributes = {
  .name = "display_attributes",
  .stack_size = 64 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

const osThreadAttr_t recv_uart_attributes = {
  .name = "recv_uart_attributes",
  .stack_size = 64 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

#define ATTR(name,sizes,prio) const osThreadAttr_t attr_##name = {\
  .name = #name,\
  .stack_size = (sizes) * 4,\
  .priority = (osPriority_t) prio,\
}
/* Uart initial */

void Uart_init( uint8_t *pData, uint16_t Size)
{

    HAL_UART_Receive_IT(&huart1, uart_recv_data+2, 1);


}


void recv_uart(void *arg)
{
    for (;;) {

        xSemaphoreTake(task_semaphr,portMAX_DELAY);

        osDelay(1);
    }

}



void send_can(void *arg)
{

    for (;;) {

		osDelay(1);
        CAN_senddata(&hcan);

        
    } 
        
        
    

}

void send_usart(void *arg)
{
    uint32_t len=10;
    uint8_t sdata[17]={0};
    for (;;) {

        /* if timeout set as portMAX_DELAY  ,that mean the task will block forever utill give a semaphr  */
        xSemaphoreTake(task_semaphr, portMAX_DELAY); //portMAX_DELAY

        uint8_t temp[10]={0};
        for (int i=0 ;i < len;i++) {

            uint32_t t=index.index;
            for(int j=0;j < i;j++) {
                t /= 10;
            }
            temp[len-1-i] = t % 10 +48;
        }
        #if 1
        memcpy(sdata,arrys,5);
        for(int i=0;i<5;i++){
          
            sdata[i] += 48;
        }
        sdata[2]='.';
        sdata[5]='\'';
        sdata[6]='C';
        sdata[7]=' ';
        sdata[8]=' ';
        sdata[9]=' ';
        sdata[10]=' ';

        memcpy(&sdata[11],arry0,4);
        for(int i=11;i<15;i++){
          
            sdata[i] += 48;
        }  
        sdata[15]=' ';
        sdata[16]=' ';
        
        HAL_UART_Transmit(&huart1,sdata,17,1000);
        #endif
        HAL_UART_Transmit(&huart1,temp,len,1000);

       HAL_UART_Transmit(&huart1,"\r\n",2,1000);//join this function find t
      


    }

}


//#define DELAY
void display(void *arg)
{
    float Temperature = 0;
    uint16_t temp1=0;
    for(;;) {

        
        #if 1
        dp_star();
        xSemaphoreTake(task_semaphr, portMAX_DELAY);
        /* Wait 2s 20000 * 100us =  */

        #ifdef DELAY
        __HAL_TIM_SET_COUNTER(&htim2, 0);
        HAL_TIM_Base_Start(&htim2);  
        while (__HAL_TIM_GET_COUNTER(&htim2) <20000){}
        #endif

        HAL_ADC_Stop(&hadc2);
        HAL_ADCEx_Calibration_Start(&hadc2);

        HAL_ADC_Start(&hadc2);
        HAL_ADC_PollForConversion(&hadc2, 100);
        
        temp1 = HAL_ADC_GetValue(&hadc2);
        for( int i=0 ; i< 4; i++) {
            uint16_t da = temp1;
            for(int j =0; j < i;j++) {
                da /= 10;
            }
            //da >>= i;
            //arry0[11-i] = da&0x1 ;
            arry0[3-i] = da%10 ;
        }
        #endif   
       
        #if 1
        float value = HAL_ADC_GetValue(&hadc1); /// 3、获取转换结果，把结果赋值给value变量
        float Vol_Value = value * (3.3 / 4096);

        Temperature = (1.43 - Vol_Value) / 0.0043 + 25;
        //printf("MCU Internal Temperature: %.4f\r\n", Temperature);
        // printf("MCU Internal Temperature: \r\n");
        temp = Temperature*100;
        arrys[0] = temp / 1000;
        arrys[1] = temp / 100 % 10;
        arrys[2] = 100;
        arrys[3] = temp / 10 % 10;
        arrys[4] = temp % 10;        
        
        //BaseType_t pxHigherPriorityTaskWoken;
        //xSemaphoreGiveFromISR(task_semaphr,&pxHigherPriorityTaskWoken);
        //xSemaphoreGive(task_semaphr);
        Set_x_y(12,6);
        for (int k = 0; k < 4; k++)
        {
            for (int i = 0; i < 6; i++)
            {
                {
                    write_data(0);
                }
            }
        }

        Set_x_y(12,6);
        for (int k = 0; k < 4; k++)
        {
            for (int i = 0; i < 6; i++)
            {
                write_data(F6x8[arry0[k] + 16][i]);
                
            }
        }    
        
        clear_();
        uint8_t arry1[4]={0};
        if (Temperature > 40)
        {
            
            arry1[3] = 'W' - 32;
            arry1[2] = 'A' - 32;
            arry1[1] = 'R' - 32;
            arry1[0] = 'N' - 32;
            Set_x_y(16,7);
        }
        else {
            
            arry1[3] = 'N' - 32;
            arry1[2] = 'O' - 32;
            arry1[1] = 'R' - 32;
            arry1[0] = 'M' - 32;
            Set_x_y(16,0);
        }

        for (int k = 3; k >= 0; k--)
        {
            for (int i = 0; i < 6; i++)
            {
                {
                    write_data(F6x8[arry1[k]][i]);
                }
            }
        }


        Set_x_y(94,7);
        for (int k = 0; k < 5; k++)
        {
            for (int i = 0; i < 6; i++)
            {
                if (arrys[k] == 100)
                {
                    write_data(F6x8[14][i]);
                }
                else
                {
                    write_data(F6x8[arrys[k] + 16][i]);
                }
            }
        }
        

        osDelay(1);
        #endif
        
    }
}

void main_api(void *arg)
{


    
    task_semaphr = xSemaphoreCreateBinary();
                   
    //osThreadNew(recv_uart,NULL,&recv_uart_attributes);
    //osThreadNew(send_can,NULL,&send_can_attributes);
    //osThreadNew(send_usart,NULL,&send_usart_attributes);
    osThreadNew(display,NULL,&display_attributes);
    for (;;) {

		
    }
}



void app_entry()
{

    osThreadNew(main_api, NULL, &main_api_attributes);
	
}



void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) // 接受邮箱0挂起中断回调函数
{
  
BaseType_t pxHigherPriorityTaskWoken;

    #if 1
    if (hcan->Instance == CAN1 )
    {

     
        HAL_CAN_GetRxMessage(hcan, CAN_FILTER_FIFO0, &RXHeader, RXmessage); // 获取数据
        //xSemaphoreGive(task_semaphr);//用此函数会造成任务优先级 卡死，
        xSemaphoreGiveFromISR(task_semaphr,&pxHigherPriorityTaskWoken);//* Use this function give a semaphr in interrupt service request */
        index.index++;
        
  
    }
    #endif
}



#define OFFSET 2
/**
  * @brief  Rx Transfer completed callbacks.
  * @param  huart  Pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

    static uint8_t * p = uart_recv_data + OFFSET;
    static uint8_t comd[]="starts";
    static BaseType_t pxHigherPriorityTaskWoken;  
    static uint8_t sizes =0;
    if (*p == '\n') {
        sizes = p - uart_recv_data -OFFSET + 1;

        

        if (*(p-1) != '\r' || *(p-2) == '\r' || *(p-2) == '\n' || *(p-2) == 0) {
            HAL_UART_Transmit(huart,"Eror command\r\n",sizeof("Eror command\r\n"),1000);
       
        }
        else {

        
            if (sizes > 2)
                HAL_UART_Transmit(huart,uart_recv_data+OFFSET,sizes,1000);

            int ss=0;
            for (int i=OFFSET ;i <sizes -2 ;i ++) {
                ss += uart_recv_data[i] ^ comd[i-OFFSET];
            }

            if (!ss) {
                xSemaphoreGiveFromISR(task_semaphr,&pxHigherPriorityTaskWoken);
                HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_8);
            }
        }
		p= uart_recv_data+OFFSET;
        memset(uart_recv_data+OFFSET, 0, sizes);
    }
    else {
        
        p++;

        if ( p - uart_recv_data >= 100) {
            p=uart_recv_data;
        }
        
    }


    
    HAL_UART_Receive_IT(huart, p, uart_recv_len);
}

