#include <Arduino.h>
#include <CCom.h>
#include <Frames/Frames.h>
#include "CSlave.h"
#include <CAVRCom.h>

auto com = CAVRCom(EControlMode::PROGRAMATIC);

CSlave slave(com);

void setup() {
  // put your setup code here, to run once:
  slave.OnSetup();;
  Serial.begin(9600);
}

void loop() {
  slave.HandleLoop();
}
