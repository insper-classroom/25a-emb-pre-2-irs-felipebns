#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
const int LED = 4;

volatile int flag = 0;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { // fall edge
    flag = !flag;
  }
}

int main() {
  stdio_init_all();

  gpio_init(LED);
  gpio_set_dir(LED, GPIO_OUT);

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_set_irq_enabled_with_callback(
      BTN_PIN_R, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);

  while (true) {
    if (flag == 1){
      gpio_put(LED, 1);
      sleep_ms(50);
    } else if (flag == 0){
      gpio_put(LED, 0);
      sleep_ms(50);
    }
  }
}
