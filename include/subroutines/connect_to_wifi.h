#ifndef CONNECT_TO_WIFI_H
#define CONNECT_TO_WIFI_H

#include <external_library_includes.h>
#include <subroutines/update_guislice.h>
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

    // TODO: get TLS working between signal and api
    client.setInsecure();
}
void connect_to_wifi()
{
    gslc_SetPageCur(&m_gui, E_PG_WIFICON);
    gslc_Update(&m_gui);
    initWifi();

    if (WiFi.status() == WL_CONNECTED)
    {
        delay(4000);

        // pull latest occupancy capacity numbers from remote and set them to the display
        // occupancy_request(client, "pull", occupancy, capacity); //
        // Update OCCUPANCY and CAPACITY GUI numbers
        Serial.println("SAYING WIFI CONNECTED");
        gslc_SetPageCur(&m_gui, E_PG_MAIN);
        Serial.println("UPDATING GUISLICE UI");
        update_all_GSlice_UI();
    }

    // TODO:
    // verify connection to api.chalmersproject.com
}

#endif