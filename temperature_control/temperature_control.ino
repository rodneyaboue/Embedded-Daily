#include <LiquidCrystal.h>
#include <DHT.h>
#define  DHT_PIN 6
#define DHTTYPE DHT11
#define LED_ROUGE 9
#define LED_BLEUE 10

// === Seuils de température ===
const float TEMP_BASSE = 22.0;  // seuil bas
const float TEMP_HAUTE = 22.20;  // seuil haut

DHT dht(DHT_PIN, DHTTYPE);;

int rs = 12;
int en = 11;
int d4 = 5;
int d5 = 4;
int d6 = 3;
int d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  dht.begin();
  pinMode(LED_ROUGE, OUTPUT);
  pinMode(LED_BLEUE, OUTPUT);
  lcd.clear();
}

void loop() {
  
float temp = dht.readTemperature();
float hum = dht.readHumidity();
 if (isnan(temp) || isnan(hum)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Erreur capteur");
    delay(2000);
    return;
  }

// Affichage sur LCD
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Temp : ");
lcd.print(temp);
lcd.setCursor(0,1);
lcd.print("Humidity : ");
lcd.print(hum);

  // === Contrôle des LEDs ===
  if (temp <= TEMP_BASSE) {
    // Température trop basse → LED bleue clignote
    digitalWrite(LED_BLEUE, HIGH);
    delay(500);
    digitalWrite(LED_BLEUE, LOW);
    delay(500);
  }
  else if (temp >= TEMP_HAUTE) {
    // Température trop haute → LED rouge clignote
    digitalWrite(LED_ROUGE, HIGH);
    delay(500);
    digitalWrite(LED_ROUGE, LOW);
    delay(500);
  }
  else {
    // Température normale → LEDs éteintes
    digitalWrite(LED_ROUGE, LOW);
    digitalWrite(LED_BLEUE, LOW);
    delay(1000);
  } 

}
