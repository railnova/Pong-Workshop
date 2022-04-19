/**
 * Copyright Railnova 2022
 * Authors : Bultot Geoffrey & Lea Vielfaure
 * Railnova Proprietary Licence
 */

#include <zephyr.h>
#include <sys/printk.h>
#include <dt-bindings/gpio/gpio.h>
#include <logging/log.h>
#include <drivers/gpio.h>
#include <drivers/display.h>
#include "rn_LED_matrix.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

extern uint8_t led_matrix[8][8];

void main(void)
{
    while(true){
        led_matrix_refreshMatrix();
        led_matrix_print();
        k_sleep(K_MSEC(1000));
    }
}
