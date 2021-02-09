#include <SoftwareSerial.h>

SoftwareSerial mySerial(11, 8); // RX, TX

#define Threshold_on  150
#define Threshold_off  50
#define T0 10
#define T1 9

byte tanks[2] = {0, 0};

void read_tank(int tank)
{
  for (int ch = 0; ch < 8; ch++)
  {
    int value = 0;
    for (int i = 0; i < 20; i++)
    {
      value += analogRead(ch);
    }
    if (value / 20 > Threshold_on)
    {
      bitWrite(tanks[tank], ch , 1);
    }
    else if (value / 20 < Threshold_off)
    {
      bitWrite(tanks[tank], ch , 0);
    }
  }
}
void setup() {
  mySerial.begin(300);
  pinMode(T0, OUTPUT);
  pinMode(T1, OUTPUT);

}

void loop() {
  digitalWrite(T0, HIGH);
  digitalWrite(T1, LOW);
  read_tank(0);
  digitalWrite(T1, HIGH);
  digitalWrite(T0, LOW);
  read_tank(1);
  mySerial.write(tanks, 2);

  delay(3000);

}
