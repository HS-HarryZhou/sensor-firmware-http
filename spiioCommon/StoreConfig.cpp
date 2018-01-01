
/*******************************************************************************
* Copyright (C) 2017, 2017 Spiio, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Jens-Ole Graulund <jensole@spiio.com>, December 2017

* Contributors:
*    Jens-Ole Graulund - initial API and implementation
*******************************************************************************/

#include "StoreConfig.h"
#include "SpiioUtils.h"

SPIIO::StoreConfig::StoreConfig()
{
    store.collection_count = MEASUREMENT_COLLECTION_COUNT;
    store.collection_interval = MEASUREMENT_COLLECTION_INTERVAL;
};

int const& SPIIO::StoreConfig::collection_count() const
{
    return store.collection_count;
};

void SPIIO::StoreConfig::collection_count(int const& count)
{
    store.collection_count = count;
};

int const& SPIIO::StoreConfig::collection_interval() const
{
    return store.collection_interval;
};

void SPIIO::StoreConfig::collection_interval(int const& interval)
{
    store.collection_interval = interval;
};