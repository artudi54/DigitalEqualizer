cmake_minimum_required (VERSION 3.10)
project(digital-equalizer  C CXX ASM)

# Compiler options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")

# Target
## Sources
SET(HEADERS
)
set(SOURCES
	src/main.cpp
)

## Elf executable
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_NAME ${PROJECT_NAME}.elf)
## Bin dump
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.elf ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.bin
)

# Includes
target_include_directories(${PROJECT_NAME}
	PUBLIC
		include
	PRIVATE
		include/controller
)

# Libraries
## Controller properties
set(DEVICE_FAMILY STM32F40_41xxx)
set(HSE_VALUE 8000000)

## Library link
add_subdirectory(lib)
target_link_libraries(${PROJECT_NAME} PRIVATE lib)

## Linker script
target_link_libraries(${PROJECT_NAME} PRIVATE -T${PROJECT_SOURCE_DIR}/linker/stm32f407vgt.ld)

