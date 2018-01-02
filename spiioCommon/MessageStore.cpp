/*******************************************************************************
* Copyright (C) 2017, 2017 Spiio, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Jens-Ole Graulund <jensole@spiio.com>, December 2017

* Contributors:
*    Jens-Ole Graulund - initial API and implementation
*******************************************************************************/
#include "MessageStore.h"
#include "SpiioCommon/SpiioUtils.h"

#include <stdio.h>

SPIIO::MessageStore::MessageStore(SPIIO::StoreConfig& storeConfig)
    : config(storeConfig)
{
    store.reserve(MAX_STORE_MEASUREMENTS + 1);
};

bool SPIIO::MessageStore::DoPostReadings() const
{
    return (store.size() > 0 && store.size() == (unsigned)config.collection_count());
};

int SPIIO::MessageStore::GetCollectionInterval() const
{
    return config.collection_interval();
};

void SPIIO::MessageStore::collection_interval(const int interval)
{
    config.collection_interval(interval);
};

void SPIIO::MessageStore::collection_count(const int count)
{
    config.collection_count(count);
};

void SPIIO::MessageStore::add(SPIIO::Message message)
{
    if (store.size() >= MAX_STORE_MEASUREMENTS) {
        store.erase(store.begin());
    }
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
    string JsonString = "";
    if (!store.empty()) {
        int i = 0;
        for (std::vector<SPIIO::Message>::const_iterator it = store.begin(); it != store.end(); ++it) {
            string measurement = "";

            (*it).JSONstringify(measurement);
            if (i > 0) {
                JsonString = JsonString + "," + measurement;
            } else {
                JsonString += measurement;
            }
            i++;
        }
    };
    body = "[" + JsonString + "]";
};
