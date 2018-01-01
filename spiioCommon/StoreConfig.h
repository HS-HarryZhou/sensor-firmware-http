/*******************************************************************************
* Copyright (C) 2017, 2017 Spiio, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Jens-Ole Graulund <jensole@spiio.com>, December 2017

* Contributors:
*    Jens-Ole Graulund - initial API and implementation
*******************************************************************************/

#ifndef _STORECONFIG_H_
#define _STORECONFIG_H_

namespace SPIIO {
class StoreConfig {
public:
    StoreConfig();

    int const& collection_count() const;
    void collection_count(int const& count);

    int const& collection_interval() const;
    void collection_interval(int const& interval);

private:
    struct
    {
        int collection_count;
        int collection_interval;
    } store;
};
}

#endif // _STORECONFIG_H_