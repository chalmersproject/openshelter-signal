#ifndef CONNECT_TO_WIFI_H
#define CONNECT_TO_WIFI_H

#include <external_library_includes.h>
// #include <WiFiClientSecure.h> // create TLS connection
// #include <WiFiManager.h>

WiFiClientSecure client;
void initWifi()
{
    WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
    // WiFi.begin(_WIFI_SSID, _WIFI_PWD);

    // https://github.com/tzapu/WiFiManager/blob/master/examples/Basic/Basic.ino
    // WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wm;

    bool res;
    res = wm.autoConnect("Chalmers-Signal");
    if (!res)
    {
        Serial.println("Failed to connect");
        // ESP.restart();
    }
    else
    {
        // if you get here you have connected to the WiFi
        Serial.println("connected...yeey :)");
    }
    // Serial.println("Connecting..");
    // while (WiFi.status() != WL_CONNECTED)
    // {
    //   delay(500);
    //   Serial.println(".");
    // }
    // Serial.printf("SSID: %s\nIP: %s\n", _WIFI_SSID, WiFi.localIP().toString().c_str());
}

#endif