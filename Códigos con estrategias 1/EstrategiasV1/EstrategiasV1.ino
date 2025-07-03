//Librería
#include <TimerOne.h>

///////////////MOTORES//////////////////
int segMov = 0;
#define T_GIRO 3
#define T_RECTO 6
#define PMW_BUSQ_LENTO 100
#define PMW_BUSQ_RAP 255
#define PMW_ATAQUE_RAP 255
//Derecha
#define PIN_MOTOR_DER_A 1
#define PIN_MOTOR_DER_B 2
#define PIN_PMW_DER 3
int pmwDer = 0;
//Izquierda
#define PIN_MOTOR_IZQ_A 4
#define PIN_MOTOR_IZQ_B 5
#define PIN_PMW_IZQ 6
int pmwIzq = 0;

//////////////SENSORES////////////////
//Distancia
#define DIST_CERCA 20
//Derecha
#define PIN_TRIG_DER 7
#define PIN_ECHO_DER 8
int distDer = 0;
//Centro
#define PIN_TRIG_CEN 9
#define PIN_ECHO_CEN 10
int distCen = 0;
//Izquierda
#define PIN_TRIG_IZQ 11
#define PIN_ECHO_IZQ 12
int distIzq = 0;

//Piso
//Derecha
#define SENS_PISO_DER A0
int pisoDer = 0;
//Izquierda
#define SENS_PISO_IZQ A1
int pisoIzq = 0;

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
#define PIN_BOTON_IZQ 8
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
#define ATAQUE_RAPIDO 3
#define ATAQUE_LENTO 4
#define NOS_CAEMOS 5
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

  //Motores
  pinMode(PIN_MOTOR_DER_A, OUTPUT);
  pinMode(PIN_MOTOR_DER_B, OUTPUT);
  pinMode(PIN_MOTOR_IZQ_A, OUTPUT);
  pinMode(PIN_MOTOR_IZQ_B, OUTPUT);

  //Botones
  pinMode(PIN_BOTON_DER, INPUT_PULLUP);
  pinMode(PIN_BOTON_IZQ, INPUT_PULLUP);

  //Distancia
  /*
pinMode(PIN_TRIG_IZQ, OUTPUT);
  pinMode(PIN_ECHO_IZQ, INPUT);
  digitalWrite(PIN_TRIG_IZQ, LOW);

  pinMode(PIN_TRIG_CEN, OUTPUT);
  pinMode(PIN_ECHO_CEN, INPUT);
  digitalWrite(PIN_TRIG_CEN, LOW);

  pinMode(PIN_TRIG_DER, OUTPUT);
  pinMode(PIN_ECHO_DER, INPUT);
  digitalWrite(PIN_TRIG_DER, LOW);
*/
  Serial.println(estado);
}

void loop() {
  //Motores
  digitalWrite(PIN_PMW_DER, pmwDer);
  digitalWrite(PIN_PMW_IZQ, pmwIzq);

  //Piso
  pisoDer = analogRead(SENS_PISO_DER);
  pisoIzq = analogRead(SENS_PISO_IZQ);

  //Distancia
  /*
  lecturaSensorDistDer = SensorDist(PIN_TRIG_DER, PIN_ECHO_DER);
  lecturaSensorDistCen = SensorDist(PIN_TRIG_CEN, PIN_ECHO_CEN);
  lecturaSensorDistIzq = SensorDist(PIN_TRIG_IZQ, PIN_ECHO_IZQ);
  */

  estados();
}

