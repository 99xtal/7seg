#include <stdlib.h>
#include "pico/stdlib.h"

#define CLOCK_DELAY_US = 5

typedef struct sr_74hc595 {
    int clk_pin;
    int data_pin;
    int latch_pin;
} sr_74hc595;

sr_74hc595 * new_sr_74hc595(int clk_pin, int data_pin, int latch_pin) {
    // Allocate memory for shift register
    sr_74hc595 *shift_register = (sr_74hc595 *) malloc(sizeof(sr_74hc595));

    shift_register->clk_pin = clk_pin;
    shift_register->data_pin = data_pin;
    shift_register->latch_pin = latch_pin;

    return shift_register;
};

// Creates clock signal
void clock_signal(sr_74hc595 *sr) {
    gpio_put(sr->clk_pin, 1);
    sleep_us(5);
    gpio_put(sr->clk_pin, 0);
    sleep_us(5);
};

// Enables latch pin
void latch_enable(struct sr_74hc595 *shreg_74hc595) {
    gpio_put(shreg_74hc595->latch_pin, 1);
    sleep_us(5);
    gpio_put(shreg_74hc595->latch_pin, 0);
}

void sr_74hc595_send_data(sr_74hc595 *sr, uint8_t data) {
    for (int i = 0; i < 8 ; i++) {
        gpio_put(sr->data_pin, (data >> i) & (0x01));
        clock_signal(sr);
    }

    latch_enable(sr);
};
