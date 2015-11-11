cmake_minimum_required(VERSION 3.3)

SET(CMAKE_SYSTEM_NAME Generic)
include (CMakeForceCompiler)
CMAKE_FORCE_CXX_COMPILER(/usr/local/gcc-arm-none-eabi-4_9-2015q2/bin/arm-none-eabi-g++ GNU)
CMAKE_FORCE_C_COMPILER(/usr/local/gcc-arm-none-eabi-4_9-2015q2/bin/arm-none-eabi-gcc GNU)

set(SOFTDEVICE S110)
set(tools /usr/local/gcc-arm-none-eabi-4_9-2015q2)

set(CMAKE_CXX_COMPILER  ${tools}/bin/arm-none-eabi-g++)
set(CMAKE_C_COMPILER    ${tools}/bin/arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER  ${tools}/bin/arm-none-eabi-as)
set(SIZE_COMMAND        ${tools}/bin/arm-none-eabi-size)
set(OBJCOPY_COMMAND     ${tools}/bin/arm-none-eabi-objcopy)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR cortex-m0plus)

set(MAIN_TARGET        ${PROJECT_NAME}.elf)

# NRF related
set(NRF_ROOT                $ENV{HOME}/nrf)
set(NRF_SDK                 ${NRF_ROOT}/sdk)
set(NRF_SDK_ROOT            ${NRF_SDK}/nrf51_sdk_latest)
set(SDK_COMPONENTS          ${NRF_SDK_ROOT}/components)
set(NRF_TOOLCHAIN           ${SDK_SDK_COMPONENTS}/toolchain)
set(DEVICE_INCLUDES         ${SDK_SDK_COMPONENTS}/device)
set(GCC                     ${NRF_TOOLCHAIN}/gcc)

set(CMAKE_C_FLAGS "-DBOARD_PCA10028 -DSOFTDEVICE_PRESENT -DNRF51 -DS110 -DBLE_STACK_SUPPORT_REQD -DBSP_DEFINES_ONLY -mcpu=cortex-m0 -mthumb -mabi=aapcs --std=gnu99 -Wall -Werror -O3 -mfloat-abi=soft -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-builtin --short-enums -DDEBUG -g -O0  -lc -lnosys -std=gnu99 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -flto -fno-move-loop-invariants -Wextra -g3 -DBLE_STACK_SUPPORT_REQD -DDEBUG -g -O1 -DBOARD_PCA10031 -DNRF51 -D__need___va_list -w -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics --specs=nano.specs")
set(CMAKE_ASM_FLAGS -x assembler-with-c -DBOARD_PCA10028 -DSOFTDEVICE_PRESENT -DNRF51 -DS110 -DBLE_STACK_SUPPORT_REQD -DBSP_DEFINES_ONLY -DDEBUG)

include_directories(
    ${SDK_COMPONENTS}/toolchain
    ${SDK_COMPONENTS}/toolchain/gcc
    ${SDK_COMPONENTS}/softdevice/${SOFTDEVICE}/headers
    ${NRF_SDK_ROOT}/examples/bsp
    ${SDK_COMPONENTS}/device
    ${SDK_COMPONENTS}/drivers_nrf/hal
)

set(SOURCE_FILES
    ${SDK_COMPONENTS}/toolchain/system_nrf51.c
    ${SDK_COMPONENTS}/drivers_nrf/hal/nrf_delay.c
    main.c)

project(blinky)
add_executable(${MAIN_TARGET} ${SOURCE_FILES})

add_custom_command(
        TARGET ${MAIN_TARGET}
        COMMAND ${SIZE_COMMAND} ${MAIN_TARGET}
        COMMAND ${OBJCOPY_COMMAND} -O ihex ${MAIN_TARGET} ${PROJECT_NAME}.hex
        COMMAND ${OBJCOPY_COMMAND} -O binary ${MAIN_TARGET} ${PROJECT_NAME}.bin
)
