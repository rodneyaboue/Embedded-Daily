#include <LiquidCrystal.h>

#define BUTTONPIN 2  // bouton du joystick

const int ledRed = 3;
const int ledOrange = 4;
const int ledGreen = 5;

// LCD pins
int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// --- Configurable ---
const int NUM_PLAYERS = 3;  // Nombre de joueurs/tours
unsigned long delayBetweenRounds = 2000; // pause entre les tours

void setup() {
  pinMode(BUTTONPIN, INPUT_PULLUP); // résistance interne
  pinMode(ledRed, OUTPUT);
  pinMode(ledOrange, OUTPUT);
  pinMode(ledGreen, OUTPUT);

  lcd.begin(16, 2);
  lcd.print("Reaction Racer");
  delay(1500);
  lcd.clear();
  Serial.begin(9600);
}

void loop() {
  unsigned long fastestTime = 999999; // initialement très grand
  int fastestPlayer = -1;

  for (int player = 1; player <= NUM_PLAYERS; player++) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Player ");
    lcd.print(player);
    lcd.setCursor(0,1);
    lcd.print("Get Ready...");
    delay(1000);

    // --- Séquence de feux ---
    digitalWrite(ledRed, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("RED - Get Ready");
    delay(1000 + random(1000, 3000));

    digitalWrite(ledRed, LOW);
    digitalWrite(ledOrange, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ORANGE - Ready?");
    delay(500 + random(500, 1500));

    digitalWrite(ledOrange, LOW);
    digitalWrite(ledGreen, HIGH); // feu vert
    unsigned long chronoStart = millis();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("GREEN - GO!");
    lcd.setCursor(0,1);
    lcd.print("Time: 0 ms");
    Serial.println("GO! Chrono started!");

    unsigned long reactionTime = 0;

    // --- Chrono en direct jusqu'à appui ---
    while (true) {
      int buttonState = digitalRead(BUTTONPIN);
      unsigned long currentTime = millis() - chronoStart;

      // Affichage live sur LCD
      lcd.setCursor(6,1);
      lcd.print("      "); // effacer l'ancienne valeur
      lcd.setCursor(6,1);
      lcd.print(currentTime);
      lcd.print(" ms");

      if (buttonState == LOW) {
        reactionTime = currentTime;
        Serial.print("Player ");
        Serial.print(player);
        Serial.print(" pressed! Reaction time: ");
        Serial.print(reactionTime);
        Serial.println(" ms");
        break;
      }
      delay(10);
    }

    // --- Fin de tour ---
    digitalWrite(ledGreen, LOW);

    // Vérifier si c'est le meilleur temps
    if (reactionTime < fastestTime) {
      fastestTime = reactionTime;
      fastestPlayer = player;
    }

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Player ");
    lcd.print(player);
    lcd.setCursor(0,1);
    lcd.print("Time: ");
    lcd.print(reactionTime);
    lcd.print(" ms");
    delay(delayBetweenRounds);
  }

  // --- Afficher le gagnant ---
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Fastest Player:");
  lcd.setCursor(0,1);
  lcd.print("Nb ");
  lcd.print(fastestPlayer);
  lcd.print(" - ");
  lcd.print(fastestTime);
  lcd.print(" ms");

  Serial.print("Fastest Player: ");
  Serial.print(fastestPlayer);
  Serial.print(" with ");
  Serial.print(fastestTime);
  Serial.println(" ms");

  delay(10000); // pause avant nouvelle manche
}
