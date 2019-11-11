cmake_minimum_required (VERSION 3.10)
project(BSP LANGUAGES C)

set(SOURCES
    src/Components/cs43l22/cs43l22.c
    src/Components/exc7200/exc7200.c
    src/Components/ft6x06/ft6x06.c
    src/Components/ili9325/ili9325.c
    src/Components/ili9341/ili9341.c
    src/Components/l3gd20/l3gd20.c
    src/Components/lis302dl/lis302dl.c
    src/Components/lis3dsh/lis3dsh.c
    src/Components/ls016b8uy/ls016b8uy.c
    src/Components/lsm303dlhc/lsm303dlhc.c
    src/Components/mfxstm32l152/mfxstm32l152.c
    src/Components/otm8009a/otm8009a.c
    src/Components/ov2640/ov2640.c
    src/Components/s5k5cag/s5k5cag.c
    src/Components/st7735/st7735.c
    src/Components/st7789h2/st7789h2.c
    src/Components/stmpe1600/stmpe1600.c
    src/Components/stmpe811/stmpe811.c
    src/Components/ts3510/ts3510.c
    src/Components/wm8994/wm8994.c
    src/STM32F4-Discovery/stm32f4_discovery.c
    src/STM32F4-Discovery/stm32f4_discovery_accelerometer.c
    src/STM32F4-Discovery/stm32f4_discovery_audio.c
)

add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC src/Components src/STM32F4-Discovery)
target_link_libraries(${PROJECT_NAME} PUBLIC stm32f4xx HAL)
