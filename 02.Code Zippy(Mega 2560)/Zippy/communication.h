//========= Communication =========//
void sendMessage()
{
    for (unsigned char i = 0; i < NUMBER_OF_ADDRESSES; i++)
    {
        // Check if the value is valid
        if (isnan(actual_values[i]))
        {
            // If the previously sent value is still NAN
            if (!isnan(prev_values[i]))
            {
                // Send invalid value
                // TODO:::::: Send invalid value
                char buffer[11];
                if (i < 10)
                {
                    buffer[0] = '0';
                    buffer[1] = i + '0';
                }
                else
                {
                    buffer[0] = (int)(i / 10) + '0';
                    buffer[1] = i % 10 + '0';
                }
                buffer[2] = '/';
                for (int j = 3; j < 10; j++)
                {
                    buffer[j] = '9';
                }
                buffer[10] = '\n';

                //  Update prev value
                prev_values[i] = actual_values[i];

                //** Send value **//
                for (int k = 0; k < 11; k++)
                {
                    Serial.write(buffer[k]);
                }
            }
        }
        else
        {
            if (actual_values[i] != prev_values[i])
            {
                char buffer[11];
                // Extract integer part whith 2 digitis
                int intpart = (int)(actual_values[i] * 100);

                //** Fill buffer **//
                //** Adress **//
                if (i < 10)
                {
                    buffer[0] = '0';
                    buffer[1] = i + '0';
                }
                else
                {
                    buffer[0] = (int)(i / 10) + '0';
                    buffer[1] = i % 10 + '0';
                }

                //** Sign **//
                if (actual_values[i] < 0)
                {
                    buffer[2] = '-';
                    intpart = intpart * (-1);
                }
                else
                {
                    buffer[2] = '+';
                }

                //** Number **//
                for (int j = 9; j >= 3; j--)
                {
                    if (j == 7)
                    {
                        buffer[j] = '.';
                    }
                    else
                    {
                        buffer[j] = intpart % 10 + '0';
                        intpart = intpart / 10;
                    }
                }

                //** End **//
                buffer[10] = '\n';

                // Update prev value
                prev_values[i] = actual_values[i];

                //** Send value **//
                for (int k = 0; k < 11; k++)
                {
                    Serial.write(buffer[k]);
                }
            }
        }
    }
}

void reciveMessage()
{
    char buffer[11];
    char value_recived;
    int adress;
    char sign, end_message;
    float value_float = 0;

    for (int i = 0; i <= 10; i++)
    {
        if (Serial.available())
        {
            value_recived = Serial.read();
            buffer[i] = value_recived;
        }
    }

    adress = (buffer[0] - '0') * 10 + buffer[1] - '0';
    sign = buffer[2];
    if (sign == '/')
    {
       actual_values[adress] = NAN;
       return;
    }

    for (int i = 3; i <= 9; i++)
    {
        if (i != 7)
        {
            value_float = value_float * 10 + buffer[i] -'0';
        }
    }
    value_float = value_float / 100;

    if (sign == '-')
    {
        value_float = value_float * (-1);
    }

    end_message = buffer[10];

    //** Message corrupted **//
    if (end_message != '\n')
    {
        actual_values[adress] = NAN;
        return;
    }

    actual_values[adress] = value_float;
    prev_values[adress] = actual_values[adress];
}
//========= ------------- =========//