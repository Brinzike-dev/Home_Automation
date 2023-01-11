//========== Declaration ==========//
#define STATUS_MONITORING 0

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