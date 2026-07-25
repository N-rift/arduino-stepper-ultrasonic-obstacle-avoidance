const int IN1 = 2;
const int IN2 = 3;
const int IN3 = 4;
const int IN4 = 5;

const int trigPin = 6;
const int echoPin = 7;

const int obstacleDistance = 10;
const int stepDelay = 5;

int direction = 1;
bool obstacleDetected = false;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

long getDistance() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0)
    return 999;

  return duration * 0.034 / 2;
}

void stepMotor(bool a, bool b, bool c, bool d) {
  digitalWrite(IN1, a);
  digitalWrite(IN2, b);
  digitalWrite(IN3, c);
  digitalWrite(IN4, d);
  delay(stepDelay);
}

void stepForward() {
  stepMotor(1,0,1,0);
  stepMotor(0,1,1,0);
  stepMotor(0,1,0,1);
  stepMotor(1,0,0,1);
}

void stepBackward() {
  stepMotor(1,0,0,1);
  stepMotor(0,1,0,1);
  stepMotor(0,1,1,0);
  stepMotor(1,0,1,0);
}

void stopMotor() {
  stepMotor(0,0,0,0);
}

void loop() {

  long distance = getDistance();

  if (distance <= obstacleDistance && !obstacleDetected) {

    stopMotor();
    delay(500);

    direction *= -1;
    obstacleDetected = true;
  }

  if (distance > obstacleDistance) {
    obstacleDetected = false;
  }

  if (direction == 1)
    stepForward();
  else
    stepBackward();
}