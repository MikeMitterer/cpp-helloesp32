/**
 * Hello-World ESP32.
 * Blinkt eine LED und ermöglicht ein OAT update
 *
 * Wenn das OAT funktioniere soll muss im platformio.ini der Upload-Port gesetzt sein!
 *
 * Mehr:
 *      https://diyprojects.io/arduinoota-esp32-wi-fi-ota-wireless-update-arduino-ide/
 *
 * OTA mit platformio:
 *      http://docs.platformio.org/en/latest/platforms/espressif8266.html#over-the-air-ota-update
 *      
 */
#include "stdafx.h"
#include "config.h"
#include "ota.h"

#include <ESPAsyncWebServer.h>

const gpio_num_t internalLED = GPIO_NUM_2;

// Internal network I (192.168.0.0/24)
const std::string ssid{ "MikeMitterer-LS" };
const std::string password{ HelloESP32_PASSWORD_LS };

void setup() {
    Serial.begin(115200);

    // initialize digital pin LED_BUILTIN as an output.
    pinMode(internalLED, OUTPUT);

    Serial.println("Booting");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), password.c_str());
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("Connection Failed! Rebooting...");
        delay(5000);
        ESP.restart();
    }

    initOTA();
    ArduinoOTA.begin();

    Serial.println("Ready");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    ArduinoOTA.handle();

    Serial.println("Hello OAT!");

    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);                       // wait for a second

    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(100);
}