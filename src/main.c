#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_GPIO 2 // Pin GPIO2 digunakan untuk mengontrol LED pada board ESP32 DevKit v1

void led_control_task(void *pvParameters) {
    while (1) {
        printf("Pola 1: LED menyala selama 1s dalam 5s\n");
        gpio_set_level(LED_GPIO, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(LED_GPIO, 0);
        vTaskDelay(4000 / portTICK_PERIOD_MS);

        printf("Pola 2: LED menyala selama 2s dalam 5s\n");
        gpio_set_level(LED_GPIO, 1);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        gpio_set_level(LED_GPIO, 0);
        vTaskDelay(3000 / portTICK_PERIOD_MS);

        printf("Pola 3: LED menyala selama 3s dalam 5s\n");
        gpio_set_level(LED_GPIO, 1);
        vTaskDelay(3000 / portTICK_PERIOD_MS);
        gpio_set_level(LED_GPIO, 0);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

void app_main() {
    esp_rom_gpio_pad_select_gpio(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

    xTaskCreate(&led_control_task, "led_control_task", 2048, NULL, 5, NULL);
}