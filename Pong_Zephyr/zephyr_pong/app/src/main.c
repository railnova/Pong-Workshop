/**
 * Copyright Railnova 2022
 * Authors : Bultot Geoffrey & Lea Vielfaure
 * Railnova Proprietary Licence
 */

#include <zephyr.h>
#include <logging/log.h>

#include "rn_LED_matrix.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

void main(void)
{
    while(true){
        LOG_INF("led_matrix_set(0,0,1)");
        led_matrix_set(0,0,1);
        k_sleep(K_SECONDS(1));

        LOG_INF("led_matrix_set(0,0,0)");
        led_matrix_set(0,0,0);
        k_sleep(K_SECONDS(1));
    }
}
