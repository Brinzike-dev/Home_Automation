//*********************************************************//
//*                Home Atomation v0.2                    *//
//*   Ce cupride acest cod :                              *//
//* - Cominicare dintre cele doua controllere integrate   *//
//* prin port serial                                      *//
//*********************************************************//

//========== Includes ==========//
//** Include librarys **//
#include <DHT.h>
//** Include Settings **//
#include "settings.h"
//** Include Functions **//
#include "setup.h"
#include "communication.h"
#include "functions.h"

//========== -------- ==========//

//========== Setup ==========//
void setup()
{
  Serial.begin(115200);

  //** Begin Librarys **//
  dht_room.begin();
  dht_outside.begin();

  //** pinMode setup **//
  pinMode(RELAY_HEATING_PIN, OUTPUT);
  pinMode(SOIL_HUM_COL_1_PIN, INPUT);
  pinMode(PUMP_COL_1_PIN, OUTPUT);

  actual_values[ADR_SET_TEMP_HEATER] = 18;
  prev_values[ADR_SET_TEMP_HEATER] = 18;
}
//========== ------ ==========//

//========== Loop ==========//
void loop()
{
  readSensors();
  //*** Control Heater ***//
  heating();
  monitoring();
  checkAllValuesToSend();
  reciveMessage();
  delay(1);
}
