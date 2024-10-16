#define BLYNK_TEMPLATE_ID "TMPL6KeqWa9Yg"
#define BLYNK_TEMPLATE_NAME "DoorLockSystem"
#define BLYNK_AUTH_TOKEN "WNfNQmsPkbPRdYsd3trNY2Le3yqH_60k"

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <BlynkSimpleEsp32.h>

#define SS_PIN 5
#define RST_PIN 0

#define SSID "Nhat Truong"
#define PASS "Team__3T"

MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;
byte nuidPICC[4] = {0x23, 0x59, 0xA6, 0x29};
byte nuidPICC_1[4] = {0xF3, 0xF3, 0xA4, 0x14};

char auth[] = BLYNK_AUTH_TOKEN;

BLYNK_WRITE(V1)
{
    if (param.asInt() == 1)
    {
        Serial.write(1);
    }
    else if (param.asInt() == 2)
    {
        Serial.write(2);
    }
}

void setup()
{
    Serial.begin(9600);
    SPI.begin();
    rfid.PCD_Init();

    for (byte i = 0; i < 6; i++)
    {
        key.keyByte[i] = 0xFF;
    }

    Blynk.begin(auth, SSID, PASS);
}

void loop()
{
    Blynk.run();

    if (!rfid.PICC_IsNewCardPresent())
    {
        return;
    }

    if (!rfid.PICC_ReadCardSerial())
    {
        return;
    }

    if (rfid.uid.uidByte[0] == nuidPICC[0] &&
        rfid.uid.uidByte[1] == nuidPICC[1] &&
        rfid.uid.uidByte[2] == nuidPICC[2] &&
        rfid.uid.uidByte[3] == nuidPICC[3])
    {
        Serial.write(1);
        Blynk.virtualWrite(V0, "Welcome FPT!");
    }
    else
    {
        Serial.write(2);
        Blynk.virtualWrite(V0, "WRONG CARD!!");
    }

    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
}