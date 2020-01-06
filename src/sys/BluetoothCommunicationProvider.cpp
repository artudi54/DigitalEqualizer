#include "BluetoothCommunicationProvider.hpp"
#include <algorithm>
#include <cstring>
#include <stdexcept>
#include <stm32f4xx_hal.h>

UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_rx;
char* data;
std::uint32_t length;

extern "C" void USART2_IRQHandler(void) {
    HAL_UART_IRQHandler(&huart2);
}

extern "C" void DMA1_Stream5_IRQHandler(void) {
    HAL_DMA_IRQHandler(&hdma_usart2_rx);
}

extern "C" void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
   if (huart == &huart2) {
       if (HAL_UART_Receive_DMA(&huart2, reinterpret_cast<std::uint8_t*>(data), length) != HAL_OK)
           throw std::runtime_error("Failed to enable receive mode");
   }
}

extern "C" void HAL_UART_MspInit(UART_HandleTypeDef* huart) {
    GPIO_InitTypeDef GPIO_InitStruct = {};
    if(huart->Instance == USART2) {
        __HAL_RCC_USART2_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        hdma_usart2_rx.Instance = DMA1_Stream5;
        hdma_usart2_rx.Init.Channel = DMA_CHANNEL_4;
        hdma_usart2_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
        hdma_usart2_rx.Init.PeriphInc = DMA_PINC_DISABLE;
        hdma_usart2_rx.Init.MemInc = DMA_MINC_ENABLE;
        hdma_usart2_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        hdma_usart2_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
        hdma_usart2_rx.Init.Mode = DMA_NORMAL;
        hdma_usart2_rx.Init.Priority = DMA_PRIORITY_LOW;
        hdma_usart2_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
        if (HAL_DMA_Init(&hdma_usart2_rx) != HAL_OK)
            throw std::runtime_error("Failed to initialize bluetooth module");

        __HAL_LINKDMA(huart, hdmarx, hdma_usart2_rx);

        HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(USART2_IRQn);
    }

}

namespace sys {
    static constexpr std::uint32_t TIMEOUT = 1000;

    BluetoothCommunicationProvider::BluetoothCommunicationProvider()
        : buffer{}
        , position(0) {

        __HAL_RCC_DMA1_CLK_ENABLE();
        HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);

        huart2.Instance = USART2;
        huart2.Init.BaudRate = 9600;
        huart2.Init.WordLength = UART_WORDLENGTH_8B;
        huart2.Init.StopBits = UART_STOPBITS_1;
        huart2.Init.Parity = UART_PARITY_NONE;
        huart2.Init.Mode = UART_MODE_TX_RX;
        huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
        huart2.Init.OverSampling = UART_OVERSAMPLING_16;
        if (HAL_UART_Init(&huart2) != HAL_OK)
            throw std::runtime_error("Failed to initialize bluetooth module");

        data = buffer.data();
        length = static_cast<std::uint32_t>(buffer.size());
        HAL_UART_RxCpltCallback(&huart2);
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

    bool BluetoothCommunicationProvider::hasSizedMessage() const {
        return getIncomingDataSize() >= sizeof(std::uint32_t);
    }

    void BluetoothCommunicationProvider::receiveSizedMessage(char *bytes) {
        if (!hasSizedMessage())
            throw std::runtime_error("No message is pending to receive");
        std::uint32_t length;
        copyCircullar(&length, sizeof(std::uint32_t));
        while (getIncomingDataSize() < length);
        copyCircullar(bytes, length);
    }

    std::uint32_t BluetoothCommunicationProvider::getIncomingDataSize() const {
        std::uint32_t readPosition =  buffer.size() - __HAL_DMA_GET_COUNTER(&hdma_usart2_rx);
        std::uint32_t count = (readPosition + buffer.size() - position) % buffer.size();
        return count;
    }

    void BluetoothCommunicationProvider::copyCircullar(void *destination, std::uint32_t length) {
        std::uint32_t beforeEndLength = std::min(length, static_cast<std::uint32_t>(buffer.size() - 1 - position));

        std::memcpy(destination, buffer.data() + position, beforeEndLength);
        position = (position + beforeEndLength) % buffer.size();

        length -= beforeEndLength;

        std::memcpy(destination, buffer.data() + position, length);
        position = (position + length) % buffer.size();
    }
}