/**
 * Copyright Railnova 2022
 * Authors : Bultot Geoffrey & Lea Vielfaure
 * Railnova Proprietary Licence
 */

#ifndef RN_LED_MATRIX_H_
#define RN_LED_MATRIX_H_

#include <drivers/gpio.h>
#include <dt-bindings/gpio/gpio.h>

void led_matrix_set(uint8_t x, uint8_t y, bool val);
void led_matrix_print();
void led_matrix_clear();

enum pin_interrupt {
    PIN_NOT_DEFINED = -1,
    PIN_BA1 = 0,
    PIN_BA2,
    PIN_BB1,
    PIN_BB2,
    PIN_B_RST,
};

typedef enum{
    E_LEFT = 0,
    E_RIGHT,
}t_cursor_direction;

void led_matrix_and_buttons_init();
int led_matrix_get_interrupt_label_by_pin(uint32_t pins);
int led_matrix_get_last_pin_interrupt();
void led_matrix_button_irq_state(bool irq_state);

extern void cb_button_playerA_pressed(t_cursor_direction direction);
extern void cb_button_playerB_pressed(t_cursor_direction direction);
extern void cb_button_reset_pressed();


struct score {
    uint8_t playerA;
    uint8_t playerB;
};

struct ball_coordinate {
    uint8_t x;
    uint8_t y;
    int x_dir; 
    int y_dir; 
};

struct cursor_coordinate {
    uint8_t x;
    uint8_t y1;
    uint8_t y2;
};

#endif //RN_LED_MATRIX_H_
