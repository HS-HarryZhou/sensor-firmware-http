/*******************************************************************************
* Copyright (C) 2017, 2017 Spiio, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Jens-Ole Graulund <jensole@spiio.com>, December 2017

* Contributors:
*    Jens-Ole Graulund - initial API and implementation
*******************************************************************************/

#ifndef _SPIIOUTILS_H_
#define _SPIIOUTILS_H_

using namespace std;

// The number of measurements to collect before delivering
const int MEASUREMENT_COLLECTION_COUNT = 2;
// The time interval between measurements
const int MEASUREMENT_COLLECTION_INTERVAL = 30.0;

const int SPIIO_FAILURE = -1;
const int SPIIO_SUCCESS = 0;

#endif // _SPIIOUTILS_H_