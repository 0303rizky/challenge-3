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

void pola_alphabet(void *pvParameters) {
    while (1) {
  char *alphabet = (char *)malloc(27); // 26 karakter alfabet + 1 null terminator

  if (alphabet == NULL) {
    printf("Gagal mengalokasikan memori.");
    return;

     // Inisialisasi string dengan alfabet awal (a-z)
  for (int i = 0; i < 26; i++) {
    alphabet[i] = 'a' + i;
  }
  alphabet[26] = '\0'; // Menambahkan null terminator

  // Menampilkan string awal
  printf("pola 1 ");
  printf(alphabet);

  // Melakukan pergeseran alfabet sebanyak 10 kali
  for (int k = 0; k < 10; k++) {
    // Menampilkan string setelah pergeseran (mulai dari pengulangan kedua)
    if (k > 0) {
//      printf("pola ");
//      printf(k+1);
//      printf(": ");
      printf(alphabet);
    }

    if (k < 10) {
      char first_char = alphabet[0];

      for (int i = 0; i < 25; i++) {
        alphabet[i] = alphabet[i + 1];
      }

      alphabet[25] = first_char;
    }

    // Menunggu sebentar (opsional)
        vTaskDelay(1000 / portTICK_PERIOD_MS);
  }

  // Bebaskan memori yang telah dialokasikan di heap
  free(alphabet);

  // Loop tidak perlu dijalankan secara berulang pada Arduino IDE, sehingga tidak perlu mematikan perangkat.
}
  }
    }

void app_main() {
    esp_rom_gpio_pad_select_gpio(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

    xTaskCreate(&led_control_task, "led_control_task", 2048, NULL, 5, NULL);

    xTaskCreate(pola_alphabet, "pola_alphabet_task", 2048, NULL, 1, NULL);
}