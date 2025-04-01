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
bool isMoving = false; 

enum Estado {
  IDLE,
  MOVING_FORWARD,
  MOVING_BACK,
  TURNING_LEFT,
  TURNING_RIGHT
};

Estado currentState = IDLE;

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
  
  digitalWrite(DRIVER_ENABLE_PIN, HIGH);
}

void forward() {
  digitalWrite(MOTOR_LEFT_DIRECTION_PIN, HIGH);
  analogWrite(MOTOR_LEFT_SPEED_PIN, 75);
  digitalWrite(MOTOR_RIGHT_DIRECTION_PIN, HIGH);
  analogWrite(MOTOR_RIGHT_SPEED_PIN, 75);
  currentState = MOVING_FORWARD;  
}

void stopMotors() {
  digitalWrite(MOTOR_LEFT_SPEED_PIN, 0);
  digitalWrite(MOTOR_RIGHT_SPEED_PIN, 0);
  myServo.write(90);
  currentState = IDLE;  
}

void back() {
  digitalWrite(MOTOR_LEFT_DIRECTION_PIN, LOW);
  analogWrite(MOTOR_LEFT_SPEED_PIN, 70);
  digitalWrite(MOTOR_RIGHT_DIRECTION_PIN, LOW);
  analogWrite(MOTOR_RIGHT_SPEED_PIN, 70);
  currentState = MOVING_BACK;  
}

void turnLeft() {
  digitalWrite(MOTOR_LEFT_DIRECTION_PIN, HIGH);
  analogWrite(MOTOR_LEFT_SPEED_PIN, 100);
  digitalWrite(MOTOR_RIGHT_DIRECTION_PIN, LOW);
  analogWrite(MOTOR_RIGHT_SPEED_PIN, 100);
  
  delay(700);

  stopMotors();
  currentState = IDLE;
}

void turnRight() {
  digitalWrite(MOTOR_LEFT_DIRECTION_PIN, LOW);
  analogWrite(MOTOR_LEFT_SPEED_PIN, 100);
  digitalWrite(MOTOR_RIGHT_DIRECTION_PIN, HIGH);
  analogWrite(MOTOR_RIGHT_SPEED_PIN, 100);
  
  delay(700);

  stopMotors();
  currentState = IDLE; 
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
    myServo.write(90);
    forward();
  } else {
    stopMotors();
    myServo.write(180);
    delay(1000);
    leerDistancia();
    if (distance > 15) {
      myServo.write(90);
      turnLeft();
      stopMotors();
    } else {
      myServo.write(0);
      delay(1000);
      leerDistancia();
      if (distance > 15) {
        myServo.write(90);
        turnRight();
        stopMotors();
      } else {
        myServo.write(0);
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
    } else if (op == '7') {
      myServo.write(180);
      delay(1000);
      myServo.write(90);
    } else if (op == '8') {
      myServo.write(0);
      delay(1000);
      myServo.write(90);
    }
  }

  if (autoMode) {
    autoModeAvoid();
  }

}
