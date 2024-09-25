/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define IND_LED_1_Pin GPIO_PIN_14
#define IND_LED_1_GPIO_Port GPIOC
#define IND_LED_2_Pin GPIO_PIN_15
#define IND_LED_2_GPIO_Port GPIOC
#define IR_1_TSTR_Pin GPIO_PIN_0
#define IR_1_TSTR_GPIO_Port GPIOA
#define IR_2_TSTR_Pin GPIO_PIN_1
#define IR_2_TSTR_GPIO_Port GPIOA
#define IR_3_TSTR_Pin GPIO_PIN_2
#define IR_3_TSTR_GPIO_Port GPIOA
#define IR_4_TSTR_Pin GPIO_PIN_3
#define IR_4_TSTR_GPIO_Port GPIOA
#define IR_5_TSTR_Pin GPIO_PIN_4
#define IR_5_TSTR_GPIO_Port GPIOA
#define IR_6_TSTR_Pin GPIO_PIN_5
#define IR_6_TSTR_GPIO_Port GPIOA
#define MOTOR_1_EN_C1_Pin GPIO_PIN_6
#define MOTOR_1_EN_C1_GPIO_Port GPIOA
#define MOTOR_1_EN_C2_Pin GPIO_PIN_7
#define MOTOR_1_EN_C2_GPIO_Port GPIOA
#define MOTOR_2_EN_C1_Pin GPIO_PIN_0
#define MOTOR_2_EN_C1_GPIO_Port GPIOB
#define MOTOR_2_EN_C2_Pin GPIO_PIN_1
#define MOTOR_2_EN_C2_GPIO_Port GPIOB
#define DRV_8833_FAULT_Pin GPIO_PIN_2
#define DRV_8833_FAULT_GPIO_Port GPIOB
#define IR_1_LED_Pin GPIO_PIN_12
#define IR_1_LED_GPIO_Port GPIOB
#define IR_2_LED_Pin GPIO_PIN_13
#define IR_2_LED_GPIO_Port GPIOB
#define IR_3_LED_Pin GPIO_PIN_14
#define IR_3_LED_GPIO_Port GPIOB
#define IR_4_LED_Pin GPIO_PIN_15
#define IR_4_LED_GPIO_Port GPIOB
#define IR_5_LED_Pin GPIO_PIN_8
#define IR_5_LED_GPIO_Port GPIOA
#define IR_6_LED_Pin GPIO_PIN_9
#define IR_6_LED_GPIO_Port GPIOA
#define MPU_6050_INT_Pin GPIO_PIN_10
#define MPU_6050_INT_GPIO_Port GPIOA
#define CTRL_BTN_Pin GPIO_PIN_15
#define CTRL_BTN_GPIO_Port GPIOA
#define DRV_8833_MOTOR_1_IN_1_Pin GPIO_PIN_4
#define DRV_8833_MOTOR_1_IN_1_GPIO_Port GPIOB
#define DRV_8833_MOTOR_1_IN_2_Pin GPIO_PIN_5
#define DRV_8833_MOTOR_1_IN_2_GPIO_Port GPIOB
#define DRV_8833_MOTOR_2_IN_1_Pin GPIO_PIN_6
#define DRV_8833_MOTOR_2_IN_1_GPIO_Port GPIOB
#define DRV_8833_MOTOR_2_IN_2_Pin GPIO_PIN_7
#define DRV_8833_MOTOR_2_IN_2_GPIO_Port GPIOB
#define MPU_6050_TOF_SCL_Pin GPIO_PIN_8
#define MPU_6050_TOF_SCL_GPIO_Port GPIOB
#define MPU_6050_TOF_SDA_Pin GPIO_PIN_9
#define MPU_6050_TOF_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
