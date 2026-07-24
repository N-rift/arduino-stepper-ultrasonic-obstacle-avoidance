#include <Servo.h>

Servo servo;

const int trigPin = 6;
const int echoPin = 7;

void setup() {
  servo.attach(8);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  servo.write(90);
}

long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

void loop() {

  long distance = getDistance();

  if (distance < 50) {
    servo.write(180);   // Change direction
  } else {
    servo.write(90);    // Default position
  }

  delay(100);
}