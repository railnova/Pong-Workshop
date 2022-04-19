#ifndef RN_LED_MATRIX_H_
#define RN_LED_MATRIX_H_

void led_matrix_clear();
void led_matrix_set_all();

void led_matrix_print();

void led_matrix_refreshMatrix();

uint8_t led_matrix[8][8];

#endif //RN_LED_MATRIX_H_
