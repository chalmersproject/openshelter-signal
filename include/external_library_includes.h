#ifndef EXTERN_LIBRARY_INCLUDES_H
#define EXTERN_LIBRARY_INCLUDES_H

#include <Arduino.h>

// display
#include <SPI.h>
#include <RotaryEncoder.h>

// WiFi and HTTPS requests
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h> // create TLS connection
#include <WiFiManager.h>
// JSON Support
#include <ArduinoJson.h>

// LED
#include <FastLED.h>

// GUISlice
#include "GUIsliceProjects/GUIsliceProjects_GSLC.h"
#include "guislice_init.h"
#include "guislice_callbacks.h"
#endif