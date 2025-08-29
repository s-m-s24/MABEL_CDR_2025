#include <ShiftRegister74HC595.h>

// Pines Arduino -> 74HC595
#define DATA_PIN 11
#define CLOCK_PIN 9
#define LATCH_PIN 10

// Map entradas Monster
#define AIN1 4  // Q4
#define AIN2 3  // Q3
#define BIN1 1  // Q1
#define BIN2 2  // Q2

// PWM directo desde Arduino
#define PMWA 5  // PWM Motor A
#define PMWB 6  // PWM Motor B

ShiftRegister74HC595<1> sr(DATA_PIN, CLOCK_PIN, LATCH_PIN);
//ShiftRegister74HC595<1> sr(11, 9, 10);

// ---------- Funciones de control ----------
void motorA_adelante() {
  sr.set(AIN1, LOW);
  sr.set(AIN2, HIGH);
  sr.updateRegisters();  // update the pins to the set values
}

void derecha() {
  sr.set(AIN1, LOW);
  sr.set(AIN2, HIGH);
  sr.updateRegisters();  // update the pins to the set values
    sr.set(BIN1, LOW);
  sr.set(BIN2, HIGH);
  sr.updateRegisters();  // update the pins to the set values
}

void motorA_atras() {
  sr.set(AIN1, HIGH);
  sr.set(AIN2, LOW);
  sr.updateRegisters();  // update the pins to the set values
}

void motorA_stop() {
  sr.set(AIN1, LOW);
  sr.set(AIN2, LOW);
  sr.updateRegisters();  // update the pins to the set values
}

void motorB_adelante() {
  sr.set(BIN1, HIGH);
  sr.set(BIN2, LOW);
  sr.updateRegisters();  // update the pins to the set values
}

void motorB_atras() {
  sr.set(BIN1, LOW);
  sr.set(BIN2, HIGH);
  sr.updateRegisters();  // update the pins to the set values
}

void motorB_stop() {
  sr.set(BIN1, LOW);
  sr.set(BIN2, LOW);
  sr.updateRegisters();  // update the pins to the set values
}

// ------------------------------------------

void setup() {
  pinMode(PMWA, OUTPUT);
  pinMode(PMWB, OUTPUT);
}

void loop() {
  // Velocidad máxima
  analogWrite(PMWA, 100);
  analogWrite(PMWB, 100);
  derecha();
}
