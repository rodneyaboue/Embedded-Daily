#include <LiquidCrystal.h>
#include <Servo.h>

// === CONFIGURATION ===
#define TRIG_PIN 8
#define ECHO_PIN 9
#define IR_PIN 10
#define SERVO_PIN 11
#define LED_VERTE 12
#define LED_ROUGE 13

#define DISTANCE_DETECTION 10       // cm
#define PLACES_MAX 3
#define TEMPS_ATTENTE_PASSAGE 5000  // 3 secondes

// LiquidCrystal(rs, en, d4, d5, d6, d7)
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
Servo barriere;

// Variables globales
int places_disponibles = PLACES_MAX;
bool entree_detectee = false;
bool sortie_detectee = false;
bool passageEnCours = false;  // pour ne lire l'IR qu'une seule fois

// === FONCTIONS ===
long mesureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duree = pulseIn(ECHO_PIN, HIGH);
  long distance = duree * 0.034 / 2;
  return distance;
}

void ouvrirBarriere() {
  barriere.write(90);
}

void fermerBarriere() {
  barriere.write(0);
}

void afficherLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Parking System");
  lcd.setCursor(0, 1);
  lcd.print("Places: ");
  lcd.print(places_disponibles);
}

// === SETUP ===
void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(IR_PIN, INPUT);
  pinMode(LED_VERTE, OUTPUT);
  pinMode(LED_ROUGE, OUTPUT);

  barriere.attach(SERVO_PIN);
  fermerBarriere();

  lcd.begin(16, 2);
  afficherLCD();
}

// === LOOP PRINCIPALE ===
void loop() {
  long distance = mesureDistance();
  int irState = digitalRead(IR_PIN);

  // --- DÉTECTION D’ENTRÉE ---
  if (distance < DISTANCE_DETECTION && !entree_detectee) {
    entree_detectee = true;

    if (places_disponibles > 0) {
      Serial.println("Vehicule detecte a l'entree");
      ouvrirBarriere();
      digitalWrite(LED_VERTE, HIGH);

      passageEnCours = true;  // lecture IR autorisée
      unsigned long t0 = millis();
      bool passageConfirme = false;

      // Lecture IR une seule fois pendant TEMPS_ATTENTE_PASSAGE
      while (millis() - t0 < TEMPS_ATTENTE_PASSAGE) {
        if (passageEnCours && digitalRead(IR_PIN) == LOW) {
          delay(2000);
          passageConfirme = true;
          passageEnCours = false; // bloque nouvelles lectures IR
          break;
        }
      }

      if (passageConfirme) {
        delay(2000);
        places_disponibles--;
        Serial.println("Passage confirme, mise a jour du compteur");
      } else {
        Serial.println("Aucun passage detecte -> annulation");
      }

      fermerBarriere();
      digitalWrite(LED_VERTE, LOW);
      afficherLCD();
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Parking complet!");
      delay(500);
      afficherLCD();
    }
  }
  if (distance >= DISTANCE_DETECTION) {
    entree_detectee = false;
    passageEnCours = false;  // reset pour le prochain véhicule
  }

  // --- DÉTECTION DE SORTIE ---
  if (irState == LOW && !sortie_detectee) {
    sortie_detectee = true;
    digitalWrite(LED_ROUGE, HIGH);

    if (places_disponibles < PLACES_MAX) {
      places_disponibles++;
      ouvrirBarriere();
      delay(2000);
      fermerBarriere();
      afficherLCD();
    }

    digitalWrite(LED_ROUGE, LOW);
  }
  if (irState == HIGH) sortie_detectee = false;

  delay(100);
}