void estados() {
  switch (estado) {
    Serial.println(estado);

    case INICIO:
      antiReboteBotonDer();
      antiReboteBotonIzq();  //Serial.print("Seleccion: ");Serial.print(seleccion);Serial.print(" | cambio: ");Serial.println(cambioSeleccion);

      boton_Der = flagBotDer;  //Serial.print("Derecha: ");if (boton_Der == PULSADO) {Serial.print("PULSADO");} else {Serial.print("NO PULSADO");}
      boton_Izq = flagBotIzq;  //Serial.print(" | Izquierda: ");if (boton_Izq == PULSADO) {Serial.println("PULSADO");} else {Serial.println("NO PULSADO");}

      //Seleccionar
      //Opciones posibles de seleccion
      int maxOpciones;
      if (seleccion == 0) {
        maxOpciones = MAX_DIR;
      }
      //Selección
      if (boton_Der == PULSADO) {
        flagBotDer = N_PULSADO;
        estrategias = estrategias + 1;
        if (estrategias > maxOpciones) {
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
        maxOpciones = MAX_BUSQ;
        direccion = estrategias;
        estrategias = 1;  //Serial.println("direccion");
        cambioSeleccion = true;
      }
      //Paso a elegir ataque
      if ((seleccion == BUSQUEDA) && (cambioSeleccion == false)) {
        maxOpciones = MAX_ATAQUE;
        busqueda = estrategias + MAX_BUSQ;
        estrategias = 1;  //Serial.println("busqueda");
        cambioSeleccion = true;
      }
      //Inicio el código
      if (seleccion == ATAQUE) {
        maxOpciones = MAX_ATAQUE;
        ataque = estrategias + MAX_ATAQUE;
        estado = BUSQUEDA_LENTA;  //Serial.print("Dirección: "); Serial.print(direccion); Serial.print(" | Busqueda: "); Serial.print(busqueda); Serial.print(" | Ataque: "); Serial.print(ataque);
      }
      break;

    case BUSQUEDA_LENTA:
      Serial.print("LENTA | ");
      distDer = SensorDist(PIN_TRIG_DER, PIN_ECHO_DER);
      distCen = SensorDist(PIN_TRIG_CEN, PIN_ECHO_CEN);
      distIzq = SensorDist(PIN_TRIG_IZQ, PIN_ECHO_IZQ);
      if ((distDer == false) && (distCen == false) && (distIzq == false)) {
        pmwDer = PMW_LENTO;
        pmwIzq = PMW_LENTO;
        if (segMov <= T_GIRO) {
          if (direccion == DERECHA) {
            Serial.print("DERECHA | ");
            derecha();
          }
          if (direccion == IZQUIERDA) {
            Serial.print("IZQUIERDA | ");
            izquierda();
          }
        } else if ((segMov > T_GIRO) && (segMov <= T_RECTO)) {
          adelante();
        }
      }
      if ((distDer == true) && (distCen == true) && (distIzq == true)) {
        estado = ataque;
      }
      break;

    case BUSQUEDA_RAPIDA:
      /*Serial.println("RAPIDA");
      if (direccion == DERECHA){
        Serial.print("DERECHA | ");
      }
      if (direccion == IZQUIERDA){
        Serial.print("IZQUIERDA | ");
      }
      if (ataque == 1)
      {
        Serial.println("RAPIDO");
      }
      if (ataque == 2)
      {
        Serial.println("LENTO");
      }
      */
      break;

    case ATAQUE_RAPIDO:
    pmwDer = PMW_ATAQUE_RAP;
    pmwCen = PMW_ATAQUE_RAP;
    pmwIzq = PMW_ATAQUE_RAP;
    break;
  }
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

//Función de distancia
bool SensorDist(int TRIGGER, int ECHO) {
  long tiempo;    //tiempo que demora en llegar el echo
  long distance;  //distancia en centimetros
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);  //Enviamos un pulso de 10us
  digitalWrite(TRIGGER, LOW);
  tiempo = pulseIn(ECHO, HIGH);  //obtenemos el ancho del pulso
  distance = tiempo / 59;        //escalamos el tiempo a una distancia en cm
  bool cerca = false;
  if (distance <= DIST_CERCA) {
    cerca = true;
  } else {
    cerca = false;
  }
  return (cerca);
}

//Antirrebote derecho
void antiReboteBotonDer(void) {
  bool estadoBotonDer = digitalRead(PIN_BOTON_DER);
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
  bool estadoBotonIzq = digitalRead(PIN_BOTON_IZQ);
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
  if (ms >= 1000) {
    seg = seg + 1;
    segBotonIzq = segBotonIzq + 1;
    segBotonDer = segBotonDer + 1;
    segMov = segMov + 1;
    ms = ms - 1000;
  }
  return;
}