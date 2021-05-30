#include <Arduino_FreeRTOS.h>
#include <timers.h>

#define RED 6
#define YELLOW 7
#define BLUE 8

#define BLUE_TIMER_PERIOD (pdMS_TO_TICKS(120))
#define RED_TIMER_PERIOD (pdMS_TO_TICKS(300))

TimerHandle_t xBlueTimer, xRedTimer;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);

  digitalWrite(RED, LOW);
  digitalWrite(BLUE, LOW);

  BaseType_t xBlueTimerStarted, xRedTimerStarted;

  xBlueTimer = xTimerCreate("Blue Timer", BLUE_TIMER_PERIOD, pdTRUE, 0, prvTimerCallback);
  xRedTimer = xTimerCreate("Red Timer", RED_TIMER_PERIOD, pdTRUE, 0, prvTimerCallback);

  if ((xBlueTimer != NULL) && (xRedTimer != NULL))
  {
    xBlueTimerStarted = xTimerStart(xBlueTimer, 0);
    xRedTimerStarted = xTimerStart(xRedTimer, 0);
  }

  while ((xBlueTimerStarted != pdPASS) && (xRedTimerStarted != pdPASS))
  {
  }
}

void loop() {}

uint32_t blueExecutionCount;

void prvTimerCallback(TimerHandle_t xTimer)
{
  TickType_t xTimeNow;

  xTimeNow = xTaskGetTickCount();

  if (xTimer == xBlueTimer)
  {
    blueExecutionCount++;

    Serial.print("Blue Timer Execution: ");
    Serial.println(xTimeNow);

    digitalWrite(BLUE, digitalRead(BLUE) ^ 1);

    if (blueExecutionCount == 100)
    {
      xTimerStop(xBlueTimer, 0);
    }
  }
  else
  {
    Serial.print("Red Timer Execution: ");
    Serial.print(xTimeNow);
    Serial.print("  RED LED State: ");
    Serial.println(digitalRead(RED));

    digitalWrite(RED, digitalRead(RED) ^ 1);
  }
}