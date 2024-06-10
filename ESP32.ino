#define BLYNK_TEMPLATE_ID "TMPL33XRdh8rV"
#define BLYNK_TEMPLATE_NAME "accident avoiding system"
#define BLYNK_AUTH_TOKEN "F_tiayA3z4ehjVdMVQ4iOHFEhS7e20cd"
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <TinyGPSPlus.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "realme";  
char pass[] = "12345678";  

#define BUZZ_PIN 18
#define SWITCH_PIN 19

TinyGPSPlus gps;

void setup() {
  Serial.begin(9600);
  
  Blynk.begin(auth, ssid, pass);
  pinMode(SWITCH_PIN, INPUT);

  pinMode(BUZZ_PIN, OUTPUT);
  
  
  delay(3000);
}

void loop() {
  Blynk.run();

  

displayInfo();
  if (digitalRead(SWITCH_PIN) == HIGH) {
    delay(500);
    while (Serial2.available() > 0) {
      if (gps.encode(Serial2.read())) {
        displayInfo();
         Blynk.virtualWrite(V1, "Denger area go slow");
         digitalWrite(BUZZ_PIN, HIGH);
         delay(3000);
         digitalWrite(BUZZ_PIN, LOW);
         
      }
    }

    if (millis() > 5000 && gps.charsProcessed() < 10) {
      Serial.println(F("No GPS detected: check wiring."));
      while (true);
    }
  }
  
  delay(1000);
}

void displayInfo() {
  Serial.print(F("Location: "));

  char locationStr[20];

  if (gps.location.isValid()) {
    sprintf(locationStr, "%.6f,%.6f", gps.location.lat(), gps.location.lng());
  } else {
    sprintf(locationStr, "NO_GPS");
  }

  Blynk.virtualWrite(V0, locationStr);
//Blynk.virtualWrite(V0, "19.89225, 75.3466");
  Serial.print("Lat: ");
  Serial.print(gps.location.lat(), 6);
  Serial.print(F(", Lng: "));
  Serial.print(gps.location.lng(), 6);
  Serial.println();
}