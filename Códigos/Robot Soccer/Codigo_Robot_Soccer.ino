#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

// Definición de pines para el control de los motores
#define PWMA 32
#define AIN1 25
#define AIN2 33
#define STBY 26
#define BIN1 27
#define BIN2 14
#define PWMB 12

char estado = 'S'; // Estado inicial: detenido

void setup() {

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(STBY, OUTPUT);
  
  digitalWrite(STBY, HIGH); // Activar el controlador de motor
  Serial.begin(115200);
  SerialBT.begin("Robot_Soccer"); // Cambia por el nombre de tu robot
  
  Serial.println("ESP32 listo. Esperando comandos por Bluetooth...");
}

void loop() {
  if (SerialBT.available()) {
    char entrada = SerialBT.read();
    estado = entrada;
    SerialBT.print("Comando recibido: ");
    SerialBT.println(estado);


    // Control de dirección según el estado
    switch (estado) {
      case 'F': adelante(); SerialBT.println("Adelante"); break;
      case 'B': atras(); SerialBT.println("Atrás"); break;
      case 'L': izquierda(); SerialBT.println("Izquierda"); break;
      case 'R': derecha(); SerialBT.println("Derecha"); break;
      case 'G': adelanteIzquierda(); break;
      case 'I': adelanteDerecha(); break;
      case 'H': atrasIzquierda(); break;
      case 'J': atrasDerecha(); break;
      case 'S': detener(); break;
      default: break;
    }
  }
}

// Funciones para movimiento
void atras() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMA, 255);
  analogWrite(PWMB, 255);
}

void adelante() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMA, 255);
  analogWrite(PWMB, 255);
}

void derecha() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMA, 200);
  analogWrite(PWMB, 200);
}

void izquierda() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMA, 200);
  analogWrite(PWMB, 200);
}

void detener() {
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
}

void atrasIzquierda() {
  // Solo motor derecho avanza, izquierdo va más lento
  digitalWrite(AIN1, LOW); 
  digitalWrite(AIN2, HIGH);   // Motor A adelante
  digitalWrite(BIN1, LOW); 
  digitalWrite(BIN2, HIGH);   // Motor B adelante
  analogWrite(PWMA, 150);   // Izquierdo más lento
  analogWrite(PWMB, 220);   // Derecho fuerte
}

void atrasDerecha() {
  digitalWrite(AIN1, LOW); digitalWrite(AIN2, HIGH);   // Motor A adelante
  digitalWrite(BIN1, LOW); digitalWrite(BIN2, HIGH);   // Motor B adelante
  analogWrite(PWMA, 220);   // Izquierdo fuerte
  analogWrite(PWMB, 150);   // Derecho más lento
}

void adelanteIzquierda() {
  digitalWrite(AIN1, HIGH); digitalWrite(AIN2, LOW);   // Motor A atrás
  digitalWrite(BIN1, HIGH); digitalWrite(BIN2, LOW);   // Motor B atrás
  analogWrite(PWMA, 150);   // Izquierdo más lento
  analogWrite(PWMB, 220);   // Derecho fuerte
}

void adelanteDerecha() {
  digitalWrite(AIN1, HIGH); digitalWrite(AIN2, LOW);   // Motor A atrás
  digitalWrite(BIN1, HIGH); digitalWrite(BIN2, LOW);   // Motor B atrás
  analogWrite(PWMA, 220);   // Izquierdo fuerte
  analogWrite(PWMB, 150);   // Derecho más lento
}
