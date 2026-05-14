/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "st7789\st7789.h"
#include "barracarregamento.h"
#include <stdlib.h>
#include <time.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LE_BOTAO1 HAL_GPIO_ReadPin(BOTAO1_GPIO_Port, BOTAO1_Pin)
#define LE_BOTAO2 HAL_GPIO_ReadPin(BOTAO2_GPIO_Port, BOTAO2_Pin)
#define LE_BOTAO3 HAL_GPIO_ReadPin(BOTAO3_GPIO_Port, BOTAO3_Pin)
#define LE_BOTAO4 HAL_GPIO_ReadPin(BOTAO4_GPIO_Port, BOTAO4_Pin)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  ST7789_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  ST7789_Fill_Color(0XFC07);
	  ST7789_WriteString(0, 5, "Bem vindo!", Font_16x26, BLACK, 0XFC07);
	  ST7789_WriteString(0, 50, "Aperte PA9 para      iniciar a aula", Font_11x18, BLACK, 0XFC07);
	  HAL_Delay(3000);

	  int aula = 0;

	  	  if (LE_BOTAO4 == 0){
	  		  aula = 1;

	  		      ST7789_Fill_Color(0xFFE0);
	  			  ST7789_WriteString(0, 5, "Digite a senha", Font_16x26, BLACK, YELLOW);
	  			  ST7789_WriteString(0, 50, "PA09 = primeiro   digito", Font_11x18, BLACK, YELLOW);
	  			  ST7789_WriteString(0, 90, "PA11 = segundo    digito", Font_11x18, BLACK, YELLOW);
	  			  ST7789_WriteString(0, 130, "PA10 = Confirmar", Font_11x18, BLACK, YELLOW);
	  			  HAL_Delay(3000);

	  		  while ( aula == 1){

	  			  int senha;

	  			  srand(time(NULL));
	  			  senha = (rand()%99)+1;

	  			  int digito1 = 0; // digito da dezena
	  			  int digito2 = 0; // digito da unidade

	  			  int verificacao = 0;

	  			  while (senha != 0) {

	  			  ST7789_WriteChar(90, 160, digito1 + '0', Font_16x26, BLACK, WHITE);
	  			  ST7789_WriteChar(130, 160, digito2 + '0', Font_16x26, BLACK, WHITE);
	  			  HAL_Delay(500);

	  				  if (LE_BOTAO4 == 0 ) {
	  					  HAL_Delay(500);
	  					  if (digito1 <= 8)
	  						digito1++;
	  					  else
	  						 digito1 = 0;
	  				  }
	  				  else if (LE_BOTAO2 == 0){
	  					  HAL_Delay(500);
	  					  if (digito2 <= 8)
	  						digito2++;
	  					  else
	  						digito2 = 0;
	  				  }
	  				  else if (LE_BOTAO3 == 0){
	  					  HAL_Delay(500);
	  					  verificacao = senha - (digito1 * 10 + digito2);
	  					  if (verificacao == 0){
	  						ST7789_WriteString(0, 200, "Acesso permitido", Font_11x18, GREEN, YELLOW);
	  						senha = 0;
	  					  }
	  					  else {
	  						ST7789_WriteString(0, 200, "Senha incorreta", Font_11x18, RED, YELLOW);
	  						digito1 = 0;
	  						digito2 = 0;
	  					  }
	  				  }
	  			  }

	  			 int aluno1 = 0; // digito da dezena
	  			 int aluno2 = 0; // digito da quantidade
	  			 int totalalunos = 0;
	  			ST7789_Fill_Color(0xFFE0);
	  			ST7789_WriteString(0, 0, "Numero de alunos", Font_16x26, BLACK, YELLOW);
	  			ST7789_WriteString(0, 55, "PA09 = primeiro   digito", Font_11x18, BLACK, YELLOW);
	  			ST7789_WriteString(0, 90, "PA11 = segundo    digito", Font_11x18, BLACK, YELLOW);
	  			ST7789_WriteString(0, 140, "PA10 = Confirmar", Font_11x18, BLACK, YELLOW);

	  			 while (totalalunos == 0) {
	  				ST7789_WriteChar(90, 160, aluno1 + '0', Font_16x26, BLACK, WHITE);
	  				ST7789_WriteChar(130, 160, aluno2 + '0', Font_16x26, BLACK, WHITE);
	  				 if (LE_BOTAO4 == 0){
	  					HAL_Delay(500);
	  					if (aluno1 <= 8)
	  						aluno1++;
	  					else
	  						aluno1 = 0;
	  				 }
	  				 else if (LE_BOTAO2 == 0){
	  					HAL_Delay(500);
	  					if (aluno2 <= 8)
	  						aluno2++;
	  					else
	  						aluno2 = 0;
	  				 }
	  				 else if (LE_BOTAO3 == 0){
	  					 HAL_Delay(500);
	  					 totalalunos = (aluno1 * 10) + aluno2 ;
	  				 }
	  			 }
	  			 int presencaalunos = 0;
	  			 int saidaalunos = 0;
	  			 int contador = 0;
	  			 int contadorpresenca = 0;
	  			 ST7789_Fill_Color(0xFFE0);
	  			 ST7789_WriteString(0, 0, "Alunos em sala", Font_16x26, BLACK, YELLOW);
	  			 ST7789_WriteString(0, 30, "Aperte o botao PA09 para registrar a entrada", Font_7x10, BLACK, YELLOW);
	  			 ST7789_WriteString(0, 100, "Fora de sala", Font_16x26, BLACK, YELLOW);
	  			 ST7789_WriteString(0, 125, "Aperte o botao PA11 para ganhar   registrar saida e PA09 para o     retorno", Font_7x10, BLACK, YELLOW);
	  			 ST7789_WriteString(0, 200, "Aperte PA12 e PA10 para encerrar a aula", Font_7x10, BLACK, YELLOW);
	  			 HAL_Delay(1000);

	  			 while (aula == 1){
	  				ST7789_WriteChar(100,150, saidaalunos + '0', Font_16x26, BLACK, WHITE);
	  				DrawLoadingBar(presencaalunos, totalalunos);
	  				HAL_Delay(1000);
	  				if (LE_BOTAO1 == 0 && LE_BOTAO3 == 0){
	  					 ST7789_Fill_Color(0xFFE0);
	  					 ST7789_WriteString(0, 0, "Relatorio", Font_16x26, BLACK, YELLOW);
	  					ST7789_WriteString(9, 56, "Alunos registrados", Font_11x18, BLACK, YELLOW);
	  					ST7789_WriteChar(100, 111, presencaalunos + '0', Font_16x26, BLACK, WHITE);
	  					ST7789_WriteString(9, 146, "Saidas durante a    aula", Font_11x18, BLACK, YELLOW);
	  					ST7789_WriteChar(100, 200, contador + '0', Font_16x26, BLACK, WHITE);
	  					HAL_Delay(120000);
	  					aula = 0;
	  				 }
	  				 else if (LE_BOTAO2 == 0){
	  					if (saidaalunos < 3 && presencaalunos > 0){
	  					        saidaalunos++;
	  					        presencaalunos--;
	  					        contador++;
	  					    }
	  					    else{
	  					        ST7789_WriteString(0, 175,
	  					        "Numero de pessoas fora de sala excedido",
	  					        Font_7x10, RED, YELLOW);
	  					        HAL_Delay(100);
	  					    }
	  				 }
	  				 else if (LE_BOTAO3 == 0){
	  					    if(saidaalunos > 0 && presencaalunos > 0){
	  					        saidaalunos--;
	  					        presencaalunos++;
	  					    }
	                    }
	  				 else if (LE_BOTAO4 == 0){

	  					    if (presencaalunos < totalalunos){
	  					        presencaalunos++;
	  					        contadorpresenca++;
	  					    }
	  					    else{
	  					        ST7789_WriteString(0, 50,
	  					        "Numero maximo de alunos atingido",
	  					        Font_7x10, BLACK, YELLOW);
	  					    }
	  					}
	  				 }
	  		 	 }
	  		  }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ST7789_CS_GPIO_Port, ST7789_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, ST7789_DC_Pin|ST7789_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : ST7789_CS_Pin */
  GPIO_InitStruct.Pin = ST7789_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ST7789_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ST7789_DC_Pin ST7789_RST_Pin */
  GPIO_InitStruct.Pin = ST7789_DC_Pin|ST7789_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : BOTAO4_Pin BOTAO3_Pin BOTAO2_Pin BOTAO1_Pin */
  GPIO_InitStruct.Pin = BOTAO4_Pin|BOTAO3_Pin|BOTAO2_Pin|BOTAO1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

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

#ifdef  USE_FULL_ASSERT
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
