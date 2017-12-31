/*******************************************************************************
* Copyright (C) 2017, 2017 Spiio, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Jens-Ole Graulund <jensole@spiio.com>, December 2017

* Contributors:
*    Jens-Ole Graulund - initial API and implementation
*******************************************************************************/

#include "Config.h"

using namespace std;

SPIIO::Config::Config()
{
    sensor_hub.url = "http://sensorhub.staging.spiio.com/readings/";
    sensor_hub.port = 80;
    authn.url = "http://authn.staging.spiio.com/token";
    authn.port = 80;
};
