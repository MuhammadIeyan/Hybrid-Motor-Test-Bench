int increm = 0; // Variable pour l'augmentation/diminution progressive de la tension const int choixPin = 9; // Pin pour la commande de vitesse
const int motorOnOffPin = 8; // Broche pour allumer/éteindre le moteur (digitale) const int
motorDirectionPin = 7; // Broche pour le sens de rotation (digitale) bool motorOn = false; // État du
moteur
bool motorForward = true; // Direction du moteur

void setup() {
  Serial.begin(9600);
  pinMode(choixPin, OUTPUT);
  pinMode(motorOnOffPin, OUTPUT); // Configure la broche d'allumage/éteignage en sortie
  pinMode(motorDirectionPin, OUTPUT);// Configure la broche de direction en sortie
  digitalWrite(motorOnOffPin, LOW); // Éteint initialement le moteur digitalWrite(motorDirectionPin, LOW); // Par défaut, tourne dans le sens "forward"
  Serial.println("Entrez 'on' pour allumer le moteur, 'off' pour l'éteindre,");
  Serial.println("'forward' pour avancer, 'backward' pour reculer.");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readString();
    input.trim(); // Supprimer les espaces en début et en fin de chaîne
    
    if (input == "on") {
      motorOn = true;
      Serial.println("Moteur allumé.");
    }

    else if (input == "off") {
      motorOn = false;
      Serial.println("Moteur éteint.");
      analogWrite(choixPin, 0); // Assure que le moteur est éteint } else if (input== "forward") {
      motorForward = true;
      Serial.println("Direction : Avant.");
    }

    else if (input == "backward") {
      motorForward = false;
      Serial.println("Direction : Arrière.");
    }

    else {
      Serial.println("Commande invalide. Entrez 'on', 'off', 'forward' ou 'backward'."); }
    }

    // Si le moteur est allumé et une direction est définie
    if (motorOn) {
      digitalWrite(motorOnOffPin, HIGH); // Allume le moteur
      
      // Changer la direction du moteur
      if (motorForward) {
        digitalWrite(motorDirectionPin, HIGH); // Avant
      }
      
      else {
        digitalWrite(motorDirectionPin, LOW); // Arrière
      }
      
      // Augmente la tension de 0 à 5V (0 à 255) en 5 secondes
      for (increm = 0; increm <= 255; increm++) {
      
        analogWrite(choixPin, increm);
        delay(20); // 20 ms pour chaque pas => 255 * 20 ms = ~5 secondes }
        
        // Maintient la tension à 5V pendant 10 secondes
        analogWrite(choixPin, 255);
        delay(10000);
      }
      
      // Diminue la tension de 5V à 0V en 5 secondes
      for (increm = 255; increm >= 0; increm--) {
        analogWrite(choixPin, increm);
        delay(20); // 20 ms pour chaque pas => 255 * 20 ms = ~5 secondes }
        // Éteint le moteur une fois le cycle terminé
        motorOn = false; // Réinitialise l'état
        digitalWrite(motorOnOffPin, LOW); // Éteint le moteur
        Serial.println("Cycle terminé, moteur éteint.");
      }
    }
}