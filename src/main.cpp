#include <Arduino.h>
#include "CCom.h"
#include "CAVRCom.h"
#include "CSlaveInstance.h"
#include "CMasterInstance.h"

auto com = CAVRCom(EControlMode::PROGRAMATIC);

//CMasterInstance masterTesst(com);
CSlaveInstance slaveTest(com);

unsigned long nextTime = 0;
void setup()
{
 // masterTest.OnSetup();
 Serial.begin(9600);
 Serial.println("started");
 slaveTest.OnSetup();
}

void loop()
{
  /*if (millis() >= nextTime)
  {
    //masterTest.SetWheelsTargetRpm(1525);
    nextTime = millis() + 500;
  }*/
  slaveTest.HandleLoop();
 // Serial.println("ok");
}
