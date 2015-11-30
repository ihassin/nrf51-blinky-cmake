/* Copyright (c) 2014 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 */

/** @file
 *
 * @defgroup blinky_example_main main.c
 * @{
 * @ingroup blinky_example
 * @brief Blinky Example Application main file.
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "boards.h"

#define RUN_TEST(func) UnityDefaultTestRun(func, #func, __LINE__)

#include "unity.h"
#include "tests.h"

const uint8_t leds_list[LEDS_NUMBER] = LEDS_LIST;

/**
 * @brief Function for application main entry.
 */
int main(void)
{
    UnityBegin("main.c");

    LEDS_CONFIGURE(LEDS_MASK);
//    LEDS_INVERT(1 << leds_list[0]);     // Blue

    RUN_TEST(test_1);

    if(Unity.TestFailures == 0)
    {
        LEDS_INVERT(1 << leds_list[2]);     // Green
    } else {
        LEDS_INVERT(1 << leds_list[1]);     // Red
    }

#if 0
    // Configure LED-pins as outputs.
    LEDS_CONFIGURE(LEDS_MASK);

    // Toggle LEDs.
    while (true)
    {
        for (int i = 0; i < LEDS_NUMBER; i++)
        {
            LEDS_INVERT(1 << leds_list[i]);
            nrf_delay_ms(140);
        }
    }
#endif

}


/** @} */
