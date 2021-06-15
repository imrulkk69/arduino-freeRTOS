// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       Send_Recv_Queue_in_ISR.ino
    Created:	06/15/2021 12:19:58 PM
    Author:     DESKTOP-OI1RMCG\IMRUL
*/

// Define User Types below here or use a .h file
//
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <queue.h>

// Define Function Prototypes that use User Types below here or use a .h file
//
#define RED		6
#define BLUE	7
#define YELLOW	8

// Define Functions below here or use other .ino or cpp files
//
uint8_t timer1_counter;
static const char *pcStrings[] = {
	"Hello\r\n",
	"Hi\r\n",
	"I\r\n",
	"am\r\n",
	"here\r\n"
};

QueueHandle_t xIntegerQueue, xStringQueue;

// The setup() function runs once each time the micro-controller starts
void setup()
{
	Serial.begin(9600);
	pinMode(RED, OUTPUT);
	pinMode(BLUE, OUTPUT);
	pinMode(YELLOW, OUTPUT);
	
	xIntegerQueue  =  xQueueCreate(5,sizeof(uint32_t ));
	xStringQueue  = xQueueCreate(5,sizeof(char *));
	
	xTaskCreate(vIntegerGenerator, "Integer Generator", 100, NULL, 1, NULL);
	xTaskCreate(vStringPrinter, "String printer", 100, NULL, 1, NULL);
			 
	Serial.println("System Started....");
	 
	InterruptInit();		
}

// Add the main program code into the continuous loop() function
void loop(){}
	
ISR(TIMER1_OVF_vect)
{
	TCNT1 = timer1_counter;
	uint32_t receivedNumber;
		
	xQueueReceiveFromISR(xIntegerQueue, &receivedNumber, pdFALSE);
	receivedNumber &=0x03; //Trimming 	
	xQueueSendToBackFromISR(xStringQueue, &pcStrings[receivedNumber], pdFALSE);	
}	

void InterruptInit()
{
	noInterrupts();
		TCCR1A = 0;
		TCCR1B = 0;
		
		timer1_counter = 34286;
		
		TCNT1 = timer1_counter;
		TCCR1B |= (1 << CS12);
		TIMSK1 |= (1 << TOIE1);
						 
	interrupts();
}

void vIntegerGenerator(void *pvParamerters)
{
	TickType_t xLastExecutionTime;
	const TickType_t xDelay200ms = pdMS_TO_TICKS(200);
	uint32_t valueToSend = 0;
	xLastExecutionTime = xTaskGetTickCount();
	
	while(true)
	{
		xTaskDelayUntil(&xLastExecutionTime, xDelay200ms);
		for(int i = 0; i < 5; i++)
		{							
			xQueueSendToBack(xIntegerQueue, &valueToSend, 0);	
			valueToSend++;	
		}
	}
}

void vStringPrinter(void *pvParamerters)
{
	char* pcString;
	
	while(true)
	{
		xQueueReceive(xStringQueue, &pcString, portMAX_DELAY);
		Serial.print(pcString);
	}	
}

