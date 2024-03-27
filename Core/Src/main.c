/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "adc.h"
#include "can.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "needle.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

//local master 
// git branch --set-upstream-to=origin/master master 

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/************************************6*8***********************************/
const unsigned char F6x8[][6] =
    {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // sp
        0x00, 0x00, 0x00, 0x2f, 0x00, 0x00, // !
        0x00, 0x00, 0x07, 0x00, 0x07, 0x00, // "
        0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14, // #
        0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12, // $
        0x00, 0x62, 0x64, 0x08, 0x13, 0x23, // %
        0x00, 0x36, 0x49, 0x55, 0x22, 0x50, // &
        0x00, 0x00, 0x05, 0x03, 0x00, 0x00, // '
        0x00, 0x00, 0x1c, 0x22, 0x41, 0x00, // (
        0x00, 0x00, 0x41, 0x22, 0x1c, 0x00, // )
        0x00, 0x14, 0x08, 0x3E, 0x08, 0x14, // *
        0x00, 0x08, 0x08, 0x3E, 0x08, 0x08, // +
        0x00, 0x00, 0x00, 0xA0, 0x60, 0x00, // ,
        0x00, 0x08, 0x08, 0x08, 0x08, 0x08, // -
        0x00, 0x00, 0x60, 0x60, 0x00, 0x00, // .
        0x00, 0x20, 0x10, 0x08, 0x04, 0x02, // /
        0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E, // 0
        0x00, 0x00, 0x42, 0x7F, 0x40, 0x00, // 1
        0x00, 0x42, 0x61, 0x51, 0x49, 0x46, // 2
        0x00, 0x21, 0x41, 0x45, 0x4B, 0x31, // 3
        0x00, 0x18, 0x14, 0x12, 0x7F, 0x10, // 4
        0x00, 0x27, 0x45, 0x45, 0x45, 0x39, // 5
        0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30, // 6
        0x00, 0x01, 0x71, 0x09, 0x05, 0x03, // 7
        0x00, 0x36, 0x49, 0x49, 0x49, 0x36, // 8
        0x00, 0x06, 0x49, 0x49, 0x29, 0x1E, // 9
        0x00, 0x00, 0x36, 0x36, 0x00, 0x00, // :
        0x00, 0x00, 0x56, 0x36, 0x00, 0x00, // ;
        0x00, 0x08, 0x14, 0x22, 0x41, 0x00, // <
        0x00, 0x14, 0x14, 0x14, 0x14, 0x14, // =
        0x00, 0x00, 0x41, 0x22, 0x14, 0x08, // >
        0x00, 0x02, 0x01, 0x51, 0x09, 0x06, // ?
        0x00, 0x32, 0x49, 0x59, 0x51, 0x3E, // @
        0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C, // A
        0x00, 0x7F, 0x49, 0x49, 0x49, 0x36, // B
        0x00, 0x3E, 0x41, 0x41, 0x41, 0x22, // C
        0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C, // D
        0x00, 0x7F, 0x49, 0x49, 0x49, 0x41, // E
        0x00, 0x7F, 0x09, 0x09, 0x09, 0x01, // F
        0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A, // G
        0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F, // H
        0x00, 0x00, 0x41, 0x7F, 0x41, 0x00, // I
        0x00, 0x20, 0x40, 0x41, 0x3F, 0x01, // J
        0x00, 0x7F, 0x08, 0x14, 0x22, 0x41, // K
        0x00, 0x7F, 0x40, 0x40, 0x40, 0x40, // L
        0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F, // M
        0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F, // N
        0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E, // O
        0x00, 0x7F, 0x09, 0x09, 0x09, 0x06, // P
        0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E, // Q
        0x00, 0x7F, 0x09, 0x19, 0x29, 0x46, // R
        0x00, 0x46, 0x49, 0x49, 0x49, 0x31, // S
        0x00, 0x01, 0x01, 0x7F, 0x01, 0x01, // T
        0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F, // U
        0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F, // V
        0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F, // W
        0x00, 0x63, 0x14, 0x08, 0x14, 0x63, // X
        0x00, 0x07, 0x08, 0x70, 0x08, 0x07, // Y
        0x00, 0x61, 0x51, 0x49, 0x45, 0x43, // Z
        0x00, 0x00, 0x7F, 0x41, 0x41, 0x00, // [
        0x00, 0x55, 0x2A, 0x55, 0x2A, 0x55, // 55
        0x00, 0x00, 0x41, 0x41, 0x7F, 0x00, // ]
        0x00, 0x04, 0x02, 0x01, 0x02, 0x04, // ^
        0x00, 0x40, 0x40, 0x40, 0x40, 0x40, // _
        0x00, 0x00, 0x01, 0x02, 0x04, 0x00, // '
        0x00, 0x20, 0x54, 0x54, 0x54, 0x78, // a
        0x00, 0x7F, 0x48, 0x44, 0x44, 0x38, // b
        0x00, 0x38, 0x44, 0x44, 0x44, 0x20, // c
        0x00, 0x38, 0x44, 0x44, 0x48, 0x7F, // d
        0x00, 0x38, 0x54, 0x54, 0x54, 0x18, // e
        0x00, 0x08, 0x7E, 0x09, 0x01, 0x02, // f
        0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C, // g
        0x00, 0x7F, 0x08, 0x04, 0x04, 0x78, // h
        0x00, 0x00, 0x44, 0x7D, 0x40, 0x00, // i
        0x00, 0x40, 0x80, 0x84, 0x7D, 0x00, // j
        0x00, 0x7F, 0x10, 0x28, 0x44, 0x00, // k
        0x00, 0x00, 0x41, 0x7F, 0x40, 0x00, // l
        0x00, 0x7C, 0x04, 0x18, 0x04, 0x78, // m
        0x00, 0x7C, 0x08, 0x04, 0x04, 0x78, // n
        0x00, 0x38, 0x44, 0x44, 0x44, 0x38, // o
        0x00, 0xFC, 0x24, 0x24, 0x24, 0x18, // p
        0x00, 0x18, 0x24, 0x24, 0x18, 0xFC, // q
        0x00, 0x7C, 0x08, 0x04, 0x04, 0x08, // r
        0x00, 0x48, 0x54, 0x54, 0x54, 0x20, // s
        0x00, 0x04, 0x3F, 0x44, 0x40, 0x20, // t
        0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C, // u
        0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C, // v
        0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C, // w
        0x00, 0x44, 0x28, 0x10, 0x28, 0x44, // x
        0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C, // y
        0x00, 0x44, 0x64, 0x54, 0x4C, 0x44, // z
        0x14, 0x14, 0x14, 0x14, 0x14, 0x14, // horiz lines
};

