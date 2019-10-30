cmake_minimum_required (VERSION 3.10)
project(stm32f4xx LANGUAGES C ASM)

add_library(${PROJECT_NAME} 
    src/startup_stm32f407xx.s
    src/system_stm32f4xx.c
)

# Includes
target_include_directories(${PROJECT_NAME}  PUBLIC include include/CMSIS)

# Compile definitions
target_compile_definitions(${PROJECT_NAME} PUBLIC ${DEVICE_FAMILY})

# Optimization level
if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(optimization -O0)
else()
    set(optimization -Os)
endif()
target_compile_options(${PROJECT_NAME} PUBLIC ${optimization})
