#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "74hc595.c"

#define DATA_PIN 20
#define CLK_PIN 15
#define LATCH_PIN 14

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

  uint8_t map[128];
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

  // Init clock pin
  gpio_init(CLK_PIN);
  gpio_set_dir(CLK_PIN, 1);

  // Init data pin
  gpio_init(DATA_PIN);
  gpio_set_dir(DATA_PIN, 1);

  // Init latch pin
  gpio_init(LATCH_PIN);
  gpio_set_dir(LATCH_PIN, 1);

  sr_74hc595 *shift_register = new_sr_74hc595(CLK_PIN, DATA_PIN, LATCH_PIN);

  char *test_string = "314159265";
  int i = 0;
  while (true)  {
    while (test_string[i] != '\0') {
      uint8_t mask = map[test_string[i]];
      sr_74hc595_send_data(shift_register, mask);
      sleep_ms(250);
      i++;
    }
    sleep_ms(1000);
    i = 0;
  }
}
