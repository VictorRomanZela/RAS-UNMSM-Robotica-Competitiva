#include <SoftwareSerial.h>

// CONFIGURACIÓN DEL BLUETOOTH HC-05 

// PINES DEL MOTOR IZQUIERDO
#define PWMA 5  
#define AIN1 2  
#define AIN2 7  

// PINES DEL MOTOR DERECHO
#define PWMB 6  
#define BIN1 8  
#define BIN2 12 

// PIN DE ACTIVACIÓN DEL DRIVER 
#define STBY 9  

char estado = 'S'; 


int velMaxima = 255;
int velGiro = 150;  

void setup() {
  BT.begin(9600);
  
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  
  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH); 
}

void loop() {
  if (BT.available() > 0) {
    estado = BT.read();
  }

  // LÓGICA DE MOVIMIENTO
  switch (estado) {
    
    case 'F': // Adelante
      analogWrite(PWMA, velMaxima); 
      analogWrite(PWMB, velMaxima);
      digitalWrite(AIN1, HIGH); 
      digitalWrite(AIN2, LOW);
      digitalWrite(BIN1, HIGH); 
      digitalWrite(BIN2, LOW);
      break;

    case 'B': // Atrás
      analogWrite(PWMA, velMaxima); 
      analogWrite(PWMB, velMaxima);
      digitalWrite(AIN1, LOW);  
      digitalWrite(AIN2, HIGH);
      digitalWrite(BIN1, LOW);  
      digitalWrite(BIN2, HIGH);
      break;

    case 'R': // Derecha 
      analogWrite(PWMA, velGiro); 
      analogWrite(PWMB, velGiro);
      digitalWrite(AIN1, HIGH); 
      digitalWrite(AIN2, LOW);
      digitalWrite(BIN1, LOW);  
      digitalWrite(BIN2, HIGH);
      break;

    case 'L': // Izquierda 
      analogWrite(PWMA, velGiro); 
      analogWrite(PWMB, velGiro);
      digitalWrite(AIN1, LOW);  
      digitalWrite(AIN2, HIGH);
      digitalWrite(BIN1, HIGH); 
      digitalWrite(BIN2, LOW);
      break;

    case 'I': // Diagonal Adelante-Derecha 
      analogWrite(PWMA, 220); 
      analogWrite(PWMB, velGiro);
      digitalWrite(AIN1, HIGH); 
      digitalWrite(AIN2, LOW);
      digitalWrite(BIN1, LOW);  
      digitalWrite(BIN2, LOW);
      break;

    case 'G': // Diagonal Adelante-Izquierda 
      analogWrite(PWMA, velGiro); 
      analogWrite(PWMB, 220);
      digitalWrite(AIN1, LOW);  
      digitalWrite(AIN2, LOW);
      digitalWrite(BIN1, HIGH); 
      digitalWrite(BIN2, LOW);
      break;

    case 'J': // Diagonal Atrás-Derecha 
      analogWrite(PWMA, 220); 
      analogWrite(PWMB, velGiro);
      digitalWrite(AIN1, LOW);  
      digitalWrite(AIN2, HIGH);
      digitalWrite(BIN1, LOW);  
      digitalWrite(BIN2, LOW);
      break;

    case 'H': // Diagonal Atrás-Izquierda 
      analogWrite(PWMA, velGiro); 
      analogWrite(PWMB, 220);
      digitalWrite(AIN1, LOW);  
      digitalWrite(AIN2, LOW);
      digitalWrite(BIN1, LOW);  
      digitalWrite(BIN2, HIGH);
      break;

    case 'S': // Stop 
      analogWrite(PWMA, 0); 
      analogWrite(PWMB, 0);
      digitalWrite(AIN1, LOW);  
      digitalWrite(AIN2, LOW);
      digitalWrite(BIN1, LOW);  
      digitalWrite(BIN2, LOW);
      break;
  }
}
