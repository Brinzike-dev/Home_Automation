//========== Includes ==========//
//** Arduino IoT **//
#include "arduino_secrets.h"
#include "thingProperties.h"

//** Include librarys **//

//** Include Settings **//

//** Include Functions **//
#include "setup.h"
#include "functions.h"
#include "communication.h"
//========== -------- ==========//

void setup()
{
  // Initialize serial and wait for port to open:
  Serial.begin(115200);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop()
{
  ArduinoCloud.update();
  reciveMessage();
  updateValues();

  delay(1);
}

void onTempSetChange()
{
  sendMessage(ADR_SET_TEMP_HEATER, temp_set);
}