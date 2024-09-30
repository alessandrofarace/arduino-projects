#include <Servo.h>

Servo myServo;

int const ledPinRight = 4;
int const ledPinLeft = 7;
int const minAngle = 60;
int const maxAngle = 120;

void setup() {
  pinMode(ledPinRight, OUTPUT);
  pinMode(ledPinLeft, OUTPUT);
  myServo.attach(9);
  Serial.begin(9600);
}

void loop() {
  moveHead();
  delay(5000);
}

void moveHead() {
  digitalWrite(ledPinRight, HIGH);
  digitalWrite(ledPinLeft, HIGH);
  for (int i = 0; i <= maxAngle - minAngle; i++) {
    myServo.write(minAngle + i);
    delay(50);
  }
  for (int i = 0; i <= maxAngle - minAngle; i++) {
    myServo.write(maxAngle - i);
    delay(50);
  }
  digitalWrite(ledPinRight, LOW);
  digitalWrite(ledPinLeft, LOW);  
}
