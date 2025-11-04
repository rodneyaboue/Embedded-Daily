// #include <LiquidCrystal.h>

// #define BUTTONPIN 2  // bouton du joystick
// int buttonState = HIGH;  // état initial (INPUT_PULLUP)

// const int ledRed = 3;
// const int ledOrange = 4;
// const int ledGreen = 5;

// unsigned long chronoStart = 0;
// unsigned long reactionTime = 0;
// bool greenLight = false;

// // LCD pins
// int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
// LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// void setup() {
//   pinMode(BUTTONPIN, INPUT_PULLUP); // résistance interne
//   pinMode(ledRed, OUTPUT);
//   pinMode(ledOrange, OUTPUT);
//   pinMode(ledGreen, OUTPUT);

//   lcd.begin(16, 2);
//   lcd.print("Reaction Racer");
//   delay(1000);
//   lcd.clear();
//   Serial.begin(9600);
// }

// void loop() {
//   delay(1000);
//   lcd.clear();
//   // Séquence feux
//   digitalWrite(ledRed, HIGH);
//   digitalWrite(ledOrange, LOW);
//   digitalWrite(ledGreen, LOW);
//   lcd.clear();
//   lcd.setCursor(0,0);
//   lcd.print("RED - Get Ready");
//   delay(1000 + random(0, 2000));

//   digitalWrite(ledRed, LOW);
//   digitalWrite(ledOrange, HIGH);
//   lcd.clear();
//   lcd.setCursor(0,0);
//   lcd.print("ORANGE - Ready?");
//   delay(500 + random(0, 1000));

//   digitalWrite(ledOrange, LOW);
//   digitalWrite(ledGreen, HIGH); // feu vert
//   greenLight = true;
//   chronoStart = millis();
//   lcd.clear();
//   lcd.setCursor(0,0);
//   lcd.print("GREEN - GO!");
//   lcd.setCursor(0,1);
//   lcd.print("Press joystick!");
//   Serial.println("GO! Chrono started!");

//   // Attente appui joystick
//   while (true) {
//     buttonState = digitalRead(BUTTONPIN);

//     if (buttonState == LOW) { // bouton appuyé
//       reactionTime = millis() - chronoStart;
//       Serial.print("Joystick pressed! Reaction time: ");
//       Serial.print(reactionTime);
//       Serial.println(" ms");

//       lcd.clear();
//       lcd.setCursor(0,0);
//       lcd.print("ReactTime:");
//       // lcd.setCursor(0,1);
//       lcd.print(reactionTime);
//       lcd.print(" ms");
//       break;
//     }
//     delay(10); // anti-rebond simple
//   }

//   // Fin de séquence
//   greenLight = false;
//   digitalWrite(ledGreen, LOW);

//   delay(10000); // pause avant nouvelle séquence
// }
#include <LiquidCrystal.h>

#define BUTTONPIN 2  // bouton du joystick
int buttonState = HIGH;  // état initial (INPUT_PULLUP)

const int ledRed = 3;
const int ledOrange = 4;
const int ledGreen = 5;

unsigned long chronoStart = 0;
unsigned long reactionTime = 0;
bool greenLight = false;

// LCD pins
int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

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
  greenLight = true;
  chronoStart = millis();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("GREEN - GO!");
  lcd.setCursor(0, 1);
  lcd.print("Time: 0 ms");
  Serial.println("GO! Chrono started!");

  // --- Chrono en direct jusqu'à appui ---
  while (true) {
    buttonState = digitalRead(BUTTONPIN);
    unsigned long currentTime = millis() - chronoStart;

    // Affichage en direct
    lcd.setCursor(6, 1);
    lcd.print("      "); // effacer ancienne valeur
    lcd.setCursor(6, 1);
    lcd.print(currentTime);
    lcd.print(" ms");

    if (buttonState == LOW) { // bouton appuyé
      reactionTime = currentTime;
      Serial.print("Joystick pressed! Reaction time: ");
      Serial.print(reactionTime);
      Serial.println(" ms");

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Final Reaction:");
      lcd.setCursor(0, 1);
      lcd.print(reactionTime);
      lcd.print(" ms");
      break;
    }
    delay(10); // anti-rebond simple
  }

  // --- Fin de séquence ---
  greenLight = false;
  digitalWrite(ledGreen, LOW);
  delay(10000); // pause avant nouvelle manche
}
