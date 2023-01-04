//========== Declare From Settings Pins ==========//
#define DHT_PIN_ROOM SET_DHT_PIN_ROOM
#define RELAY_HEATING_PIN SET_RELAY_HEATING_PIN
#define DHT_PIN_OUTSIDE SET_DHT_PIN_OUTSIDE

//$$$$$1
#define SOIL_HUM_COL_1_PIN SET_SOIL_HUM_COL_1_PIN
//$$$$$1

//$$$$$2
#define PUMP_COL_1_PIN SET_PUMP_COL_1_PIN
//$$$$$2
//========== -------- ==========//

//========== Library Setup ==========//
//----- DHT 22 -----//
#define DHTTYPE_ROOM DHT22                         // DHT 22  (AM2302)
DHT dht_room(DHT_PIN_ROOM, DHTTYPE_ROOM);          //// Initialize DHT sensor for normal 16mhz Arduino
#define DHTTYPE_OUTSIDE DHT22                      // DHT 22  (AM2302)
DHT dht_outside(DHT_PIN_OUTSIDE, DHTTYPE_OUTSIDE); //// Initialize DHT sensor for normal 16mhz Arduino
//========== ------------- ==========//

//========== Declaration ==========//
#define STATUS_MONITORING 0

#define INVALID_VALUE B1111111
#define INVALID_FLOAT -100000

//!!!!!!!!!!!!!!! Update number of value !!!!!!!!!!!!!!!//
#define NUMBER_OF_ADDRESSES 9

//** Adress of datas **//
#define ADR_TEMP_AIR_ROOM 0
#define ADR_HUMIDITY_AIR_ROOM 1
#define ADR_TEMP_AIR_OUTSIDE 2
#define ADR_HUMIDITY_AIR_OUTSIDE 3
#define ADR_STATUS_HEATER 4
#define ADR_SOIL_HUMIDITY_COL_1 5
#define ADR_COMMAND_PUMP_COL_1 6
#define ADR_SET_TEMP_HEATER 7
#define ADR_AUTOWATERING 8

float actual_values[NUMBER_OF_ADDRESSES];
float prev_values[NUMBER_OF_ADDRESSES];

//$$$$$1
//** Soil Humidity **//
#define MAX_VAL_SOIL_HUM 800                            // Is 0% Humidity
#define MIN_VAL_SOIL_HUM 400                            // Is 100% Humidity
#define DIFERENCE (MAX_VAL_SOIL_HUM - MIN_VAL_SOIL_HUM) // Diference
#define NUMBER_OF_MEASUREMENTS 10
//$$$$$1

//$$$$$2
//** Watering **//
#define VALUE_START_WATERING 50
#define VALUE_STOP_WATERING 80

//$$$$$3
// bool autowatering = false;
// bool watering_pump = false;
//$$$$$3

//$$$$$2

//========== --------- ==========//

//========== Errors ==========//
bool error_read_dht_room = true;
bool error_read_dht_outside = true;

//$$$$$1
bool error_read_soil_hum_1 = true;
//$$$$$1

//========== ------ ==========//