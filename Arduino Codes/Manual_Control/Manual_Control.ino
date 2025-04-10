#define MOTOR_LEFT_SPEED_PIN 5       // Velocidad de los motores izquierdos
#define MOTOR_LEFT_DIRECTION_PIN 7   // Dirección de los motores izquierdos
#define MOTOR_RIGHT_SPEED_PIN 6      // Velocidad de los motores derechos
#define MOTOR_RIGHT_DIRECTION_PIN 8  // Dirección de los motores derechos
#define DRIVER_ENABLE_PIN 3          // Habilitación del driver
#define PIN_Servo_z 10               // PIN del servo
#define TRIG_PIN 13
#define ECHO_PIN 12

#include <Servo.h>

Servo myServo;

char op;
long duration;
int distance;
bool autoMode = false;
bool isMoving = false;
int anguloServo = 90;
int lastPosition = anguloServo;

enum Estado {
  IDLE,
  MOVING_FORWARD,
  MOVING_BACK,
  TURNING_LEFT,
  TURNING_RIGHT,
  TURNING_LEFT_SERVO,
  TURNING_RIGHT_SERVO,
  INITIAL_POSITION,
  TURNING_LEFT_SERVO2,
  TURNING_RIGHT_SERVO2,
  STOPPING_SERVO
};

Estado currentState = IDLE;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(20);
  Serial.println("Iniciando");

  pinMode(MOTOR_LEFT_SPEED_PIN, OUTPUT);
  pinMode(MOTOR_LEFT_DIRECTION_PIN, OUTPUT);
  pinMode(MOTOR_RIGHT_SPEED_PIN, OUTPUT);
  pinMode(MOTOR_RIGHT_DIRECTION_PIN, OUTPUT);
  pinMode(DRIVER_ENABLE_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  myServo.attach(PIN_Servo_z);  // Inicializas el servo en el PIN donde está conectado
  myServo.write(anguloServo);   // Empieza en el ángulo de 90 grados (Cada vez que se prenda el coche, se pondrá en esta posición)

  digitalWrite(DRIVER_ENABLE_PIN, HIGH);
}

// Función para avanzar hacía adelante

void forward() {
  digitalWrite(MOTOR_LEFT_DIRECTION_PIN, HIGH);   // Motor izquierdo hacía adelante
  analogWrite(MOTOR_LEFT_SPEED_PIN, 75);          // Velocidad de 75 (La velocidad son señales por ancho de pulso y mientras mayor sea el valor, más rápido girarán los motores)
  digitalWrite(MOTOR_RIGHT_DIRECTION_PIN, HIGH);  // Motor derecho hacía adelante
  analogWrite(MOTOR_RIGHT_SPEED_PIN, 75);         // Velocidad de 75 (La velocidad son señales por ancho de pulso y mientras mayor sea el valor, más rápido girarán los motores)
  currentState = MOVING_FORWARD;                  // Se queda en el estado actual para no modificar el flujo o evitar que se cambié repentinamente
}

// Función para detener motores

void stopMotors() {
  digitalWrite(MOTOR_LEFT_SPEED_PIN, 0);   // Velocidad de 0 (Así los motores no girarán)
  digitalWrite(MOTOR_RIGHT_SPEED_PIN, 0);  // Velocidad de 0 (Así los motores no girarán)
  currentState = IDLE;                     // Se queda en el estado actual para no modificar el flujo o evitar que se cambié repentinamente
}

// Función para ir hacía atrás

void back() {
  digitalWrite(MOTOR_LEFT_DIRECTION_PIN, LOW);   // Motor izquierdo hacía atrás
  analogWrite(MOTOR_LEFT_SPEED_PIN, 70);         // Velocidad de 70 (La velocidad son señales por ancho de pulso y mientras mayor sea el valor, más rápido girarán los motores)
  digitalWrite(MOTOR_RIGHT_DIRECTION_PIN, LOW);  // Motor derecho hacía atrás
  analogWrite(MOTOR_RIGHT_SPEED_PIN, 70);        // Velocidad de 70 (La velocidad son señales por ancho de pulso y mientras mayor sea el valor, más rápido girarán los motores)
  currentState = MOVING_BACK;                    // Se queda en el estado actual para no modificar el flujo o evitar que se cambié repentinamente
}

// Función para girar el coche hacía la izquierda

void turnLeft() {

  // En esta parte haremos que el motor izquierdo vaya hacia adelante y el motor derecho vaya hacia atrás con la misma velocidad
  // Al hacer este movimiento la tracción hará que el coche gire hacía la izquierda en este caso, que es el que avanza
  // Y con la ayuda del delay, decidimos aproximadamente cuántos milisegundos queremos que el coche haga este giro
  // En este caso, le ponemos 570 (por aproximación) para que gire apróximadamente en un ángulo de 90 grados

  digitalWrite(MOTOR_LEFT_DIRECTION_PIN, HIGH);  // Motor izquierdo hacía adelante
  analogWrite(MOTOR_LEFT_SPEED_PIN, 100);        // Velocidad de 100 (La velocidad son señales por ancho de pulso y mientras mayor sea el valor, más rápido girarán los motores)
  digitalWrite(MOTOR_RIGHT_DIRECTION_PIN, LOW);  // Motor derecho hacía atrás
  analogWrite(MOTOR_RIGHT_SPEED_PIN, 100);       // Velocidad de 100 (La velocidad son señales por ancho de pulso y mientras mayor sea el valor, más rápido girarán los motores)

  delay(570);  // Gira por 570 milisegundos esperando que su posición haya cambiado 90 grados

  stopMotors();         // Se detiene en seco el coche
  currentState = IDLE;  // Se pone el estado actual en IDLE para que no siga girando
}

