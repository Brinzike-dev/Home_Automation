//========= Functions =========//
void readSensors()
{
    //----- DHT ROOM -----//
    datas[ADR_TEMP_AIR_ROOM] = dht_room.readTemperature();
    datas[ADR_HUMIDITY_AIR_ROOM] = dht_room.readHumidity();

    //----- Check Error -----//
    if (isnan(datas[ADR_TEMP_AIR_ROOM]) || isnan(datas[ADR_HUMIDITY_AIR_ROOM]))
    {
        error_read_dht_room = true;
    }
    else
    {
        error_read_dht_room = false;
    }

    //----- DHT OUTSIDE -----//
    datas[ADR_TEMP_AIR_OUTSIDE] = dht_outside.readTemperature();
    datas[ADR_HUMIDITY_AIR_OUTSIDE] = dht_outside.readHumidity();

    //----- Check Error -----//
    if (isnan(datas[ADR_TEMP_AIR_OUTSIDE]) || isnan(datas[ADR_HUMIDITY_AIR_OUTSIDE]))
    {
        error_read_dht_outside = true;
    }
    else
    {
        error_read_dht_outside = false;
    }

    //$$$$$1
    int average_val_soil_hum_1 = 0;
    for (int i = 0; i < NUMBER_OF_MEASUREMENTS; i++)
    {
        average_val_soil_hum_1 += int(((MAX_VAL_SOIL_HUM - analogRead(SOIL_HUM_COL_1_PIN)) * 100) / DIFERENCE);
// TODO:::::: Sa dispara delay-ul asta. Incetineste rularea
        delay(10);
    }

    if (average_val_soil_hum_1 <= 0 || average_val_soil_hum_1 > 100)
    {
        error_read_soil_hum_1 = true;
        datas[ADR_SOIL_HUMIDITY_COL_1] = NAN;
    }
    else
    {
        error_read_soil_hum_1 = false;
        datas[ADR_SOIL_HUMIDITY_COL_1] = average_val_soil_hum_1 / NUMBER_OF_MEASUREMENTS; // Give value from 0 and 100
    }
    //$$$$$1
}

void heating()
{
    if (error_read_dht_room)
    {
        datas[ADR_STATUS_HEATER] = 0;
        digitalWrite(RELAY_HEATING_PIN, HIGH);
        return;
    }

    if (datas[ADR_TEMP_AIR_ROOM] < datas[ADR_SET_TEMP_HEATER] - 0.5)
    {
        datas[ADR_STATUS_HEATER] = 1;
    }

    if (datas[ADR_TEMP_AIR_ROOM] > datas[ADR_SET_TEMP_HEATER])
    {
        datas[ADR_STATUS_HEATER] = 0;
    }

    (datas[ADR_STATUS_HEATER]) ? (digitalWrite(RELAY_HEATING_PIN, LOW)) : (digitalWrite(RELAY_HEATING_PIN, HIGH));
}

//$$$$$2
void watering()
{
    if (datas[ADR_AUTOWATERING])
    {
        // Check if soil humidity sensor work ok
        if (error_read_soil_hum_1)
        {
            datas[ADR_COMMAND_PUMP_COL_1] = 0;
        }
        else
        {
            if (datas[ADR_SOIL_HUMIDITY_COL_1] < VALUE_START_WATERING)
            {
                datas[ADR_COMMAND_PUMP_COL_1] = 1;
            }

            if (datas[ADR_SOIL_HUMIDITY_COL_1] > VALUE_STOP_WATERING)
            {
                datas[ADR_COMMAND_PUMP_COL_1] = 0;
            }
        }
    }

//TODO::::: POSIBLE REVERSE HIGH WITH LOW
    (datas[ADR_COMMAND_PUMP_COL_1])?(digitalWrite(PUMP_COL_1_PIN, HIGH)):(digitalWrite(PUMP_COL_1_PIN, LOW););
}
//$$$$$2

void monitoring()
{
    if (STATUS_MONITORING)
    {
        if (error_read_dht_room)
        {
            Serial.println("-----> Error reading temp and hum");
        }
        else
        {
            Serial.print("-----> Humidity: ");
            Serial.print(datas[ADR_HUMIDITY_AIR_ROOM]);
            Serial.print("%  Temperature: ");
            Serial.print(datas[ADR_TEMP_AIR_ROOM]);
            Serial.println("°C ");

            Serial.print("-----> Value of prev temp room : ");
            Serial.println(datas[ADR_TEMP_AIR_ROOM - 1]);
        }

        Serial.print("-----> Heating status: ");
        Serial.println(datas[ADR_STATUS_HEATER]);
    }
}

//========= --------- ==========//