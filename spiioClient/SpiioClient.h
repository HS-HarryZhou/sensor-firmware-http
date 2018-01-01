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

#include "mbed.h"

#include "SpiioCommon/Config.h"
#include "SpiioCommon/Device.h"
#include "SpiioCommon/MessageStore.h"

#include "Token.h"

using namespace std;
namespace SPIIO {
class SpiioClient {
public:
    SpiioClient(const SPIIO::Config& config, const SPIIO::Device& device);

    ~SpiioClient();

    int publish(SPIIO::MessageStore& store);

private:
    NetworkInterface* _network;

    const SPIIO::Device _device;
    const SPIIO::Config _config;

    void getToken();

    int parseAuthnResponse(const char* jsonData);
    int parseReadingsResponse(const char* jsonData);

    SPIIO::Token token;
};
}
#endif // _SPIIOCLIENT_H_