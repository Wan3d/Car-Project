#define MOTOR_LEFT_SPEED_PIN 5
#define MOTOR_LEFT_DIRECTION_PIN 7
#define MOTOR_RIGHT_SPEED_PIN 6
#define MOTOR_RIGHT_DIRECTION_PIN 8
#define DRIVER_ENABLE_PIN 3

char op;

void setup() {
  Serial.begin(9600);
  Serial.println("Iniciando");

  pinMode(MOTOR_LEFT_SPEED_PIN, OUTPUT);
  pinMode(MOTOR_LEFT_DIRECTION_PIN, OUTPUT);
  pinMode(MOTOR_RIGHT_SPEED_PIN, OUTPUT);
  pinMode(MOTOR_RIGHT_DIRECTION_PIN, OUTPUT);
  pinMode(DRIVER_ENABLE_PIN, OUTPUT);
  digitalWrite(DRIVER_ENABLE_PIN, HIGH);
}

void forward() {
  digitalWrite(MOTOR_LEFT_DIRECTION_PIN, HIGH);
  analogWrite(MOTOR_LEFT_SPEED_PIN, 60);
  digitalWrite(MOTOR_RIGHT_DIRECTION_PIN, HIGH);
  analogWrite(MOTOR_RIGHT_SPEED_PIN, 60);
  delay(500);
}

void stopMotors() {
  digitalWrite(MOTOR_LEFT_SPEED_PIN, 0);
  digitalWrite(MOTOR_RIGHT_SPEED_PIN, 0);
}

void back() {
  digitalWrite(MOTOR_LEFT_DIRECTION_PIN, LOW);
  analogWrite(MOTOR_LEFT_SPEED_PIN, 60);
  digitalWrite(MOTOR_RIGHT_DIRECTION_PIN, LOW);
  analogWrite(MOTOR_RIGHT_SPEED_PIN, 60);
  delay(500);
}

void turnLeft() {
  // Giro a la derecha 90 grados
  digitalWrite(MOTOR_LEFT_DIRECTION_PIN, HIGH);
  analogWrite(MOTOR_LEFT_SPEED_PIN, 60);
  digitalWrite(MOTOR_RIGHT_DIRECTION_PIN, LOW);
  analogWrite(MOTOR_RIGHT_SPEED_PIN, 60);
  delay(490);

  // Detener motores
  digitalWrite(MOTOR_LEFT_SPEED_PIN, 0);
  digitalWrite(MOTOR_RIGHT_SPEED_PIN, 0);
}

void turnRight() {
  // Giro a la izquierda 90 grados
  digitalWrite(MOTOR_LEFT_DIRECTION_PIN, LOW);
  analogWrite(MOTOR_LEFT_SPEED_PIN, 60);
  digitalWrite(MOTOR_RIGHT_DIRECTION_PIN, HIGH);
  analogWrite(MOTOR_RIGHT_SPEED_PIN, 60);
  delay(490);

  // Detener motores
  digitalWrite(MOTOR_LEFT_SPEED_PIN, 0);
  digitalWrite(MOTOR_RIGHT_SPEED_PIN, 0);
}

void loop() {
  if (Serial.available()) {

    op = Serial.read();
    Serial.write(op);

    if (op == '1') {
      forward();
    } else if (op == '2') {
      stopMotors();
    } else if (op == '3') {
      back();
    } else if (op == '4') {
      turnLeft();
    } else if (op == '5') {
      turnRight();
    }
  }
}
