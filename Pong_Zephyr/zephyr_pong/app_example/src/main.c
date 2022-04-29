/**
 * Copyright Railnova 2022
 * Authors : Bultot Geoffrey & Lea Vielfaure
 * Railnova Proprietary Licence
 */

#include <zephyr.h>
#include <logging/log.h>

#include "rn_LED_matrix.h"
#include "rn_pong_game_example.h"

/*
 * This discribe the log level, you can choose between :
 * LOG_LEVEL_NONE, LOG_LEVEL_ERR, LOG_LEVEL_WRN, LOG_LEVEL_INF, LOG_LEVEL_DBG
 * The associated LOG_xxx() message will be printed depending on the level selected. 
 */
LOG_MODULE_REGISTER(main_example, LOG_LEVEL_DBG);

K_WORK_DEFINE(button_playerA_work, button_playerA_pressed);
K_WORK_DEFINE(button_playerB_work, button_playerB_pressed);
K_WORK_DEFINE(button_reset_work, button_reset_pressed);

/**
 * @brief Callback handler for the buttons. 
 */
void buttons_callback(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    int pin; 
    pin = led_matrix_get_interrupt_label_by_pin(pins);

    if(pin == PIN_BA1 || pin == PIN_BA2){
        k_work_submit(&button_playerA_work);
    }
    else if(pin == PIN_BB1 || pin == PIN_BB2){
        k_work_submit(&button_playerB_work);
    } 
    else if(pin == PIN_B_RST){
        k_work_submit(&button_reset_work);
    }
    
    return;
}

/**
 * @brief Work to perform when player A press one of his buttons. 
 *        This job set up called inside buttons_callback
 */
void button_playerA_pressed(struct k_work *work){
    int pin = led_matrix_get_last_pin_interrupt();
    switch(pin){
        case PIN_BA1:
            LOG_DBG("Player A button 1 pressed");
            break;

        case PIN_BA2:
            LOG_DBG("Player A button 2 pressed");
            break;

        default:
            LOG_DBG("Unknown button pressed for player A");
            break;
    }

    return;
}

/**
 * @brief Work to perform when player B press one of his buttons. 
 *        This job set up called inside buttons_callback
 */
void button_playerB_pressed(struct k_work *work){
    int pin = led_matrix_get_last_pin_interrupt();
    switch(pin){
        case PIN_BB1:
            LOG_DBG("Player B button 1 pressed");
            break;

        case PIN_BB2:
            LOG_DBG("Player B button 2 pressed");
            break;

        default:
            LOG_DBG("Unknown button pressed for player B");
            break;
    }

    return;
}

/**
 * @brief Work to perform when the reset button is pressed. 
 *        This job set up called inside buttons_callback
 */
void button_reset_pressed(struct k_work *work){
    LOG_DBG("Reset button pressed");
    reset_game();
    return;
}

// Take into account that refresh frequency = 10 ms
void main(void)
{    
    led_matrix_init_buttons_callback(buttons_callback);
    k_work_init(&button_playerA_work, button_playerA_pressed);
    k_work_init(&button_playerB_work, button_playerB_pressed);
    k_work_init(&button_reset_work, button_reset_pressed);

    reset_game();
    LOG_INF("Score = %i - %i", score.playerA, score.playerB);

    int i;

    score.playerA = 12;
    score.playerB = 97;

    led_matrix_clear();
    k_sleep(K_SECONDS(1));
    
    while(true){

        led_matrix_clear();

        for(i=0;i<100;i++){
            score.playerA = i;
            score.playerB = i;
            display_score();
            k_sleep(K_SECONDS(2)); 
            
        }
    }
}
