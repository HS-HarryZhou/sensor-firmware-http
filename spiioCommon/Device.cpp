
/*******************************************************************************
* Copyright (C) 2017, 2017 Spiio, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Jens-Ole Graulund <jensole@spiio.com>, December 2017

* Contributors:
*    Jens-Ole Graulund - initial API and implementation
*******************************************************************************/
#include "Device.h"
#include "mbed.h"

using namespace std;

// More info at: https://github.com/vpcola/MQTTGateway/blob/master/DownloadFile.cpp
static unsigned int base64enc_len(const char* str)
{
    return (((strlen(str) - 1) / 3) + 1) << 2;
}

static void base64enc(const char* input, unsigned int length, char* output)
{
    static const char base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    unsigned int c, c1, c2, c3;
    for (unsigned int i = 0, j = 0; i < length; i += 3, j += 4) {
        c1 = ((((unsigned char)*((unsigned char*)&input[i]))));
        c2 = (length > i + 1) ? ((((unsigned char)*((unsigned char*)&input[i + 1])))) : 0;
        c3 = (length > i + 2) ? ((((unsigned char)*((unsigned char*)&input[i + 2])))) : 0;

        c = ((c1 & 0xFC) >> 2);
        output[j + 0] = base64[c];
        c = ((c1 & 0x03) << 4) | ((c2 & 0xF0) >> 4);
        output[j + 1] = base64[c];
        c = ((c2 & 0x0F) << 2) | ((c3 & 0xC0) >> 6);
        output[j + 2] = (length > i + 1) ? base64[c] : '=';
        c = (c3 & 0x3F);
        output[j + 3] = (length > i + 2) ? base64[c] : '=';
    }
    output[(((length - 1) / 3) + 1) << 2] = '\0';
}

static string encode(const string& str)
{
    char* out = new char[base64enc_len(str.c_str())];
    base64enc(str.c_str(), str.length(), out);
    string res(out);
    delete[] out;
    return res;
}

SPIIO::Device::Device()
{
    device.id = "0c2a690d0867";
    device.secret = "spiiodevice";
    device.model = "deviceModel";
    device.imei = "deviceImei";

    const string identity = device.id + ":" + device.secret;
    device.basicAuth = encode(identity);
};

string const& SPIIO::Device::id() const
{
    return device.id;
};

void SPIIO::Device::id(string const& aId)
{
    device.id = aId;
};

string const& SPIIO::Device::secret() const
{
    return device.secret;
};

void SPIIO::Device::secret(string const& aSecret)
{
    device.secret = aSecret;
};

string const& SPIIO::Device::model() const
{
    return device.model;
};

void SPIIO::Device::model(string const& aModel)
{
    device.model = aModel;
};

string const& SPIIO::Device::imei() const
{
    return device.imei;
};

void SPIIO::Device::imei(string const& aImei)
{
    device.imei = aImei;
};

string const& SPIIO::Device::basicAuth() const
{
    return device.basicAuth;
};