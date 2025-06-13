#include <TimerOne.h>

//Motores
int const PIN_PMW_DER = 7;
int const PIN_PMW_IZQ = 6;
int pmwDer = 255;
int pmwIzq = 255;
int const PIN_MOTOR_DER_A = 5;
int const PIN_MOTOR_DER_B = 4;
int const PIN_MOTOR_IZQ_A = 8;
int const PIN_MOTOR_IZQ_B = 3;
int ms = 0;
int seg = 0;

void setup() 
{

  Timer1.initialize(1000); //Cada cuantos milisegundos queremos que interrumpa el timer, en este caso: 1000
  Timer1.attachInterrupt(ISR_Timer); //A dónde queremos ir en la interrupción, en este caso: ISR_Timer (la función más abajo);
  
  digitalWrite(PIN_PMW_DER, pmwDer);
  digitalWrite(PIN_PMW_IZQ, pmwIzq);
  pinMode(PIN_MOTOR_DER_A, OUTPUT);
  pinMode(PIN_MOTOR_DER_B, OUTPUT);
  pinMode(PIN_MOTOR_IZQ_A, OUTPUT);
  pinMode(PIN_MOTOR_IZQ_B, OUTPUT);
}

void loop() 
{
  digitalWrite(PIN_PMW_DER, pmwDer);
  
  /*
  
  digitalWrite(PIN_PMW_DER, pmwDer);
  digitalWrite(PIN_PMW_IZQ, pmwIzq);
  delay (3000);
  pmwDer = pmwDer - 100;
  pmwIzq = pmwIzq - 100;
  
  */
}

//FUNCIONES MOTORES
void adelante()
{
  digitalWrite(PIN_MOTOR_DER_A, HIGH);
  digitalWrite(PIN_MOTOR_DER_B, LOW);

  digitalWrite(PIN_MOTOR_IZQ_A, HIGH);
  digitalWrite(PIN_MOTOR_IZQ_B, LOW);
}

void atras()
{
  digitalWrite(PIN_MOTOR_DER_A, LOW);
  digitalWrite(PIN_MOTOR_DER_B, HIGH);

  digitalWrite(PIN_MOTOR_IZQ_A, LOW);
  digitalWrite(PIN_MOTOR_IZQ_B, HIGH);
}

void izquierda()
{
  digitalWrite(PIN_MOTOR_DER_A, LOW);
  digitalWrite(PIN_MOTOR_DER_B, HIGH);

  digitalWrite(PIN_MOTOR_IZQ_A, HIGH);
  digitalWrite(PIN_MOTOR_IZQ_B, LOW);
}

void derecha()
{
  digitalWrite(PIN_MOTOR_DER_A, HIGH);
  digitalWrite(PIN_MOTOR_DER_B, LOW);

  digitalWrite(PIN_MOTOR_IZQ_A, LOW);
  digitalWrite(PIN_MOTOR_IZQ_B, HIGH);
}

void frenar()
{
  digitalWrite(PIN_MOTOR_DER_A, LOW);
  digitalWrite(PIN_MOTOR_DER_B, LOW);

  digitalWrite(PIN_MOTOR_IZQ_A, LOW);
  digitalWrite(PIN_MOTOR_IZQ_B, LOW);
}

//Función del timer
void ISR_Timer(void) //Crea la función de qué va a hacer cuando se produzca una interrupción
{
  ms = ms + 1;
  if (ms >= 1000)
  {
    seg = seg + 1;
    ms = ms - 1000;
  }
  return;
}


