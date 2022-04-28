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
    PIN_B1_UP = 0,
    PIN_B1_DOWN,
    PIN_B2_UP,
    PIN_B2_DOWN,
    PIN_B_RST,
};

void led_matrix_init_buttons_callback(gpio_callback_handler_t handler);
int led_matrix_get_pin_interrupt(uint32_t pins);

#endif //RN_LED_MATRIX_H_
