
/*******************************************************************************
* Copyright (C) 2017, 2017 Spiio, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Jens-Ole Graulund <jensole@spiio.com>, December 2017

* Contributors:
*    Jens-Ole Graulund - initial API and implementation
*******************************************************************************/

#include <stdio.h>

#include "Message.h"
#include "SpiioUtils.h"

SPIIO::Message::Message(float battery, float light, float moisture, float temperature, int time)
{
    message.battery = battery;
    message.light = light;
    message.moisture = moisture;
    message.temperature = temperature;
    message.time = time;
};

SPIIO::Message::Message(){};

float const& SPIIO::Message::battery() const
{
    return message.battery;
};

void SPIIO::Message::battery(float const& aBattery)
{
    message.battery = aBattery;
};

float const& SPIIO::Message::light() const
{
    return message.light;
};

void SPIIO::Message::light(float const& aLight)
{
    message.light = aLight;
};

float const& SPIIO::Message::moisture() const
{
    return message.moisture;
};

void SPIIO::Message::moisture(float const& aMoisture)
{
    message.moisture = aMoisture;
};

float const& SPIIO::Message::temperature() const
{
    return message.temperature;
};

void SPIIO::Message::temperature(float const& aTemperature)
{
    message.temperature = aTemperature;
};

int const& SPIIO::Message::time() const
{
    return message.time;
};

void SPIIO::Message::time(int const& aTime)
{
    message.time = aTime;
};

void SPIIO::Message::JSONstringify(string& JSONString) const
{
    // battery
    char m[6];
    sprintf(m, "%f", message.moisture);
    string moist = m;

    //temperature
    char t[6];
    sprintf(t, "%f", message.temperature);
    string temp = t;

    //light
    char l[6];
    sprintf(l, "%f", message.light);
    string light = l;

    //battery
    char b[6];
    sprintf(b, "%f", message.battery);
    string batt = b;

    // time
    char x[6];
    sprintf(x, "%i", message.time);
    string time = x;

    JSONString = "{\"moist\":" + moist + ",\"temp\":" + temp + ",\"light\":" + light + ",\"batt\":" + batt + ",\"time\":" + time + "}";
};