#define BLYNK_TEMPLATE_ID "TMPL2qTqYaXdb"
#define BLYNK_TEMPLATE_NAME "SEMAFORO"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


char auth[] = "pI-HZ45t_KY2YSTEKCtK2Icv4EwQxvQc";
char ssid[] = "VELOCITY_JONATHAN";
char pass[] = "0941022956";

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


void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

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


}

void loop() {
  Blynk.run();
  
  digitalWrite(V1_VERDE, HIGH);//Led semaforo verde 1 encendido.
  digitalWrite(P1_ROJO, HIGH);//Led peatonal rojo 1 encendido.
  digitalWrite(V2_ROJO, HIGH);//Led semaforo rojo 2 encendido.
  digitalWrite(P2_VERDE, HIGH);//Led peatonal verde 2 encendido.
  delay(8000);                              //Espera de 3 segundos

  digitalWrite(V1_VERDE, LOW);//Led semaforo verde 1 apagado.
  digitalWrite(V1_AMARILLO, HIGH);//Led semaforo amarillo 1 encendido.
  delay(4000);                              //Espera de 1 segundo

  digitalWrite(V1_AMARILLO, LOW);//Led semaforo amarillo 1 apagado.
  digitalWrite(P1_ROJO, LOW);//Led peatonal rojo 1 apagado.
  digitalWrite(V2_ROJO, LOW);//Led semaforo rojo 2 apagado.
  digitalWrite(P2_VERDE, LOW);//Led peatonal verde 2 apagado.

  digitalWrite(V1_ROJO, HIGH);//Led semaforo rojo 1 encendido.
  digitalWrite(P1_VERDE, HIGH);//Led peatonal verde 1 encendido.
  digitalWrite(V2_VERDE, HIGH);//Led semaforo verde 2 encendido.
  digitalWrite(P2_ROJO, HIGH);//Led peatonal rojo 2 encendido.
  delay(8000);                             //Espera de 3 segundos

  digitalWrite(V2_VERDE, LOW);//Led semaforo verde 2 apagado.
  digitalWrite(V2_AMARILLO, HIGH);//Led semaforo amarillo 2 encendido.
  delay(4000);                             //Espera de 1 segundo

  digitalWrite(V1_ROJO, LOW);//Led semaforo rojo 1 apagado.
  digitalWrite(P1_VERDE, LOW);//Led peatonal verde 1 apagado.
  digitalWrite(V2_AMARILLO, LOW);//Led semaforo amarillo 2 apagado.
  digitalWrite(P2_ROJO, LOW);//Led peatonal rojo 2 apagado.

}
