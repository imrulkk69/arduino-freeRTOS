#include <avr8-stub.h>
#include <app_api.h>


#define RED 6
#define YELLOW 7
#define BLUE 8

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  digitalWrite(BLUE, HIGH);
  delay(500);
  digitalWrite(BLUE, LOW);
  delay(500);
}
