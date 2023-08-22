cmake_minimum_required(VERSION 3.14)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)


project(FreeRTOS-example C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

set(PICO_FREERTOS-EXAMPLES_PATH ${PROJECT_SOURCE_DIR})

# Initialize the SDK
pico_sdk_init()

# Statically link FreeRTOS
add_library(FreeRTOS STATIC
    ${FREERTOS_KERNEL_SRC}/event_groups.c
    ${FREERTOS_KERNEL_SRC}/list.c
    ${FREERTOS_KERNEL_SRC}/portable/GCC/ARM_CM0/port.c
    ${FREERTOS_KERNEL_SRC}/portable/MemMang/heap_3.c
    ${FREERTOS_KERNEL_SRC}/tasks.c

    )


target_include_directories(FreeRTOS PUBLIC
    FreeRTOS-example/include
    ${FREERTOS_KERNEL_SRC}/include
    ${FREERTOS_KERNEL_SRC}/portable/GCC/ARM_CM0
)

# Add FreeRTOS-example
add_subdirectory(FreeRTOS-example)
