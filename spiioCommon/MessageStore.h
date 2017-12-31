/*******************************************************************************
* Copyright (C) 2017, 2017 Spiio, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Jens-Ole Graulund <jensole@spiio.com>, December 2017

* Contributors:
*    Jens-Ole Graulund - initial API and implementation
*******************************************************************************/

#ifndef _MESSAGESTORE_H_
#define _MESSAGESTORE_H_

#include <Message.h>
#include <vector>

using namespace std;
namespace SPIIO {
class MessageStore {
public:
    MessageStore();
    void add(SPIIO::Message message);
    int count();
    void reset();
    void JSONstringify(string& body);
    // void JSONstringify(char* str, size_t len);

private:
    vector<SPIIO::Message> store;
};
}

#endif // _MESSAGESTORE_H_