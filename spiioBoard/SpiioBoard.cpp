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
#include "WakeUp.h"

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
Device sleep implmented with https://os.mbed.com/users/Sissors/code/WakeUp/file/65c04a02ad45/WakeUp.h/
More on sleep in Mbed OS5.6: https://os.mbed.com/docs/v5.6/reference/sleep-manager.html
TODO not sure how this should work.
*/
void SPIIO::SpiioBoard::hibernate()
{
    // Set wakeup time for 2 seconds
    //WakeUp::set(MEASUREMENT_COLLECTION_INTERVAL);

    // Enter sleep, the program won't go beyond this point until it is woken up
    //sleep();

    // wait(MEASUREMENT_COLLECTION_INTERVAL);
    wait(30.0);
}
