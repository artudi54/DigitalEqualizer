add_subdirectory(startup)
add_subdirectory(stm32f4xx)

add_library(lib INTERFACE)
target_link_libraries(lib INTERFACE stm32f4xx startup)

