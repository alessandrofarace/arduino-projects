const int ledPin = 12;
const int buttonPin = 8;
const int phototransistorPin = A0;

struct Range {
  float min;
  float max;
};

Range phototransistorRange = { 1024.0, 0.0 };

void setup() {
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  pinMode(buttonPin, INPUT);
}

void loop() {
  int buttonState = digitalRead(buttonPin);
  float phototransistorValue = analogRead(phototransistorPin);

  Serial.print("Phototransistor value: ");
  Serial.println(phototransistorValue);
  Serial.print("Phototransistor voltage: ");
  Serial.println(phototransistorVoltage);

  if (buttonState == HIGH) {
    phototransistorRange = calibrate();
  }

  if (phototransistorValue < phototransistorRange.min) {
    digitalWrite(ledPin, HIGH);
  }else {
    digitalWrite(ledPin, LOW);
  }

  delay(1000);
}

Range calibrate() {
    Serial.println("Calibrating");
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
    
    Serial.print("Min: ");
    Serial.println(r.min);
    Serial.print("Max: ");
    Serial.println(r.max);

    return r;
}
