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

enum pin_interrupt {
    PIN_NOT_DEFINED = -1,
    PIN_BA1 = 0,
    PIN_BA2,
    PIN_BB1,
    PIN_BB2,
    PIN_B_RST,
};

void led_matrix_init_buttons_callback(gpio_callback_handler_t handler);
int led_matrix_get_interrupt_label_by_pin(uint32_t pins);
int led_matrix_get_last_pin_interrupt(void);


struct score {
    uint8_t playerA;
    uint8_t playerB;
};

struct ball_coordinate {
    uint8_t x;
    uint8_t y;
};

struct cursor_coordinate {
    uint8_t x;
    uint8_t y1;
    uint8_t y2;
};

#endif //RN_LED_MATRIX_H_
