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

    // Reset score
    score.playerA = 0;
    score.playerB = 0;

    start_new_round();

    return;
}

/**
 * @brief Display the score depending on the number and the position.
 * @param position 
 */
void get_led_matrix_depending_on_number(bool position, uint8_t number, uint8_t temp_matrix[][8]){

    int i,j;
    uint64_t number_image = 0x00;
    uint8_t bit_pos = 0;

    switch(number){
        case 0:
            number_image = 0x0060909090906000;
            break;

        case 1:
            number_image = 0x00808080a0c08000;
            break;

        case 2:
            number_image = 0x00f0204090906000;
            break;

        case 3:
            number_image = 0x007080806040f000;
            break;

        case 4:
            number_image = 0x0040f05010101000;
            break;

        case 5:
            number_image = 0x007080807010f000;
            break;

        case 6:
            number_image = 0x006090907010e000;
            break;

        case 7:
            number_image = 0x004040408090f000;
            break;

        case 8:
            number_image = 0x0060909060906000;
            break;

        case 9:
            number_image = 0x00f08080f090f000;
            break;

        default:
            LOG_ERR("Number is not valid, it should be [0,9]");

    }

    // If we display number on the left
    if(position == LEFT){
        for(i = 0; i < 8; i++){
            bit_pos = bit_pos + 4;
            for(j = 0; j < 4; j++){
                temp_matrix[i][j] =  (number_image>>bit_pos) & 0x1;
                bit_pos++;
            }
        }
    }

    // If we display number on the right
    else {
        for(i = 0; i < 8; i++){
            bit_pos = bit_pos + 4;
            for(j = 4; j < 8; j++){
                temp_matrix[i][j] =  (number_image>>bit_pos) & 0x1;
                bit_pos++;
            }
        }
    }

    return;
}


/**
 * @brief Display the score.
 */
void display_score(void) {

    LOG_DBG("Display score game");
    int i,j;
    uint8_t matrix_temp[8][8];

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

    // Display score for player A
    if(score.playerA > 99 || score.playerB > 99) {
        LOG_ERR("Score to high, reset game");
        return;
    }

    uint8_t unit = score.playerA%10;
    uint8_t tens = score.playerA/10;
    get_led_matrix_depending_on_number(LEFT, tens, matrix_temp);
    get_led_matrix_depending_on_number(RIGHT, unit, matrix_temp);

    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
            if(matrix_temp[i][j]){
                led_matrix_set(i, j, 1);
            }
        }
    }

    k_sleep(K_SECONDS(3));

    unit = score.playerB%10;
    tens = score.playerB/10;
    get_led_matrix_depending_on_number(LEFT, tens, matrix_temp);
    get_led_matrix_depending_on_number(RIGHT, unit, matrix_temp);

    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
            if(matrix_temp[i][j]){
                led_matrix_set(i, j, 1);
            }
        }
    }

    k_sleep(K_SECONDS(3));

    return;
}

