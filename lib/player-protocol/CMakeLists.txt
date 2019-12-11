cmake_minimum_required (VERSION 3.10)
project(player-protocol LANGUAGES CXX)

# Source code
SET(HEADERS
	include/player_protocol/MediumChangedMessage.hpp
	include/player_protocol/Message.hpp
	include/player_protocol/MessageSerializer.hpp
	include/player_protocol/MessageType.hpp
	include/player_protocol/TimeChangedMessage.hpp
)
set(SOURCES
	src/player_protocol/MediumChangedMessage.cpp
	src/player_protocol/Message.cpp
	src/player_protocol/MessageSerializer.cpp
	src/player_protocol/TimeChangedMessage.cpp
		src/player_protocol/VolumeChanged.cpp include/player_protocol/VolumeChanged.hpp src/player_protocol/PlayRequest.cpp include/player_protocol/PlayRequest.hpp)

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
		include/player_protocol
)

# Optimization level
if(CMAKE_BUILD_TYPE MATCHES Debug)
  set(additional_flags -O0)
else()
  set(additional_flags -O3)
endif()
target_compile_options(${PROJECT_NAME} PUBLIC ${additional_flags})
