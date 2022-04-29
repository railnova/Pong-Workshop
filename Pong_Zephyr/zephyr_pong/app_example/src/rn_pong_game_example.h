/**
 * Copyright Railnova 2022
 * Authors : Bultot Geoffrey & Lea Vielfaure
 * Railnova Proprietary Licence
 */

extern struct score score;
extern struct cursor_coordinate cursor_playerA;
extern struct cursor_coordinate cursor_playerB;
extern struct ball_coordinate ball;

#define RIGHT 0
#define LEFT 1

void reset_game(void);

void button_playerA_pressed(struct k_work *work);
void button_playerB_pressed(struct k_work *work);
void button_reset_pressed(struct k_work *work);


