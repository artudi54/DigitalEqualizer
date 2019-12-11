cmake_minimum_required (VERSION 3.10)
project(player-protocol LANGUAGES CXX)

# Source code
SET(HEADERS
	include/player_protocol/MessageType.hpp
)
set(SOURCES
		test.cpp)

# Executable
add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

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
		src
)

# Optimization level
if(CMAKE_BUILD_TYPE MATCHES Debug)
  set(additional_flags -O0)
else()
  set(additional_flags -O3)
endif()
target_compile_options(${PROJECT_NAME} PUBLIC ${additional_flags})
