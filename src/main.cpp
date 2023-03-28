// Echo Trigger ertsllen T = Trigger Zeit<10µs output
// Echo = input
// Abstandsmessung mit Ultraschallgerät
#include <Arduino.h>
#define trigger 2
#define echo 3

bool lastEcho = LOW;
unsigned long zeit_1 = 0;
unsigned long zeit_2 = 0;
unsigned long wartePause = 500;
unsigned long letzteZeit = 0;
double Abstand;

void setup()
{
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
}

void loop()
{
  if (millis() - letzteZeit > wartePause)
  {
    digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger, LOW);
    letzteZeit = millis();
    Serial.println("trigger");
  }
  int echoWert = digitalRead(echo);

  if (echoWert == HIGH && lastEcho == LOW)
  {
    zeit_1 = micros();
    Serial.println("HiGH");
  }
  if (echoWert == LOW && lastEcho == HIGH)
  {
    zeit_2 = micros();
    // Serial.println(zeit_1);
    // Serial.println(zeit_2);
    Abstand = ((zeit_2 - zeit_1) * 0.0334) / 2;
    Serial.println("LOW");
    Serial.println(Abstand);
  }
  lastEcho=echoWert;
}