#include <Arduino_FreeRTOS.h>
#include <semphr.h>

SemaphoreHandle_t xMutex;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  xMutex = xSemaphoreCreateMutex();

  xTaskCreate(vOutputTask, "Printer Task 1", 100, "Task 1 ############################# Task1 \r\n", 1, NULL);
  xTaskCreate(vOutputTask, "Printer Task 2", 100, "Task 2 ----------------------------- Task2 \r\n", 2, NULL);
}

void loop() {}

void vOutputTask(void *pvParameters)
{
  char *pcStringToPrint;
  pcStringToPrint = (char *)pvParameters;

  while (true)
  {
    printer(pcStringToPrint);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void printer(const char *pcString)
{
  xSemaphoreTake(xMutex, portMAX_DELAY);
  Serial.println(pcString);
  xSemaphoreGive(xMutex);
}
