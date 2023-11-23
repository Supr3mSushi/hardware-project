#include <Wire.h>
#include <MFRC522.h>
#include <SPI.h>
#include <WiFi.h>
#include <ArduinoJson.h>

#define RST_PIN 2   // Broche de réinitialisation (RST) du lecteur RFID
#define SS_PIN  6    // Broche SDA du lecteur RFID (pour ESP32)

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Crée un objet MFRC522

// UID du badge autorisé
byte authorizedUID[][4] = {
  {0xA3, 0x03, 0x69, 0x99},
  {0x14, 0x99, 0xE3, 0x62},
};

const char *ssid = "NUMERICABLE-82B5";
const char *password = "KHC2EA722X";

const char* apiIP = "192.168.1.2";
const int apiPort = 3000;

// Fonction pour se connecter au WiFi
void connectToWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");
}

// Fonction pour envoyer une requête POST
void sendPostRequest(const char* url, const char* data, int port) {
  WiFiClient client;

  if (client.connect(apiIP, port)) {
    client.print("POST ");
    client.print(url);
    client.print(" HTTP/1.1\r\n");
    client.print("Host: ");
    client.print(apiIP);
    client.print(":");
    client.print(port);
    client.print("\r\n");
    client.print("Content-Type: application/json\r\n");
    client.print("Content-Length: ");
    client.print(strlen(data));
    client.print("\r\n\r\n");
    client.print(data);

    Serial.println("POST Request sent to API");
  } else {
    Serial.println("Failed to connect to API");
  }

  client.stop();
}


// Fonction pour envoyer une requête GET
void sendGetRequest(const char* url) {
  WiFiClient client;

  if (client.connect(apiIP, apiPort)) {
    client.print("GET ");
    client.print(url);
    client.print(" HTTP/1.1\r\n");
    client.print("Host: ");
    client.print(apiIP);
    client.print("\r\n\r\n");

    Serial.println("GET Request sent to API");
  } else {
    Serial.println("Failed to connect to API");
  }

  client.stop();
}

// Fonction pour envoyer une requête DELETE
void sendDeleteRequest(const char* url) {
  WiFiClient client;

  if (client.connect(apiIP, apiPort)) {
    client.print("DELETE ");
    client.print(url);
    client.print(" HTTP/1.1\r\n");
    client.print("Host: ");
    client.print(apiIP);
    client.print("\r\n\r\n");

    Serial.println("DELETE Request sent to API");
  } else {
    Serial.println("Failed to connect to API");
  }

  client.stop();
}

// Fonction pour envoyer une requête PUT
void sendPutRequest(const char* url, const char* data) {
  WiFiClient client;

  if (client.connect(apiIP, apiPort)) {
    client.print("PUT ");
    client.print(url);
    client.print(" HTTP/1.1\r\n");
    client.print("Host: ");
    client.print(apiIP);
    client.print("\r\n");
    client.print("Content-Type: application/json\r\n");
    client.print("Content-Length: ");
    client.print(strlen(data));
    client.print("\r\n\r\n");
    client.print(data);

    Serial.println("PUT Request sent to API");
  } else {
    Serial.println("Failed to connect to API");
  }

  client.stop();
}

// Fonction pour envoyer une requête PATCH
void sendPatchRequest(const char* url, const char* data) {
  WiFiClient client;

  if (client.connect(apiIP, apiPort)) {
    client.print("PATCH ");
    client.print(url);
    client.print(" HTTP/1.1\r\n");
    client.print("Host: ");
    client.print(apiIP);
    client.print("\r\n");
    client.print("Content-Type: application/json\r\n");
    client.print("Content-Length: ");
    client.print(strlen(data));
    client.print("\r\n\r\n");
    client.print(data);

    Serial.println("PATCH Request sent to API");
  } else {
    Serial.println("Failed to connect to API");
  }

  client.stop();
}

// ... Autres fonctions nécessaires ...

void setup() {
  Serial.begin(115200);  // Initialise la communication série
  Wire.begin();
  while (!Serial);
  SPI.begin();
  mfrc522.PCD_Init();
  delay(4);
  mfrc522.PCD_DumpVersionToSerial();
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);
  connectToWiFi();
}

void loop() {
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(7, LOW);

  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    Serial.print("Carte détectée avec UID : ");
    mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
    Serial.println();

    if (compareUID(authorizedUID, mfrc522.uid.uidByte, mfrc522.uid.size)) {
      Serial.println("Accès autorisé !");

      // Exemple d'utilisation des fonctions avec le port spécifié
      sendPostRequest("/api/badges", "{\"badge_id\":\"123\", \"name\":\"John Doe\"}", 3000);
      sendGetRequest("/api/badges", 3000);
      sendPutRequest("/api/badges/{id}", "{\"badge_id\":\"123\", \"name\":\"John Smith\"}", 3000);
      sendDeleteRequest("/api/badges/{id}", 3000);
      sendPatchRequest("/api/badges/{badge_id}/scan", "{\"scanned\":true}", 3000);

      digitalWrite(3, HIGH);
      delay(1000);
    } else {
      Serial.println("Accès refusé !");
      digitalWrite(4, HIGH);
      delay(1000);
    }

    mfrc522.PICC_HaltA();
  }
  // cleanupAuthorizedUID();
}
