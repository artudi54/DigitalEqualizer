#include <stm32f4xx_hal.h>
#include <stdexcept>
#include "BluetoothCommunicationProvider.hpp"

UART_HandleTypeDef huart2;
extern "C" void USART2_IRQHandler(void) {
    HAL_UART_IRQHandler(&huart2);
}

extern "C" void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
    GPIO_InitTypeDef GPIO_InitStruct = {};
    if(huart->Instance==USART2)
    {
        __HAL_RCC_USART2_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(USART2_IRQn);
    }

}

namespace sys {
    static constexpr std::uint32_t TIMEOUT = 100;
    BluetoothCommunicationProvider::BluetoothCommunicationProvider() {
        huart2.Instance = USART2;
        huart2.Init.BaudRate = 9600;
        huart2.Init.WordLength = UART_WORDLENGTH_8B;
        huart2.Init.StopBits = UART_STOPBITS_1;
        huart2.Init.Parity = UART_PARITY_NONE;
        huart2.Init.Mode = UART_MODE_TX_RX;
        huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
        huart2.Init.OverSampling = UART_OVERSAMPLING_16;
        if (HAL_UART_Init(&huart2) != HAL_OK) {
            throw std::runtime_error("Failed to initialize bluetooth module");
        }
    }

    void BluetoothCommunicationProvider::transmitSizedMessage(const char* bytes, std::uint32_t length) {
        HAL_StatusTypeDef result;
        result = HAL_UART_Transmit(&huart2, reinterpret_cast<std::uint8_t*>(&length), sizeof(std::uint32_t), TIMEOUT);
        if (result != HAL_OK)
            throw std::runtime_error("Failed to transmit message through bluetooth");
        result = HAL_UART_Transmit(&huart2, const_cast<std::uint8_t*>(reinterpret_cast<const std::uint8_t*>(bytes)), static_cast<std::uint16_t>(length), TIMEOUT);
        if (result != HAL_OK)
            throw std::runtime_error("Failed to transmit message through bluetooth");
    }

    bool BluetoothCommunicationProvider::hasSizedMessage() {
        return __HAL_UART_GET_FLAG(&huart2, UART_FLAG_RXNE);
    }

    void BluetoothCommunicationProvider::receiveSizedMessage(char *bytes) {
        HAL_StatusTypeDef result;
        std::uint32_t length;

        result = HAL_UART_Receive(&huart2, reinterpret_cast<std::uint8_t*>(&length), sizeof(std::uint32_t), TIMEOUT);
        if (result != HAL_OK)
            throw std::runtime_error("Failed to receive message through bluetooth");
        result = HAL_UART_Receive(&huart2, reinterpret_cast<std::uint8_t*>(bytes), static_cast<std::uint16_t>(length), TIMEOUT);
        if (result != HAL_OK)
            throw std::runtime_error("Failed to receive message through bluetooth");
    }
}