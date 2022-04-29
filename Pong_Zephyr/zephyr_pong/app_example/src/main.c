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

/**
 * @brief Work to perform when player A press one of his buttons. 
 *        This job set up called inside buttons_callback
 */
void cb_button_playerA_pressed(int pin){
    switch(pin){
        case PIN_BA1:
            LOG_DBG("Player A button 1 pressed (going up)");
            if(cursor_playerA.y2 != 1){
                led_matrix_set(cursor_playerA.x, cursor_playerA.y1, 0);
                led_matrix_set(cursor_playerA.x, cursor_playerA.y2, 0);
                cursor_playerA.y2 = cursor_playerA.y1;
                cursor_playerA.y1--;
            }  
            break;

        case PIN_BA2:
            LOG_DBG("Player A button 2 pressed (going down)");
            if(cursor_playerA.y1 != 6){
                led_matrix_set(cursor_playerA.x, cursor_playerA.y1, 0);
                led_matrix_set(cursor_playerA.x, cursor_playerA.y2, 0);
                cursor_playerA.y1 = cursor_playerA.y2;
                cursor_playerA.y2++;
            }
            break;

        default:
            LOG_DBG("Unknown button pressed for player A");
            break;
    }

    led_matrix_set(cursor_playerA.x, cursor_playerA.y1, 1);
    led_matrix_set(cursor_playerA.x, cursor_playerA.y2, 1);

    return;
}

/**
 * @brief Work to perform when player B press one of his buttons. 
 *        This job set up called inside buttons_callback
 */
void cb_button_playerB_pressed(int pin){
    switch(pin){
        case PIN_BB1:
            LOG_DBG("Player B button 1 pressed (going up)");
            if(cursor_playerB.y2 != 1){
                led_matrix_set(cursor_playerB.x, cursor_playerB.y1, 0);
                led_matrix_set(cursor_playerB.x, cursor_playerB.y2, 0);
                cursor_playerB.y2 = cursor_playerB.y1;
                cursor_playerB.y1--;
            }
            break;

        case PIN_BB2:
            LOG_DBG("Player B button 2 pressed (going down)");
            if(cursor_playerB.y1 != 6){
                led_matrix_set(cursor_playerB.x, cursor_playerB.y1, 0);
                led_matrix_set(cursor_playerB.x, cursor_playerB.y2, 0);
                cursor_playerB.y1 = cursor_playerB.y2;
                cursor_playerB.y2++;
            }
            break;

        default:
            LOG_DBG("Unknown button pressed for player B");
            break;
    }

    led_matrix_set(cursor_playerB.x, cursor_playerB.y1, 1);
    led_matrix_set(cursor_playerB.x, cursor_playerB.y2, 1);

    return;
}

/**
 * @brief Work to perform when the reset button is pressed. 
 *        This job set up called inside buttons_callback
 */
void cb_button_reset_pressed(){
    LOG_DBG("Reset button pressed");
    reset_game();
    return;
}


void main(void)
{    
    game_ongoing = false;
    led_matrix_and_buttons_init();

    reset_game();
    LOG_INF("Score = %i - %i", score.playerA, score.playerB);
    k_sleep(K_SECONDS(1));
    
    while(true){
        pong_game();
        k_sleep(K_MSEC(500));
    }
}
