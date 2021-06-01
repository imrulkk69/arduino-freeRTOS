#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#define RED 6
#define YELLOW 7
#define BLUE 8

SemaphoreHandle_t xBinarySemaphore;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  xBinarySemaphore = xSemaphoreCreateBinary();

  xTaskCreate(vRedLEDTask, "Red LED Task", 100, NULL, 1, NULL);
  xTaskCreate(vYellowLEDTask, "Yellow LED Task", 100, NULL, 1, NULL);
  xTaskCreate(vBlueLEDTask, "Green LED Task", 100, NULL, 1, NULL);
}

void loop() {}

void vRedLEDTask(void *pvParameters)
{
  pinMode(RED, OUTPUT);

  xSemaphoreGive(xBinarySemaphore);

  while (true)
  {
    xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
    Serial.println("This is RED task!");
    xSemaphoreGive(xBinarySemaphore);
    vTaskDelay(1);
  }
}

void vYellowLEDTask(void *pvParameters)
{
  pinMode(YELLOW, OUTPUT);
  while (true)
  {
    xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
    Serial.println("This is YELLOW task!");
    xSemaphoreGive(xBinarySemaphore);
    vTaskDelay(1);
  }
}

void vBlueLEDTask(void *pvParameters)
{
  pinMode(BLUE, OUTPUT);

  while (true)
  {
    xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
    Serial.println("This is BLUE task!");
    xSemaphoreGive(xBinarySemaphore);
    vTaskDelay(1);
  }
}