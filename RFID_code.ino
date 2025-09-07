#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Store previous scan data
struct Attendance {
  String cardID;
  String name;
  bool isCheckedIn;
};

Attendance records[10];  // Max 10 entries
int recordCount = 0;

String validCards[][2] = {
    {"EC75C71", "Krishna"},
    {"C77372", "Ravi"},
    {"2226353", "Abhay"},
    {"5E3362", "Devesh sir"}};

int totalCards = sizeof(validCards) / sizeof(validCards[0]);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.init();
  lcd.backlight();

  Serial.println("CLEARDATA");
  Serial.println("LABEL, Time, Card ID, Name, Status, Time IN, Time OUT");
  Serial.println("RESETTIMER");

  lcd.setCursor(0, 0);
  lcd.print("Scan Your Card");
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial()) return;

  String cardID = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    cardID += String(mfrc522.uid.uidByte[i], HEX);
  }
  cardID.toUpperCase();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Checking...");
  delay(1000);

  String personName = "";
  bool isValid = false;

  for (int i = 0; i < totalCards; i++) {
    if (cardID.equalsIgnoreCase(validCards[i][0])) {
      isValid = true;
      personName = validCards[i][1];
      break;
    }
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  
  if (isValid) {
    bool found = false;
    for (int i = 0; i < recordCount; i++) {
      if (records[i].cardID == cardID) {
        found = true;
        if (records[i].isCheckedIn) {
          lcd.print("Goodbye, ");
          lcd.setCursor(0, 1);
          lcd.print(personName);
          Serial.print("DATA, TIME, ");
          Serial.print(cardID);
          Serial.print(", ");
          Serial.print(personName);
          Serial.print(", Exited, , TIME");
          Serial.println();
          records[i].isCheckedIn = false;
        } else {
          lcd.print("Welcome Back!");
          lcd.setCursor(0, 1);
          lcd.print(personName);
          Serial.print("DATA, TIME, ");
          Serial.print(cardID);
          Serial.print(", ");
          Serial.print(personName);
          Serial.print(", Present, TIME, ");
          Serial.println();
          records[i].isCheckedIn = true;
        }
        break;
      }
    }
    if (!found) {
      records[recordCount].cardID = cardID;
      records[recordCount].name = personName;
      records[recordCount].isCheckedIn = true;
      recordCount++;
      lcd.print("Welcome:");
      lcd.setCursor(0, 1);
      lcd.print(personName);
      Serial.print("DATA, TIME, ");
      Serial.print(cardID);
      Serial.print(", ");
      Serial.print(personName);
      Serial.print(", Present, TIME, ");
      Serial.println();
    }
  } else {
    lcd.print("Access Denied");
    lcd.setCursor(0, 1);
    lcd.print("Try Again");
    Serial.print("DATA, TIME, ");
    Serial.print(cardID);
    Serial.print(", Unknown, Absent");
    Serial.println();
  }

  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scan Your Card");
}