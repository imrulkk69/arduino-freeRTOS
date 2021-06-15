#include <Arduino_FreeRTOS.h>
#include "queue.h"
#define    RED   6
#define    YELLOW    7
#define   BLUE      8



QueueHandle_t xIntegerQueue, xStringQueue;
int timer1_counter ;

void setup(){

  Serial.begin(9600);
  xTaskCreate(vIntegerGenerator, "Integer Generator", 100,NULL,1,NULL);
  xTaskCreate(vStringPrinter," String Printer", 100, NULL, 1,NULL);

 xIntegerQueue  =  xQueueCreate(5,sizeof(uint32_t ));
 xStringQueue  = xQueueCreate(5,sizeof(char *));

  InterruptInit();

}


void vIntegerGenerator(void *pvParameters)
{
  TickType_t xLastExecutionTime;
  const TickType_t xDelay200ms = pdMS_TO_TICKS(200);
  uint32_t vlaueToSend = 0;
  
  xLastExecutionTime  = xTaskGetTickCount();

  while(1)
  {
    vTaskDelayUntil(&xLastExecutionTime,xDelay200ms);
    for(int i=0;i<5;i++)
    {
      xQueueSendToBack(xIntegerQueue,&vlaueToSend,0);
      vlaueToSend++;
    }
  }
  
}

void vStringPrinter(void *pvParameters)
{
  char *pcString;
  while(1)
  {
    xQueueReceive(xStringQueue,&pcString,portMAX_DELAY);
    Serial.println(pcString);
  }
}


ISR(TIMER1_OVF_vect)
{
  TCNT1 = timer1_counter;
  uint32_t receivedNumber;
  static const char *pcStrings[]=
  {
    "Hello\r\n",
    "Hi\r\n",
    "I\r\n",
    "am\r\n",
    "here\r\n",
    
  };
  xQueueReceiveFromISR(xIntegerQueue,&receivedNumber,pdFALSE);
  receivedNumber &=0x03;
  xQueueSendToBackFromISR(xStringQueue,&pcStrings[receivedNumber],pdFALSE);
  
}

void loop(){}


void InterruptInit()
{
  noInterrupts();
  TCCR1A =0;
  TCCR1B =0;

  timer1_counter = 34286;

  TCNT1 = timer1_counter;
  TCCR1B |=(1<<CS12);
  TIMSK1 |= (1 << TOIE1);
  interrupts();

  
}

