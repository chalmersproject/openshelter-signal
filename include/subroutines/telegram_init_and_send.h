#ifndef TELEGRAM_INIT_AND_SEND_H
#define TELEGRAM_INIT_AND_SEND_H
#include <external_library_includes.h>

//
// globals and attributes
//
#include <globals/globals.h> //this contains timers used in this script
#include <globals/attributes.h>
#include <globals/graphql_queries.h> // PUSH and PULL graphql queries that are sent to API
#include <shelter_secrets.h>         // API secret and shelter ID
#include <subroutines/connect_to_wifi.h>
#include <subroutines/http_request.h>

UniversalTelegramBot bot(BOT_TOKEN, client);
String Response;

void set_datetime()
{
    client.setInsecure();
    Serial.print("Retrieving time: ");
    configTime(0, 0, "pool.ntp.org"); // get UTC time via NTP
    time_t now = time(nullptr);
    while (now < 24 * 3600)
    {
        Serial.print(".");
        delay(100);
        now = time(nullptr);
    }
}
#endif