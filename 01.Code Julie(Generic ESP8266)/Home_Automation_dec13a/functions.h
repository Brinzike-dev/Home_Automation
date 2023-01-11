//========= Functions =========//
void updateValues()
{
    humidity_inside = actual_values[ADR_HUMIDITY_AIR_ROOM];
    temp_inside = actual_values[ADR_TEMP_AIR_ROOM];
    status_heater = (bool)actual_values[ADR_STATUS_HEATER];
    temp_outside = actual_values[ADR_TEMP_AIR_OUTSIDE];
}
//========= --------- ==========//