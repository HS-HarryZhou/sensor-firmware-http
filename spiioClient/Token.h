/*******************************************************************************
* Copyright (C) 2017, 2017 Spiio, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Jens-Ole Graulund <jensole@spiio.com>, December 2017

* Contributors:
*    Jens-Ole Graulund - initial API and implementation
*******************************************************************************/

#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <string>

using namespace std;
namespace SPIIO {
class Token {
public:
    Token();

    string const& access_token() const;
    void access_token(string const& newAccess_token);

    int const& expiresIn() const;
    void expiresIn(int const& newExpiresIn);

    void reset();
    bool isValid() const;
    bool isExpired() const;

private:
    struct
    {
        string access_token;
        int expiresIn;
    } token;
};
}

#endif // _TOKEN_H_