#include <WiFi.h> // Bibliothèque WiFi pour ESP32
#include <HTTPClient.h>

// Remplacer par les informations de votre partage de connexion
const char* ssid = "RedmiNote11 ";   // Nom du SSID de votre partage de connexion
const char* password = "123456789";              // Mot de passe du partage de connexion
const char* serverName = "http://192.168.62.104:3000/data";

void setup() {
  // Initialisation de la communication série pour le débogage
  Serial.begin(115200);
  delay(1000); // Attendre un peu pour éviter d'initier trop vite

  // Connexion au Wi-Fi
  Serial.println();
  Serial.println("Connexion au Wi-Fi...");
  
  // Lancement de la tentative de connexion
  WiFi.begin(ssid, password);

  // Attendre que l'ESP32 soit connecté au Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  // Une fois connecté
  Serial.println("");
  Serial.println("Wi-Fi connecté !");
  Serial.print("Adresse IP : ");
  Serial.println(WiFi.localIP());  // Afficher l'adresse IP locale

   if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;

    // Démarrer la requête GET
    http.begin(serverName);
    int httpResponseCode = http.GET();  // Effectuer la requête GET

    if (httpResponseCode > 0) { // Si la requête est réussie
      String response = http.getString();  // Réponse du serveur
      Serial.print("Réponse du serveur : ");
      Serial.println(response);
    } else {
      Serial.print("Erreur dans la requête : ");
      Serial.println(httpResponseCode);
    }
    
    // Libérer les ressources
    http.end();
  }
}





void loop() {
  // Rester connecté au Wi-Fi
}



/*
void setup() {
  Serial.begin(115200);
  delay(1000);
  
  // Démarrer le module WiFi
  Serial.println("Scan des réseaux WiFi en cours...");
  WiFi.mode(WIFI_STA);
  WiFi.disconnect(); // S'assurer qu'il n'est connecté à rien
  delay(1000);

  // Scanner les réseaux disponibles
  int n = WiFi.scanNetworks();
  Serial.println("Scan terminé !");
  
  if (n == 0) {
    Serial.println("Aucun réseau WiFi trouvé");
  } else {
    Serial.print(n);
    Serial.println(" réseaux WiFi trouvés :");
    for (int i = 0; i < n; ++i) {
      // Afficher le SSID et la puissance du signal de chaque réseau
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));   // Nom du réseau (SSID)
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));   // Puissance du signal
      Serial.println(" dBm)");
      delay(10);
    }
  }
}

void loop() {
  // Rien à faire ici
}
*/