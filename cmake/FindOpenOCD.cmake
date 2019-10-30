find_program(
    OPENOCD NAMES "openocd"
    DOC "OpenOCD debugger and flash utility"
)

if(DEFINED OpenOCD_FIND_REQUIRED AND NOT OPENOCD)
    message(FATAL_ERROR "OpenOCD not found!")
endif()
