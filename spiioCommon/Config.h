/*******************************************************************************
* Copyright (C) 2017, 2017 Spiio, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Jens-Ole Graulund <jensole@spiio.com>, December 2017

 * Contributors:
*    Jens-Ole Graulund - initial API and implementation
 *******************************************************************************/

/*
  This is config information defined at firmware production
  Assume this configuration is placed in af file on the MCU file system
*/

#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <string>

using namespace std;

namespace SPIIO {
class Config {
public:
    Config();

    struct
    {
        string url;
        int port;
    } sensor_hub;

    struct
    {
        string url;
        int port;
    } authn;
};
}

#endif // _CONFIG_H_
