#include <zephyr.h>
#include <logging/log.h>
#include <stdlib.h>

#include "rn_LED_matrix.h"
#include "pong_game.h"

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
}

/**
 * @brief Reset the game: 
 *              - Reset score
 *              - Reset ball position
 *              - Reset cursors position
 */
void reset_game(void) {
}

/**
 * @brief Game main loop
 *              - Move the ball to the next position
 *              - Handle the collisions with the limits of the matrix
 *              and the cursor
 *              - Update score
 *              - End the game when needed
 */
void pong_game(void) {
}