//========= Functions =========//
void readSensors()
{
    //----- DHT ROOM -----//
    if (AVAILABLE_DHT_ROOM)
    {
        actual_values[ADR_TEMP_AIR_ROOM] = dht_room.readTemperature();
        actual_values[ADR_HUMIDITY_AIR_ROOM] = dht_room.readHumidity();

        //----- Check Error -----//
        if (isnan(actual_values[ADR_TEMP_AIR_ROOM]) || isnan(actual_values[ADR_HUMIDITY_AIR_ROOM]))
        {
            error_read_dht_room = true;
        }
        else
        {
            error_read_dht_room = false;
        }
    }

    //----- DHT OUTSIDE -----//
    if (AVAILABLE_DHT_OUTSIDE)
    {
        actual_values[ADR_TEMP_AIR_OUTSIDE] = dht_outside.readTemperature();
        actual_values[ADR_HUMIDITY_AIR_OUTSIDE] = dht_outside.readHumidity();

        //----- Check Error -----//
        if (isnan(actual_values[ADR_TEMP_AIR_OUTSIDE]) || isnan(actual_values[ADR_HUMIDITY_AIR_OUTSIDE]))
        {
            error_read_dht_outside = true;
        }
        else
        {
            error_read_dht_outside = false;
        }
    }

    //----- Soil Humidity Column 1 -----//
    if (AVAILABLE_SOIL_HUMIDITY_COL_1)
    {
        int average_val_soil_hum_1 = 0;
        int val_soil_hum_1 = 0;
        for (int i = 0; i < NUMBER_OF_MEASUREMENTS; i++)
        {
            average_val_soil_hum_1 += int(((MAX_VAL_SOIL_HUM - analogRead(SOIL_HUM_COL_1_PIN)) * 100) / DIFERENCE);

            // TODO:::::: Sa dispara delay-ul asta. Incetineste rularea
            delay(10);
        }
        val_soil_hum_1 = average_val_soil_hum_1 / NUMBER_OF_MEASUREMENTS;

        if (val_soil_hum_1 <= 0 || val_soil_hum_1 > 100)
        {
            error_read_soil_hum_1 = true;
            actual_values[ADR_SOIL_HUMIDITY_COL_1] = NAN;
        }
        else
        {
            error_read_soil_hum_1 = false;
            actual_values[ADR_SOIL_HUMIDITY_COL_1] = val_soil_hum_1; // Give value from 0 and 100
        }
    }
}

void heating()
{
    if (AVAILABLE_HEATING_ROOM)
    {
        if (error_read_dht_room)
        {
            actual_values[ADR_STATUS_HEATER] = 0;
        }
        else
        {
            if (actual_values[ADR_TEMP_AIR_ROOM] < actual_values[ADR_SET_TEMP_HEATER] - 0.5)
            {
                actual_values[ADR_STATUS_HEATER] = 1;
            }

            if (actual_values[ADR_TEMP_AIR_ROOM] > actual_values[ADR_SET_TEMP_HEATER])
            {
                actual_values[ADR_STATUS_HEATER] = 0;
            }
        }

        (actual_values[ADR_STATUS_HEATER]) ? (digitalWrite(RELAY_HEATING_PIN, LOW)) : (digitalWrite(RELAY_HEATING_PIN, HIGH));
    }
}

void watering()
{
    if (AVAILABLE_WATERING_COL_1)
    {
        if (actual_values[ADR_AUTOWATERING])
        {
            // Check if soil humidity sensor work ok
            if (error_read_soil_hum_1)
            {
                actual_values[ADR_COMMAND_PUMP_COL_1] = 0;
            }
            else
            {
                if (actual_values[ADR_SOIL_HUMIDITY_COL_1] < VALUE_START_WATERING)
                {
                    actual_values[ADR_COMMAND_PUMP_COL_1] = 1;
                }

                if (actual_values[ADR_SOIL_HUMIDITY_COL_1] > VALUE_STOP_WATERING)
                {
                    actual_values[ADR_COMMAND_PUMP_COL_1] = 0;
                }
            }
        }

        (actual_values[ADR_COMMAND_PUMP_COL_1]) ? (digitalWrite(PUMP_COL_1_PIN, LOW)) : (digitalWrite(PUMP_COL_1_PIN, HIGH));
    }
}

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
            Serial.print(actual_values[ADR_HUMIDITY_AIR_ROOM]);
            Serial.print("%  Temperature: ");
            Serial.print(actual_values[ADR_TEMP_AIR_ROOM]);
            Serial.println("°C ");

            Serial.print("-----> Value of prev temp room : ");
            Serial.println(prev_values[ADR_TEMP_AIR_ROOM]);
        }

        Serial.print("-----> Heating status: ");
        Serial.println(actual_values[ADR_STATUS_HEATER]);
    }
}

void checkAllValuesToSend()
{
    for (unsigned char i = 0; i < NUMBER_OF_ADDRESSES; i++)
    {
        if (isnan(actual_values[i]))
        {
            if (!isnan(prev_values[i]))
            {
                sendMessage(i, actual_values[i]);
                prev_values[i] = NAN;
            }
        }
        else if (actual_values[i] != prev_values[i])
        {
            sendMessage(i, actual_values[i]);
            prev_values[i] = actual_values[i];
        }
    }
}
//========= --------- ==========//