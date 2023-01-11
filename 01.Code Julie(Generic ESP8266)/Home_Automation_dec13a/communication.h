//========= Communication =========//
void sendMessage(unsigned char address, float value)
{
    char buffer[11];
    int intpart = (int)(value * 100);

    //** Fill Buffer **//
    //** Address char 0-1 **//
    if (address < 10)
    {
        buffer[0] = '0';
        buffer[1] = address + '0';
    }
    else
    {
        buffer[0] = (int)(address / 10) + '0';
        buffer[1] = address % 10 + '0';
    }

    if (isnan(value))
    {
        //** Sign char 2 **//
        buffer[2] = '/';

        //** Number char 3-9**//
        for (int j = 3; j < 10; j++)
        {
            buffer[j] = '9';
        }
    }
    else
    {
        //** Sign char 2 **//
        if (value < 0)
        {
            buffer[2] = '-';
            intpart = intpart * (-1);
        }
        else
        {
            buffer[2] = '+';
        }

        //** Number char 3-9**//
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
    }

    //** End **//
    buffer[10] = '\n';

    //** Send value **//
    for (int i = 0; i <= 10; i++)
    {
        Serial.write(buffer[i]);
    }
}

void reciveMessage()
{
    char buffer[11];
    char value_recived;
    int address;
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

    address = (buffer[0] - '0') * 10 + buffer[1] - '0';
    sign = buffer[2];
    if (sign == '/')
    {
        actual_values[address] = NAN;
        return;
    }

    for (int i = 3; i <= 9; i++)
    {
        if (i != 7)
        {
            value_float = value_float * 10 + buffer[i] - '0';
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
        return;
    }

    actual_values[address] = value_float;
    prev_values[address] = actual_values[address];
}
//========= ------------- =========//