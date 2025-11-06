#include <Servo.h>
#include <LiquidCrystal.h>

#define TRIG_PIN 9
#define ECHO_PIN 10
#define SERVO_PIN 11
#define LED_GREEN 6
#define LED_RED 7
#define BUZZER 8

Servo servo;
LiquidCrystal lcd(12, 13, 5, 4, 3, 2);

const int DANGER_DIST = 20; // cm
const int SERVO_STEP_DELAY = 30; // ms entre pas
const unsigned long BLINK_INTERVAL = 400; // ms pour LED verte
const unsigned long BEEP_INTERVAL = 800; // ms pour bip calme

int currentAngle = 0;
int servoDirection = 1; // 1=avancer, -1=reculer
long duration;
int distance;

unsigned long previousBlink = 0;
bool greenState = false;

unsigned long previousBeep = 0;

void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  servo.attach(SERVO_PIN);
  lcd.begin(16, 2);
  lcd.print("System starting...");
  delay(1500);
  lcd.clear();
}

void loop() {
  // --- Balayage servo ---
  currentAngle += servoDirection;
  if (currentAngle >= 180) servoDirection = -1;
  if (currentAngle <= 0) servoDirection = 1;
  servo.write(currentAngle);

  distance = getDistance();
  displayLCD(distance);
  displaySerial(distance);

  // --- Gestion LED verte clignotante ---
  unsigned long now = millis();
  if (distance > 0 && distance > DANGER_DIST) {
    if (now - previousBlink >= BLINK_INTERVAL) {
      previousBlink = now;
      greenState = !greenState;
      digitalWrite(LED_GREEN, greenState ? HIGH : LOW);

      // Bip doux à chaque clignotement
      if (greenState) {
        tone(BUZZER, 400, 80); // non-bloquant
      }
    }
    digitalWrite(LED_RED, LOW);
  }

  // --- Danger : LED rouge + buzzer rapide ---
  if (distance > 0 && distance <= DANGER_DIST) {
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, LOW);
    tone(BUZZER, 1000); // son continu jusqu'à sortie de danger
  } else if (!(greenState && distance > DANGER_DIST)) {
    noTone(BUZZER); // stop bip continu si pas de danger
  }

  delay(SERVO_STEP_DELAY); // vitesse constante du servo
}

// Mesure distance HC-SR04
int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 20000); // timeout 20ms
  if (duration == 0) return -1;
  return duration * 0.034 / 2;
}

// Affichage sur LCD
void displayLCD(int d) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dist: ");
  if (d < 0) lcd.print("--cm");
  else lcd.print(d), lcd.print("cm");

  lcd.setCursor(0, 1);
  if (d > 0 && d <= DANGER_DIST) lcd.print("Objet proche!");
  else lcd.print("Zone securisee");
}

// Affichage sur Serial
void displaySerial(int d) {
  Serial.print("Angle: "); Serial.print(currentAngle);
  Serial.print(" | Distance: ");
  if (d < 0) Serial.print("No echo");
  else Serial.print(d);
  Serial.print(" cm | Objet detecte: ");
  if (d > 0 && d <= DANGER_DIST) Serial.println("Oui");
  else Serial.println("Non");
}
