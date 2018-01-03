/*******************************************************************************
* Copyright (C) 2017, 2017 Spiio, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Jens-Ole Graulund <jensole@spiio.com>, December 2017

* Contributors:
*    Jens-Ole Graulund - initial API and implementation
*******************************************************************************/

#ifndef _SPIIOCLIENT_H_
#define _SPIIOCLIENT_H_

#include "NetworkInterface.h"
#include "mbed.h"

#include "SpiioCommon/Config.h"
#include "SpiioCommon/Device.h"
#include "SpiioCommon/MessageStore.h"

#include "Token.h"

using namespace std;
namespace SPIIO {

typedef struct
{
    int collection_count;
    int collection_interval;
} CollectionConfig;

typedef struct
{
    string access_token;
    string token_type;
    int expires_in;
} AuthnResponse;

class SpiioClient {
public:
    SpiioClient(NetworkInterface* nw, const SPIIO::Config& config, const SPIIO::Device& device);
    int publish(SPIIO::MessageStore& store);

private:
    NetworkInterface* _network;

    SPIIO::Device _device;
    SPIIO::Config _config;

    void getToken();

    int parseAuthnResponse(const char* jsonData, AuthnResponse& authnResponse);
    int parseReadingsResponse(const char* jsonData, CollectionConfig& config);

    SPIIO::Token token;
};
}
#endif // _SPIIOCLIENT_H_