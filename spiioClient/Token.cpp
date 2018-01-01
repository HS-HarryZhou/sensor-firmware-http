
/*******************************************************************************
* Copyright (C) 2017, 2017 Spiio, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Jens-Ole Graulund <jensole@spiio.com>, December 2017

* Contributors:
*    Jens-Ole Graulund - initial API and implementation
*******************************************************************************/

#include "Token.h"

using namespace std;

SPIIO::Token::Token()
{
    token.access_token = "";
    token.expiresIn = 0;
};

string const& SPIIO::Token::access_token() const
{
    return token.access_token;
};

int const& SPIIO::Token::expires_in() const
{
    return token.expiresIn;
};

string const& SPIIO::Token::token_type() const
{
    return token.token_type;
};

void SPIIO::Token::access_token(string const& newAccess_token)
{
    token.access_token = newAccess_token;
};

void SPIIO::Token::expires_in(int const& newExpiresIn)
{
    token.expiresIn = newExpiresIn;
};

void SPIIO::Token::token_type(string const& type)
{
    token.token_type = type;
};

bool SPIIO::Token::isValid() const
{
    return !token.access_token.empty();
};

// TODO calculate token expiration.
bool SPIIO::Token::isExpired() const
{
    return false;
};

void SPIIO::Token::reset()
{
    token.access_token = "";
    token.expiresIn = 0;
};