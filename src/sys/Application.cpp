#include "Application.hpp"
#include <stdexcept>

#include <stm32f4xx_hal.h>
#include <ff.h>
#include <drivers/user_diskio.h>
#include <drivers/fatfs_sd.h>


extern SPI_HandleTypeDef hspi1;

namespace sys {
    Application::Application() {
        if (instance != nullptr)
            throw std::runtime_error("Application was already created");
        initializeHAL();
        initializeClock();
        initializeLED();
        initializeStdIO();
        initializeSDCard();
        instance = this;
    }

    int Application::exec() {
        while (true);
        return 0;
    }

    void Application::initializeHAL() {
        HAL_Init();
    }

    void Application::initializeClock() {
        RCC_OscInitTypeDef RCC_OscInitStruct = {};
        RCC_ClkInitTypeDef RCC_ClkInitStruct = {};

        __HAL_RCC_PWR_CLK_ENABLE();
        __HAL_RCC_SYSCFG_CLK_ENABLE();
        __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

        RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
        RCC_OscInitStruct.HSEState = RCC_HSE_ON;
        RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
        RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
        RCC_OscInitStruct.PLL.PLLM = 25;
        RCC_OscInitStruct.PLL.PLLN = 144;
        RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
        RCC_OscInitStruct.PLL.PLLQ = 4;
        if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
            //TODO
        }

        RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                      | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
        RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
        RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
        RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
        RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

        if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
            //TODO
        }
    }

    void Application::initializeLED() {
        __HAL_RCC_GPIOD_CLK_ENABLE();
        GPIO_InitTypeDef gpio;
        gpio.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
        gpio.Mode = GPIO_MODE_OUTPUT_PP;
        gpio.Pull = GPIO_NOPULL;
        gpio.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(GPIOD, &gpio);
    }

    void Application::initializeStdIO() {
    }


    void Application::initializeSDCard() {
        initializeSDCardSPI();
        initializeSDCardSPICS();
        initializeSDCardSPIIO();
        initializeSDCardFatFS();
    }

    void Application::initializeSDCardSPI() {
        __HAL_RCC_SPI1_CLK_ENABLE();
        hspi1.Instance = SPI1;
        hspi1.Init.Mode = SPI_MODE_MASTER;
        hspi1.Init.Direction = SPI_DIRECTION_2LINES;
        hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
        hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
        hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
        hspi1.Init.NSS = SPI_NSS_SOFT;
        hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
        hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
        hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
        hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
        hspi1.Init.CRCPolynomial = 10;
        if (HAL_SPI_Init(&hspi1) != HAL_OK) {
            //TODO
        }
    }

    void Application::initializeSDCardSPICS() {
        __HAL_RCC_GPIOB_CLK_ENABLE();
        GPIO_InitTypeDef GPIO_InitStruct = {};
        GPIO_InitStruct.Pin = GPIO_PIN_0;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    }

    Application* Application::instance = nullptr;

    void Application::initializeSDCardSPIIO() {
        __HAL_RCC_GPIOA_CLK_ENABLE();
        GPIO_InitTypeDef GPIO_InitStruct = {};
        GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    }

    void Application::initializeSDCardFatFS() {
        char path[4];
        uint8_t result;
        result = FATFS_LinkDriver(&USER_Driver, path);
        if (result != FR_OK) {
            //TODO
        }

        static FATFS fs;
        result = f_mount(&fs, path, 1);
        if (result != FR_OK) {
            //TODO
            while (true);
        }
    }

    void Application::sysTickHandler() {
        SDTimer_Handler();
        HAL_IncTick();
    }

    void Application::errorHandler() {
        while (true);
    }
}