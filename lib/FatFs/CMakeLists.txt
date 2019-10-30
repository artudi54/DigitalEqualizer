cmake_minimum_required (VERSION 3.10)
project(FatFs LANGUAGES C)

set(SOURCES
    src/diskio.c
    src/ff.c
    src/ff_gen_drv.c
    src/drivers/fatfs_sd.c
    src/drivers/user_diskio.c
    src/option/ccsbcs.c
    src/option/syscall.c
    src/option/unicode.c
)

add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC src)
target_link_libraries(${PROJECT_NAME} PUBLIC stm32f4xx HAL)
