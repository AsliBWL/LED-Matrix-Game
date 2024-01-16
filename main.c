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
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "P10.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
extern Pixel P[15], R[110];
extern uint8_t pData[16];
Pixel E[28];
uint8_t x_shift = 9;
uint8_t y_shift = 9;
uint8_t x_person_left = 0;
uint8_t x_person_right = 0;
extern uint8_t i_left, i_right, i_rem_right, i_rem_left, s;
void FillPixelX(int start, int end, int Y)
{
	for (int m = start + 1; m < end; m++)
	{
		R[m].x = R[m - 1].x + 1;
		R[m].y = Y;
	}
}
void FillPixelY(int start, int end, int X, int direction)
{
	int a = 0;
	if (direction == 0)
	{
		a = -1;
	}
	else
	{
		a = 1;
	}
	for (int m = start + 1; m < end; m++)
	{
		R[m].y = R[m - 1].y + a;
		R[m].x = X;
	}
}
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
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
  MX_SPI2_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_SPI_Init (&hspi2);
  HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  //A person
	P[0].x = 1;
	P[0].y = 1;
	P[1].x = 1;
	P[1].y = 2;
	P[2].x = 2;
	P[2].y = 3;
	P[3].x = 3;
	P[3].y = 2;
	P[4].x = 3;
	P[4].y = 1;
	P[5].x = 2;
	P[5].y = 4;
	P[6].x = 2;
	P[6].y = 5;
	P[7].x = 1;
	P[7].y = 5;
	P[8].x = 0;
	P[8].y = 5;
	P[9].x = 3;
	P[9].y = 5;
	P[10].x = 4;
	P[10].y = 5;
	P[11].x = 2;
	P[11].y = 6;
	P[12].x = 1;
	P[12].y = 7;
	P[13].x = 2;
	P[13].y = 8;
	P[14].x = 3;
	P[14].y = 7;
	//Начальное смещение человека
	for (int i = 0; i < 15; i++)
	{
		P[i].x += x_shift;
		P[i].y += y_shift;
	}
	//A road
	R[0].x = 0;
	R[0].y = 0;
	FillPixelX(0, 5, 0);
	R[5].x = 5;
	R[5].y = 0;
	FillPixelY(5, 7, 5, 1);
	R[7].x = 5;
	R[7].y = 2;
	FillPixelX(7, 12, 2);
	R[12].x = 10;
	R[12].y = 2;
	R[13].x = 10;
	R[13].y = 1;
	FillPixelX(13, 20, 1);
	R[20].x = 17;
	R[20].y = 1;
	FillPixelY(20, 22, 17, 1);
	R[22].x = 17;
	R[22].y = 3;
	FillPixelX(22, 29, 3);
	R[29].x = 24;
	R[29].y = 3;
	FillPixelY(29, 31, 24, 1);
	R[31].x = 24;
	R[31].y = 5;
	FillPixelX(31, 35, 5);
	R[35].x = 28;
	R[35].y = 5;
	FillPixelY(35, 40, 28, 0);
	R[40].x = 28;
	R[40].y = 0;
	FillPixelX(40, 46, 0);
	R[46].x = 34;
	R[46].y = 0;
	R[47].x = 34;
	R[47].y = 1;
	FillPixelX(47, 52, 1);
	R[52].x = 39;
	R[52].y = 1;
	R[53].x = 39;
	R[53].y = 0;
	FillPixelX(53, 60, 0);
	R[60].x = 46;
	R[60].y = 0;
	FillPixelY(60, 63, 46, 1);
	R[63].x = 46;
	R[63].y = 3;
	FillPixelX(63, 66, 3);
	R[66].x = 49;
	R[66].y = 3;
	R[67].x = 49;
	R[67].y = 2;
	R[68].x = 49;
	R[68].y = 1;
	FillPixelX(68, 72, 1);
	R[72].x = 53;
	R[72].y = 1;
	R[73].x = 53;
	R[73].y = 0;
	FillPixelX(73, 80, 0);
	R[80].x = 60;
	R[80].y = 0;
	R[81].x = 60;
	R[81].y = 1;
	R[82].x = 60;
	R[82].y = 2;
	FillPixelX(82, 88, 2);
	R[88].x = 66;
	R[88].y = 2;
	R[89].x = 66;
	R[89].y = 3;
	R[90].x = 66;
	R[90].y = 4;
	FillPixelX(90, 96, 4);
	R[96].x = 72;
	R[96].y = 4;
	R[97].x = 72;
	R[97].y = 3;
	R[98].x = 72;
	R[98].y = 2;
	FillPixelX(98, 103, 2);
	R[103].x = 77;
	R[103].y = 2;
	R[104].x = 77;
	R[104].y = 1;
	R[105].x = 77;
	R[105].y = 0;
	FillPixelX(105, 109, 0);
	R[109].x = 81;
	R[109].y = 0;
	x_person_left = P[0].x;
	x_person_right = P[4].x;
	for (int i = 0; i < 110; i++)
	{
		if (R[i].x == x_person_left)
		{
			i_left = i;
			break;
		}
	}
	for (int i = 0; i < 110; i++)
	{
		if (R[i].x == x_person_right)
		{
			i_right = i;
			break;
		}
	}
	i_rem_left = i_left;
	i_rem_right = i_right;
	//End
	//E
	E[0].x = 12;
	E[0].y = 4;
	E[1].x = 11;
	E[1].y = 4;
	E[2].x = 10;
	E[2].y = 4;
	E[3].x = 10;
	E[3].y = 5;
	E[4].x = 10;
	E[4].y = 6;
	E[5].x = 10;
	E[5].y = 7;
	E[6].x = 10;
	E[6].y = 8;
	E[7].x = 11;
	E[7].y = 8;
	E[8].x = 12;
	E[8].y = 8;
	E[9].x = 11;
	E[9].y = 6;
	E[10].x = 12;
	E[10].y = 6;
	//n
	E[11].x = 14;
	E[11].y = 4;
	E[12].x = 14;
	E[12].y = 5;
	E[13].x = 14;
	E[13].y = 6;
	E[14].x = 15;
	E[14].y = 6;
	E[15].x = 16;
	E[15].y = 6;
	E[16].x = 16;
	E[16].y = 5;
	E[17].x = 16;
	E[17].y = 4;
	//d
	E[18].x = 20;
	E[18].y = 8;
	E[19].x = 20;
	E[19].y = 7;
	E[20].x = 20;
	E[20].y = 6;
	E[21].x = 20;
	E[21].y = 5;
	E[22].x = 20;
	E[22].y = 4;
	E[23].x = 19;
	E[23].y = 4;
	E[24].x = 18;
	E[24].y = 4;
	E[25].x = 18;
	E[25].y = 5;
	E[26].x = 18;
	E[26].y = 6;
	E[27].x = 19;
	E[27].y = 6;

  while (1)
  {
	  if (s == 1)
	  {
	      clearScreen((uint8_t*) pData);
	      drawPixels(E, 28, (uint8_t*) pData, P10AB_11);
		  HAL_GPIO_WritePin(nOE_GPIO_Port, nOE_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_SET);
		  HAL_SPI_Transmit(&hspi2, (uint8_t*) pData, 16, 10);
		  HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(nOE_GPIO_Port, nOE_Pin, GPIO_PIN_SET);
		  HAL_Delay(0.5);

		  clearScreen((uint8_t*) pData);
	      drawPixels(E, 28, (uint8_t*) pData, P10AB_10);
		  HAL_GPIO_WritePin(nOE_GPIO_Port, nOE_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_SET);
		  HAL_SPI_Transmit(&hspi2, (uint8_t*) pData, 16, 10);
		  HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(nOE_GPIO_Port, nOE_Pin, GPIO_PIN_SET);
		  HAL_Delay(0.5);

		  clearScreen((uint8_t*) pData);
	      drawPixels(E, 28, (uint8_t*) pData, P10AB_01);
		  HAL_GPIO_WritePin(nOE_GPIO_Port, nOE_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_RESET);
		  HAL_SPI_Transmit(&hspi2, (uint8_t*) pData, 16, 10);
		  HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(nOE_GPIO_Port, nOE_Pin, GPIO_PIN_SET);
		  HAL_Delay(0.5);

		  clearScreen((uint8_t*) pData);
	      drawPixels(E, 28, (uint8_t*) pData, P10AB_00);
		  HAL_GPIO_WritePin(nOE_GPIO_Port, nOE_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_RESET);
		  HAL_SPI_Transmit(&hspi2, (uint8_t*) pData, 16, 10);
		  HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(nOE_GPIO_Port, nOE_Pin, GPIO_PIN_SET);
		  HAL_Delay(0.5);
	  }
	  else
	  {
	      clearScreen((uint8_t*) pData);
	      drawPixels(P, 15, (uint8_t*) pData, P10AB_11);
		  drawPixels(R, 110, (uint8_t*) pData, P10AB_11);
		  HAL_GPIO_WritePin(nOE_GPIO_Port, nOE_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_SET);
		  HAL_SPI_Transmit(&hspi2, (uint8_t*) pData, 16, 10);
		  HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(nOE_GPIO_Port, nOE_Pin, GPIO_PIN_SET);
		  HAL_Delay(0.5);

		  clearScreen((uint8_t*) pData);
	      drawPixels(P, 15, (uint8_t*) pData, P10AB_10);
		  drawPixels(R, 110, (uint8_t*) pData, P10AB_10);
		  HAL_GPIO_WritePin(nOE_GPIO_Port, nOE_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_SET);
		  HAL_SPI_Transmit(&hspi2, (uint8_t*) pData, 16, 10);
		  HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(nOE_GPIO_Port, nOE_Pin, GPIO_PIN_SET);
		  HAL_Delay(0.5);

		  clearScreen((uint8_t*) pData);
	      drawPixels(P, 15, (uint8_t*) pData, P10AB_01);
		  drawPixels(R, 110, (uint8_t*) pData, P10AB_01);
		  HAL_GPIO_WritePin(nOE_GPIO_Port, nOE_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_RESET);
		  HAL_SPI_Transmit(&hspi2, (uint8_t*) pData, 16, 10);
		  HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(nOE_GPIO_Port, nOE_Pin, GPIO_PIN_SET);
		  HAL_Delay(0.5);

		  clearScreen((uint8_t*) pData);
	      drawPixels(P, 15, (uint8_t*) pData, P10AB_00);
		  drawPixels(R, 110, (uint8_t*) pData, P10AB_00);
		  HAL_GPIO_WritePin(nOE_GPIO_Port, nOE_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_RESET);
		  HAL_SPI_Transmit(&hspi2, (uint8_t*) pData, 16, 10);
		  HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(nOE_GPIO_Port, nOE_Pin, GPIO_PIN_SET);
		  HAL_Delay(0.5);
	  }

	// Чтобы загрузить файлы, их надо положить в папки и нажать рефреш (правой кнопкой мыши по названию проекта (внутри Project Explore)

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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
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
