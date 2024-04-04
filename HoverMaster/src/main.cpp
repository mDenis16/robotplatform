#include <Arduino.h>
#include <CCom.h>
#include <CAVRCom.h>
#include <CMasterInstance.h>

auto com = CAVRCom(EControlMode::PROGRAMATIC);
CMasterInstance masterTest(com);

unsigned long nextTime = 0;
void setup()
{

  Serial.begin(9600);
  Serial.println("started");
  masterTest.OnSetup();
}

void loop()
{
  static int16_t val = 40;
  if (millis() >= nextTime && val <= 300)
  {
    masterTest.SetWheelsTargetRpm(val++);
    val += 10;
    nextTime = millis() + 200;
  }
  masterTest.HandleLoop();
}
