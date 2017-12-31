/*******************************************************************************
* Copyright (C) 2017, 2017 Spiio, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Jens-Ole Graulund <jensole@spiio.com>, December 2017

* Contributors:
*    Jens-Ole Graulund - initial API and implementation
*******************************************************************************/

#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <string>

using namespace std;

namespace SPIIO {
class Message {
public:
    Message(float battery, float light, float moisture, float temperature, int time);
    Message();

    float const& battery() const;
    void battery(float const& abattery);

    float const& light() const;
    void light(float const& light);

    float const& moisture() const;
    void moisture(float const& moisture);

    float const& temperature() const;
    void temperature(float const& temperature);

    int const& time() const;
    void time(int const& time);

    void JSONstringify(string& JsonString) const;


private:
    struct
    {
        float battery;
        float light;
        float moisture;
        float temperature;
        int time;
    } message;
};
}

#endif // _MESSAGE_H_