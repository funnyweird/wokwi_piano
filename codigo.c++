// Código para piano no Wokwi
// Este é um exemplo básico de código C++ para um piano digital

#include <Arduino.h>

// Definição dos pinos para as teclas do piano
const int teclas[] = {2, 3, 4, 5, 6, 7, 8, 9};
const int buzzer = 10;

// Frequências das notas musicais
const int frequencias[] = {
  262, // C4
  294, // D4
  330, // E4
  349, // F4
  392, // G4
  440, // A4
  494, // B4
  523  // C5
};

void setup() {
  Serial.begin(9600);
  
  // Configurar pinos das teclas como entrada com pull-up
  for (int i = 0; i < 8; i++) {
    pinMode(teclas[i], INPUT_PULLUP);
  }
  
  // Configurar buzzer como saída
  pinMode(buzzer, OUTPUT);
  
  Serial.println("Piano Digital Iniciado!");
  Serial.println("Pressione as teclas para tocar as notas...");
}

void loop() {
  // Verificar cada tecla
  for (int i = 0; i < 8; i++) {
    if (digitalRead(teclas[i]) == LOW) {
      // Tecla pressionada - tocar nota
      tone(buzzer, frequencias[i]);
      Serial.print("Tocando nota ");
      Serial.print(i + 1);
      Serial.print(" - Frequência: ");
      Serial.println(frequencias[i]);
      
      // Aguardar tecla ser solta
      while (digitalRead(teclas[i]) == LOW) {
        delay(10);
      }
      
      // Parar o som
      noTone(buzzer);
    }
  }
  
  delay(10);
}
