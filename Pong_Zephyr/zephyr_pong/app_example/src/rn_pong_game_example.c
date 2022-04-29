/**
 * Copyright Railnova 2022
 * Authors : Bultot Geoffrey & Lea Vielfaure
 * Railnova Proprietary Licence
 */

#include <zephyr.h>
#include <logging/log.h>

#include "rn_LED_matrix.h"
#include "rn_pong_game_example.h"


LOG_MODULE_REGISTER(rn_pong_game, LOG_LEVEL_DBG);


struct score score;
struct cursor_coordinate cursor_playerA;
struct cursor_coordinate cursor_playerB;
struct ball_coordinate ball;


/**
 * @brief Start new round. 
 *              - Reset ball position
 *              - Reset cursors position
 */
void start_new_round(void) {

    LOG_DBG("Start new round game");
    int i,j;

    // Reset all matrix 
    for(i=0; i<8; i++){
        for(j=0; j<8; j++){
            led_matrix_set(i,j,0);
        }
    }

    // Reset ball position
    ball.x = 4;
    ball.y = 3;
    led_matrix_set(ball.x, ball.y, 1);

    // Reset cursor position
    cursor_playerA.x = 0;
    cursor_playerA.y1 = 3;
    cursor_playerA.y2 = (cursor_playerA.y1 + 1);

    cursor_playerB.x = 7;
    cursor_playerB.y1 = cursor_playerA.y1;
    cursor_playerB.y2 = (cursor_playerB.y1 + 1);

    led_matrix_set(cursor_playerA.x, cursor_playerA.y1, 1);
    led_matrix_set(cursor_playerA.x, cursor_playerA.y2, 1);
    led_matrix_set(cursor_playerB.x, cursor_playerB.y1, 1);
    led_matrix_set(cursor_playerB.x, cursor_playerB.y2, 1);

    k_sleep(K_MSEC(100));

    return;
}

/**
 * @brief Reset the game: 
 *              - Reset score
 *              - Reset ball position
 *              - Reset cursors position
 */
void reset_game(void) {

    LOG_DBG("Resetting game");
    int i,j;

    // Reset score
    score.playerA = 0;
    score.playerB = 0;

    start_new_round();

    return;
}


/**
 * @brief Display the score.
 */
void display_score(void) {

    LOG_DBG("Display score game");
    int i,j;

    // Power on all leds 
    for(i=0; i<8; i++){
        for(j=0; j<8; j++){
            led_matrix_set(i,j,1);
        }
    }

    k_sleep(K_MSEC(50));

    // Power off all leds 
    for(i=0; i<8; i++){
        for(j=0; j<8; j++){
            led_matrix_set(i,j,0);
        }
    }

    k_sleep(K_MSEC(50));

    // Display score

    return;
}

