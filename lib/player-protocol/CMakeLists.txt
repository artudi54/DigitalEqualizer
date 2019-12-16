cmake_minimum_required (VERSION 3.10)
project(player-protocol LANGUAGES CXX)

# Source code
SET(HEADERS
    include/player_protocol/changed/MediumChangedMessage.hpp
    include/player_protocol/changed/TimeChangedMessage.hpp
	include/player_protocol/changed/VolumeChangedMessage.hpp

	include/player_protocol/request/ChangeMediumRequest.hpp
	include/player_protocol/request/ChangeVolumeRequest.hpp
	include/player_protocol/request/PauseRequest.hpp
	include/player_protocol/request/PlaylistRequest.hpp
	include/player_protocol/request/PlayRequest.hpp
	include/player_protocol/request/SeekRequest.hpp
	include/player_protocol/request/StopRequest.hpp

	include/player_protocol/response/ErrorResponse.hpp
	include/player_protocol/response/OkResponse.hpp
	include/player_protocol/response/PlaylistResponse.hpp

	include/player_protocol/Message.hpp
	include/player_protocol/MessageSerializer.hpp
	include/player_protocol/MessageType.hpp
	include/player_protocol/MessageVisitor.hpp
)
set(SOURCES
	src/player_protocol/changed/MediumChangedMessage.cpp
	src/player_protocol/changed/TimeChangedMessage.cpp
	src/player_protocol/changed/VolumeChangedMessage.cpp

	src/player_protocol/request/ChangeMediumRequest.cpp
	src/player_protocol/request/ChangeVolumeRequest.cpp
	src/player_protocol/request/PauseRequest.cpp
	src/player_protocol/request/PlaylistRequest.cpp
	src/player_protocol/request/PlayRequest.cpp
	src/player_protocol/request/SeekRequest.cpp
	src/player_protocol/request/StopRequest.cpp

	src/player_protocol/response/ErrorResponse.cpp
	src/player_protocol/response/OkResponse.cpp
	src/player_protocol/response/PlaylistResponse.cpp

	src/player_protocol/Message.cpp
	src/player_protocol/MessageSerializer.cpp
	src/player_protocol/MessageVisitor.cpp

	src/player_protocol/MessageFactory.cpp
	src/player_protocol/MessageFactory.hpp
)

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
		include/player_protocol/changed
		include/player_protocol/request
		include/player_protocol/response
)

# Optimization level
if(CMAKE_BUILD_TYPE MATCHES Debug)
  set(additional_flags -O0)
else()
  set(additional_flags -O3)
endif()
target_compile_options(${PROJECT_NAME} PUBLIC ${additional_flags})
