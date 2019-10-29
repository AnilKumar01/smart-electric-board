#include <Arduino.h>
#include "SEB.h"
#include <WiFiManager.h>

void setup() {
  //initializeKeyboard();
  Serial.begin(9600);
  configureAllAppliences();
  setAllAppliancesToDefaultState();
}

void loop() {
  refresh();
}
