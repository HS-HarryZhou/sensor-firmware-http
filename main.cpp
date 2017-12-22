/*******************************************************************************
 * Copyright (c) 2014, 2015 IBM Corp.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 *
 * The Eclipse Public License is available at
 *    http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at
 *   http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Ian Craggs - initial API and implementation and/or initial documentation
 *    Ian Craggs - make sure QoS2 processing works, and add device headers
 *******************************************************************************/

/**
  This is a sample program to illustrate the use of the MQTT Client library
  on the mbed platform.  The Client class requires two classes which mediate
  access to system interfaces for networking and timing.  As long as these two
  classes provide the required public programming interfaces, it does not matter
  what facilities they use underneath. In this program, they use the mbed
  system libraries.

 */

// change this to 0 to output messages to serial instead of LCD
#define USE_LCD 0

#if USE_LCD
#include "C12832.h"

// the actual pins are defined in mbed_app.json and can be overridden per target
C12832 lcd(LCD_MOSI, LCD_SCK, LCD_MISO, LCD_A0, LCD_NCS);

#define logMessage \
  lcd.cls();       \
  lcd.printf

#else

#define logMessage printf

#endif

#define MQTTCLIENT_QOS2 1

#include "easy-connect.h"
#include "http_request.h"
#include "MQTTNetwork.h"
#include "MQTTmbed.h"
#include "MQTTClient.h"

int arrivedcount = 0;

void messageArrived(MQTT::MessageData &md)
{
  MQTT::Message &message = md.message;
  logMessage("Message arrived: qos %d, retained %d, dup %d, packetid %d\r\n", message.qos, message.retained, message.dup, message.id);
  logMessage("Payload %.*s\r\n", message.payloadlen, (char *)message.payload);
  ++arrivedcount;
}

void dump_response(HttpResponse *res)
{
  printf("Status: %d - %s\n", res->get_status_code(), res->get_status_message().c_str());

  printf("Headers:\n");
  for (size_t ix = 0; ix < res->get_headers_length(); ix++)
  {
    printf("\t%s: %s\n", res->get_headers_fields()[ix]->c_str(), res->get_headers_values()[ix]->c_str());
  }
  printf("\nBody (%d bytes):\n\n%s\n", res->get_body_length(), res->get_body_as_string().c_str());
}

int main(int argc, char *argv[])
{
  float version = 0.6;
  char *topic = "mbed-sample";

  logMessage("HelloMQTT: version is %.2f\r\n", version);

  while (true)
  {

    NetworkInterface *network = easy_connect(true);
    if (!network)
    {
      logMessage("HelloMQTT: No network %.2f\r\n", version);
      return -1;
    }

    logMessage("HelloMQTT: GOT network %.2f\r\n", version);

    // Do a GET request to httpbin.org
    {
      // By default the body is automatically parsed and stored in a buffer, this is memory heavy.
      // To receive chunked response, pass in a callback as last parameter to the constructor.
      HttpRequest *get_req = new HttpRequest(network, HTTP_GET, "http://httpbin.org/ip");

      HttpResponse *get_res = get_req->send();
      if (!get_res)
      {
        printf("HttpRequest failed (error code %d)\n", get_req->get_error());
        return 1;
      }

      printf("\n----- HTTP GET response -----\n");
      dump_response(get_res);

      delete get_req;
    }

    MQTTNetwork mqttNetwork(network);

    MQTT::Client<MQTTNetwork, Countdown, 500> client = MQTT::Client<MQTTNetwork, Countdown, 500>(mqttNetwork);

    const char *hostname = "mqtt.staging.spiio.com";
    int port = 1883;

    logMessage("Connecting to %s:%d\r\n", hostname, port);
    int rc = mqttNetwork.connect(hostname, port);
    if (rc != 0)
      logMessage("rc from TCP connect is %d\r\n", rc);

    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
    data.MQTTVersion = 4;
    data.clientID.cstring = "mbed-sample";
    data.username.cstring = "0c2a690d0867@jwt";
    //data.password.cstring = "0c2a690d0867";
    data.password.cstring = "eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpc3MiOiJodHRwOi8vYXV0aG4uc3BpaW8uY29tIiwic3ViIjoiZGV2aWNlLzBjMmE2OTBkMDg2NyIsImp0aSI6IjE5ZTNjYzkyLWU4MzUtNGM4ZS1iZTM2LTQ3NzQ1MjEwZDk3MyIsImlhdCI6MTUxMjU4MTcwMCwiZXhwIjoxNzM1Njg5NjAwfQ.qmItTcAcKc7AV5kLNzXYCWgVmvX1lRhSCbWF3Bf7POU";

    if ((rc = client.connect(data)) != 0)
      logMessage("rc from MQTT connect is %d\r\n", rc);

    MQTT::Message message;

    // QoS 1
    char buf[100];
    sprintf(buf, "Hello World!  QoS 0 message from app version %f\r\n", version);

    message.qos = MQTT::QOS1;
    message.retained = false;
    message.dup = false;
    message.payload = (void *)buf;
    message.payloadlen = strlen(buf) + 1;
    client.publish(topic, message);

    if ((rc = client.disconnect()) != 0)
      logMessage("rc from disconnect was %d\r\n", rc);

    mqttNetwork.disconnect();

    logMessage("Version %.2f: finish %d msgs\r\n", version, arrivedcount);

    network->disconnect();

    delete network;

    wait(30.0);
  }

  return 0;
}
