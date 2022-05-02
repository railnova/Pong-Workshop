/**
 * Copyright Railnova 2022
 * Authors : Bultot Geoffrey & Lea Vielfaure
 * Railnova Proprietary Licence
 */

#include <zephyr.h>
#include <logging/log.h>

#include "rn_LED_matrix.h"
#include "pong_game.h"

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
void cb_button_playerA_pressed(t_cursor_direction direction){
    return;
}

/**
 * @brief Work to perform when player B press one of his buttons. 
 *        This job set up called inside buttons_callback
 */
void cb_button_playerB_pressed(t_cursor_direction direction){
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