// Función parar girar el coche hacía la derecha

void turnRight() {

  // En esta parte haremos que el motor izquierdo vaya hacia atrás y el motor derecho vaya hacia adelante con la misma velocidad
  // Al hacer este movimiento la tracción hará que el coche gire hacía la derecho en este caso, que es el que avanza
  // Y con la ayuda del delay, decidimos aproximadamente cuántos milisegundos queremos que el coche haga este giro
  // En este caso, le ponemos 570 (por aproximación) para que gire apróximadamente en un ángulo de 90 grados

  digitalWrite(MOTOR_LEFT_DIRECTION_PIN, LOW);    // Motor izquierdo hacía atrás
  analogWrite(MOTOR_LEFT_SPEED_PIN, 100);         // Velocidad de 100 (La velocidad son señales por ancho de pulso y mientras mayor sea el valor, más rápido girarán los motores)
  digitalWrite(MOTOR_RIGHT_DIRECTION_PIN, HIGH);  // Motor derecho hacía adelante
  analogWrite(MOTOR_RIGHT_SPEED_PIN, 100);        // Velocidad de 100 (La velocidad son señales por ancho de pulso y mientras mayor sea el valor, más rápido girarán los motores)

  delay(570);  // Gira por 570 milisegundos esperando que su posición haya cambiado 90 grados

  stopMotors();         // Se detiene en seco el coche
  currentState = IDLE;  // Se pone el estado actual en IDLE para que no siga girando
}

// Función para girar hacía la izquierdo el servomotor

void turnLeftServo() {
  myServo.write(180);   // Gira el servomotor 180 grados (O sea, hacía la izquierda)
  leerDistancia();      // Lee la distancia actual para saber si detecta un obstáculo (Esto para futuros avances del proyecto)
  currentState = IDLE;  // Se pone el estado actual en IDLE para que no siga girando
}

// Función para girar hacía la derecha el servomotor

void turnRightServo() {
  myServo.write(0);     // Gira el servomotor 0 grados (O sea, hacía la derecha)
  leerDistancia();      // Lee la distancia actual para saber si detecta un obstáculo (Esto para futuros avances del proyecto)
  currentState = IDLE;  // Se pone el estado actual en IDLE para que no siga girando
}

// Función para cambiar la posición del servomotor a su estado inicial (90 grados | Mirando hacía el frente)

void initialPosition() {
  myServo.write(90);    // Gira el servomotor 90 grados (O sea, mira hacía el frente)
  leerDistancia();      // Lee la distancia actual para saber si detecta un obstáculo (Esto para futuros avances del proyecto)
  currentState = IDLE;  // Se pone el estado actual en IDLE para que no siga girando
}

// Función para leer la distancia

void leerDistancia() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Leer duración del pulso y calcular la distancia
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.0344 / 2;  // Calcular distancia en centímetros

  Serial.println(distance);
}

/*void autoModeAvoid() {
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
}*/

void loop() {
  leerDistancia();  // Siempre lee la distancia
  delay(200);       // Evita que envíe muchos datos, así que le pones un pequeño delay

  String input = Serial.readStringUntil('\n');  // Lee los datos que se envían desde Python hasta el salto de línea (que también se envía codificado por Python, es como un punto final).
  input.trim();                                 // En caso de que el input tenga espacios, se eliminan

  // Si el tamaño del input es mayor a 0 (o sea, que se haya enviado un dato) y el primer caracter del input es un digito...
  if (input.length() > 0 && isDigit(input[0])) {
    int valorLeido = input.toInt();  // Convertimos el input (string) a un entero

    // Si el valor que leímos está entre 0 y 180, entonces podemos mover el servo. En caso de no estarlo, no se puede realizar movimiento
    if (valorLeido >= 0 && valorLeido <= 180) {
      myServo.write(valorLeido);  // Se mueve el servo conforme a lo que va recibiendo por Python
      lastPosition = valorLeido;  // En caso de necesitarlo, asignamos el valor leído a una variable entera por si necesitamos volver o quedarnos ahí
    }
  } else {
    char op = input[0];  // En caso de que el valor no fuera un número, entonces agarramos el primer caracter del string y lo asignamos a una variable de tipo char

    // A partir de aquí, según que carácter haya sido el guardado, cambiará el estado
    // Una vez cambiado el estado, en el segundo switch va a llamar funciones según el estado en el que esté

    switch (op) {
      case 'A': currentState = MOVING_FORWARD; break;
      case 'B': currentState = IDLE; break;
      case 'C': currentState = MOVING_BACK; break;
      case 'D': currentState = TURNING_LEFT; break;
      case 'E': currentState = TURNING_RIGHT; break;
      case 'F': currentState = TURNING_LEFT_SERVO; break;
      case 'G': currentState = TURNING_RIGHT_SERVO; break;
      case 'H': currentState = INITIAL_POSITION; break;
      case 'I': currentState = TURNING_LEFT_SERVO2; break;
      case 'J': currentState = TURNING_RIGHT_SERVO2; break;
      case 'K': currentState = STOPPING_SERVO; break;
    }
  }

  switch (currentState) {
    case MOVING_FORWARD: forward(); break;
    case IDLE: stopMotors(); break;
    case MOVING_BACK: back(); break;
    case TURNING_LEFT: turnLeft(); break;
    case TURNING_RIGHT: turnRight(); break;
    case TURNING_LEFT_SERVO: turnLeftServo(); break;
    case TURNING_RIGHT_SERVO: turnRightServo(); break;
    case INITIAL_POSITION: initialPosition(); break;
    default: stopMotors(); break;
  }
}
