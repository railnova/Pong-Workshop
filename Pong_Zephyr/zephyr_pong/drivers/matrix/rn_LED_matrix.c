/**
 * Copyright Railnova 2022
 * Authors : Bultot Geoffrey & Lea Vielfaure
 * Railnova Proprietary Licence
 */

#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <dt-bindings/gpio/gpio.h>
#include <logging/log.h>

#include "rn_LED_matrix.h"

LOG_MODULE_REGISTER(rn_led_matrix, LOG_LEVEL_DBG);

// Macro to get the gpio structure using the device tree
#define GET_PIN_INFO(node_id, pha, idx) GPIO_DT_SPEC_GET_BY_IDX(node_id, pha, idx),

// Get led matrix node in the device tree
#define MATRIX_NODE  DT_INST(0, zephyr_railnova_led_matrix)
#define ROW_COUNT    DT_PROP_LEN(MATRIX_NODE, rowgpios)
#define COL_COUNT    DT_PROP_LEN(MATRIX_NODE, colgpios)

// Declare buttons structures & callback
#define NB_BUTTON 5
enum button_labels {
	B_RIGHT_UP = 0,
	B_RIGHT_DOWN,
    B_LEFT_UP,
    B_LEFT_DOWN,
    B_RESET,
};

static enum pin_interrupt last_pin_isr;

struct button_cfg {
    struct gpio_dt_spec gpio;
    struct gpio_callback callback;
};

struct button_cfg buttons[NB_BUTTON];

// Right button
const struct gpio_dt_spec br_up = GPIO_DT_SPEC_GET(DT_NODELABEL(br_up), gpios);
const struct gpio_dt_spec br_down = GPIO_DT_SPEC_GET(DT_NODELABEL(br_down), gpios);
// Left button
const struct gpio_dt_spec bl_up = GPIO_DT_SPEC_GET(DT_NODELABEL(bl_up), gpios);
const struct gpio_dt_spec bl_down = GPIO_DT_SPEC_GET(DT_NODELABEL(bl_down), gpios);
// Reset button
const struct gpio_dt_spec brst = GPIO_DT_SPEC_GET(DT_NODELABEL(breset), gpios);


// Matrix definition
static uint8_t matrix[8][8];

// Refresh frequency of the matrix & delayed work associated
#define REFRESH_FREQUENCY K_MSEC(10)
struct k_work_delayable refresh;

// Structure for GPIO specification by rows/column
struct display_drv_config {
    struct gpio_dt_spec rows[ROW_COUNT];
    struct gpio_dt_spec cols[COL_COUNT];
};

// Assignation of the GPIOs by rows/columns depending on the device tree
static const struct display_drv_config instance_config =
{
    .rows = { DT_FOREACH_PROP_ELEM(DT_NODELABEL(led_matrix), rowgpios, GET_PIN_INFO) },
    .cols = { DT_FOREACH_PROP_ELEM(DT_NODELABEL(led_matrix), colgpios, GET_PIN_INFO) },
};


/**
 * @brief Delayed work performed to set the proper GPIO depending 
 *        on the matrix.
 */
static void led_matrix_refresh(struct k_work *work){
    int row, col;
    for(row = 0; row < 8; row++){
        for(col = 0; col < 8; col++){
            gpio_pin_set_dt(&instance_config.rows[row], 0);
            gpio_pin_set_dt(&instance_config.cols[col], 0);

            if(matrix[row][col] != 0){
                // LOG_DBG("Row_pin = %d, Col_pin = %d", instance_config.rows[row].pin, instance_config.cols[col].pin);
                gpio_pin_set_dt(&instance_config.rows[row], 1);
                gpio_pin_set_dt(&instance_config.cols[col], 1);
            }   
        }
    }

    k_work_reschedule(&refresh, REFRESH_FREQUENCY);
}


/**
 * @brief Set the x, y value of the matrix to the assigned value.     
 * @attention x = [0,7], y = [0,7]
 * @example led_matrix_set(3, 4, 1)
 *          R0 x  x  x  x  x  x  x  x
 *          R1 x  x  x  x  x  x  x  x
 *          R2 x  x  x  x  x  x  x  x
 *          R3 x  x  x  x  1  x  x  x
 *          R4 x  x  x  x  x  x  x  x
 *          R5 x  x  x  x  x  x  x  x
 *          R6 x  x  x  x  x  x  x  x
 *          R7 x  x  x  x  x  x  x  x
 *             C0 C1 C2 C3 C4 C5 C6 C7
 */
void led_matrix_set(uint8_t x, uint8_t y, bool val){
    if(x >= ROW_COUNT){
        LOG_ERR("x value is out of bounds (x = %i), max value = %i", x, (ROW_COUNT-1));
        return;
    }
    else if(y >= COL_COUNT){
        LOG_ERR("y value is out of bounds (y = %i), max value = %i", y, (COL_COUNT-1));
        return;
    }

    matrix[y][x] = (uint8_t)val;
    return;
}


