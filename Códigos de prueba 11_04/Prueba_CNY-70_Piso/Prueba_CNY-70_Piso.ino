//Sensor de Piso
//Derecha
#define SENS_PISO_DER A0
int lectPisoDer = 0;
//Izquierda
#define SENS_PISO_IZQ A1  
int lectPisoIzq = 0;

void setup ()
{
Serial.begin (9600); 
}

void loop ()
{
lectPiso1 = analogRead (SENS_PISO1);
Serial.println (lectPiso1)
lectPiso2 = analogRead (SENS_PISO2);
Serial.println (lectPiso2)
}
