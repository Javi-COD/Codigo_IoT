#define BLYNK_TEMPLATE_ID "TMPL2qTqYaXdb"
#define BLYNK_TEMPLATE_NAME "SEMAFORO"

char auth[] = "pI-HZ45t_KY2YSTEKCtK2Icv4EwQxvQc";
char ssid[] = "VELOCITY_JONATHAN";
char password[] = "0941022956";

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266mDNS.h>
#include <WiFiUDP.h>
#include <ArduinoOTA.h>

// Definición de pines para el semáforo vehicular
const int V1_ROJO = D0; //V1_ROJO
const int V1_AMARILLO = D1; //V1_AMARILLO
const int V1_VERDE = D2; //V1_VERDE

// Definición de pines para el semáforo peatonal
const int P1_ROJO = D3; //P1_ROJO
const int P1_VERDE = D4; //P1_VERDE

// Definición de pines para el semáforo vehicular
const int V2_ROJO = D5; //V2_ROJO
const int V2_AMARILLO = D6; //V2_AMARILLO
const int V2_VERDE = D7; //V2_VERDE

// Definición de pines para el semáforo peatonal
const int P2_ROJO = D8; //P2_ROJO
const int P2_VERDE = 3; //P2_VERDE

// Estado de los LEDs
int ledState1 = LOW;
int ledState2 = LOW;
int ledState3 = LOW;
int ledState4 = LOW;

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, password);
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

  // Configurar los pines como salida
  pinMode(V1_ROJO, OUTPUT);
  pinMode(V1_AMARILLO, OUTPUT);
  pinMode(V1_VERDE, OUTPUT);

  pinMode(P1_ROJO, OUTPUT);
  pinMode(P1_VERDE, OUTPUT);

  pinMode(V2_ROJO, OUTPUT);
  pinMode(V2_AMARILLO, OUTPUT);
  pinMode(V2_VERDE, OUTPUT);
  
  pinMode(P2_ROJO, OUTPUT);
  pinMode(P2_VERDE, OUTPUT);

  // Inicializar el estado de los LEDs
  digitalWrite(V1_ROJO, ledState1);
  digitalWrite(P1_ROJO, ledState2);
  digitalWrite(V2_ROJO, ledState3);
  digitalWrite(P2_ROJO, ledState4);

  // Configurar el estado inicial de los widgets LED en la aplicación Blynk
  Blynk.virtualWrite(V1, ledState1);
  Blynk.virtualWrite(V4, ledState2);
  Blynk.virtualWrite(V6, ledState3);
  Blynk.virtualWrite(V9, ledState4);
//  pinMode(LED_PIN, OUTPUT);
//  digitalWrite(LED_PIN, LOW);
}

void loop() {
  ArduinoOTA.handle();
  Blynk.run();

}

BLYNK_WRITE(V1) {
  ledState1 = param.asInt();
  digitalWrite(V1_ROJO, ledState1);
  Blynk.virtualWrite(V1, ledState1); // Actualizar el estado del widget LED en la aplicación Blynk
}

BLYNK_WRITE(V4) {
  ledState2 = param.asInt();
  digitalWrite(P1_ROJO, ledState2);
  Blynk.virtualWrite(V4, ledState2); // Actualizar el estado del widget LED en la aplicación Blynk
}

BLYNK_WRITE(V6) {
  ledState3 = param.asInt();
  digitalWrite(V2_ROJO, ledState3);
  Blynk.virtualWrite(V6, ledState3); // Actualizar el estado del widget LED en la aplicación Blynk
}

BLYNK_WRITE(V9) {
  ledState4 = param.asInt();
  digitalWrite(P2_ROJO, ledState4);
  Blynk.virtualWrite(V9, ledState4); // Actualizar el estado del widget LED en la aplicación Blynk
}