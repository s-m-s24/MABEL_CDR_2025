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
lectPisoDer = analogRead (SENS_PISO_DER);
Serial.println (lectPisoDer);
lectPisoIzq = analogRead (SENS_PISO_IZQ);
Serial.println (lectPisoIzq);
}
