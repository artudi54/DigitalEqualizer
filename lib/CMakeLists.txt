add_subdirectory(stm32f4xx)
add_subdirectory(HAL)
add_subdirectory(BSP)
add_subdirectory(FatFs)

add_library(lib INTERFACE)
target_link_libraries(lib INTERFACE stm32f4xx HAL BSP FatFs)

