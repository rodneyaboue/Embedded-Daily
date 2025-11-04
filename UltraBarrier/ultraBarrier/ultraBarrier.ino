#include <Servo.h>

const int trigPin = 7;
const int echoPin = 8;
const int ledPin = 6; // LED qui clignote
const int servoPin = 4; // pin du servo

long duration;
int distance;
int seuil = 50; // seuil de distance en cm
Servo barrierServo;

// Temps de fermeture après passage (ms)
unsigned long closeDelay = 5000; 
unsigned long lastDetectionTime = 0;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  barrierServo.attach(servoPin);
  barrierServo.write(0); // barrière initialement baissée
  Serial.begin(9600);
}

void loop() {
  // Mesure de la distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // conversion en cm

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Vérifier détection
  if (distance < seuil) {
    digitalWrite(ledPin, HIGH); // LED clignote
    barrierServo.write(100);      // lever la barrière
    lastDetectionTime = millis(); // mémoriser le dernier passage
    delay(100); // LED clignotement rapide
    digitalWrite(ledPin, LOW);
    delay(100);
  } else {
    // LED éteinte
    digitalWrite(ledPin, LOW);
    // Vérifier si le délai après passage est écoulé
    if (millis() - lastDetectionTime >= closeDelay) {
      barrierServo.write(0); // abaisser barrière
    }
    delay(200);
  }
}
