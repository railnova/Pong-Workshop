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

void main(void){
	
	uint8_t len =0;// 
    while(true){
        refreshMatrix();
        dbg_print_matrix();
        k_sleep(K_MSEC(1000));
    }
}