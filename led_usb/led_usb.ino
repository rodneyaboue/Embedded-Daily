void setup() {
  pinMode(13, OUTPUT);  // LED intégrée
  Serial.begin(9600);   // Communication série USB
}

void loop() {
  if (Serial.available() > 0) {
    char cmd = Serial.read();  // Lire le caractère envoyé par le Pi
    if (cmd == '1') {
      digitalWrite(13, HIGH);  // Allumer LED
    } else if (cmd == '0') {
      digitalWrite(13, LOW);   // Éteindre LED
    }
  }
}
