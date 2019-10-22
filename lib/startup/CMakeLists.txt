 add_library(startup
 	src/startup_stm32f40_41xxx.s
	src/system_stm32f4xx.c
)
target_link_libraries(startup PRIVATE stm32f4xx)