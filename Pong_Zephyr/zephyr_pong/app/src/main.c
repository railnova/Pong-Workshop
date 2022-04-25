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
    int i = 0;
    while(true){
        for(i = 0; i<8; i++){
            led_matrix_print();
            k_sleep(K_SECONDS(1));
            led_matrix[i][i] = 1;
        }
        i = 0;
    }
}
