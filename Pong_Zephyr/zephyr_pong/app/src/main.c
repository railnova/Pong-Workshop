/**
 * Copyright Railnova 2022
 * Authors : Bultot Geoffrey & Lea Vielfaure
 * Railnova Proprietary Licence
 */

#include <zephyr.h>
#include <logging/log.h>

#include "rn_LED_matrix.h"

/*
 * This discribe the log level, you can choose between :
 * LOG_LEVEL_NONE, LOG_LEVEL_ERR, LOG_LEVEL_WRN, LOG_LEVEL_INF, LOG_LEVEL_DBG
 * The associated LOG_xxx() message will be printed depending on the level selected. 
 */
LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

// Structure to use for coordinates & scores
static struct score score;
static struct cursor_coordinate cursor_playerA;
static struct cursor_coordinate cursor_playerB;
static struct ball_coordinate ball;

/**
 * @brief Callback handler for the buttons. 
 */
void buttons_callback(const struct device *dev, struct gpio_callback *cb,
		    uint32_t pins)
{
    int pin; 
    pin = led_matrix_get_pin_interrupt(pins);

    switch(pin){
        case PIN_BA1:
            LOG_DBG("Right up button pressed");
            break;

        case PIN_BA2:
            LOG_DBG("Right down button pressed");
            break;

        case PIN_BB1:
            LOG_DBG("Left up button pressed");
            break;

        case PIN_BB2:
            LOG_DBG("Left down button pressed");
            break;

        case PIN_B_RST:
            LOG_DBG("Reset button pressed");
            break;

        default:
            break;

    }
}

void main(void)
{
    led_matrix_init_buttons_callback(buttons_callback);
  
    score.playerA = 0;
    score.playerB = 0;

    LOG_INF("Starting pong game");
    led_matrix_print();
    k_sleep(K_SECONDS(10));
    

    while(true){
        LOG_INF("led_matrix_set(0,0,1)");
        led_matrix_set(0,0,1);
        k_sleep(K_SECONDS(1));

        LOG_INF("led_matrix_set(0,0,0)");
        led_matrix_set(0,0,0);
        k_sleep(K_SECONDS(1));
    }
}
