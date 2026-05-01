#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11); // RX is not used , TX

char data;
int speedValue = 150; // default speed (0–255)

void setup() {
  BT.begin(115200);   // your working baud rate default baud rate is 9600
  Serial.begin(115200);  // i am using 115200

  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);

  pinMode(9, OUTPUT); // ENA
  pinMode(3, OUTPUT); // ENB
}

void loop() {

  if (BT.available()) {
    data = BT.read();
    Serial.println(data);

    // SPEED CONTROL (0–9 from app)
    if (data >= '0' && data <= '9') {
      speedValue = map(data - '0', 0, 9, 0, 255);
    }

    // Apply speed
    analogWrite(9, speedValue);
    analogWrite(3, speedValue);

    // STOP first
    digitalWrite(7, LOW);
    digitalWrite(6, LOW);
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);

    switch (data) {

      case 'F': // Forward
        digitalWrite(7, HIGH);
        digitalWrite(6, LOW);
        digitalWrite(5, HIGH);
        digitalWrite(4, LOW);
        break;

      case 'B': // Backward
        digitalWrite(7, LOW);
        digitalWrite(6, HIGH);
        digitalWrite(5, LOW);
        digitalWrite(4, HIGH);
        break;

      case 'L': // Left
        digitalWrite(7, LOW);
        digitalWrite(6, HIGH);
        digitalWrite(5, HIGH);
        digitalWrite(4, LOW);
        break;

      case 'R': // Right
        digitalWrite(7, HIGH);
        digitalWrite(6, LOW);
        digitalWrite(5, LOW);
        digitalWrite(4, HIGH);
        break;

      case 'G': // Forward Left
        digitalWrite(7, LOW);
        digitalWrite(6, LOW);
        digitalWrite(5, HIGH);
        digitalWrite(4, LOW);
        break;

      case 'I': // Forward Right
        digitalWrite(7, HIGH);
        digitalWrite(6, LOW);
        digitalWrite(5, LOW);
        digitalWrite(4, LOW);
        break;

      case 'H': // Backward Left
        digitalWrite(7, LOW);
        digitalWrite(6, LOW);
        digitalWrite(5, LOW);
        digitalWrite(4, HIGH);
        break;

      case 'J': // Backward Right
        digitalWrite(7, LOW);
        digitalWrite(6, HIGH);
        digitalWrite(5, LOW);
        digitalWrite(4, LOW);
        break;

      case 'S': // Stop
        break;
    }
  }
}