int V1_rojo = D0;
int V1_amarillo = D1;
int V1_verde = D2;

int V2_rojo = D3;
int V2_amarillo = D4;
int V2_verde = D5;

int P1_rojo = D6;
int P1_verde = D7;

int P2_rojo = D8;
int P2_verde = 3;

const int D = 100;

void setup() {
  // put your setup code here, to run once:
pinMode(V1_rojo, OUTPUT);
pinMode(V1_amarillo, OUTPUT);
pinMode(V1_verde, OUTPUT);

pinMode(V2_rojo, OUTPUT);
pinMode(V2_amarillo, OUTPUT);
pinMode(V2_verde, OUTPUT);

pinMode(P1_rojo, OUTPUT);
pinMode(P1_verde, OUTPUT);

pinMode(P2_rojo, OUTPUT);
pinMode(P2_verde, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

digitalWrite(V1_rojo, HIGH);
delay(D);
digitalWrite(V1_amarillo, HIGH);
delay(D);
digitalWrite(V1_verde, HIGH);
delay(D);

digitalWrite(V2_rojo, HIGH);
delay(D);
digitalWrite(V2_amarillo, HIGH);
delay(D);
digitalWrite(V2_verde, HIGH);
delay(D);

digitalWrite(P1_rojo, HIGH);
delay(D);
digitalWrite(P1_verde, HIGH);
delay(D);

digitalWrite(P2_rojo, HIGH);
delay(D);
digitalWrite(P2_verde, HIGH);
delay(D);

digitalWrite(V1_rojo, LOW);
delay(D);
digitalWrite(V1_amarillo, LOW);
delay(D);
digitalWrite(V1_verde, LOW);
delay(D);

digitalWrite(V2_rojo, LOW);
delay(D);
digitalWrite(V2_amarillo, LOW);
delay(D);
digitalWrite(V2_verde, LOW);
delay(D);

digitalWrite(P1_rojo, LOW);
delay(D);
digitalWrite(P1_verde, LOW);
delay(D);

digitalWrite(P2_rojo, LOW);
delay(D);
digitalWrite(P2_verde, LOW);
delay(D);

}
