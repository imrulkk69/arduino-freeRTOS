#include <Arduino_FreeRTOS.h>
#include <queue.h>

#define RED 6
#define YELLOW 7
#define BLUE 8

QueueHandle_t xQueue1;
QueueHandle_t xQueue2;

QueueSetHandle_t xQueueSet;

void setup()
{
  Serial.begin(9600);

  pinMode(BLUE, OUTPUT);

  xQueue1 = xQueueCreate(1, sizeof(char *));
  xQueue2 = xQueueCreate(1, sizeof(char *));

  xQueueSet = xQueueCreateSet(1 * 2);

  xQueueAddToSet(xQueue1, xQueueSet);
  xQueueAddToSet(xQueue2, xQueueSet);

  //Task Creation
  xTaskCreate(vSenderTask1, "Sender Task 1", 100, NULL, 1, NULL);
  xTaskCreate(vSenderTask2, "Sender Task 2", 100, NULL, 1, NULL);

  xTaskCreate(vReceiverTask, "Reciver Task", 100, NULL, 1, NULL);
}

void loop() {}

void vSenderTask1(void *pvParameters)
{
  BaseType_t qStatus;
  const TickType_t xBlockTime = pdMS_TO_TICKS(100);
  const char *const messageToSend = "Message from Sender 1";

  while (1)
  {
    vTaskDelay(xBlockTime);
    qStatus = xQueueSend(xQueue1, &messageToSend, 0);

    if (qStatus == pdPASS)
    {
      digitalWrite(BLUE, HIGH);
    }
  }
}

void vSenderTask2(void *pvParameters)
{
  BaseType_t qStatus;
  const TickType_t xBlockTime = pdMS_TO_TICKS(200);
  const char *const messageToSend = "Hello from sender 2";

  while (1)
  {
    vTaskDelay(xBlockTime);
    qStatus = xQueueSend(xQueue1, &messageToSend, 0);

    if (qStatus == pdPASS)
    {
      digitalWrite(BLUE, HIGH);
    }
  }
}

void vReceiverTask(void *pvParameters)
{
  QueueHandle_t xQueueThatContainsData;
  char *pcReceivingString;

  while (1)
  {
    BaseType_t qStatus;
    xQueueThatContainsData = (QueueHandle_t)xQueueSelectFromSet(xQueueSet, portMAX_DELAY);
    qStatus = xQueueReceive(xQueueThatContainsData, &pcReceivingString, 0);

    if (qStatus == pdPASS)
    {
      digitalWrite(BLUE, LOW);
    }

    Serial.println(pcReceivingString);
  }
}