/**
 * @brief Print all the matrix on the serial port.
 */
void led_matrix_print(void){
    int row, col;
    printk("  ______________________________\r\n");
    for(row = 0; row < 8; row++){
        for(col = 0; col < 8; col++){
            if(matrix[row][col]){
                printk("   @");
            }else{
                printk("   O");
            }
        }
        printk("\r\n");
    }
    printk("  ______________________________\r\n");
}


/**
 * @brief Initialisation of buttons interrupts and callback creation.
 */
void led_matrix_init_buttons_callback(gpio_callback_handler_t handler){
    for(int i = 0; i < NB_BUTTON; i++){
        device_is_ready(buttons[i].gpio.port);
        gpio_pin_configure_dt(&buttons[i].gpio, GPIO_INPUT);
        gpio_pin_interrupt_configure_dt(&buttons[i].gpio, GPIO_INT_EDGE_TO_ACTIVE);
        gpio_init_callback(&buttons[i].callback, handler, BIT(buttons[i].gpio.pin)); 
        gpio_add_callback(buttons[i].gpio.port, &buttons[i].callback);
        LOG_DBG("Set up button at %s pin %d\n", buttons[i].gpio.port->name, buttons[i].gpio.pin);
    }
}


/**
 * @brief Recover pin name depending on the callback pin variable.
 */
int led_matrix_get_interrupt_label_by_pin(uint32_t pins){

    int pin_label = PIN_NOT_DEFINED;

    if(pins & BIT(buttons[B_RIGHT_UP].gpio.pin)) {
        LOG_DBG("Player A button 1 pressed");
        pin_label = PIN_BA1;
    }
    else if(pins & BIT(buttons[B_RIGHT_DOWN].gpio.pin)) {
        LOG_DBG("Player A button 2 pressed");
        pin_label = PIN_BA2;
    }
    else if(pins & BIT(buttons[B_LEFT_UP].gpio.pin)) {
        LOG_DBG("Player B button 1 pressed");
        pin_label = PIN_BB1;
    }
    else if(pins & BIT(buttons[B_LEFT_DOWN].gpio.pin)) {
        LOG_DBG("Player B button 2 pressed");
        pin_label = PIN_BB2;
    }
    else if(pins & BIT(buttons[B_RESET].gpio.pin)) {
        LOG_DBG("Reset button pressed");
        pin_label = PIN_B_RST;
    }

    last_pin_isr = pin_label;

    return pin_label;
}

/**
 * @brief Recover the last button pin that gives an interrupt.
 */
int led_matrix_get_last_pin_interrupt(void){

    return last_pin_isr;
}

/**
 * @brief Initialisation of the matrix driver. 
 */
static int instance_init(const struct device *dev)
{
    int i;

    // Led matrix initialisation
    LOG_DBG("instancied MATRIX R:%d , C:%d",ROW_COUNT,COL_COUNT);
    
    for (i = 0; i < ROW_COUNT; i++) {
        device_is_ready(instance_config.rows[i].port);
        gpio_pin_configure_dt(&instance_config.rows[i], GPIO_OUTPUT_ACTIVE);
        gpio_pin_set_dt(&instance_config.rows[i], 0);
    }
    for (i = 0; i < COL_COUNT; i++) {
        device_is_ready(instance_config.cols[i].port);
        gpio_pin_configure_dt(&instance_config.cols[i], GPIO_OUTPUT_ACTIVE);
        gpio_pin_set_dt(&instance_config.cols[i], 0);
    }

    // Buttons initialisations
    buttons[B_RIGHT_UP].gpio = br_up;
    buttons[B_RIGHT_DOWN].gpio = br_down;
    buttons[B_LEFT_UP].gpio = bl_up;
    buttons[B_LEFT_DOWN].gpio = bl_down;
    buttons[B_RESET].gpio = brst;

    for(i = 0; i < NB_BUTTON; i++){
        device_is_ready(buttons[i].gpio.port);
        gpio_pin_configure_dt(&buttons[i].gpio, GPIO_INPUT);
        gpio_pin_interrupt_configure_dt(&buttons[i].gpio, GPIO_INT_EDGE_TO_ACTIVE);
    }

    // Initialise delay work for led matrix refresh
    LOG_DBG("Init delayed work to refresh matrix");
    k_work_init_delayable(&refresh, led_matrix_refresh);
    k_work_schedule(&refresh, REFRESH_FREQUENCY);

    return 0;
}

DEVICE_DT_DEFINE(MATRIX_NODE, instance_init, NULL, NULL, 
                &instance_config, POST_KERNEL, CONFIG_GPIO_INIT_PRIORITY, NULL);
