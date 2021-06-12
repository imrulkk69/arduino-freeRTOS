// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       Sync_Task_Event_Group.ino
    Created:	06/12/2021 12:48:48 PM
    Author:     DESKTOP-OI1RMCG\IMRUL
*/

// Define User Types below here or use a .h file
//

#include <Arduino_FreeRTOS.h>
#include <event_groups.h>


// Define Function Prototypes that use User Types below here or use a .h file
//

#define RED 6
#define YELLOW 7 
#define BLUE 8

#define TASKA_BIT (1UL << 0UL)
#define TASKB_BIT (1UL << 1UL)
#define TASKC_BIT (1UL << 2UL)

// Define Functions below here or use other .ino or cpp files
//

EventGroupHandle_t xEventGroup;
EventBits_t allSyncBits  = (TASKA_BIT | TASKB_BIT | TASKC_BIT);

// The setup() function runs once each time the micro-controller starts
void setup()
{
	pinMode(RED, OUTPUT);
	pinMode(YELLOW, OUTPUT);
	pinMode(BLUE, OUTPUT);
	
	xEventGroup = xEventGroupCreate();
	
	xTaskCreate(vTaskA, "TASK A", 100, NULL, 1, NULL);	
	xTaskCreate(vTaskB, "TASK B", 100, NULL, 1, NULL);	
	xTaskCreate(vTaskC, "TASK C", 100, NULL, 1, NULL);	
}

// Add the main program code into the continuous loop() function
void loop(){}

void vTaskA(void *pvParameters)
{
	EventBits_t uxReturn;
	
	while(true)
	{
		uxReturn = xEventGroupSync(xEventGroup, TASKA_BIT, allSyncBits, portMAX_DELAY);		
		if((uxReturn & allSyncBits) == allSyncBits)
		{
			digitalWrite(RED, digitalRead(RED) ^ 1);
			vTaskDelay(pdMS_TO_TICKS(200));
		}
	}
}

void vTaskB(void *pvParameters)
{
	EventBits_t uxReturn;
	
	while(true)
	{
		uxReturn = xEventGroupSync(xEventGroup, TASKB_BIT, allSyncBits, portMAX_DELAY);
		
		if((uxReturn & allSyncBits) == allSyncBits)
		{
			digitalWrite(YELLOW, digitalRead(YELLOW) ^ 1);
			vTaskDelay(pdMS_TO_TICKS(200));
		}
	}
}


void vTaskC(void *pvParameters)
{
	EventBits_t uxReturn;
	
	while(true)
	{
		uxReturn = xEventGroupSync(xEventGroup, TASKC_BIT, allSyncBits, portMAX_DELAY);
		
		if((uxReturn & allSyncBits) == allSyncBits)
		{
			digitalWrite(BLUE, digitalRead(BLUE) ^ 1);
			vTaskDelay(pdMS_TO_TICKS(200));
		}
	}
}

