#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
const int BTN_PIN_G = 26;

volatile int flag_r = 0;
volatile int flag_g = 0;

const int LED_R = 4;
const int LED_G = 6;

void btn_callback(uint gpio, uint32_t events) {
  if (gpio == BTN_PIN_R) {     
    flag_r = !flag_r;
  } else if (gpio == BTN_PIN_G) {
    flag_g = !flag_g;
  }
}

int main() {
  stdio_init_all();

  gpio_init(LED_R);
  gpio_set_dir(LED_R, GPIO_OUT);

  gpio_init(LED_G);
  gpio_set_dir(LED_G, GPIO_OUT);

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_init(BTN_PIN_G);
  gpio_set_dir(BTN_PIN_G, GPIO_IN);
  gpio_pull_up(BTN_PIN_G);

  // callback led r (first)
  gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_FALL, true, &btn_callback);

  // callback led g (nao usar _with_callback)
  gpio_set_irq_enabled(BTN_PIN_G, GPIO_IRQ_EDGE_RISE, true);

  while (true) {
    sleep_ms(50);
    gpio_put(LED_R, flag_r);
    gpio_put(LED_G, flag_g);
  }
}
