//Librería
#include <TimerOne.h>
#include <ShiftRegister74HC595.h>

///////////////MOTORES//////////////////
int msMov = 0;
#define T_GIRO_10 10
#define T_GIRO_90 100
#define T_RECTO 100
#define PMW_BUSQ_LENTO 100
#define PMW_BUSQ_RAP 150
#define PMW_ATAQUE_LENTO 100
#define PMW_ATAQUE_RAP 150
#define PMW_GIRO 150

// --- Mapeo de salidas según tu primer esquema ---
#define LED1 5   // QB (pin 1 del 74HC595)
#define LED2 6   // QC (pin 2)
#define LED3 7   // QD (pin 3)
#define LED4 15  // QD (pin 3)

// --- Pines Arduino Nano conectados al 74HC595 ---
#define DATA_PIN 11   // SER (pin 14 del 74HC595)
#define CLOCK_PIN 9   // SRCLK / SH_CP (pin 11 del 74HC595)
#define LATCH_PIN 10  // RCLK / ST_CP (pin 12 del 74HC595)


ShiftRegister74HC595<1> sr(DATA_PIN, CLOCK_PIN, LATCH_PIN);

#define AIN1 4  // Q4
#define AIN2 3  // Q3
#define BIN1 1  // Q1
#define BIN2 2  // Q2
// PWM directo desde Arduino
#define PMWA 5  // PWM Motor A
#define PMWB 6  // PWM Motor B
//Funciones de movimiento
void buscar(void);
#define AVANZO 0
#define GIRO 1
int estadoBuscar = AVANZO;
void centrar(int);

//////////////SENSORES////////////////
//Distancia
#define DIST_CERCA 20
//Derecha
#define PIN_TRIG_DER 12
#define PIN_ECHO_DER 8
int distDer = 0;
//Centro
#define PIN_TRIG_CEN 7
#define PIN_ECHO_CEN 4
int distCen = 0;
//Izquierda
#define PIN_TRIG_IZQ 3
#define PIN_ECHO_IZQ 2
int distIzq = 0;

int pmwDer = 150;
int pmwIzq = 150;

//Piso
//Derecha
#define SENS_PISO_DER 5
bool pisoDer = false;
//Izquierda
#define SENS_PISO_IZQ 4
bool pisoIzq = false;
//Blanco y negro
#define BLANCO 400
bool leerPiso(int);

/////////BOTONES/////////
//Común
#define PULSADO LOW
#define N_PULSADO HIGH
#define T_REBOTE 1

//Derecha
#define PIN_BOTON_DER 7
//Antirrebote derecho
void antiReboteBotonDer(void);
#define ESPERA_BOT_DER 1
#define CONFIRMACION_BOT_DER 2
#define LIBERACION_BOT_DER 3
bool flagBotDer = N_PULSADO;
int maqBotonDer = ESPERA_BOT_DER;
int segBotonDer = 0;
//Lectura
bool boton_Der = N_PULSADO;

//Izquierda
#define PIN_BOTON_IZQ 6
//Antirrebote izquierdo
void antiReboteBotonIzq(void);
#define ESPERA_BOT_IZQ 1
#define CONFIRMACION_BOT_IZQ 2
#define LIBERACION_BOT_IZQ 3
bool flagBotIzq = N_PULSADO;
int maqBotonIzq = ESPERA_BOT_IZQ;
int segBotonIzq = 0;
//Lectura
bool boton_Izq = N_PULSADO;


/////////////TIMER//////////////
int ms = 0;
int seg = 0;

////////MAQUINA DE ESTADOS//////////
//Estados
#define INICIO 0
#define BUSQUEDA_LENTA 1
#define BUSQUEDA_RAPIDA 2
#define CENTRAR 3
#define ATAQUE_LENTO 4
#define ATAQUE_RAPIDO 5
#define NOS_CAEMOS 6
int estado = INICIO;

//Selección
int estrategias = 1;
int seleccion = 0;
bool cambioSeleccion = false;
//Dirección
#define DIRECCION 1
#define MAX_DIR 2
//Búsqueda
#define BUSQUEDA 2
#define MAX_BUSQ 2
//Ataque
#define ATAQUE 3
#define MAX_ATAQUE 2

//Estrategias
int direccion;
int busqueda;
int ataque;
//Dirección
#define DERECHA 1
#define IZQUIERDA 2


