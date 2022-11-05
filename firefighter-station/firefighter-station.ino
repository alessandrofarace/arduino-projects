const int piezoPin = 7;
const int blueLedPin = 8;
const int redLedPin = 12;
const int phototransistorPin = A0;
const int alarmDuration = 10000;
const int blinkPeriod = 500;

struct Range {
  float min;
  float max;
};

Range phototransistorRange = { 1024.0, 0.0 };

void setup() {
  pinMode(blueLedPin, OUTPUT);
  digitalWrite(blueLedPin, LOW);
  pinMode(redLedPin, OUTPUT);
  digitalWrite(redLedPin, LOW);
  phototransistorRange = calibrate();
}

void loop() {
  float phototransistorValue = analogRead(phototransistorPin);
  if (phototransistorValue < phototransistorRange.min / 2) {
    blink();
  }
}

void blink() {
  float startTime = millis();
  while (millis() - startTime < alarmDuration){
    int subcycle = (millis() - startTime) / blinkPeriod;
    if (subcycle % 2 == 0) {
      tone(piezoPin, 1000, blinkPeriod);
      digitalWrite(blueLedPin, HIGH);
      digitalWrite(redLedPin, LOW);
    }else {
      tone(piezoPin, 750, blinkPeriod);
      digitalWrite(blueLedPin, LOW);
      digitalWrite(redLedPin, HIGH);
    }
  }
  digitalWrite(blueLedPin, LOW);
  digitalWrite(redLedPin, LOW);
}

Range calibrate() {
  digitalWrite(blueLedPin, HIGH);
  digitalWrite(redLedPin, HIGH);
  float min = 1024.0;
  float max = 0;
  delay(1000);
  float startTime = millis();
  while (millis() - startTime < 5000){
    float phototransistorValue = analogRead(phototransistorPin);
    if (phototransistorValue > max) {
      max = phototransistorValue;
    }
    if (phototransistorValue < min) {
      min = phototransistorValue;
    }
  }
  Range r = { min, max };
  digitalWrite(blueLedPin, LOW);
  digitalWrite(redLedPin, LOW);
  return r;
}