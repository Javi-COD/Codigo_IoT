#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUDP.h>
#include <ArduinoOTA.h>

// Replace with your network credentials
const char* ssid = "VELOCITY_JONATHAN";
const char* password = "0941022956";

const int LED_PIN = D2; // Connect the LED to this pin

void setup() {
  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  // Port defaults to 8266
  ArduinoOTA.setPort(8266);

  // Hostname
  ArduinoOTA.setHostname("ESP8266-OTA");

  // No authentication
  //ArduinoOTA.setPassword((const char *)NULL);

  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });

  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  ArduinoOTA.handle();
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  delay(1000);
}
