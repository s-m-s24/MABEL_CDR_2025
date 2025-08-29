//Sensor de Piso
//Derecha
#define SENS_PISO_DER A5
int lectPisoDer = 0;
//Izquierda
#define SENS_PISO_IZQ A4
int lectPisoIzq = 0;

void setup ()
{
Serial.begin (9600); 
}

void loop ()
{
lectPisoDer = analogRead (SENS_PISO_DER);
Serial.print("Derecha: ");
Serial.print (lectPisoDer);
lectPisoIzq = analogRead (SENS_PISO_IZQ);
Serial.print(" | Izquierda: ");
Serial.println (lectPisoIzq);
}
