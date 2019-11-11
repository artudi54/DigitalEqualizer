cmake_minimum_required (VERSION 3.10)
project(digital-equalizer LANGUAGES C CXX ASM)

# CMake setup
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
if(NOT CMAKE_BUILD_TYPE) 
    set(CMAKE_BUILD_TYPE Release)
endif()

# Source code
SET(HEADERS
	include/audio/AudioPlayer.hpp
	include/audio/WavAudioMetadata.hpp
	include/audio/WavAudioReader.hpp
	include/audio/WavFormatTag.hpp
	include/filesystem/DirectoryListing.hpp
	include/filesystem/FileReadStream.hpp
	include/sys/Application.hpp
	include/sys/LedDiodeControl.hpp
	include/sys/Task.hpp
)
set(SOURCES
	src/audio/AudioPlayer.cpp
	src/audio/WavAudioMetadata.cpp
	src/audio/WavAudioReader.cpp
	src/filesystem/DirectoryListing.cpp
	src/filesystem/FileReadStream.cpp
	src/sys/Application.cpp
	src/sys/LedDiodeControl.cpp
	src/sys/Task.cpp
	src/main.cpp
)

# Executable
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_NAME ${PROJECT_NAME}.elf)

# Binary dump
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.elf ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.bin
)

# Compiler options
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)

# Includes
target_include_directories(${PROJECT_NAME}
	PUBLIC
        include
	PRIVATE
		include/audio
		include/filesystem
        include/sys
)

# Libraries
## Controller properties
set(DEVICE_FAMILY STM32F407xx)
set(HSE_VALUE 8000000)
set(HSI_VALUE 16000000)

# Optimization level
if(CMAKE_BUILD_TYPE MATCHES Debug)
  set(additional_flags -O0)
else()
  set(additional_flags -Os)
endif()
target_compile_options(${PROJECT_NAME} PUBLIC ${additional_flags})

# Library link
add_subdirectory(lib)
target_link_libraries(${PROJECT_NAME} PRIVATE lib)

# Linker script
target_link_libraries(${PROJECT_NAME} PRIVATE -T${PROJECT_SOURCE_DIR}/linker/stm32f407vgt.ld)

# Install
find_package(OpenOCD REQUIRED)
set(OPENOCD_CONFIG ${PROJECT_SOURCE_DIR}/config/stm32f4discovery.cfg)
set(FLASHED_FILE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.elf)
install(CODE
	"execute_process(COMMAND ${OPENOCD} -f ${OPENOCD_CONFIG} -c \"program ${FLASHED_FILE} verify reset exit\")"
)
