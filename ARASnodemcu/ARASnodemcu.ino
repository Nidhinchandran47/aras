
#define BLYNK_TEMPLATE_ID "TMPLQryJonCe"
#define BLYNK_DEVICE_NAME "led"
#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#include <SFE_BMP180.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>
#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG
#define soil A0
#define APP_DEBUG
//SFE_BMP180 pressure;
// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"
#include <DHT.h>

DHT dht2(2,DHT11); 
BLYNK_WRITE(V0)
{
  int data = param.asInt();
  digitalWrite(15,data);
}
BLYNK_WRITE(V1)
{
  int data1 = param.asInt();
  digitalWrite(14,data1);
}
BLYNK_WRITE(V2)
{
  int data2 = param.asInt();
  digitalWrite(16,data2);
}
void setup()
{
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(0,OUTPUT);
  pinMode(soil,INPUT);
  pinMode(15,OUTPUT);
  pinMode(14,OUTPUT);
  pinMode(16,OUTPUT);

  digitalWrite(5,LOW);
  digitalWrite(4,LOW);
  digitalWrite(0,LOW);
  digitalWrite(14,LOW);
  digitalWrite(15,LOW);
  digitalWrite(16,LOW);
  Serial.begin(115200);
  delay(100);

  BlynkEdgent.begin();
}

void loop() {
  double tm;
  double p;
 
  BlynkEdgent.run();
   int Svalue = analogRead(soil);
  Svalue = map(Svalue, 0, 1024, 0, 100);
  Svalue = (Svalue - 100) * -1;
  Blynk.virtualWrite(V5, Svalue);
  //Serial.println(Svalue);
  /*pressure.getTemperature(t);
  Serial.println(t);
  pressure.getPressure(p,t);
  Serial.println(p);*/
  tm = dht2.readTemperature();
  p = dht2.readHumidity();
  Blynk.virtualWrite(V3, p);
  Blynk.virtualWrite(V4, tm);
   Serial.println();
  if(tm>=32)
{
  digitalWrite(5,HIGH);
}
else
{
  digitalWrite(5,LOW);
}
 if(tm<=25)
{
  digitalWrite(4,HIGH);
}
else
{
  digitalWrite(4,LOW);
}
 if(Svalue<=50)
{
  digitalWrite(0,LOW);
}
else
{
  digitalWrite(0,HIGH);
}
}
