#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define FIRST_GPIO 12

// 7-segment digit bitmasks
#define SEG7_0 0x3f
#define SEG7_1 0x06
#define SEG7_2 0x5b;
#define SEG7_3 0x4f;
#define SEG7_4 0x66;
#define SEG7_5 0x6d;
#define SEG7_6 0x7d;
#define SEG7_7 0x07;
#define SEG7_8 0x7f;
#define SEG7_9 0x67;

int main() {
  stdio_init_all();

  int map[128];
  map['0'] = SEG7_0;
  map['1'] = SEG7_1;
  map['2'] = SEG7_2;
  map['3'] = SEG7_3;
  map['4'] = SEG7_4;
  map['5'] = SEG7_5;
  map['6'] = SEG7_6;
  map['7'] = SEG7_7;
  map['8'] = SEG7_8;
  map['9'] = SEG7_9;

  // Init GPIO
  for (int gpio = FIRST_GPIO; gpio < FIRST_GPIO + 7; gpio++) {
    gpio_init(gpio);
    gpio_set_dir(gpio, GPIO_OUT);
    gpio_set_outover(gpio, GPIO_OVERRIDE_INVERT);
  }

  char *test_string = "314159265";
  int i = 0;
  while (true)  {
    while (test_string[i] != '\0') {
      int32_t mask = map[test_string[i]] << FIRST_GPIO; 
      gpio_set_mask(mask);
      sleep_ms(250);
      gpio_clr_mask(mask);
      i++;
    }
    sleep_ms(1000);
    i = 0;
  }
}
