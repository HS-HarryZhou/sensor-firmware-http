/*******************************************************************************
* Copyright (C) 2017, 2017 Spiio, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Jens-Ole Graulund <jensole@spiio.com>, December 2017

* Contributors:
*    Jens-Ole Graulund - initial API and implementation
*******************************************************************************/

#ifndef _DEVICE_H_
#define _DEVICE_H_

#include <string>

using namespace std;
namespace SPIIO {
class Device {
public:
    Device();

    string const& id() const;
    void id(string const& aId);

    string const& secret() const;
    void secret(string const& aSecret);

    string const& model() const;
    void model(string const& aModel);

    string const& imei() const;
    void imei(string const& aImei);

    string const& basicAuth() const;

private:
    struct
    {
        string id;
        string secret;
        string model;
        string imei;
        string basicAuth;
    } device;
};
}

#endif // _DEVICE_H_