# THIS FILE IS AUTO GENERATED FROM THE TEMPLATE! DO NOT CHANGE!
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.20)

# 环境选择
if(WIN32)
    message(STATUS "Now is windows!")

    # specify cross compilers and tools
    # set(TOOLPATH "D:/ToolPath/Arm-None-Eabi-Gcc/Base_File/10 2021.10/bin/arm-none-eabi-")
    set(TOOLPATH "D:/ToolPath/Arm-None-Eabi-Gcc/Base_File/14.2 rel1/bin/arm-none-eabi-")
    set(CMAKE_C_COMPILER ${TOOLPATH}gcc.exe)
    set(CMAKE_CXX_COMPILER ${TOOLPATH}g++.exe)
    set(CMAKE_ASM_COMPILER ${TOOLPATH}gcc.exe)
    set(CMAKE_AR ${TOOLPATH}ar.exe)
    set(CMAKE_OBJCOPY ${TOOLPATH}objcopy.exe)
    set(CMAKE_OBJDUMP ${TOOLPATH}objdump.exe)
    set(SIZE ${TOOLPATH}size.exe)
elseif(UNIX)
    message(STATUS "Now is UNIX-like OS!")
    set(CMAKE_C_COMPILER ${TOOLPATH}gcc)
    set(CMAKE_CXX_COMPILER ${TOOLPATH}g++)
    set(CMAKE_ASM_COMPILER ${TOOLPATH}gcc)
    set(CMAKE_AR ${TOOLPATH}ar)
    set(CMAKE_OBJCOPY ${TOOLPATH}objcopy)
    set(CMAKE_OBJDUMP ${TOOLPATH}objdump)
    set(SIZE ${TOOLPATH}size)
else()
    message(STATUS "Unsupported system!")
endif()

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# project settings
project(STM32F103C8T6_HAL_CMake C CXX ASM)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

# Uncomment for hardware floating point
add_compile_options(-mfloat-abi=soft -mfpu=fpv4-sp-d16)
add_link_options(-mfloat-abi=soft -mfpu=fpv4-sp-d16)

# Uncomment for software floating point
# add_compile_options(-mfloat-abi=soft)
add_compile_options(-mcpu=cortex-m3 -mthumb -mthumb-interwork)
add_compile_options(-ffunction-sections -fdata-sections -fno-common -fmessage-length=0)

# uncomment to mitigate c++17 absolute addresses warnings
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-register")

# Enable assembler files preprocessing
# add_compile_options($<$<COMPILE_LANGUAGE:ASM>:-x$<SEMICOLON>assembler-with-cpp>)
message("CMAKE_BUILD_TYPE:\t" ${CMAKE_BUILD_TYPE})
message("version:\t1.0.0")

if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    message(VERBOSE "Maximum optimization for speed")
    add_compile_options(-Ofast)
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    message(VERBOSE "Maximum optimization for speed, debug info included")
    add_compile_options(-Ofast -g)
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
    message(VERBOSE "Maximum optimization for size")
    add_compile_options(-Os)
else()
    message(VERBOSE "Minimal optimization, debug info included")
    add_compile_options(-Og -g)
    # add_definitions(-DDEBUG -DUSE_HAL_DRIVER)
endif()

add_compile_options(-Wall)

# 库文件
include_directories(
    Core/Inc
    Core/ThreadSafe
    Drivers/CMSIS/Device/ST/STM32F1xx/Include
    Drivers/CMSIS/Include
    Drivers/STM32F1xx_HAL_Driver/Inc
    Drivers/STM32F1xx_HAL_Driver/Inc/Legacy
    Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2
    Middlewares/Third_Party/FreeRTOS/Source/include
    Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3)

# add_definitions(-DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xx)

# 源文件
file(GLOB_RECURSE SOURCES
    "Core/Src/*.c"
    "Core/Startup/startup_stm32f103c8tx.s"
    "Core/ThreadSafe/*.c"
    "Drivers/STM32F1xx_HAL_Driver/Src/*.c"
    "Middlewares/Third_Party/FreeRTOS/*.c"
)

set(LINKER_SCRIPT
    ${CMAKE_SOURCE_DIR}/STM32F103C8TX_FLASH.ld
)

add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
add_link_options(-mcpu=cortex-m3 -mthumb -mthumb-interwork)
add_link_options(-T ${LINKER_SCRIPT})

add_link_options(--specs=nano.specs --specs=nosys.specs -u _printf_float)

add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})

target_compile_definitions(${PROJECT_NAME}.elf PRIVATE STM32F103xB)

set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
    COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
    COMMENT "Building ${HEX_FILE}
Building ${BIN_FILE}")