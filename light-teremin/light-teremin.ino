const int piezoPin = 8;
const int ledPin = 13;
const int phototransistorPin = A0;

struct Range {
  float min;
  float max;
};

Range phototransistorRange = {1024.0, 0.0};

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  phototransistorRange = calibrate();
  digitalWrite(ledPin, LOW);
}

void loop() {
  float phototransistorValue = analogRead(phototransistorPin);
  int pitch = map(
    phototransistorValue, 
    phototransistorRange.min, 
    phototransistorRange.max, 
    50,
    4000
  );
  tone(piezoPin, pitch, 20);
  delay(10);
}

Range calibrate() {
    float min = 1024.0;
    float max = 0.0;
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
    Range r = {min, max};
    return r;
}

