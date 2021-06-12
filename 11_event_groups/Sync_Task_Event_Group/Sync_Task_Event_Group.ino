#include <Arduino_FreeRTOS.h>
#include <event_groups.h>

// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       Sync_Task_Event_Group.ino
    Created:	06/10/2021 1:36:48 PM
    Author:     DESKTOP-OI1RMCG\IMRUL
*/

// Define User Types below here or use a .h file
//
#define RED 6
#define YELLOW 7
#define BLUE 8

#define TASKA_BIT (1UL<<0UL)
#define TASKB_BIT (1UL<<1UL)
#define TASKC_BIT (1UL<<2UL)

// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//

EventGroupHandle_t xEventGroup;

// The setup() function runs once each time the micro-controller starts
void setup()
{
	pinMode(RED, OUTPUT);
	pinMode(YELLOW, OUTPUT);
	pinMode(BLUE, OUTPUT);
	
	xEventGroup = xEventGroupCreate();
	
	xTaskCreate(vTaskA, "Task A", 100, NULL, 1, NULL);
	xTaskCreate(vTaskB, "Task B", 100, NULL, 1, NULL);
	xTaskCreate(vTaskC, "Task C", 100, NULL, 1, NULL);
	
	
}

// Add the main program code into the continuous loop() function
void loop(){}

void vTaskA(void *pvParameters)
{
	while(true)
	{
		
	}	
}

void vTaskB(void *pvParameters)
{
	while(true)
	{
		
	}
}

void vTaskC(void *pvParameters)
{
	while(true)
	{
		
	}
}