char smalls[][40] = {
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xF0,0xFE,0xFE,0xF8,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    },

    {0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xC0,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xE0,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
    },

    {0x01,0x01,0x03,0x07,0x07,0x0F,0x1F,0x3F,0x3F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x3F,0x3F,0x1F,0x0F,0x0F,0x07,0x03,0x01,0x01,
    },

    { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xF0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    },

    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x78,0x7F,0x3F,0x1F,0x0F,0x0F,0x07,0x03,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x07,0x0F,0x1F,0x3F,0x3F,0x7C,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    }, 
};

void write_command(uint8_t com)
{

    uint8_t datas[2];
    datas[0] = 0;
    datas[1] = com;
    HAL_I2C_Master_Transmit(&hi2c1, 0x78, datas, 2, 1000);
}
void write_data(uint8_t data)
{
    uint8_t datas[2];
    datas[0] = 0x40;
    datas[1] = data;
    HAL_I2C_Master_Transmit(&hi2c1, 0x78, datas, 2, 1000);
}

void OLED_Set_Pos(unsigned char x, unsigned char y)
{
    write_command(0xb0 + y);
    write_command(((x & 0xf0) >> 4) | 0x10);
    write_command((x & 0x0f));
}

void dis_init()
{

    write_command(0xAE); // 关闭显示

    write_command(0x20);     // 设置显示模式
    write_command(0x02);     // 设置位页地址模式
    write_command(0xB0); // 写显示内容 页地址             设置page地址起始地址
    write_command(0x10);     // 写显示内容 列地址高四位        columnd地址起始的高4位
    write_command(0x00);     // 写显示内容 列列地址低四位      columnd地址起始的低4位

    write_command(0x21); // 设置 columnd(列) 的限制地址
    write_command(0x0);  // 设置 columnd(列) 起始地址
    write_command(0xff); // 设置 columnd(列) 结束地址

    write_command(0x22); // 设置 页 的限制地址
    write_command(0x0);  // 设置 页 起始地址
    write_command(0x7);  // 设置 页 结束地址

    // 设置RAM中垂直第N位重定向位COM0,也就是垂直高度64位的显示屏垂直高度的COM0（COM0-COM63）设置成RAM内存中第N位，
    // 即，显示屏的第1个位置显示内容的地址重定向到RAM中地址N，整个地址循环定向到显示屏显示
    // 也即，显示屏从RAM第N个地址所对应的内容开始显示
    write_command(0x40 + 0);

    write_command(0x81); // contract control         设置对比度命令
    write_command(0xff); //--128                      设置对比度 1-255

    write_command(0xA6); //--normal / reverse 显示反转，A6:黑底白字  A7:白底黑字

    // 固定参数
    {
    write_command(0xA1); // set segment remap

    write_command(0xA8); //--set multiplex ratio(1 to 64)
    write_command(0x3F); //--1/32 duty

    write_command(0xA1); // set segment remap 列重定向

    write_command(0xD3); //-set display offset
    write_command(0x00); //

    write_command(0xD5); // set osc division 设置显示帧数
    write_command(0xF0); //

    write_command(0xD8); // set area color mode off
    write_command(0x05); //

    write_command(0xD9); // Set Pre-Charge Period 预充电周期
    write_command(0xF1); //

    write_command(0xC8); // Com scan direction
    write_command(0xDA); // set com pin configuartion
    write_command(0x12); //

    write_command(0xDB); // set Vcomh 设置电平
    write_command(0x30); //

    write_command(0x8D); // set charge pump enable
    write_command(0x14); //

    write_command(0x20); // set charge pump enable
    write_command(0x00); //
}
    write_command(0xAF); //--turn on oled panel 打开显示

    HAL_Delay(1);

    for (int i = 0; i < 8; i++)
    {
        write_command(0xb0 + i); // 设置页地址  0~7
        write_command(0x00);     // 设置显示位置—列地址 低四位
        write_command(0x10);     // 设置显示位置—列地址 高四位
        for (int n = 0; n < 128; n++)
            write_data(0);
    }
    
}


