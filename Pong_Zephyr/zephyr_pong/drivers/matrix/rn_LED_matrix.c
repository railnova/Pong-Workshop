#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <dt-bindings/gpio/gpio.h>
#include <logging/log.h>

#define GET_PIN_INFO(node_id, pha, idx) GPIO_DT_SPEC_GET_BY_IDX(node_id, pha, idx),

#define MATRIX_NODE  DT_INST(0, zephyr_railnova_led_matrix)
#define ROW_COUNT    DT_PROP_LEN(MATRIX_NODE, rowgpios)
#define COL_COUNT    DT_PROP_LEN(MATRIX_NODE, colgpios)

#define REFRESH_FREQUENCY K_MSEC(10)

#define PIN_LOW 0
#define PIN_HIGH 1

struct display_drv_config {
    struct gpio_dt_spec rows[ROW_COUNT];
    struct gpio_dt_spec cols[COL_COUNT];
};

LOG_MODULE_REGISTER(rn_led_matrix, LOG_LEVEL_DBG);

static struct display_drv_config instance_config=
{
    .rows = { DT_FOREACH_PROP_ELEM(DT_NODELABEL(led_matrix), rowgpios, GET_PIN_INFO) },
    .cols = { DT_FOREACH_PROP_ELEM(DT_NODELABEL(led_matrix), colgpios, GET_PIN_INFO) },
};

extern uint8_t led_matrix[8][8];

static struct k_work_delayable refresh;

static void led_matrix_set_reset(uint8_t set_reset){
    int row, col;
    for(row = 0; row < 8; row++){
        for(col = 0; col < 8; col++){
            led_matrix[row][col]=set_reset;
        }
    }
}

void led_matrix_refreshMatrix(struct k_work *work){
    int row, col;
    for(row = 0; row < 8; row++){
        for(col = 0; col < 8; col++){
            gpio_pin_set_dt(&(instance_config.rows[row]), led_matrix[row][col]);
            gpio_pin_set_dt(&(instance_config.cols[col]), led_matrix[row][col]);
            if(led_matrix[row][col]){
                printk("R: %d , C:%d\n\r",instance_config.rows[row].pin,instance_config.cols[col].pin);
            }
        }
    }

    k_work_reschedule(&refresh, REFRESH_FREQUENCY);
}

void led_matrix_clear(void){
    led_matrix_set_reset(PIN_HIGH);
}
void led_matrix_set_all(void){
    led_matrix_set_reset(PIN_LOW);
}

void led_matrix_print(void){
    int row = 0;
    int col = 0;
    printk("__________________________________\r\n");
    for(row = 0; row < 8; row++){
        for(col = 0; col < 8; col++){
            if(led_matrix[row][col]){
                printk("1");
            }else{
                printk("0");
            }
        }
        printk("\r\n");
    }
    printk("__________________________________\r\n");
}

static int instance_init(const struct device *dev)
{
    uint8_t i;
    LOG_DBG("instancied MATRIX R:%d , C:%d",ROW_COUNT,COL_COUNT);
    
    for (i = 0; i < ROW_COUNT; i++) {
        device_is_ready(instance_config.rows[i].port);
        gpio_pin_configure_dt(&(instance_config.rows[i]), GPIO_OUTPUT_ACTIVE);
        gpio_pin_set_dt(&(instance_config.rows[i]), PIN_LOW);
    }
    for (i = 0; i < COL_COUNT; i++) {
        device_is_ready(instance_config.cols[i].port);
        gpio_pin_configure_dt(&(instance_config.cols[i]), GPIO_OUTPUT_ACTIVE);
        gpio_pin_set_dt(&(instance_config.cols[i]), PIN_LOW);
    }

    LOG_DBG("Init delayed work to refresh matrix");
    k_work_init_delayable(&refresh, led_matrix_refreshMatrix);

    return 0;
}

DEVICE_DT_DEFINE(MATRIX_NODE,
         instance_init, NULL,
         NULL, &instance_config,
         POST_KERNEL, CONFIG_GPIO_INIT_PRIORITY, NULL);
