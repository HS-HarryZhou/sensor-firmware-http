/*******************************************************************************
* Copyright (C) 2017, 2017 Spiio, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Jens-Ole Graulund <jensole@spiio.com>, December 2017

* Contributors:
*    Jens-Ole Graulund - initial API and implementation
*******************************************************************************/

#include "easy-connect.h"
#include "http_request.h"
#include "jsmn.h"

#include "SpiioClient.h"
#include "SpiioCommon/SpiioUtils.h"

#include <string>

using namespace std;

void dump_response(HttpResponse* res)
{
    printf("Status: %d - %s\n", res->get_status_code(), res->get_status_message().c_str());

    printf("Headers:\n");
    for (size_t ix = 0; ix < res->get_headers_length(); ix++) {
        printf("\t%s: %s\n", res->get_headers_fields()[ix]->c_str(), res->get_headers_values()[ix]->c_str());
    }
    printf("\nBody (%d bytes):\n\n%s\n", res->get_body_length(), res->get_body_as_string().c_str());
}

SPIIO::SpiioClient::SpiioClient(const SPIIO::Config& config, const SPIIO::Device& device)
    : _device(device)
    , _config(config)
{
    _network = easy_connect(true);
}

SPIIO::SpiioClient::~SpiioClient()
{
    _network->disconnect();
}

int SPIIO::SpiioClient::publish(SPIIO::MessageStore& store)
{
    // Check messages batch limit reached before publishing
    if (store.count() < MEASUREMENT_COLLECTION_COUNT && store.count() > 0) {
        return SPIIO_SUCCESS;
    }

    // Renew token ?
    getToken();
    if (!token.isValid()) {
        return SPIIO_FAILURE;
    }

    string url = _config.sensor_hub.url + _device.id();
    HttpRequest* post_req = new HttpRequest(_network, HTTP_POST, url.c_str());
    post_req->set_header("x-access-token", token.access_token());
    post_req->set_header("Content-Type", "application/json");

    string body;
    store.JSONstringify(body);

    const char* jsonstr = body.c_str();

    printf("\nPosting Readings : %s\n", jsonstr);

    // Post the readings.
    HttpResponse* get_res = post_req->send(jsonstr, strlen(jsonstr));
    if (!get_res) {
        return SPIIO_FAILURE;
    }

    // TODO debug mode
    dump_response(get_res);

    // TODO parse response
    // parseReadingsResponse(response);

    // Readings delivered - empty readings in the message store
    store.reset();
    body = "";

    delete post_req;
    return SPIIO_SUCCESS;
};

void SPIIO::SpiioClient::getToken()
{
    // Do we already have a valid token ?
    if (token.isValid() && !token.isExpired()) {
        return;
    }

    // Token is invalid. Get a new token;
    token.reset();

    HttpRequest* post_req = new HttpRequest(_network, HTTP_POST, _config.authn.url.c_str());

    // Create Basic Authorization header with base64 encoding of <myDevice.id>:<myDevice.secret>
    post_req->set_header("Authorization", "Basic " + _device.basicAuth());
    post_req->set_header("Content-Type", "application/x-www-form-urlencoded");
    const char body[] = "grant_type=client_credentials";

    // POST the request
    HttpResponse* post_res = post_req->send(body, strlen(body));

    // We didn't receive response.
    if (!post_res) {
        return;
    }

    // TODOD debug mode
    dump_response(post_res);

    // parse the response and update token object
    std::string content = post_res->get_body_as_string();
    const char* response = content.c_str();
    parseAuthnResponse(response);

    delete post_req;
    return;
}

static int jsoneq(const char* json, jsmntok_t* tok, const char* s)
{
    if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start && strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
        return 0;
    }
    return -1;
}

int SPIIO::SpiioClient::parseAuthnResponse(const char* jsonData)
{
    jsmn_parser p;
    jsmntok_t t[128];

    jsmn_init(&p);
    int r = jsmn_parse(&p, jsonData, strlen(jsonData), t, sizeof(t) / sizeof(t[0]));

    if (r < 0) {
        printf("Parse failed\n");
        return -1;
    }

    if ((r > 0) && (t[0].type == JSMN_OBJECT)) {
        /* Loop over all keys of the root object */
        for (int i = 1; i < r; i++) {
            if (jsoneq(jsonData, &t[i], "access_token") == 0) {
                std::string tokenString = std::string((const char*)(jsonData + t[i + 1].start), (size_t)t[i + 1].end - t[i + 1].start);
                token.access_token(tokenString);
                i++;
            } else {
                // discard the rest of the tokens
            }
        }
        return 0;
    } else {
        return -1;
    }
}