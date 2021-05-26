#include <Arduino_FreeRTOS.h>
#include <queue.h>

#define RED       6
#define YELLOW    7
#define BLUE      8

typedef int TaskProfiler;

TaskProfiler SenderTaskProfiler, ReceiverTaskProfiler;

typedef enum {
  eSender1,
  eSender2
} DataSource_t;

typedef struct
{
  uint8_t ucValue;
  DataSource_t eDataSource;
} Data_t;

static const Data_t xStructToSend[2] = {
  {100, eSender1},
  {50, eSender2}
};

QueueHandle_t xQueue;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(BLUE, OUTPUT);

  xQueue = xQueueCreate(3, sizeof(Data_t));

  xTaskCreate(vSenderTask, "Sender Task 1", 100, (void *) &(xStructToSend[0]), 2, NULL);
  xTaskCreate(vSenderTask, "Sender Task 2", 100, (void *) &(xStructToSend[1]), 2, NULL);
  xTaskCreate(vReceiverTask, "Reciver Task", 100, NULL, 2, NULL);
}

void loop() {}

void vSenderTask(void *pvParameters)
{
  BaseType_t xStatus;
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);

  while(1)
  {
    xStatus = xQueueSend(xQueue, pvParameters, xTicksToWait);
    if(xStatus != pdPASS)
    {
      Serial.println("Could not send to the Queue!");
    }
  }
}

void vReceiverTask(void *pvParameters)
{
  BaseType_t xStatus;
  Data_t xReceivedStructure;
  //const TickType_t xTicksToWait = pdMS_TO_TICKS(100);

  while(1)
  {
    xStatus = xQueueReceive(xQueue, &xReceivedStructure, 0);
           
    if(xStatus == pdPASS)
    {
      if(xReceivedStructure.eDataSource == eSender1)
      {
        //Serial.print("This is From Sender 1: ");
        //Serial.println(xReceivedStructure.ucValue);
      }
      else if(xReceivedStructure.eDataSource == eSender2)
      {
        Serial.print("This is From Sender 2:");
        Serial.println(xReceivedStructure.ucValue);
      }
    }
    else
    {
      Serial.println("Could not receviced data from queue.");
    }
  }
}