void movde_()
{
    for (int k = 0; k < 128; k++)
    {
        write_command(0xB0);
        write_command(0x00 + k % 16);
        write_command(0x10 + k / 16);
        for (int i = 0; i < 10; i++)
            write_data(0x0f);

        HAL_Delay(1);

        write_command(0xB0);
        write_command(0x00 + k % 16);
        write_command(0x10 + k / 16);
        for (int m = 0; m < 10; m++)
            write_data(0);
    }
}
void Set_x_y(uint8_t x, uint8_t y)
{
    write_command(0xB0 + y);
    write_command(((x & 0xf0) >> 4) | 0x10);
    write_command((x & 0x0f));
}
void clear_()
{

    Set_x_y(94, 7);
    for (int k = 4; k >= 0; k--)
    {
        for (int i = 0; i < 6; i++)
        {
            write_data(0);
        }
    }

    Set_x_y(16, 7);
    for (int k = 4; k >= 0; k--)
    {
        for (int i = 0; i < 6; i++)
        {

            {
                write_data(0);
            }
        }
    }

    Set_x_y(16, 0);
    for (int k = 4; k >= 0; k--)
    {
        for (int i = 0; i < 6; i++)
        {

            {
                write_data(0);
            }
        }
    }
}
void delays(uint16_t ums)
{
    HAL_TIM_Base_Start(&htim2);
    __HAL_TIM_SET_COUNTER(&htim2, 0);

    while (__HAL_TIM_GET_COUNTER(&htim2) < ums)
    {
    }

    HAL_TIM_Base_Stop(&htim2);

}
void dp_star()
{
    for (int i = 0; i < 5; i++)
    {

        write_command(0xB0 + i + 1);
        write_command(((64 & 0xf0) >> 4) | 0x10);
        write_command((64 & 0x0f));

        for (int n = 0; n < 40; n++)
        {
            write_data(smalls[i][n]);
        }
    }
}

