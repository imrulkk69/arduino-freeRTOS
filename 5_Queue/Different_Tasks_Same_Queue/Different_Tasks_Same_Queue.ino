#include <Arduino_FreeRTOS.h>
#include <queue.h>


#define RED       6
#define YELLOW    7
#define BLUE      8

typedef int TaskProfiler;

TaskProfiler SenderTaskProfiler, ReceiverTaskProfiler;

QueueHandle_t yearQueue;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(BLUE, OUTPUT);

  yearQueue = xQueueCreate(5, sizeof(uint32_t));

  xTaskCreate(vSenderTask, "Sender Task 1", 100, (void *) 1999, 1, NULL);
  xTaskCreate(vSenderTask, "Sender Task 2", 100, (void *) 2021, 1, NULL);
  xTaskCreate(vReceiverTask, "Reciver Task", 100, NULL, 2, NULL);
}

void loop() {}

void vSenderTask(void *pvParameters)
{
  BaseType_t qStatus;
  uint32_t valueToSend;
  valueToSend = (uint32_t) pvParameters;

  while(1)
  {
    qStatus = xQueueSend(yearQueue, &valueToSend, 0);
    if(qStatus != pdPASS)
    {
      Serial.println("Could not sent to the queue.");
    }
    
    digitalWrite(RED, HIGH);  

    //vTaskDelay(500 / portTICK_PERIOD_MS);  
    for(int i =0; i<30000; i++){}
  }
}

void vReceiverTask(void *pvParameters)
{
  BaseType_t qStatus;
  uint32_t valueReceived;
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);

  while(1)
  {
    qStatus = xQueueReceive(yearQueue, &valueReceived, xTicksToWait);

    if(qStatus == pdPASS)
    {
      Serial.print("Data Received: ");
      Serial.println(valueReceived);
    }
    else 
    {
      Serial.println("Data Received Error....");
    }

    digitalWrite(RED, LOW);

    //vTaskDelay(500 / portTICK_PERIOD_MS);  
    for(int i =0; i<30000; i++){}
  }
}