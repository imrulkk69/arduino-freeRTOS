#include <Arduino_FreeRTOS.h>
#include <timers.h>

#define ONE_SHOT_TIMER_PERIOD (pdMS_TO_TICKS(500))
#define AUTO_RELOAD_TIMER_PERIOD (pdMS_TO_TICKS(300))

TimerHandle_t xTimer1, xTimer2;
BaseType_t xTimer1_Started, xTimer2_Started;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  xTimer1 = xTimerCreate(
      "One Shot",
      ONE_SHOT_TIMER_PERIOD,
      pdFALSE,
      0,
      prvOneShotTimerCallback);

  xTimer2 = xTimerCreate(
      "Auto Reload",
      AUTO_RELOAD_TIMER_PERIOD,
      pdTRUE,
      0,
      prvAutoReloadTimerCallback);

  /* if (xTimer1 == NULL)
    Serial.println("xTimer1 is NULL");
  if (xTimer2 == NULL)
    Serial.println("xTimer2 is NULL"); */

  if ((xTimer1 != NULL) && (xTimer2 != NULL))
  {
    xTimer1_Started = xTimerStart(xTimer1, 0);
    xTimer2_Started = xTimerStart(xTimer2, 0);
  }

  while ((xTimer1_Started != pdPASS) && (xTimer2_Started != pdPASS))
  {
  }
}

void loop() {}

void prvOneShotTimerCallback(TimerHandle_t xTimer)
{
  static TickType_t xTimeNow;
  xTimeNow = xTaskGetTickCount();

  Serial.print("One Shot timer callback execution: ");
  Serial.println(xTimeNow);
}

void prvAutoReloadTimerCallback(TimerHandle_t xTimer)
{
  static TickType_t xTimeNow;
  xTimeNow = xTaskGetTickCount();

  Serial.print("Auto Reload timer callback execution: ");
  Serial.println(xTimeNow);
}