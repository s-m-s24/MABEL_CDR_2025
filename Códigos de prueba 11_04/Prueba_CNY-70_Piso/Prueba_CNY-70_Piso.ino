int const SENS_PISO1 = A0;  
int lectPiso1 = 0;

void setup ()
{
pinMode (SENS_PISO1,INPUT); //(probablemente innecesario)
Serial.begin (9600); 
}

void loop ()
{
lectPiso1 = analogRead (SENS_PISO1);
Serial.println (lectPiso1)
}
