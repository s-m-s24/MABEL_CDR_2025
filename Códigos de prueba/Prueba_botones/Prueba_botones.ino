//Botones de estrategias
#define PIN_BOTON_DER 7
#define PIN_BOTON_IZQ 8
#define PULSADO LOW
#define N_PULSADO HIGH
bool lectura_Boton_Der = N_PULSADO;
bool lectura_Boton_Izq = N_PULSADO;

void setup() {
  //Botones
  pinMode(PIN_BOTON_DER,INPUT_PULLUP);
  pinMode(PIN_BOTON_IZQ,INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  lectura_Boton_Der = digitalRead(PIN_BOTON_DER);
  Serial.print("Derecha: ");
  if (lectura_Boton_Der == PULSADO) {
    Serial.print("PULSADO");
  }
  else {
    Serial.print("NO PULSADO");
  }
  lectura_Boton_Izq = digitalRead(PIN_BOTON_IZQ);
  Serial.print(" | Izquierda: ");
  if (lectura_Boton_Izq == PULSADO) {
    Serial.println("PULSADO");
  }
  else {
    Serial.println("NO PULSADO");
  }
}