char recv[100] = {0};
uint8_t data_len = 0;

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_USART1_UART_Init();
    MX_TIM2_Init();
    MX_ADC1_Init();
    MX_CAN_Init();
    MX_ADC2_Init();
    /* USER CODE BEGIN 2 */

    dis_init();
   
    Uart_init( NULL, 1);
    // HAL_UART_Receive_IT(&huart1, (uint8_t *)&recv[data_len], 1);

    float Temperature;
    // HAL_TIM_Base_Start_IT(&htim2);

    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 100); /* start adc and set timeout is 100 ms */

    int ks = 0;
    while (0)
    {

        // CAN_senddata(&hcan);
        //
        // HAL_Delay(1000);
        CAN_senddata(&hcan);
        HAL_TIM_Base_Start(&htim2);
        __HAL_TIM_SET_COUNTER(&htim2, 0);

        while (1)
        {
        }

#if 1
        __HAL_TIM_SET_COUNTER(&htim2, 0);
        HAL_TIM_Base_Start_IT(&htim2);

        dp_star();

        while (__HAL_TIM_GET_COUNTER(&htim2) < 15000)
        {
        }

        HAL_TIM_Base_Stop_IT(&htim2);

#endif
        uint16_t temp = 0;

#if 1

        float value = HAL_ADC_GetValue(&hadc1); 
        float Vol_Value = value * (3.3 / 4096);
        // int Temperature=0;
        Temperature = (1.43 - Vol_Value) / 0.0043 + 25;
        // printf("MCU Internal Temperature: %.4f\r\n", Temperature);
        //  printf("MCU Internal Temperature: \r\n");

        dp_star();
        clear_();
        uint8_t arrys[5] = {0};
        if (Temperature > 40)
        {

            arrys[3] = 'W' - 32;
            arrys[2] = 'A' - 32;
            arrys[1] = 'R' - 32;
            arrys[0] = 'N' - 32;
            Set_x_y(16, 7);
        }
        else
        {

            arrys[3] = 'N' - 32;
            arrys[2] = 'O' - 32;
            arrys[1] = 'R' - 32;
            arrys[0] = 'M' - 32;
            Set_x_y(16, 0);
        }

        for (int k = 3; k >= 0; k--)
        {
            for (int i = 0; i < 6; i++)
            {
                {
                    write_data(F6x8[arrys[k]][i]);
                }
            }
        }

        ks++;

        temp = Temperature * 100;
        arrys[4] = temp / 1000;
        arrys[3] = temp / 100 % 10;
        arrys[2] = 100;
        arrys[1] = temp / 10 % 10;
        arrys[0] = temp % 10;
        Set_x_y(94, 7);

        for (int k = 4; k >= 0; k--)
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
    }

#endif

    #if 1
    

    #endif
    /* USER CODE END 2 */

    /* Init scheduler */
    osKernelInitialize(); /* Call init function for freertos objects (in freertos.c) */
    // MX_FREERTOS_Init();
     app_entry();
    /* Start scheduler */
    osKernelStart();

    /* We should never get here as control is now taken by the scheduler */
    /* Infinite loop */
    /* USER CODE BEGIN WHILE */

    int kn = 0;

    while (1)
    {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */

        // void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);//Use this funtion as IRQ function for : HAL_UART_Receive_IT(&huart1, (uint8_t *)&recv[data_len], 1);

        if (kn >= 10000)
        {
            kn = 0;
        }
        int arrys[4] = {0};
        arrys[3] = kn % 10;
        arrys[2] = kn / 10 % 10;
        arrys[1] = kn / 100 % 10;
        arrys[0] = kn / 1000 % 10;
        write_command(0xB0 + 7);
        write_command(0x00 + 104 % 16); // 
        write_command(0x10 + 104 / 16); // 
        HAL_Delay(1);
        for (int k = 0; k < 4; k++)
        {
            for (int i = 0; i < 6; i++)
                write_data(F6x8[arrys[k] + 16][i]);
        }

#if 1

        for (int k = 0; k < 128; k++)
        {
            write_command(0xB0);
            write_command(0x00 + k % 16);
            write_command(0x10 + k / 16);
            for (int i = 0; i < 10; i++)
                write_data(0x0f);

            HAL_Delay(1);

            write_command(0xB0);
            write_command(0x00 + k % 16);
            write_command(0x10 + k / 16);
            for (int m = 0; m < 10; m++)
                write_data(0);
        }
    }
#endif

    /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
    PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  Period elapsed callback in non blocking mode
 * @note   This function is called  when TIM3 interrupt took place, inside
 * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
 * a global variable "uwTick" used as application time base.
 * @param  htim : TIM handle
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    /* USER CODE BEGIN Callback 0 */

    /* USER CODE END Callback 0 */
    if (htim->Instance == TIM3)
    {
        HAL_IncTick();
    }
    /* USER CODE BEGIN Callback 1 */
    else if (htim->Instance == TIM2)
    {
      
    }
    /* USER CODE END Callback 1 */
}



/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
