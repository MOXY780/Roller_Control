/**
  ******************************************************************************
  * File Name          : gpio.c
  * Description        : This file provides code for the configuration
  *                      of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LOAD_Pin|SYNC_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, INP_1_Pin|INP_2_Pin|INP_3_Pin|INP_4_Pin 
                          |LD2_Pin|EN_OUT_Pin|EN_PWR_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, EN_Pin|INP_5_Pin|INP_6_Pin|IGN_Pin 
                          |INP_8_Pin|INP_7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PCPin PCPin */
  GPIO_InitStruct.Pin = B1_USER_Pin|Fault_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PCPin PCPin */
  GPIO_InitStruct.Pin = LOAD_Pin|SYNC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PAPin PAPin PAPin PAPin 
                           PAPin PAPin PAPin */
  GPIO_InitStruct.Pin = INP_1_Pin|INP_2_Pin|INP_3_Pin|INP_4_Pin 
                          |LD2_Pin|EN_OUT_Pin|EN_PWR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = OUT_ERROR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(OUT_ERROR_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin PBPin PBPin 
                           PBPin PBPin */
  GPIO_InitStruct.Pin = EN_Pin|INP_5_Pin|INP_6_Pin|IGN_Pin 
                          |INP_8_Pin|INP_7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin PBPin PBPin 
                           PBPin */
  GPIO_InitStruct.Pin = CONT1_Pin|CONT0_Pin|CONT4_Pin|CONT3_Pin 
                          |CONT2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */
/**
  * @brief  This function set GPOs to default values.
  * @param  None
  * @retval None
  */
void SetGPOtoDefault(void)
{
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SYNC_GPIO_Port, SYNC_Pin, GPIO_PIN_RESET); 
	HAL_GPIO_WritePin(LOAD_GPIO_Port, LOAD_Pin, GPIO_PIN_RESET); 
	HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET); 
	HAL_GPIO_WritePin(EN_OUT_GPIO_Port, EN_OUT_Pin, GPIO_PIN_RESET); 
	HAL_GPIO_WritePin(IGN_GPIO_Port, IGN_Pin, GPIO_PIN_RESET); 
	HAL_GPIO_WritePin(EN_PWR_GPIO_Port, EN_PWR_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(INP_1_GPIO_Port, INP_1_Pin, GPIO_PIN_RESET); 
	HAL_GPIO_WritePin(INP_2_GPIO_Port, INP_2_Pin, GPIO_PIN_RESET); 
	HAL_GPIO_WritePin(INP_3_GPIO_Port, INP_3_Pin, GPIO_PIN_RESET); 
	HAL_GPIO_WritePin(INP_4_GPIO_Port, INP_4_Pin, GPIO_PIN_RESET); 
	HAL_GPIO_WritePin(INP_5_GPIO_Port, INP_5_Pin, GPIO_PIN_RESET); 
	HAL_GPIO_WritePin(INP_6_GPIO_Port, INP_6_Pin, GPIO_PIN_RESET); 
	HAL_GPIO_WritePin(INP_7_GPIO_Port, INP_7_Pin, GPIO_PIN_RESET); 
	HAL_GPIO_WritePin(INP_8_GPIO_Port, INP_8_Pin, GPIO_PIN_RESET);
}

/**
  * @brief  This function enable power for remote control.
  * @param  None
  * @retval None
  */
void EnableRemote(void)
{
	HAL_GPIO_WritePin(EN_PWR_GPIO_Port, EN_PWR_Pin, GPIO_PIN_SET);
}

/**
  * @brief  This function get Battery Warning.
  * @param  None
  * @retval None
  */
GPIO_PinState GetBatWarn(void)
{
	return HAL_GPIO_ReadPin(CONT0_GPIO_Port, CONT0_Pin);
}

/**
  * @brief  This function get Oil Warning.
  * @param  None
  * @retval None
  */
GPIO_PinState GetOilWarn(void)
{
	return HAL_GPIO_ReadPin(CONT1_GPIO_Port, CONT1_Pin);
}

/**
  * @brief  This function get Temp Warning.
  * @param  None
  * @retval None
  */
GPIO_PinState GetTempWarn(void)
{
	return HAL_GPIO_ReadPin(CONT2_GPIO_Port, CONT2_Pin);
}

/**
  * @brief  This function get Error from Power Supply of Remote.
  * @param  None
  * @retval None
  */
GPIO_PinState GetOutError(void)
{
	return HAL_GPIO_ReadPin(OUT_ERROR_GPIO_Port, OUT_ERROR_Pin);
}

/**
  * @brief  This function get Error from Output driver.
  * @param  None
  * @retval None
  */
GPIO_PinState GetFault(void)
{
	return HAL_GPIO_ReadPin(Fault_GPIO_Port, Fault_Pin);
}
/* USER CODE END 2 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
