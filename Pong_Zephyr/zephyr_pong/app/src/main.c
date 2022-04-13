/**
 * Copyright Railnova 20222 - [year]
 * Authors : Bultot Geoffrey
 * Railnova Proprietary Licence
 */

#include <zephyr.h>
#include <sys/printk.h>

void main(void)
{
	printk("Hello World! %s\n", CONFIG_BOARD);
}
