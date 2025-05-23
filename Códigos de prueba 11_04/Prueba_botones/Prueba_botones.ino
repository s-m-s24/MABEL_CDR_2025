//Botones de estrategias
#define PIN_BOTON_DER A2
#define PIN_BOTON_IZQ A3
#define PULSADO HIGH
#define N_PULSADO LOW
bool lectura_Boton_Der = N_PULSADO;
bool lectura_Boton_Izq = N_PULSADO;

void setup() {
  //Botones
  Serial.begin(9600);
}

void loop() {
  lectura_Boton_Der = digitalRead(PIN_BOTON_DER);
  if (lectura_Boton_Der == PULSADO) {
    Serial.println("PULSADO");
  }
  else {
    Serial.println("NO PULSADO");
  }
  lectura_Boton_Izq = digitalRead(PIN_BOTON_IZQ);
  if (lectura_Boton_Izq == PULSADO) {
    Serial.println("PULSADO");
  }
  else {
    Serial.println("NO PULSADO");
  }
}