void setup() {
  Serial.begin(9600);

  Timer1.initialize(1000);            //Cada cuantos milisegundos queremos que interrumpa el timer, en este caso: 1000
  Timer1.attachInterrupt(ISR_Timer);  //A dónde queremos ir en la interrupción, en este caso: ISR_Timer (la función más abajo);

  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);

  //Botones
  pinMode(PIN_BOTON_DER, INPUT);
  pinMode(PIN_BOTON_IZQ, INPUT);

  //Distancia
  pinMode(PIN_TRIG_IZQ, OUTPUT);
  pinMode(PIN_ECHO_IZQ, INPUT);
  digitalWrite(PIN_TRIG_IZQ, LOW);

  pinMode(PIN_TRIG_CEN, OUTPUT);
  pinMode(PIN_ECHO_CEN, INPUT);
  digitalWrite(PIN_TRIG_CEN, LOW);

  pinMode(PIN_TRIG_DER, OUTPUT);
  pinMode(PIN_ECHO_DER, INPUT);
  digitalWrite(PIN_TRIG_DER, LOW);

  //Piso
  pinMode(SENS_PISO_IZQ, INPUT);
  pinMode(SENS_PISO_DER, INPUT);

  Serial.println(estado);
  sr.setAllLow();
}

void loop() {
  //Motores
  //digitalWrite(PMWA, pmwDer);
  //digitalWrite(PMWB, pmwIzq);

  //Piso
  pisoDer = leerPiso(SENS_PISO_DER);
  pisoIzq = leerPiso(SENS_PISO_IZQ);

  estados();
}

void estados() {
  switch (estado) {
    Serial.println(estado);

    case INICIO:
      delay(100);
      antiReboteBotonDer();
      antiReboteBotonIzq();

      Serial.print("Seleccion: ");
      Serial.print(seleccion);
      Serial.print(" | cambio: ");
      Serial.println(cambioSeleccion);

      boton_Der = flagBotDer;
      Serial.print("Derecha: ");
      if (boton_Der == PULSADO) {
        Serial.print("PULSADO");
      } else {
        Serial.print("NO PULSADO");
      }
      boton_Izq = flagBotIzq;
      Serial.print(" | Izquierda: ");
      if (boton_Izq == PULSADO) {
        Serial.println("PULSADO");
      } else {
        Serial.println("NO PULSADO");
      }

      //Seleccionar
      //Opciones posibles de seleccion
      int maxOpciones;
      if (seleccion == 0) {
        maxOpciones = 2;
      }
      //Selección
      if (boton_Der == PULSADO) {
        flagBotDer = N_PULSADO;
        estrategias = estrategias + 1;
        if (estrategias > 2) {
          estrategias = 1;
        }
        Serial.println(estrategias);
      }
      //Lo que quiero seleccionar
      if (boton_Izq == PULSADO) {
        flagBotIzq = N_PULSADO;
        seleccion = seleccion + 1;
        cambioSeleccion = false;
      }

      //Gurado seleccion
      //Paso a elegir búsqueda
      if ((seleccion == DIRECCION) && (cambioSeleccion == false)) {
        maxOpciones = 2;
        direccion = estrategias;
        estrategias = 1;
        Serial.println("direccion");
        cambioSeleccion = true;
        sr.set(LED1, HIGH);
      }
      //Paso a elegir ataque
      if ((seleccion == BUSQUEDA) && (cambioSeleccion == false)) {
        maxOpciones = 2;
        busqueda = estrategias + 1;
        estrategias = 1;
        Serial.println("busqueda");
        cambioSeleccion = true;
        sr.set(LED2, HIGH);
      }
      //Inicio el código
      if (seleccion == ATAQUE) {
        maxOpciones = 2;
        delay(5000);
        sr.set(LED4, HIGH);
        ataque = estrategias + 3;
        estado = busqueda;
        Serial.print("Dirección: ");
        Serial.print(direccion);
        Serial.print(" | Busqueda: ");
        Serial.print(busqueda);
        Serial.print(" | Ataque: ");
        Serial.print(ataque);
        sr.set(LED3, HIGH);
      }
      break;

    case BUSQUEDA_LENTA:
      Serial.print("BUSCA | ");
      distDer = SensorDist(PIN_TRIG_DER, PIN_ECHO_DER);
      distCen = SensorDist(PIN_TRIG_CEN, PIN_ECHO_CEN);
      distIzq = SensorDist(PIN_TRIG_IZQ, PIN_ECHO_IZQ);
      Serial.print(distDer);
      Serial.print(" | ");
      Serial.print(distCen);
      Serial.print(" | ");
      Serial.println(distIzq);

      pmwDer = PMW_BUSQ_LENTO;  //SENS: ROJO, AMARILLO, NARANJA, VERDE

      pmwIzq = PMW_BUSQ_LENTO;  //PLACA: ROJO, VERDE, NARANJA, AMARILLO

      if ((pisoDer == true) || (pisoIzq == true)) {
        estado = NOS_CAEMOS;
      }
      if (distCen == true) {
        estado = ataque;
      } else if ((distDer == false) && (distCen == false) && (distIzq == false)) {
        buscar(PMW_BUSQ_LENTO);
      } else if ((distIzq == true) || (distDer == true)) {
        centrar(PMW_BUSQ_LENTO);
      }
      break;

    case BUSQUEDA_RAPIDA:
      distDer = SensorDist(PIN_TRIG_DER, PIN_ECHO_DER);
      distCen = SensorDist(PIN_TRIG_CEN, PIN_ECHO_CEN);
      distIzq = SensorDist(PIN_TRIG_IZQ, PIN_ECHO_IZQ);
      Serial.print(distDer);
      Serial.print(" | ");
      Serial.print(distCen);
      Serial.print(" | ");
      Serial.println(distIzq);


      pmwDer = PMW_ATAQUE_RAP;
      pmwIzq = PMW_ATAQUE_RAP;

      if ((pisoDer == true) || (pisoIzq == true)) {
        estado = NOS_CAEMOS;
      }
      if (distCen == true) {
        estado = ataque;
      } else if ((distDer == false) && (distCen == false) && (distIzq == false)) {
        buscar(PMW_ATAQUE_RAP);
      } else if ((distIzq == true) || (distDer == true)) {
        centrar(PMW_ATAQUE_RAP);
      }
      break;

    case ATAQUE_RAPIDO:
      Serial.print("ATAQUE RAPIDO");
      Serial.print(" | ");
      Serial.println(distCen);

      distCen = SensorDist(PIN_TRIG_CEN, PIN_ECHO_CEN);
      pmwDer = PMW_ATAQUE_LENTO;
      pmwIzq = PMW_ATAQUE_LENTO;
      motorA_adelante(PMW_ATAQUE_RAP);
      motorB_adelante(PMW_ATAQUE_RAP);
      if (distCen == false) {
        estado = busqueda;
      }
      break;

    case NOS_CAEMOS:
      Serial.print("CAEMOS |");
      Serial.print(pisoDer);
      Serial.print(" | ");
      Serial.println(pisoIzq);
      if ((pisoDer == true) && (pisoIzq == false)) {  //&&(msMov <= T_GIRO_10)
        motorB_atras(PMW_ATAQUE_RAP);
        motorA_adelante(PMW_ATAQUE_RAP);
        delay(10);
      } else if ((pisoDer == false) && (pisoIzq == true))  //&&(msMov <= T_GIRO_10)
      {
        motorB_adelante(PMW_ATAQUE_RAP);
        motorA_atras(PMW_ATAQUE_RAP);
        delay(10);
      } else if ((pisoDer == true) && (pisoIzq == true)) {
        motorA_atras(PMW_ATAQUE_RAP);
        motorB_atras(PMW_ATAQUE_RAP);
        delay(10);
      } else if (msMov > T_GIRO_10) {
        msMov = 0;
        estado = busqueda;
      }
      break;

    case ATAQUE_LENTO:
      {
        Serial.println("ATAQUE LENTO");
        Serial.print(" | ");
        Serial.println(distCen);
        distCen = SensorDist(PIN_TRIG_CEN, PIN_ECHO_CEN);
        pmwDer = PMW_ATAQUE_LENTO;
        pmwIzq = PMW_ATAQUE_LENTO;
        motorA_adelante(PMW_ATAQUE_LENTO);
        motorB_adelante(PMW_ATAQUE_LENTO);
        if (distCen == false) {
          estado = busqueda;
        }
      }
  }
}
void motorA_adelante(int pmw) {
  sr.set(AIN1, LOW);
  sr.set(AIN2, HIGH);
  sr.updateRegisters();  // update the pins to the set values
  analogWrite(PMWA, pmw);
}

