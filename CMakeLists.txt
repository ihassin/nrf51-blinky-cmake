cmake_minimum_required(VERSION 3.3)

include (CMakeForceCompiler)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR cortex-m0plus)
set(CMAKE_INCLUDE_PATH "")
enable_language(ASM)

project(nrf51822_xxac)

CMAKE_FORCE_C_COMPILER(/usr/local/gcc-arm-none-eabi-4_9-2015q2/bin/arm-none-eabi-gcc GNU)

set(tools /usr/local/gcc-arm-none-eabi-4_9-2015q2)
set(CMAKE_CXX_COMPILER  ${tools}/bin/arm-none-eabi-g++)
set(CMAKE_C_COMPILER    ${tools}/bin/arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER  ${tools}/bin/arm-none-eabi-as)
set(SIZE_COMMAND        ${tools}/bin/arm-none-eabi-size)
set(OBJCOPY_COMMAND     ${tools}/bin/arm-none-eabi-objcopy)

set(SOFTDEVICE S110)

set(BUILD_SHARED_LIBS OFF)

# NRF related
set(NRF_ROOT                $ENV{HOME}/nrf)
set(NRF_SDK                 ${NRF_ROOT}/sdk)
set(NRF_SDK_ROOT            ${NRF_SDK}/nrf51_sdk_latest)
set(SDK_COMPONENTS          ${NRF_SDK_ROOT}/components)
set(NRF_TOOLCHAIN           ${SDK_SDK_COMPONENTS}/toolchain)
set(DEVICE_INCLUDES         ${SDK_SDK_COMPONENTS}/device)
set(GCC                     ${NRF_TOOLCHAIN}/gcc)

set(MAIN_TARGET ${PROJECT_NAME}.out)

set(LINKER_SCRIPT ../blinky_gcc_nrf51.ld)

set(CMAKE_C_FLAGS "-T${LINKER_SCRIPT} -DBOARD_PCA10028 -DSOFTDEVICE_PRESENT -DNRF51 -DS110 -DBLE_STACK_SUPPORT_REQD -DBSP_DEFINES_ONLY -mcpu=cortex-m0 -mthumb -mabi=aapcs --std=gnu99 -Wall -Werror -O3 -mfloat-abi=soft -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-builtin --short-enums -DDEBUG -g -O0 -DBOARD_PCA10028 -DSOFTDEVICE_PRESENT -DNRF51 -DS110 -DBLE_STACK_SUPPORT_REQD -DBSP_DEFINES_ONLY -DDEBUG -L ${SDK_COMPONENTS}/toolchain/gcc -lc -lnosys -mcpu=cortex-m0 -mthumb -mabi=aapcs --std=gnu99 -Wall -Werror -O3 -mfloat-abi=soft -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-builtin --short-enums -DDEBUG -g -O0 -L ${SDK_COMPONENTS}/toolchain/gcc -lc -lnosys")

include_directories(
    ${SDK_COMPONENTS}/toolchain
    ${SDK_COMPONENTS}/toolchain/gcc
    ${SDK_COMPONENTS}/softdevice/${SOFTDEVICE}/headers
    ${NRF_SDK_ROOT}/examples/bsp
    ${SDK_COMPONENTS}/device
    ${SDK_COMPONENTS}/drivers_nrf/hal
)

set(SOURCE_FILES
    ${SDK_COMPONENTS}/toolchain/gcc/gcc_startup_nrf51.s
    ${SDK_COMPONENTS}/toolchain/system_nrf51.c
    ${SDK_COMPONENTS}/drivers_nrf/hal/nrf_delay.c
    main.c)

add_executable(${MAIN_TARGET} ${SOURCE_FILES})

add_custom_command(
        TARGET ${MAIN_TARGET}
        COMMAND ${SIZE_COMMAND} ${MAIN_TARGET}
        COMMAND ${OBJCOPY_COMMAND} -O ihex ${MAIN_TARGET} ${PROJECT_NAME}.hex
        COMMAND ${OBJCOPY_COMMAND} -O binary ${MAIN_TARGET} ${PROJECT_NAME}.bin
)
