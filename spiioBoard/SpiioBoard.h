/*******************************************************************************
* Copyright (C) 2017, 2017 Spiio, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Jens-Ole Graulund <jensole@spiio.com>, December 2017

* Contributors:
*    Jens-Ole Graulund - initial API and implementation
*******************************************************************************/

#ifndef _SPIIOBOARD_H_
#define _SPIIOBOARD_H_

#include "SpiioCommon/BoardConfig.h"
#include "SpiioCommon/Message.h"

using namespace std;
namespace SPIIO {
class SpiioBoard {
public:
    SpiioBoard(const SPIIO::BoardConfig& boardConfig);
    SPIIO::Message getMeasurement();
    void hibernate();

private:
    const SPIIO::BoardConfig _boardConfig;

    float _get_moisture();
    float _get_light();
    float _get_battery();
    float _get_temp();
    int _get_time();
};
}

#endif // _SPIIOBOARD_H_