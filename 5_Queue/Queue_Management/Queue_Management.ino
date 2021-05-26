#include <Arduino_FreeRTOS.h>
#include <queue.h>

QueueHandle_t yearQueue;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  yearQueue = xQueueCreate(5, sizeof(uint32_t));

  xTaskCreate(vSenderTask, "Sender Task", 100, NULL, 1, NULL);
  xTaskCreate(vReceiverTask, "ReceiverTask", 100, NULL, 1, NULL);

}

void loop() {
  // put your main code here, to run repeatedly:
}

void vSenderTask(void *pvParameters)
{
  BaseType_t qStatus;
  uint32_t valueToSend = 1999;
  while(1)
  {
    qStatus = xQueueSend(yearQueue, &valueToSend, 0);
  }
}

void vReceiverTask(void *pvParameters)
{
  BaseType_t qStatus;
  uint32_t valueToReceive;
  const TickType_t xTickToWait = pdMS_TO_TICKS(500);

  while(1)
  {
    qStatus = xQueueReceive(yearQueue, &valueToReceive, xTickToWait);

    if(qStatus)
    {
      Serial.print("Receive Value:");
      Serial.println(valueToReceive);
    }
  }

}
