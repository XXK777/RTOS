/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    can.c
 * @brief   This file provides code for the configuration
 *          of the CAN instances.
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
#include "can.h"

/* USER CODE BEGIN 0 */
#include "usart.h"
#include "tim.h"
#include "needle.h"

uint16_t local_filter_id = 0x700; /*the can id is for std can  that only allow the most heigh bit is b'111 xxxx xxxx , can receive*/
/**
 * 
 *  sFilterConfig.FilterIdHigh      = ((uint32_t)local_filter_id<<5); //设置过滤器ID�??????16�??????
    sFilterConfig.FilterIdLow       = 0;
    sFilterConfig.FilterMaskIdHigh  = ((uint32_t)local_filter_id<<5); //设置过滤器掩砝高16�??????
    sFilterConfig.FilterMaskIdLow   =0;//设置过滤器掩砝低16�??????
*/
/* USER CODE END 0 */

CAN_HandleTypeDef hcan;

/* CAN init function */
void MX_CAN_Init(void)
{

  /* USER CODE BEGIN CAN_Init 0 */

  /* USER CODE END CAN_Init 0 */

  /* USER CODE BEGIN CAN_Init 1 */

  /* USER CODE END CAN_Init 1 */
  hcan.Instance = CAN1;
  hcan.Init.Prescaler = 72;
  hcan.Init.Mode = CAN_MODE_LOOPBACK;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_6TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_6TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = DISABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN_Init 2 */
	  CAN_FilterTypeDef sFilterConfig;
 
    sFilterConfig.FilterActivation = ENABLE;//打开过滤�??????
    sFilterConfig.FilterBank = 0;//过滤�??????0 这里坯设0-13
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;//采用掩砝模弝
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;//采用32佝掩砝模�??????
    sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;//采用FIFO0
    
    sFilterConfig.FilterIdHigh      = ((uint32_t)local_filter_id<<5); //设置过滤器ID�??????16�??????
    sFilterConfig.FilterIdLow       = 0;
    sFilterConfig.FilterMaskIdHigh  = ((uint32_t)local_filter_id<<5); //设置过滤器掩砝高16�??????
    sFilterConfig.FilterMaskIdLow   =0;//设置过滤器掩砝低16�??????
    if(HAL_CAN_ConfigFilter(&hcan,&sFilterConfig) != HAL_OK)//初始化过滤器
    {
    Error_Handler();
    }
    if (HAL_CAN_Start(&hcan) != HAL_OK) // 打开Can
    { 
        Error_Handler();
    }

    if (HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK) // �??????坯接块邮�??????0挂起中断
    {
        Error_Handler();
    }
  /* USER CODE END CAN_Init 2 */

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**CAN GPIO Configuration
    PA11     ------> CAN_RX
    PA12     ------> CAN_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(USB_LP_CAN1_RX0_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();

    /**CAN GPIO Configuration
    PA11     ------> CAN_RX
    PA12     ------> CAN_TX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11|GPIO_PIN_12);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USB_LP_CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */


CAN_TxHeaderTypeDef TXHeader;
CAN_RxHeaderTypeDef RXHeader;

uint8_t TXmessage[8] = {'A','B','C','D','E','F','G','H'};
uint8_t RXmessage[8];
uint32_t pTxMailbox = 0;
TDATA index;
TASK_T TASK_FLAG = T_INTERRUPT;


void CAN_senddata(CAN_HandleTypeDef *hcan)
{
    TXHeader.StdId = 0x1f0 | local_filter_id; /*keep the second bit is 1 */
    TXHeader.ExtId = 0x0;
    TXHeader.DLC = 8;
    TXHeader.IDE = CAN_ID_STD;
    TXHeader.RTR = CAN_RTR_DATA;
    TXHeader.TransmitGlobalTime = DISABLE;
    HAL_CAN_AddTxMessage(hcan, &TXHeader, TXmessage, &pTxMailbox);
}

/* USER CODE END 1 */
