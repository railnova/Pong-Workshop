/**
 * Copyright Railnova 2022
 * Authors : Bultot Geoffrey & Lea Vielfaure
 * Railnova Proprietary Licence
 */

extern struct score score;
extern struct cursor_coordinate cursor_playerA;
extern struct cursor_coordinate cursor_playerB;
extern struct ball_coordinate ball;

extern bool game_ongoing;

#define RIGHT 0
#define LEFT 1

void pong_game(void);
void reset_game(void);
void display_score(void);


