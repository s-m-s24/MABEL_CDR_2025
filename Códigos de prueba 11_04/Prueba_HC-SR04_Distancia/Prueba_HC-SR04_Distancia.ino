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


void setup()
{
pinMode(PIN_TRIG_IZQ, OUTPUT);
pinMode(PIN_ECHO_IZQ, INPUT);
digitalWrite(PIN_TRIG_IZQ, LOW);

pinMode(PIN_TRIG_CEN, OUTPUT);
pinMode(PIN_ECHO_CEN, INPUT);
digitalWrite(PIN_TRIG_CEN, LOW);

pinMode(PIN_TRIG_DER, OUTPUT);
pinMode(PIN_ECHO_DER, INPUT);
digitalWrite(PIN_TRIG_DER, LOW);

Serial.begin(9600);
}

void loop()
{
lecturaSensorDistDer = SensorDist(PIN_TRIG_DER,PIN_ECHO_DER);
lecturaSensorDistCen = SensorDist(PIN_TRIG_CEN,PIN_ECHO_CEN);
lecturaSensorDistIzq = SensorDist(PIN_TRIG_IZQ,PIN_ECHO_IZQ);

Serial.print("Distancia derecha: ");
Serial.print(lecturaSensorDistDer);      //Enviamos serialmente el valor de la distancia
Serial.print("cm");
Serial.print(" / ");
Serial.print("Distancia centro: ");
Serial.print(lecturaSensorDistCen);      //Enviamos serialmente el valor de la distancia
Serial.print("cm");
Serial.print(" / ");
Serial.print("Distancia izquierda: ");
Serial.print(lecturaSensorDistIzq);      //Enviamos serialmente el valor de la distancia
Serial.println("cm");
}

int SensorDist (int TRIGGER, int ECHO)
{
  long tiempo; //tiempo que demora en llegar el echo
  long distance; //distancia en centimetros

  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(TRIGGER, LOW);

  tiempo = pulseIn(ECHO, HIGH); //obtenemos el ancho del pulso
  distance = tiempo / 59;           //escalamos el tiempo a una distancia en cm

  return (distance);
}
