#include <ShiftRegister74HC595.h>


// --- Pines Arduino Nano conectados al 74HC595 ---
#define DATA_PIN 11  // SER (pin 14 del 74HC595)
#define CLOCK_PIN 9  // SRCLK / SH_CP (pin 11 del 74HC595)
#define LATCH_PIN 10  // RCLK / ST_CP (pin 12 del 74HC595)


// --- Mapeo de salidas según tu primer esquema ---
#define AIN1 1   // QB (pin 1 del 74HC595)
#define AIN2 2  // QC (pin 2)
#define BIN1 3   // QD (pin 3)
#define BIN2 4  // QD (pin 3)

#define PMWA 5
#define PMWB 6


ShiftRegister74HC595<1> sr(DATA_PIN, CLOCK_PIN, LATCH_PIN);


void setup() {
  // put your setup code here, to run once:
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);

  pinMode(PMWA, OUTPUT);
  pinMode(PMWB, OUTPUT);
}


void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(PMWA, HIGH);
  digitalWrite(PMWB, HIGH);
  sr.setAllHigh();
  delay(5000);
  sr.setAllLow();
  sr.set(AIN1, HIGH);
  sr.set(AIN2, LOW);
  sr.set(BIN1, HIGH);
  sr.set(BIN2, LOW);
  delay(5000);
  sr.set(AIN1, LOW);
  sr.set(AIN2, HIGH);
  sr.set(BIN1, LOW);
  sr.set(BIN2, HIGH);
  delay(5000);
}


