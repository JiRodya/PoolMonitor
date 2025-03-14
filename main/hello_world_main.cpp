#include <cstdio>       // For printf
#include "esp_mac.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

// Add the necessary include paths
#include "sys/reent.h"

//drivers include
#include "test.h"

// Logger tag for debugging
static const char* TAG = "MAIN";

// FreeRTOS task example
void myTask(void* arg) {
    while (true) {
        ESP_LOGI(TAG, "Hello from FreeRTOS Task!");
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay 1 second
    }
}

// Main entry point
extern "C" void app_main() {
    ESP_LOGI(TAG, "Starting ESP-IDF C++ Project");

    // Create a FreeRTOS task
    xTaskCreate(myTask, "MyTask", 4096, nullptr, 1, nullptr);

    // Main loop (optional)
    while (true) {
        ESP_LOGI(TAG, "Main loop running...");
        vTaskDelay(pdMS_TO_TICKS(2000)); // Delay 2 seconds
    }
}
