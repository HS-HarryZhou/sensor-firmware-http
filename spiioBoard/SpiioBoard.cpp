/*******************************************************************************
* Copyright (C) 2017, 2017 Spiio, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Jens-Ole Graulund <jensole@spiio.com>, December 2017

* Contributors:
*    Jens-Ole Graulund - initial API and implementation
*******************************************************************************/

#include "SpiioBoard.h"
#include "SpiioCommon/SpiioUtils.h"
#include "mbed.h"
//#include "WakeUp.h"

using namespace std;

SPIIO::SpiioBoard::SpiioBoard(const SPIIO::BoardConfig& boardConfig)
    : _boardConfig(boardConfig){};

SPIIO::Message SPIIO::SpiioBoard::getMeasurement()
{
    SPIIO::Message message;
    message.battery(_get_battery());
    message.moisture(_get_moisture());
    message.light(_get_light());
    message.temperature(_get_temp());
    message.time(_get_time());

    return message;
};

/*
TODO not sure how this should work.
Device sleep with ?: https://os.mbed.com/teams/ublox/code/WakeUp/
More on sleep in Mbed OS5.6: https://os.mbed.com/docs/v5.6/reference/sleep-manager.html
Power control for Mbed (u-blox LPC1768 not included): https://os.mbed.com/users/JST2011/code/PowerControl/

*/
void SPIIO::SpiioBoard::hibernate(int period)
{
    printf("\nsleeping : %i sec\n", period);
    wait(period);
}
