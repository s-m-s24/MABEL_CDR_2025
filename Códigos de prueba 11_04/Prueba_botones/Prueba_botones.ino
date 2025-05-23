//Botones de estrategias
#define PIN_BOTON_DER A2
#define PIN_BOTON_IZQ A3
bool lectura_Boton_Der = N_PULSADO;
bool lectura_Boton_Izq = N_PULSADO;
#define PULSADO HIGH
#define N_PULSADO LOW


void setup() {
//Botones
  pinMode(PIN_BOTON_DER,INPUT);
  pinMode(PIN_BOTON_IZQ,INPUT);
}

void loop() {
lectura_Boton_Izq = digitalRead();
if (lectura_Boton_Izq == PULSADO){
  Serial.println("PULSADO");
  }
else {
  Serial.println("NO PULSADO");
  }
  
lectura_Boton_Der = digitalRead();
if (lectura_Boton_Der == PULSADO){
  Serial.println("PULSADO");
  }
else {
  Serial.println("NO PULSADO");
  }
}
