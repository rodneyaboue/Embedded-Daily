#include <LiquidCrystal.h>

// === CONFIGURATION ===
#define TRIG_PIN 8
#define ECHO_PIN 9
#define IR_PIN 10
#define LED_VERTE 12
#define LED_ROUGE 13

#define DISTANCE_ENTRE_CAPTEURS 10   // cm
#define LIMITE_VITESSE 0.4           // km/h ≈ 100 cm/s

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

bool passageIRDetecte = false;
bool passageUltrasonDetecte = false;
unsigned long tempsIR = 0;
unsigned long tempsUltrason = 0;

// === FONCTIONS ===
long mesureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duree = pulseIn(ECHO_PIN, HIGH);
  long distance = duree * 0.034 / 2; // cm
  return distance;
}

void afficherLCD(float vitesse) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Radar de vitesse");
  lcd.setCursor(0, 1);
  lcd.print("V: ");
  lcd.print(vitesse, 2);
  lcd.print(" km/h");
}

// === FONCTION CLIGNOTEMENT LED ===
void clignoterLED(int pin, int dureeTotale, int intervalle) {
  unsigned long debut = millis();
  while (millis() - debut < dureeTotale) {
    digitalWrite(pin, HIGH);
    delay(intervalle);
    digitalWrite(pin, LOW);
    delay(intervalle);
  }
}

// === SETUP ===
void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(IR_PIN, INPUT);
  pinMode(LED_VERTE, OUTPUT);
  pinMode(LED_ROUGE, OUTPUT);

  lcd.begin(16, 2);
  lcd.print("Radar pret...");
  delay(1000);
  lcd.clear();
}

// === LOOP PRINCIPALE ===
void loop() {
  // --- Détection passage capteur IR --- (désormais premier)
  int etatIR = digitalRead(IR_PIN);
  if (etatIR == LOW && !passageIRDetecte) {
    passageIRDetecte = true;
    tempsIR = millis();
    Serial.println("Passage IR detecte");
  }

  // --- Détection passage capteur ultrason --- (désormais second)
  long distance = mesureDistance();
  if (distance > 0 && distance < 100 && passageIRDetecte && !passageUltrasonDetecte) { 
    passageUltrasonDetecte = true;
    tempsUltrason = millis();
    Serial.println("Passage ultrason detecte");

    // --- Calcul vitesse ---
    float deltaTemps = (tempsUltrason - tempsIR) / 1000.0; // en secondes
    if (deltaTemps <= 0) deltaTemps = 0.001; // éviter division par zéro
    float vitesse_cmps = DISTANCE_ENTRE_CAPTEURS / deltaTemps; // cm/s
    float vitesse_kmh = vitesse_cmps * 0.036; // conversion cm/s → km/h

    Serial.print("Vitesse: "); 
    Serial.print(vitesse_kmh); 
    Serial.println(" km/h");

    afficherLCD(vitesse_kmh);

    // --- CLIGNOTEMENT LED ---
    if (vitesse_kmh > LIMITE_VITESSE) {
      Serial.println("vitesse trop elevee !");
      clignoterLED(LED_ROUGE, 2000, 200);  // clignote 2 s (intervalle 200 ms)
    } else {
      Serial.println("Vitesse correcte");
      clignoterLED(LED_VERTE, 2000, 200);  // clignote 2 s (intervalle 200 ms)
    }

    // --- Réinitialisation ---
    passageIRDetecte = false;
    passageUltrasonDetecte = false;
  }
}
