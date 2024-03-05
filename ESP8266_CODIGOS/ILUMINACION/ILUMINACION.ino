#define BLYNK_TEMPLATE_ID "TMPL2vCMY3v9B"
#define BLYNK_TEMPLATE_NAME "ILUMINACION"

#include <ESP8266WiFi.h> //LIBRERIA DE ESP8266
#include <BlynkSimpleEsp8266.h> //LIBRERIA DE BLYNK

#include <WiFiUdp.h>
#include <NTPClient.h>

///////////
#include <WiFiManager.h>
#include <strings_en.h>

#include <wm_consts_en.h>
#include <wm_strings_en.h>
#include <wm_strings_es.h>

#include <DNSServer.h>
#include <ESP8266WebServer.h>
///////////

char auth[] = "aTT9mbz8CjRZfZbCg2WsR3rME1-_Z_h6";  // Obtén el token de autenticación de la app Blynk

// Define el cliente NTP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "0.ec.pool.ntp.org");

// Define los pines de los LEDs
const int ledPin1 = D1;
const int ledPin2 = D2;
const int ledPin3 = D3;
const int ledPin4 = D4;
const int ledPin5 = D5;
const int ledPin6 = D6;

int estado1;
int estado2;
int estado3;
int estado4;



// Define la hora y minutos para encender y apagar los LEDs
const int targetHourOn = 21; // Hora de encendido (ejemplo: 18 representa las 6 PM)
const int targetMinuteOn = 29; // Minuto de encendido (ejemplo: 30 representa los 30 minutos)
const int targetHourOff = 21; // Hora de apagado (ejemplo: 19 representa las 7 PM)
const int targetMinuteOff = 32; // Minuto de apagado (ejemplo: 45 representa los 45 minutos)

// Define la hora y minutos para disminuir y aumentar la intensidad de los LEDs
const int targetHourIntensityDown = 21; // Hora de disminución de intensidad (ejemplo: 20 representa las 8 PM)
const int targetMinuteIntensityDown = 30; // Minuto de disminución de intensidad (ejemplo: 0 representa los 0 minutos)
const int targetHourIntensityUp = 21; // Hora de aumento de intensidad (ejemplo: 21 representa las 9 PM)
const int targetMinuteIntensityUp = 31; // Minuto de aumento de intensidad (ejemplo: 30 representa los 30 minutos)

// Define los valores de intensidad
const int normalIntensity = 255; // Intensidad normal de los LEDs (máximo brillo)
const int decreasedIntensity = 128; // Intensidad disminuida de los LEDs

void setup() {

  // Inicializa los pines de los LEDs
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  pinMode(ledPin6, OUTPUT);

  // Inicializa la comunicación serial
  Serial.begin(9600);
  
    // Inicialización de WiFiManager
  WiFiManager wifiManager;
  //wifiManager.resetSettings();
  
  // Intentar autoconexión WiFi previamente guardada
  if (!wifiManager.autoConnect("MiESP8266AP")) {
    Serial.println("Error de conexión y límite de tiempo alcanzado. Reiniciando...");
    delay(3000);
    ESP.restart();
  }

  // Si se logra la conexión WiFi
  Serial.println("Conexión WiFi establecida!");
  
  // Inicialización de Blynk
  Blynk.config(auth);

  // Configura el cliente NTP
  timeClient.begin();
  timeClient.setTimeOffset(-18000); // Ajusta el desfase horario a UTC-5 para Ecuador
  }

void loop() {
  Blynk.run();
  automatizacion();
digitalWrite(ledPin5, HIGH);
digitalWrite(ledPin6, HIGH);

}

void automatizacion(){

int currentHour = timeClient.getHours();
int currentMinute = timeClient.getMinutes();

    // Obtiene la hora y minutos actuales
  timeClient.update();
  Serial.print("Hora en Ecuador: ");
  Serial.print(timeClient.getFormattedTime());
  Serial.println();

      // Espera un segundo antes de volver a obtener la hora y minutos
  delay(1000);

  // Compara la hora y minutos actuales con las horas y minutos objetivo
  if (currentHour == targetHourOn && currentMinute == targetMinuteOn) {
    // Si la hora y minutos actuales coinciden con la hora y minutos de encendido, enciende los LEDs a máxima intensidad
    analogWrite(ledPin1, normalIntensity);
    analogWrite(ledPin2, normalIntensity);
    Serial.println("Se encendieron los LEDs.");

  } else if (currentHour == targetHourOff && currentMinute == targetMinuteOff) {
    // Si la hora y minutos actuales coinciden con la hora y minutos de apagado, apaga los LEDs
    analogWrite(ledPin1, 0);
    analogWrite(ledPin2, 0);
    Serial.println("Se apagaron los LEDs.");

  } else if (currentHour == targetHourIntensityDown && currentMinute == targetMinuteIntensityDown) {
    // Si la hora y minutos actuales coinciden con la hora y minutos de disminución de intensidad, ajusta la intensidad de los LEDs a un valor menor
    analogWrite(ledPin1, decreasedIntensity);
    analogWrite(ledPin2, decreasedIntensity);
    Serial.println("Se disminuyó la intensidad de los LEDs.");

  } else if (currentHour == targetHourIntensityUp && currentMinute == targetMinuteIntensityUp) {
    // Si la hora y minutos actuales coinciden con la hora y minutos de aumento de intensidad, ajusta la intensidad de los LEDs a su valor normal
    analogWrite(ledPin1, normalIntensity);
    analogWrite(ledPin2, normalIntensity);
    Serial.println("Se aumentó la intensidad de los LEDs.");
  }

}

BLYNK_WRITE(V1) {
  estado1 = param.asInt();
  digitalWrite(ledPin1, estado1);
}

BLYNK_WRITE(V2) {
  estado2 = param.asInt();
  digitalWrite(ledPin2, estado2);
}

BLYNK_WRITE(V3) {
  estado3 = param.asInt();
  digitalWrite(ledPin3, estado3);
}

BLYNK_WRITE(V4) {
  estado4 = param.asInt();
  digitalWrite(ledPin4, estado4);
}

BLYNK_WRITE(V5) {
  int intensity = param.asInt();
  analogWrite(ledPin1, map(intensity, 0, 255, 0, 1023));
  analogWrite(ledPin2, map(intensity, 0, 255, 0, 1023));
  analogWrite(ledPin3, map(intensity, 0, 255, 0, 1023));
  analogWrite(ledPin4, map(intensity, 0, 255, 0, 1023));
}

