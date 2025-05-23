#include <TimerOne.h>

//Motores y PMW
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

//Sensor de Distancia
//Derecha
#define PIN_TRIG_DER 7
#define PIN_ECHO_DER 8 
int lecturaSensorDistDer = 0;  
//Centro
#define PIN_TRIG_CEN 9
#define PIN_ECHO_CEN 10 
int lecturaSensorDistCen = 0;
//Izquierda
#define PIN_TRIG_IZQ 11
#define PIN_ECHO_IZQ 12 
int lecturaSensorDistIzq = 0;

//Sensor de Piso
//Derecha
#define SENS_PISO_DER A0
int lectPisoDer = 0;
//Izquierda
#define SENS_PISO_IZQ A1  
int lectPisoIzq = 0;

//Timer
int ms = 0;
int seg = 0;

//Estrategias
int estrategiaDeBúsqueda = BUSQUEDA_RÁPIDA;
int estrategiaDeAtaque = ATAQUE 3;

//Estrategias de búsqueda y ataque
//Estados
#define INICIO 0
#define BUSQUEDA_RÁPIDA 1
#define BUSQUEDA_LENTA 2
#define ATAQUE_RÁPIDO 3
#define ATAQUE_LENTO 3
#define NOS_CAEMOS 4
//Dirección
#define DERECHA LOW
#define IZQUIERDA HIGH
bool DIR_ARRANQUE = DERECHA;

//Botones de estrategias
#define PIN_BOTON_DER A2
#define PIN_BOTON_IZQ A3
#define PULSADO HIGH
#define N_PULSADO LOW
bool lectura_Boton_Der = N_PULSADO;
bool lectura_Boton_Izq = N_PULSADO;

void setup() 
{
  Serial.begin(9600);
  
  Timer1.initialize(1000); //Cada cuantos milisegundos queremos que interrumpa el timer, en este caso: 1000
  Timer1.attachInterrupt(ISR_Timer); //A dónde queremos ir en la interrupción, en este caso: ISR_Timer (la función más abajo);

  //Motores
  pinMode(PIN_MOTOR_DER_A, OUTPUT);
  pinMode(PIN_MOTOR_DER_B, OUTPUT);
  pinMode(PIN_MOTOR_IZQ_A, OUTPUT);
  pinMode(PIN_MOTOR_IZQ_B, OUTPUT);
}

void loop() 
{ 
  digitalWrite(PIN_PMW_DER, pmwDer);
  digitalWrite(PIN_PMW_IZQ, pmwIzq);

}

//FUNCIONES MOTORES
void adelante()
{//DER_A, IZQ_A HIGH
  digitalWrite(PIN_MOTOR_DER_A, HIGH);
  digitalWrite(PIN_MOTOR_DER_B, LOW);
  digitalWrite(PIN_MOTOR_IZQ_A, HIGH);
  digitalWrite(PIN_MOTOR_IZQ_B, LOW);
}

void atras()
{//DER_B, IZQ_B HIGH
  digitalWrite(PIN_MOTOR_DER_A, LOW);
  digitalWrite(PIN_MOTOR_DER_B, HIGH);
  digitalWrite(PIN_MOTOR_IZQ_A, LOW);
  digitalWrite(PIN_MOTOR_IZQ_B, HIGH);
}

void izquierda()
{//DER_B, IZQ_A HIGH
  digitalWrite(PIN_MOTOR_DER_A, LOW);
  digitalWrite(PIN_MOTOR_DER_B, HIGH);
  digitalWrite(PIN_MOTOR_IZQ_A, HIGH);
  digitalWrite(PIN_MOTOR_IZQ_B, LOW);
}

void derecha()
{//DER_A, IZQ_B HIGH
  digitalWrite(PIN_MOTOR_DER_A, HIGH);
  digitalWrite(PIN_MOTOR_DER_B, LOW);
  digitalWrite(PIN_MOTOR_IZQ_A, LOW);
  digitalWrite(PIN_MOTOR_IZQ_B, HIGH);
}

void frenar()
{//TODO LOW
  digitalWrite(PIN_MOTOR_DER_A, LOW);
  digitalWrite(PIN_MOTOR_DER_B, LOW);
  digitalWrite(PIN_MOTOR_IZQ_A, LOW);
  digitalWrite(PIN_MOTOR_IZQ_B, LOW);
}
