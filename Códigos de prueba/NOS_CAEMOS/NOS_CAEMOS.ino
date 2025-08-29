//Sensor de Piso
//Derecha
#define SENS_PISO_DER A6
int pisoDer = 0;
//Izquierda
#define SENS_PISO_IZQ A7
int pisoIzq = 0;
#define BLANCO 500

#define PIN_LED1 A1
#define PIN_LED2 A2


//Derecha
int const PIN_MOTOR_DER_A = 7;
int const PIN_MOTOR_DER_B = 4;
int const PIN_PMW_DER = 5;
int pmwDer = 0;
//Izquierda
int const PIN_MOTOR_IZQ_A = 3;
int const PIN_MOTOR_IZQ_B = 2;
int const PIN_PMW_IZQ = 6;
int pmwIzq = 0;

void setup() {
  Serial.begin(9600);

  //Motores
  pinMode(PIN_MOTOR_DER_A, OUTPUT);
  pinMode(PIN_MOTOR_DER_B, OUTPUT);
  pinMode(PIN_MOTOR_IZQ_A, OUTPUT);
  pinMode(PIN_MOTOR_IZQ_B, OUTPUT);

  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);

  //Piso
  pinMode(SENS_PISO_IZQ, INPUT);
  pinMode(SENS_PISO_DER, INPUT);
}

void loop() {
  //Motores
  digitalWrite(PIN_PMW_DER, 100);
  digitalWrite(PIN_PMW_IZQ, 100);
  pisoDer = leerPiso(SENS_PISO_DER);
  Serial.print("Derecha: ");
  Serial.println(pisoDer);
  pisoIzq = leerPiso(SENS_PISO_IZQ);
  Serial.print(" | Izquierda: ");
  Serial.println(pisoIzq);

  digitalWrite(PIN_LED2, HIGH);
  digitalWrite(PIN_LED1, LOW);
  if ((pisoDer == true) && (pisoIzq == false)) {  //&&(msMov <= T_GIRO_10)
    izquierda();
    Serial.println("izq");
    delay(10);
  } else if ((pisoDer == false) && (pisoIzq == true))  //&&(msMov <= T_GIRO_10)
  {
    derecha();
    Serial.println("der");
    delay(10);
  } else if ((pisoDer == true) && (pisoIzq == true)) {
    atras();
    delay(10);
  }
}

bool leerPiso(int SENS_PISO) {
  int piso = analogRead(SENS_PISO);
  bool enBlanco = false;
  if (piso <= BLANCO) {
    enBlanco = true;
  }
  return enBlanco;
}


//FUNCIONES MOTORES
void adelante() {  //DER_A, IZQ_A HIGH
  digitalWrite(PIN_MOTOR_DER_A, HIGH);
  digitalWrite(PIN_MOTOR_DER_B, LOW);
  digitalWrite(PIN_MOTOR_IZQ_A, HIGH);
  digitalWrite(PIN_MOTOR_IZQ_B, LOW);
}

void atras() {  //DER_B, IZQ_B HIGH
  digitalWrite(PIN_MOTOR_DER_A, LOW);
  digitalWrite(PIN_MOTOR_DER_B, HIGH);
  digitalWrite(PIN_MOTOR_IZQ_A, LOW);
  digitalWrite(PIN_MOTOR_IZQ_B, HIGH);
}

void izquierda() {  //DER_B, IZQ_A HIGH
  digitalWrite(PIN_MOTOR_DER_A, LOW);
  digitalWrite(PIN_MOTOR_DER_B, HIGH);
  digitalWrite(PIN_MOTOR_IZQ_A, HIGH);
  digitalWrite(PIN_MOTOR_IZQ_B, LOW);
}

void derecha() {  //DER_A, IZQ_B HIGH
  digitalWrite(PIN_MOTOR_DER_A, HIGH);
  digitalWrite(PIN_MOTOR_DER_B, LOW);
  digitalWrite(PIN_MOTOR_IZQ_A, LOW);
  digitalWrite(PIN_MOTOR_IZQ_B, HIGH);
}

void frenar() {  //TODO LOW
  digitalWrite(PIN_MOTOR_DER_A, LOW);
  digitalWrite(PIN_MOTOR_DER_B, LOW);
  digitalWrite(PIN_MOTOR_IZQ_A, LOW);
  digitalWrite(PIN_MOTOR_IZQ_B, LOW);
}