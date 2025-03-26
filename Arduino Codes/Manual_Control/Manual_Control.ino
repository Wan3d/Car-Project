#define MOTOR_LEFT_SPEED_PIN 5       // velocidad de los motores izquierdos
#define MOTOR_LEFT_DIRECTION_PIN 7   // dirección de los motores izquierdos
#define MOTOR_RIGHT_SPEED_PIN 6      // velocidad de los motores derechos
#define MOTOR_RIGHT_DIRECTION_PIN 8  // dirección de los motores derechos
#define DRIVER_ENABLE_PIN 3          // habilitación del driver
#define PIN_Servo_z 10
#define TRIG_PIN 13
#define ECHO_PIN 12

#include <Servo.h>

Servo myServo;

char op;
long duration;
int distance;
bool autoMode = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Iniciando");

  pinMode(MOTOR_LEFT_SPEED_PIN, OUTPUT);
  pinMode(MOTOR_LEFT_DIRECTION_PIN, OUTPUT);
  pinMode(MOTOR_RIGHT_SPEED_PIN, OUTPUT);
  pinMode(MOTOR_RIGHT_DIRECTION_PIN, OUTPUT);
  pinMode(DRIVER_ENABLE_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  myServo.attach(PIN_Servo_z);
  myServo.write(90);
  delay(500);

  digitalWrite(DRIVER_ENABLE_PIN, HIGH);
}

void forward() {
  digitalWrite(MOTOR_LEFT_DIRECTION_PIN, HIGH);
  analogWrite(MOTOR_LEFT_SPEED_PIN, 50);
  digitalWrite(MOTOR_RIGHT_DIRECTION_PIN, HIGH);
  analogWrite(MOTOR_RIGHT_SPEED_PIN, 50);
  delay(500);
}

void stopMotors() {
  digitalWrite(MOTOR_LEFT_SPEED_PIN, 0);
  digitalWrite(MOTOR_RIGHT_SPEED_PIN, 0);
}

void back() {
  digitalWrite(MOTOR_LEFT_DIRECTION_PIN, LOW);
  analogWrite(MOTOR_LEFT_SPEED_PIN, 50);
  digitalWrite(MOTOR_RIGHT_DIRECTION_PIN, LOW);
  analogWrite(MOTOR_RIGHT_SPEED_PIN, 50);
  delay(1350);
}

void turnLeft() {
  // Giro a la derecha 90 grados
  digitalWrite(MOTOR_LEFT_DIRECTION_PIN, HIGH);
  analogWrite(MOTOR_LEFT_SPEED_PIN, 50);
  digitalWrite(MOTOR_RIGHT_DIRECTION_PIN, LOW);
  analogWrite(MOTOR_RIGHT_SPEED_PIN, 50);
  delay(1350);

  // Detener motores
  digitalWrite(MOTOR_LEFT_SPEED_PIN, 0);
  digitalWrite(MOTOR_RIGHT_SPEED_PIN, 0);
}

void turnRight() {
  // Giro a la izquierda 90 grados
  digitalWrite(MOTOR_LEFT_DIRECTION_PIN, LOW);
  analogWrite(MOTOR_LEFT_SPEED_PIN, 50);
  digitalWrite(MOTOR_RIGHT_DIRECTION_PIN, HIGH);
  analogWrite(MOTOR_RIGHT_SPEED_PIN, 50);
  delay(1350);

  // Detener motores
  digitalWrite(MOTOR_LEFT_SPEED_PIN, 0);
  digitalWrite(MOTOR_RIGHT_SPEED_PIN, 0);
}

void leerDistancia() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Leer duración del pulso y calcular la distancia
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.0344 / 2;  // Calcular distancia en centímetros
}

void autoModeAvoid() {
  leerDistancia();
  if (distance > 15) {
    // Si la distancia es mayor a 15 cm, el servo se queda en su posición inicial y sigue avanzando el coche
    myServo.write(90);
    forward();  // Avanzar
  } else {
    stopMotors();  // Detener los motores

    myServo.write(180);  // Giro a 180 grados (Izquierda)
    delay(1000);

    leerDistancia();  // Recalcular la distancia con el sensor ultrasónico mirando hacia la izquierda

    if (distance > 15) {
      // Si la distancia nueva mirando a la izquierda es mayor a 15 cm, girar el coche
      myServo.write(180);
      delay(1000);
      turnLeft();
      stopMotors();
    } else {
      myServo.write(0);  // Si no hay camino disponible, continuar con la dirección inicial
      delay(1000);
      leerDistancia();
      if (distance > 15) {
        myServo.write(90);
        delay(1000);
        turnRight();
        stopMotors();
        //myServo.write(90);
      } else {
        myServo.write(0);
        delay(1000);
        stopMotors();
      }
    }
  }
}

void loop() {
  if (Serial.available()) {
    op = Serial.read();
    Serial.write(op);

    if (op == '1') {
      forward();
      autoMode = false;
    } else if (op == '2') {
      stopMotors();
      autoMode = false;

    } else if (op == '3') {
      back();
      autoMode = false;

    } else if (op == '4') {
      turnLeft();
      autoMode = false;

    } else if (op == '5') {
      turnRight();
      autoMode = false;

    } else if (op == '6') {
      autoMode = true;
    }
  }
  if (autoMode){
    autoModeAvoid();
  }
}
