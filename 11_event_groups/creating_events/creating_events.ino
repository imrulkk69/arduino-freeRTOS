#include <Arduino_FreeRTOS.h>
#include <event_groups.h>

#define RED 6
#define YELLOW 7
#define BLUE 8

#define TASK1_BIT (1UL << 0UL)
#define TASK2_BIT (1UL << 1UL)

EventGroupHandle_t xEventGroup;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);

  xEventGroup = xEventGroupCreate();

  xTaskCreate(vEventBitSettingTask, "Bit Setting Task", 100, NULL, 1, NULL);
  xTaskCreate(vEventBitReadingTask, "Bit Reading Task", 100, NULL, 1, NULL);
}

void loop() {}

void vEventBitSettingTask(void *pvParameters)
{
  const TickType_t xDelay500ms = pdMS_TO_TICKS(500);
  while (true)
  {
    xEventGroupSetBits(xEventGroup, TASK1_BIT);
    vTaskDelay(xDelay500ms);
    xEventGroupSetBits(xEventGroup, TASK2_BIT);
  }
}

void vEventBitReadingTask(void *pvParameters)
{
  const EventBits_t xBitsToWaitFor = (TASK1_BIT | TASK2_BIT);
  EventBits_t xEventGroupValue;

  while (true)
  {
    xEventGroupValue = xEventGroupWaitBits(xEventGroup, xBitsToWaitFor, pdTRUE, pdTRUE, portMAX_DELAY);

    if ((xEventGroupValue & TASK1_BIT) != 0)
    {
      digitalWrite(RED, digitalRead(RED) ^ 1);
    }

    if ((xEventGroupValue & TASK2_BIT) != 0)
    {
      digitalWrite(BLUE, digitalRead(BLUE) ^ 1);
    }
  }
}
