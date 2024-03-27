/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.h
  * @brief   This file contains all the function prototypes for
  *          the can.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CAN_H__
#define __CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
typedef enum{
  T_ERROR,
  T_IDLE,
  T_BUSY,
  T_INTERRUPT,
  T_RECVCAN
} TASK_T;

typedef union 
{
  uint8_t datas[4];
  uint32_t index;
} TDATA;


extern CAN_TxHeaderTypeDef TXHeader;
extern CAN_RxHeaderTypeDef RXHeader;
extern uint8_t TXmessage[8];
extern uint8_t RXmessage[8];
extern TASK_T TASK_FLAG;
extern TDATA index;

/* USER CODE END Includes */

extern CAN_HandleTypeDef hcan;

/* USER CODE BEGIN Private defines */
void CAN_senddata(CAN_HandleTypeDef *hcan);

/* USER CODE END Private defines */

void MX_CAN_Init(void);

/* USER CODE BEGIN Prototypes */
extern void app_entry(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __CAN_H__ */

