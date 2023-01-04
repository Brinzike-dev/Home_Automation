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
#define NUMBER_OF_ADDRESSES 16
#define LAST_ADRESS_TO_SENT 13

//** Adress of datas **//
//$$$$$3
// #define ADR_SET_TEMP_HEATER 0
// #define ADR_PREV_AIR_TEMP_ROOM 1
// #define ADR_ACT_AIR_TEMP_ROOM 2
// #define ADR_PREV_AIR_HUMIDITY_ROOM 3
// #define ADR_ACT_AIR_HUMIDITY_ROOM 4
// #define ADR_PREV_STATUS_HEATER 5
// #define ADR_ACT_STATUS_HEATER 6
// #define ADR_PREV_AIR_TEMP_OUTSIDE 7
// #define ADR_ACT_AIR_TEMP_OUTSIDE 8
// #define ADR_PREV_AIR_HUMIDITY_OUTSIDE 9
// #define ADR_ACT_AIR_HUMIDITY_OUTSIDE 10

// //$$$$$1
// #define ADR_PREV_SOIL_HUM_COL_1 11
// #define ADR_ACT_SOIL_HUM_COL_1 12
// //$$$$$1

// //$$$$$2
// #define ADR_PUMP_COL_1 14
// //$$$$$2

//** Addresses for variables that are sent **//
// Even addresses are used for previous values
#define ADR_TEMP_AIR_ROOM 1
#define ADR_HUMIDITY_AIR_ROOM 3
#define ADR_TEMP_AIR_OUTSIDE 5
#define ADR_HUMIDITY_AIR_OUTSIDE 7
#define ADR_STATUS_HEATER 9
#define ADR_SOIL_HUMIDITY_COL_1 11
#define ADR_COMMAND_PUMP_COL_1 13

//** Addresses for variables that are recived **//
#define ADR_SET_TEMP_HEATER (NUMBER_OF_ADDRESSES - 1)
#define ADR_AUTOWATERING (NUMBER_OF_ADDRESSES - 2)
//$$$$$3

float datas[NUMBER_OF_ADDRESSES];

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