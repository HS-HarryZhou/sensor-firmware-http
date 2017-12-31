/*******************************************************************************
* Copyright (C) 2017, 20017 Spiio, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Jens-Ole Graulund <jensole@spiio.com>, December 2017

 * Contributors:
 *    Jens-Ole Graulund - initial API and implementation
 *******************************************************************************/

/**
  This is a prototype firmware to illustrate interaction with SPIIO MQTT and HTTP Client services
  on the mbed platform.  

  Additional libraries used:
  mbed-http: https://os.mbed.com/teams/sandbox/code/mbed-http/
  JSON parser : https://os.mbed.com/users/yoonghm/code/jsmn/
  u-blox easy-connect: https://os.mbed.com/teams/ublox/code/easy-connect/#9da11cf868d9 included in the HelloMATT project
  (WakeUp: https://os.mbed.com/users/Sissors/code/WakeUp/)

  Other Links of interest:
    Sleep in Mbed OS5.6: https://os.mbed.com/docs/v5.6/reference/sleep-manager.html
    time    - https://os.mbed.com/docs/v5.6/reference/time.html
    assert  - https://os.mbed.com/docs/v5.6/reference/assert.html
    ssl/tls - https://os.mbed.com/docs/v5.6/reference/tls.html
            - https://tls.mbed.org/discussions/generic/minimal-tls-configuration-for-https-connections

  This project depends on mbed-http. Another options is to use the u-blox cellular interface.
    u-blox cellular http - https://os.mbed.com/teams/ublox/code/example-ublox-at-cellular-interface-ext/file/e1b6cd53333f/main.cpp/            
 */

#include "SpiioCommon//Message.h"
#include "SpiioCommon/Config.h"
#include "SpiioCommon/Device.h"
#include "spiioBoard/SpiioBoard.h"
#include "spiioClient/SpiioClient.h"

using namespace std;
int main(void)
{

    // Create configuration objects. Configuration objects responsiblity is to create the environment to the processing objects.
    // Configuration values can be static, derived fom MCU information or supplied during factory flash of firmware.
    const SPIIO::Device theDevice;
    const SPIIO::Config spiioNetwork;
    const SPIIO::BoardConfig boardConfig;

    // Create board to handle MCU and sensor interface
    SPIIO::SpiioBoard board(boardConfig);

    // Create Spiio service API client with:
    // - Spiio server config to know how to connect to the Spiio services.
    // - Device information to identify the sensor to the spiio service.
    SPIIO::SpiioClient spiioClient(spiioNetwork, theDevice);

    // Create message store to hold meassurements
    SPIIO::MessageStore store;
    
    while (true) {

        // Get mesasurements from the Board.
        SPIIO::Message message = board.getMeasurement();

        // Add the measurement to the message store.
        store.add(message);

        // Publish message in the store.
        // Spiio client takes care of token renewal/security
        // and decides whether to send or keep messages in the store dependent on the MEASUREMENT_COLLECTION_COUNT global paramenter.
        spiioClient.publish(store);

        // Set the board in sleep mode. Sleep period is defined by global parameter MEASUREMENT_COLLECTION_INTERVAL.
        // TODO pass parameter with sleep period. Can indirectly be changed in config in Publish.
        board.hibernate();
    }
}