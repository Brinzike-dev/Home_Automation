//========= Communication =========//
unsigned char codeFloatToChar(float val)
{
    unsigned char result = 0;

    //** Take negative value **//
    if (val < 0)
    {
        result = result | B10000000;
        val = (-1) * val;
    }

    //** Check if is in range -60...+60
    if (val <= 60)
    {
        result += (unsigned char)val << 1;
    }
    else
    {
        //** Invalide value **//
        return INVALID_VALUE;
    }

    //** Check half for degr **//
    if (val - (int)val < 0.5)
    {
        result++;
    }
    else
    {
        result = result & B11111110;
    }

    return result;
}

float codeCharToFloat(unsigned char val)
{
    float result = 0;
    //** Check for invalide value **//
    if (val == INVALID_VALUE)
    {
        //** Invalide value **//
        return INVALID_FLOAT;
    }

    //** Take Value **//
    result = (val & B01111111) >> 1;

    //** Check for half degr **//
    if (val & 1)
    {
        result += 0.5;
    }

    //** Take negative value **//
    if (val >> 7 == 1)
    {
        result = (-1) * result;
    }

    return result;
}

//$$$$$3
// void sendMessage()
// {
//     for (unsigned char i = 2; i < NUMBER_OF_ADDRESSES; i += 2)
//     {
//         if (isnan(datas[i]))
//         {
//             if (!isnan(datas[i - 1]))
//             {
//                 Serial.write(i);
//                 Serial.write(INVALID_VALUE);
//             }
//         }
//         else
//         {
//             if (datas[i] != datas[i - 1])
//             {
//                 Serial.write(i);
//                 // Particular case
//                 //$$$$$1
//                 // if (i == ADR_ACT_AIR_HUMIDITY_ROOM || 
//                 //     i == ADR_ACT_AIR_HUMIDITY_OUTSIDE ||
//                 //     i == ADR_ACT_STATUS_HEATER)
//                 // {
//                 //     Serial.write((unsigned char)datas[i]);
//                 // }
//                 // else
//                 // {
//                 //     Serial.write(codeFloatToChar(datas[i]));
//                 // }
//                 if (i == ADR_ACT_AIR_HUMIDITY_ROOM || 
//                     i == ADR_ACT_AIR_HUMIDITY_OUTSIDE ||
//                     i == ADR_ACT_STATUS_HEATER ||
//                     i == ADR_ACT_SOIL_HUM_COL_1)
//                 {
//                     Serial.write((unsigned char)datas[i]);
//                 }
//                 else
//                 {
//                     Serial.write(codeFloatToChar(datas[i]));
//                 }
//                 datas[i - 1] = datas[i]
//                 //$$$$$1
//             }
//         }
//         //$$$$$1
//         //datas[i - 1] = datas[i];
//         //$$$$$1
//     }
// }

// void reciveMessage()
// {
//     if (Serial.available())
//     {
//         int address = (int)Serial.read();

//         if (STATUS_MONITORING)
//         {
//             Serial.print("-----> Value of address recived : ");
//             Serial.println(address);
//         }

//         // Force to sync / filter invalid messages
//         if (address < 0 || address > NUMBER_OF_ADDRESSES)
//         {
//             return;
//         }

//         if (Serial.available())
//         {
//             unsigned char val = Serial.read();

//             if (STATUS_MONITORING)
//             {
//                 Serial.print("-----> Value recived : ");
//                 Serial.println(val, BIN);
//             }

//             if (val == INVALID_VALUE)
//             {
//                 datas[address] = NAN;
//             }
//             else
//             {
//                 //Particular Case
//                 //$$$$$1
//                 // if (address == ADR_ACT_AIR_HUMIDITY_ROOM ||
//                 //     address == ADR_ACT_AIR_HUMIDITY_OUTSIDE ||
//                 //     address == ADR_ACT_STATUS_HEATER)
//                 // {
//                 //     datas[address] = val;
//                 // }
//                 // else
//                 // {
//                 //     datas[address] = codeCharToFloat(val);
//                 // }
//                 if (address == ADR_ACT_AIR_HUMIDITY_ROOM ||
//                     address == ADR_ACT_AIR_HUMIDITY_OUTSIDE ||
//                     address == ADR_ACT_STATUS_HEATER ||
//                     address == ADR_ACT_SOIL_HUM_COL_1)
//                 {
//                     datas[address] = val;
//                 }
//                 else
//                 {
//                     datas[address] = codeCharToFloat(val);
//                 }
//                 //$$$$$1
//             }
//         }
//     }
// }

void sendMessage()
{
    for (unsigned char i = 1; i <= LAST_ADRESS_TO_SENT; i += 2)
    {
        if (isnan(datas[i]))
        {
            if (!isnan(datas[i - 1]))
            {
                Serial.write(i);
                Serial.write(INVALID_VALUE);
            }
        }
        else
        {
            if (datas[i] != datas[i - 1])
            {
                Serial.write(i);
                // Particular case
                //$$$$$1
                // if (i == ADR_ACT_AIR_HUMIDITY_ROOM || 
                //     i == ADR_ACT_AIR_HUMIDITY_OUTSIDE ||
                //     i == ADR_ACT_STATUS_HEATER)
                // {
                //     Serial.write((unsigned char)datas[i]);
                // }
                // else
                // {
                //     Serial.write(codeFloatToChar(datas[i]));
                // }
                if (i == ADR_HUMIDITY_AIR_ROOM || 
                    i == ADR_HUMIDITY_AIR_OUTSIDE ||
                    i == ADR_STATUS_HEATER ||
                    i == ADR_SOIL_HUMIDITY_COL_1 ||
                    i == ADR_COMMAND_PUMP_COL_1)
                {
                    Serial.write((unsigned char)datas[i]);
                }
                else
                {
                    Serial.write(codeFloatToChar(datas[i]));
                }
                datas[i - 1] = datas[i]
                //$$$$$1
            }
        }
        //$$$$$1
        //datas[i - 1] = datas[i];
        //$$$$$1
    }
}

void reciveMessage()
{
    if (Serial.available())
    {
        int address = (int)Serial.read();

        if (STATUS_MONITORING)
        {
            Serial.print("-----> Value of address recived : ");
            Serial.println(address);
        }

        // Force to sync / filter invalid messages
        if (address < 0 || address > NUMBER_OF_ADDRESSES)
        {
            return;
        }

        if (Serial.available())
        {
            unsigned char val = Serial.read();

            if (STATUS_MONITORING)
            {
                Serial.print("-----> Value recived : ");
                Serial.println(val, BIN);
            }

            if (val == INVALID_VALUE)
            {
                datas[address] = NAN;
            }
            else
            {
                //Particular Case
                //$$$$$1
                // if (address == ADR_ACT_AIR_HUMIDITY_ROOM ||
                //     address == ADR_ACT_AIR_HUMIDITY_OUTSIDE ||
                //     address == ADR_ACT_STATUS_HEATER)
                // {
                //     datas[address] = val;
                // }
                // else
                // {
                //     datas[address] = codeCharToFloat(val);
                // }
                if (address == ADR_HUMIDITY_AIR_ROOM || 
                    address == ADR_HUMIDITY_AIR_OUTSIDE ||
                    address == ADR_STATUS_HEATER ||
                    address == ADR_SOIL_HUMIDITY_COL_1 ||
                    address == ADR_COMMAND_PUMP_COL_1)
                {
                    datas[address] = val;
                }
                else
                {
                    datas[address] = codeCharToFloat(val);
                }
                //$$$$$1
            }
        }
    }
}
//$$$$$3
//========= ------------- =========//