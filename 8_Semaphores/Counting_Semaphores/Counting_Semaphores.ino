#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#define RED 6
#define YELLOW 7
#define BLUE 8

SemaphoreHandle_t xCountingSemaphore;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(BLUE, OUTPUT);

  xCountingSemaphore = xSemaphoreCreateCounting(1, 0);

  xTaskCreate(vRedLEDControllerTask, "RED LED Task", 100, NULL, 1, NULL);
  xTaskCreate(vYellowLEDControllerTask, "YELLOW LED Task", 100, NULL, 1, NULL);
  xTaskCreate(vBlueLEDControllerTask, "BLUE LED Task", 100, NULL, 1, NULL);

  xSemaphoreGive(xCountingSemaphore);
}

void loop() {}

void vRedLEDControllerTask(void *pvParameters)
{
  while (true)
  {
    xSemaphoreTake(xCountingSemaphore, portMAX_DELAY);

    digitalWrite(RED, digitalRead(RED) ^ 1);
    Serial.println("RED LED Task");

    xSemaphoreGive(xCountingSemaphore);
    vTaskDelay(1);
  }
}

void vYellowLEDControllerTask(void *pvParameters)
{
  while (true)
  {
    xSemaphoreTake(xCountingSemaphore, portMAX_DELAY);

    digitalWrite(YELLOW, digitalRead(YELLOW) ^ 1);
    Serial.println("YELLOW LED Task");

    xSemaphoreGive(xCountingSemaphore);
    vTaskDelay(1);
  }
}

void vBlueLEDControllerTask(void *pvParameters)
{
  while (true)
  {
    xSemaphoreTake(xCountingSemaphore, portMAX_DELAY);

    digitalWrite(BLUE, digitalRead(BLUE) ^ 1);
    Serial.println("BLUE LED Task");

    xSemaphoreGive(xCountingSemaphore);
    vTaskDelay(1);
  }
}
