#ifndef RN_LED_MATRIX_H_
#define RN_LED_MATRIX_H_

static int instance_init(const struct device *dev);

void led_matrix_clear();
void led_matrix_set_all();

void dbg_print_matrix();

void refreshMatrix();

#endif //RN_LED_MATRIX_H_