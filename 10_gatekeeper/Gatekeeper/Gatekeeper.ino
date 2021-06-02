#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <queue.h>

static const char *pcStringToPrint[] = {
    "Task1 ######################### Task1 \r\n",
    "Task2 ------------------------- Task2 \r\n",
    "TickHook &&&&&&&&&&&&&&&&&&&&&& TickHook \r\n"};

QueueHandle_t xPrintQueue;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  xPrintQueue = xQueueCreate(5, sizeof(char *));

  xTaskCreate(vOutputTask1, "Printer 1", 100, NULL, 1, NULL);
  xTaskCreate(vOutputTask2, "Printer 2", 100, NULL, 1, NULL);

  xTaskCreate(vGateKeeperTask, "Gatekeeper", 100, NULL, 1, NULL);
}

void loop() {}

void vOutputTask1(void *pvParameters)
{
  uint8_t indexToString = (uint8_t)pvParameters;
  char *taskMessage;
  while (true)
  {
    strcpy(taskMessage, "HELLO WORLD");
    xQueueSend(xPrintQueue, &taskMessage, 0);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void vOutputTask2(void *pvParameters)
{
  uint8_t indexToString = (uint8_t)pvParameters;
  char *taskMessage;
  while (true)
  {
    strcpy(taskMessage, "IS Everything OK!");
    xQueueSend(xPrintQueue, &taskMessage, 0);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void vGateKeeperTask(void *pvParameters)
{
  char *pcMessageToPrint;
  BaseType_t isQueueReceived;
  while (true)
  {
    isQueueReceived = xQueueReceive(xPrintQueue, &pcMessageToPrint, portMAX_DELAY);
    if (isQueueReceived == pdPASS)
    {
      Serial.println(pcMessageToPrint);
    }
  }
}

/* void vApplicationTickHook(void)
{
  static uint8_t counter = 0;
  counter++;
  if(counter >= 200)
  {
    xQueueSendToFrontFromISR(xPrintQueue, pcStringToPrint[2], NULL);
    counter = 0;
  }
} */