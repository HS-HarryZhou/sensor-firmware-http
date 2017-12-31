/*******************************************************************************
* Copyright (C) 2017, 2017 Spiio, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Jens-Ole Graulund <jensole@spiio.com>, December 2017

* Contributors:
*    Jens-Ole Graulund - initial API and implementation
*******************************************************************************/
/*
  TODO - Add max entries in the store and keep elements on FIFO principle
*/
#include "MessageStore.h"
#include <stdio.h>

SPIIO::MessageStore::MessageStore(){};

void SPIIO::MessageStore::add(SPIIO::Message message)
{
    store.push_back(message);
    printf("\nMessage pushed on store:%i\n", store.size());
};

int SPIIO::MessageStore::count()
{
    return store.size();
};

void SPIIO::MessageStore::reset()
{
    store.clear();
    // Clear memory "hack"
    std::vector<SPIIO::Message>().swap(store);
};

void SPIIO::MessageStore::JSONstringify(string& body)
{
    int storeSize = store.size();
    printf("\nFormat readings: %i\n", storeSize);

    string JsonString = "";

    if (storeSize > 0) {
        int i = 0;
        for (std::vector<SPIIO::Message>::const_iterator it = store.begin(); it != store.end(); ++it) {
            string measurement = "";

            (*it).JSONstringify(measurement);
            if (i > 0) {
                JsonString = JsonString + "," + measurement;
            } else {
                JsonString += measurement;
            }
            measurement = "";
            i++;
        }
    };

    body = "[" + JsonString + "]";
};
