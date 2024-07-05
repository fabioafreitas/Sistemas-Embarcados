#include <Arduino.h>

TaskHandle_t Task1;

void task1(void *pvParameters) {
  while (true) {
    // Your code here
    Serial.println("task1");
    vTaskDelay(pdMS_TO_TICKS(2000)); // Delay for 1 second
  }
}

void setup() {
  Serial.begin(115200);

  // Create Task1
  xTaskCreatePinnedToCore(
    task1,       // Function to implement the task
    "Task1",     // Name of the task
    10000,       // Stack size in words
    NULL,        // Task input parameter
    1,           // Priority of the task
    &Task1,      // Task handle
    0            // Core where the task should run (0 or 1)
  );
}

void loop() {
  // Main processing here
  Serial.println("Main loop running...");
  delay(1000); // Delay for 1 second
}
