#include <Servo.h>

#define MQ2_PIN A0       // Entrée analogique du capteur MQ-2
#define LED_PIN 2        // LED d'alerte visuelle
#define BUZZER_PIN 11    // Buzzer actif
#define SERVO_PIN 9      // Servo moteur (fenêtre)
#define THRESHOLD 50    // Seuil de détection du gaz (à calibrer)

Servo windowServo;       // Création de l’objet servo

void setup() {
  Serial.begin(9600);

  pinMode(MQ2_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  windowServo.attach(SERVO_PIN);
  windowServo.write(0); // Fenêtre fermée au démarrage

  Serial.println("Initialisation du capteur MQ-2...");
  delay(2000); // Chauffe initiale du capteur
  Serial.println("Prêt à détecter les gaz !");
}

void loop() {
  int sensorValue = analogRead(MQ2_PIN); // Lecture de la valeur analogique
  Serial.print("Valeur MQ-2 : ");
  Serial.println(sensorValue);

  if (sensorValue > THRESHOLD) {
    Serial.println("ALERTE : Gaz ou fumée détecté !");
    
    // Alarme sonore et visuelle
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000); // Buzzer actif (1 kHz)
    
    // Ouverture de la fenêtre (servo)
    windowServo.write(140); // Angle d'ouverture (adapter selon ton montage)
    delay(4000);            // Maintien ouvert 4 secondes

    //  Maintenir la fenêtre ouverte tant que le gaz est détecté
    while (analogRead(MQ2_PIN) > THRESHOLD) {
      Serial.println(" Gaz toujours présent - fenêtre ouverte...");
      delay(1000);
    }

    //  Air pur -> arrêt alarme + fermeture fenêtre
    Serial.println(" Air pur détecté - fermeture de la fenêtre.");
    noTone(BUZZER_PIN);
    digitalWrite(LED_PIN, LOW);
    windowServo.write(0);   // Fenêtre refermée
    delay(1000);

  } else {
    // Tout va bien
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
  }

  delay(200); // Nouvelle mesure toutes les 200 ms
}
