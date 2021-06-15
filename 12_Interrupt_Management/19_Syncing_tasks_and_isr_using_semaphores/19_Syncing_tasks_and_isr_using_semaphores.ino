#include <Arduino_FreeRTOS.h>
#include "semphr.h"

#define   RED    6
#define   YELLOW  7
#define   BLUE   8


SemaphoreHandle_t xBinarySemaphore;
int timer1_counter;

void setup()
{
  Serial.begin(9600);
  pinMode(RED,OUTPUT);
  pinMode(BLUE,OUTPUT);
  pinMode(YELLOW,OUTPUT);

  xBinarySemaphore = xSemaphoreCreateBinary();
  xTaskCreate(vHandlerTask, "Handler ",100,NULL,3,NULL);

  InterruptInit();
  
}

void vHandlerTask(void *pvParameters)
{
  while(1)
  {
   xSemaphoreTake(xBinarySemaphore,portMAX_DELAY); 
   digitalWrite(BLUE,digitalRead(BLUE)^1);
  }
}
void loop(){}

void InterruptInit(void)
{
  noInterrupts();
  TCCR1A =0;
  TCCR1B =0;
 timer1_counter = 34286;

 TCNT1  = timer1_counter;
 TCCR1B |= (1 << CS12); 
 TIMSK1 |= (1 << TOIE1);
 interrupts();
  
}

ISR(TIMER1_OVF_vect)
{

  TCNT1 =  timer1_counter;
 // xSemaphoreGiveFromISR(xBinarySemaphore,pdFALSE);
}