void motorA_atras(int pmw) {
  sr.set(AIN1, HIGH);
  sr.set(AIN2, LOW);
  sr.updateRegisters();  // update the pins to the set values
  analogWrite(PMWA, pmw);
}

void motorA_stop(int pmw) {
  sr.set(AIN1, LOW);
  sr.set(AIN2, LOW);
  sr.updateRegisters();  // update the pins to the set values
  analogWrite(PMWA, pmw);
}

void motorB_adelante(int pmw) {
  sr.set(BIN1, HIGH);
  sr.set(BIN2, LOW);
  sr.updateRegisters();  // update the pins to the set values
  analogWrite(PMWB, pmw);
}

void motorB_atras(int pmw) {
  sr.set(BIN1, LOW);
  sr.set(BIN2, HIGH);
  sr.updateRegisters();  // update the pins to the set values
  analogWrite(PMWB, pmw);
}

void motorB_stop(int pmw) {
  sr.set(BIN1, LOW);
  sr.set(BIN2, LOW);
  sr.updateRegisters();  // update the pins to the set values
  analogWrite(PMWB, pmw);
}

//Función de distancia
bool SensorDist(int TRIGGER, int ECHO) {
  long tiempo;    //tiempo que demora en llegar el echo
  long distance;  //distancia en centimetros
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);  //Enviamos un pulso de 10us
  digitalWrite(TRIGGER, LOW);
  tiempo = pulseIn(ECHO, HIGH);  //obtenemos el ancho del pulso
  distance = tiempo / 59;        //escalamos el tiempo a una distancia en cm
  //Serial.println(distance);
  bool cerca = false;
  if (distance <= DIST_CERCA) {
    cerca = true;
  } else {
    cerca = false;
  }
  return cerca;
}

