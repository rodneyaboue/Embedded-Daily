#define PIR_PIN 2       // Sortie du PIR
#define LED_PIN 13      // LED pour simuler la lumière

unsigned long dureeLum = 5000; // Temps lumière allumée après détection (30s)
unsigned long dernierMouvement = 0;

void setup() {
  Serial.begin(9600);
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.println("=== Détecteur de présence toilettes ===");
  Serial.println("En attente de mouvement...");
}

void loop() {
  int etat = digitalRead(PIR_PIN);

  if (etat == HIGH) {
    // Mouvement détecté
    Serial.println("Présence détectée !");
    digitalWrite(LED_PIN, HIGH);
    dernierMouvement = millis();  // Mémorise l'heure du dernier mouvement
  }

  // Éteindre la lumière si pas de mouvement depuis la durée définie
  if (millis() - dernierMouvement > dureeLum) {
    digitalWrite(LED_PIN, LOW);
  }

  delay(200); // Petit délai pour le moniteur série
}
