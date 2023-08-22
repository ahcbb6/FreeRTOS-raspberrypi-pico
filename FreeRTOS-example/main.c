#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include <string.h>
#include <time.h>

#include <FreeRTOS.h>
#include <task.h>

#include "pico/stdlib.h"

void vPeriodicLED(void *state);

TaskHandle_t vPeriodicLED_handle = NULL;
static uint8_t state = 1;
static const UBaseType_t defaultDelay = 1000;

/* Run a periodic task every <delay in ms> that switches the state of the LED */
void vPeriodicLED(void *state){
  TickType_t lastWakeTime;

  lastWakeTime = xTaskGetTickCount();
  for( ; ; ){
    /* Get and update the state of the LED */
    uint8_t st = !*(uint8_t*)state;
    state = (void*)&st;
    gpio_put(PICO_DEFAULT_LED_PIN, st);
    vTaskDelayUntil( &lastWakeTime, defaultDelay / portTICK_RATE_MS );
  }
  vTaskDelete(NULL);
}


int main() {
#ifndef PICO_DEFAULT_LED_PIN
#warning FreeRTOS blink example requires a board with a regular LED
#else

  gpio_init(PICO_DEFAULT_LED_PIN);
  gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
  if ( pdPASS != xTaskCreate(vPeriodicLED, "taskLED", 128, NULL, state, &vPeriodicLED_handle) ){
    /* error */
    exit(1);
  }
  vTaskStartScheduler();
  while(true){};
#endif
}