//Antirrebote derecho
void antiReboteBotonDer(void) {
  bool estadoBotonDer = analogRead(PIN_BOTON_DER);
  switch (maqBotonDer) {
    case ESPERA_BOT_DER:
      if (estadoBotonDer == PULSADO) {
        segBotonDer = 0;
        maqBotonDer = CONFIRMACION_BOT_DER;
      }
      break;
    case CONFIRMACION_BOT_DER:
      estadoBotonDer = digitalRead(PIN_BOTON_DER);
      if ((segBotonDer >= T_REBOTE) && (estadoBotonDer == N_PULSADO)) {
        maqBotonDer = ESPERA_BOT_DER;
      }
      if ((segBotonDer >= T_REBOTE) && (estadoBotonDer == PULSADO)) {
        maqBotonDer = LIBERACION_BOT_DER;
      }
      break;
    case LIBERACION_BOT_DER:
      if (estadoBotonDer == N_PULSADO) {
        flagBotDer = PULSADO;
        maqBotonDer = ESPERA_BOT_DER;
      }
      break;
  }
}

//Antirrebote izquierdo
void antiReboteBotonIzq(void) {
  bool estadoBotonIzq = analogRead(PIN_BOTON_IZQ);
  switch (maqBotonIzq) {
    case ESPERA_BOT_IZQ:
      if (estadoBotonIzq == PULSADO) {
        segBotonIzq = 0;
        maqBotonIzq = CONFIRMACION_BOT_IZQ;
      }
      break;
    case CONFIRMACION_BOT_IZQ:
      estadoBotonIzq = digitalRead(PIN_BOTON_IZQ);
      if ((segBotonIzq >= T_REBOTE) && (estadoBotonIzq == N_PULSADO)) {
        maqBotonIzq = ESPERA_BOT_IZQ;
      }
      if ((segBotonIzq >= T_REBOTE) && (estadoBotonIzq == PULSADO)) {
        maqBotonIzq = LIBERACION_BOT_IZQ;
      }
      break;
    case LIBERACION_BOT_IZQ:
      if (estadoBotonIzq == N_PULSADO) {
        flagBotIzq = PULSADO;
        maqBotonIzq = ESPERA_BOT_DER;
      }
      break;
  }
}

//Función del timer
void ISR_Timer(void)  //Crea la función de qué va a hacer cuando se produzca una interrupción
{
  ms = ms + 1;
  msMov = msMov + 1;
  if (ms >= 1000) {
    seg = seg + 1;
    segBotonIzq = segBotonIzq + 1;
    segBotonDer = segBotonDer + 1;
    ms = ms - 1000;
  }
  return;
}

void buscar(int pmw) {
  Serial.println("BUSCAR");
  switch (estadoBuscar) {
    case AVANZO:
      motorA_adelante(pmw);
      motorB_adelante(pmw);
      if (msMov >= T_RECTO) {
        estadoBuscar = GIRO;
        msMov = 0;
      }
      break;

    case GIRO:
      pmwDer = PMW_BUSQ_RAP;
      pmwIzq = PMW_BUSQ_RAP;
      if ((msMov >= T_GIRO_10) && (direccion == DERECHA)) {
        //Serial.print("DERECHA | ");
        motorA_atras(pmw);
        motorB_adelante(pmw);
      }
      if ((msMov >= T_GIRO_10) && (direccion == IZQUIERDA)) {
        //Serial.print("IZQUIERDA | ");
        motorB_atras(pmw);
        motorA_adelante(pmw);
      }
      if (msMov >= T_GIRO_10) {
        estadoBuscar = AVANZO;
        msMov = 0;
      }
      break;
  }
  return;
}

void centrar(int pmw) {
  if ((distIzq == true) && (distCen == false)) {
    motorA_atras(pmw);
    motorB_adelante(pmw);
    Serial.println("der");
  } else if ((distDer == true) && (distCen == false)) {
    motorA_adelante(pmw);
    motorB_atras(pmw);
    Serial.println("izq");
  }
  return;
}

bool leerPiso(int SENS_PISO) {
  int piso = analogRead(SENS_PISO);
  bool enBlanco = false;
  if (piso <= BLANCO) {
    enBlanco = true;
  }
  return enBlanco;
}
