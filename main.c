#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define FIRST_GPIO 12

int nums[10] = {
  0x3f,
  0x06,
  0x5b,
  0x4f,
  0x66,
  0x6d,
  0x7d,
  0x07,
  0x7f,
  0x67,
};

int main() {
  stdio_init_all();

  for (int gpio = FIRST_GPIO; gpio < FIRST_GPIO + 7; gpio++) {
    gpio_init(gpio);
    gpio_set_dir(gpio, GPIO_OUT);
    gpio_set_outover(gpio, GPIO_OVERRIDE_INVERT);
    gpio_set_outover(gpio, GPIO_OVERRIDE_INVERT);
  }

  int i;
  while (true)  {
    for (i = 0; i < 10; i++) {
      int32_t mask = nums[i] << FIRST_GPIO; 
      gpio_set_mask(mask);
      sleep_ms(250);
      gpio_clr_mask(mask);
    }
  }
}
