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

const char* apiIP = "192.168.1.2":
const int apiPort = 8080; // Le port n'est peut etre pas le bon

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

void sendDataToAPI(const char* data) {
  Serial.print("Sending data to API: ");
  Serial.println(data);

  WiFiClient client;

  if (client.connect(apiIP, apiPort)) {
    client.print("POST /votre-route HTTP/1.1\r\n"); // Saisir l'URL de l'API
    client.print("Host: ");
    client.print(apiIP);
    client.print("\r\n");
    client.print("Content-Type: application/json\r\n");
    client.print("Content-Length: ");
    client.print(strlen(data));
    client.print("\r\n\r\n");
    client.print(data);

    Serial.println("Data sent to API");
  } else {
    Serial.println("Failed to connect to Raspberry Pi");
  }

  client.stop();
}

void cleanupAuthorizedUID() {
  // Ici, vous pourriez effectuer des opérations de nettoyage si nécessaire.
  // Par exemple, effacer les données de la carte autorisée après un certain temps.
}

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
      sendDataToAPI("Access Granted");
      digitalWrite(3, HIGH);
      delay(1000);
    } else {
      Serial.println("Accès refusé !");
      sendDataToAPi("Access Denied");
      digitalWrite(4, HIGH);
      delay(1000);
    }

    mfrc522.PICC_HaltA();
  }
  cleanupAuthorizedUID();
}

bool compareUID(byte storedUID[][4], byte* detectedUID, byte size) {
  for (byte i = 0; i < 2; i++) {
    if (memcmp(storedUID[i], detectedUID, size) == 0) {
      return true;
    }
  }
  return false;
}
