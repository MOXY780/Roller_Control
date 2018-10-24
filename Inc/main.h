/**
  ******************************************************************************
  * File Name          : main.hpp
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define B1_USER_Pin GPIO_PIN_13
#define B1_USER_GPIO_Port GPIOC
#define LOAD_Pin GPIO_PIN_0
#define LOAD_GPIO_Port GPIOC
#define SYNC_Pin GPIO_PIN_1
#define SYNC_GPIO_Port GPIOC
#define ADC_PWR_Pin GPIO_PIN_2
#define ADC_PWR_GPIO_Port GPIOC
#define Fault_Pin GPIO_PIN_3
#define Fault_GPIO_Port GPIOC
#define INP_1_Pin GPIO_PIN_0
#define INP_1_GPIO_Port GPIOA
#define INP_2_Pin GPIO_PIN_1
#define INP_2_GPIO_Port GPIOA
#define INP_3_Pin GPIO_PIN_3
#define INP_3_GPIO_Port GPIOA
#define INP_4_Pin GPIO_PIN_4
#define INP_4_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define OUT_ERROR_Pin GPIO_PIN_4
#define OUT_ERROR_GPIO_Port GPIOC
#define EN_Pin GPIO_PIN_0
#define EN_GPIO_Port GPIOB
#define CONT1_Pin GPIO_PIN_1
#define CONT1_GPIO_Port GPIOB
#define CONT0_Pin GPIO_PIN_2
#define CONT0_GPIO_Port GPIOB
#define CONT4_Pin GPIO_PIN_13
#define CONT4_GPIO_Port GPIOB
#define CONT3_Pin GPIO_PIN_14
#define CONT3_GPIO_Port GPIOB
#define CONT2_Pin GPIO_PIN_15
#define CONT2_GPIO_Port GPIOB
#define EN_OUT_Pin GPIO_PIN_12
#define EN_OUT_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define EN_PWR_Pin GPIO_PIN_15
#define EN_PWR_GPIO_Port GPIOA
#define INP_5_Pin GPIO_PIN_4
#define INP_5_GPIO_Port GPIOB
#define INP_6_Pin GPIO_PIN_5
#define INP_6_GPIO_Port GPIOB
#define IGN_Pin GPIO_PIN_7
#define IGN_GPIO_Port GPIOB
#define INP_8_Pin GPIO_PIN_8
#define INP_8_GPIO_Port GPIOB
#define INP_7_Pin GPIO_PIN_9
#define INP_7_GPIO_Port GPIOB

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */
#define FORW			0x01
#define FORWR			0x02
#define RIGTH			0x03
#define BACKR			0x04
#define BACK			0x05
#define BACKL			0x06
#define LEFT			0x07
#define FORWL			0x08
#define HALT			0x09

#define JOYSTICK	0x0F
#define NORMAL		0x1F
#define VIBR			0x20
#define SLOW			0x3F
#define FAST			0x40
#define OFF				0x7F
#define ON				0x80

/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
