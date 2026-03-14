#include <Arduino.h>
#include <WiFi.h>
#include <ESP_Google_Sheet_Client.h>
#include <GS_SDHelper.h>

// =====================
// 1) WiFi credentials
// =====================
#define WIFI_SSID "GSSS_AIML2"
#define WIFI_PASSWORD "GSSS@1234"

// =====================
// 2) Service account values from JSON
// =====================
#define PROJECT_ID "women-safety-iot"
#define CLIENT_EMAIL "esp32-sheet-logger@women-safety-iot.iam.gserviceaccount.com"

// Paste the ENTIRE private key here, split across lines if needed.
// Keep the \n at the end of each line.
const char PRIVATE_KEY[] PROGMEM =
"-----BEGIN PRIVATE KEY-----\n"
"MIIEuwIBADANBgkqhkiG9w0BAQEFAASCBKUwggShAgEAAoIBAQDTnfwpiZXlE+bu\n"
"rL7lNXqJaR7gsHICKbD+Tqn0U/9Q9/pI4XtrmWBy8fI1YneAcWtFdasrcVJMmPON\n"
"6WWj6ssS8fVCMvAy/fPw0BlletkpjCoykJc8/ZmifSFX8PM1RRLMvuuqbMC4W+p8\n"
"Lq3HL29RfURp2u8mnqqjzUL5s2NcBd7tOnMZJlc6BeXkALnbyvPa4DUtU1yS4LAa\n"
"WAB84EQCiWmFMV+kTt+avgF7uyO3YKaFSaRvK0Q3UUx0tJjxc3Nbuphg29FhaWAK\n"
"xSJ7601MFSM8ySS+5Fhddh+QqdGFuS8oiQqxGBurngikDA1uRe+7P5CFOxzV2zbK\n"
"GX6vlGoNAgMBAAECgf9MeY0oI4Zfw6RyvdaN8JV2xbUfy4etirD8hV+4NE2C9iEf\n"
"Cs9PeTH/D4ISl9emIlO3QmwjsBBMTY6aiKQ4L4+kHZ7o7emGJTVaxbOwjISdwMAs\n"
"/4c84vDw3Rzy1m1mkUyhejSJATSBnh5Suo7xaNHcHTWuRHLkvt9loDrPSXkH5RZl\n"
"GHV4h/m+t72BJjSywK98h5N0Oo5JsrggptJSO5LC2WNabmHM32wo50yI9th1z+iI\n"
"f/f7i95q8V5ovAqkPCPw8Y8LAoufPQz7pqHrNiNuNdNbK9DdQxcC5IWYsVPPNbrR\n"
"aDjaqNXBOCW0i83/GJ59knAVRMm+J61zdA30OOkCgYEA8gRu+gZb3luih2RqfXtO\n"
"PtX1XWRIY8CI4VI24JzTz/iUCNrlTshnqWOegA6XjFnxzkodlKN+kjELngS4B9jP\n"
"vgirZrZ4UISQfcjFQDmt/WuLspl2zkoopYuL6v+0W6mQ6+A7rWslVXbhMNPqmFAh\n"
"sNPE9Iw+DOK7rsysBQq1V7kCgYEA39fqlJqAKjLW3BpQAaXSfjpoqttN/L86JOQF\n"
"Y6ixZ7Kq6RF80kHuZrqh0aM0zDV2gIEq3F7r6+rDeZ98CGYqKoqn5+v1xSmpA86F\n"
"dh1VF7cOY6tQ3vzs8y85kL1A9riV7vH47M6bb+/e9bmypK5mQEUbyViKMO0+HxoP\n"
"cCoSJvUCgYAUKbJlOiplOBUuWntUwPUf3wt2IGi3hs7glszjoa0z4m3S3wnDqoaY\n"
"YihOWujdVJEEssAMJiLhYxyoqZP7c2C7YFWHVSRo8OJo2FU2qJeKSW92DbsMLLl+\n"
"MUYS6gLIsDPWsvPF2utdV24jd0RQNDzaUopSJWz1/d3NDlg2g1HgYQKBgFpxc2b3\n"
"xjFGuWnVd94ykgpOr1vZoHkvCt89ArBxyLyNhGEHn9eUrC712cxKlVqtf2QMzLSd\n"
"5dU81h6eQg9iuEbYH1+mB3fSjWfsWiCPWYJrhHThE5wFtffMbQX+cfE+Q9Z4Dowg\n"
"Ls3brcq7bWL81HPDeKayD6QVN7R5YyN+3DbBAoGBAL8j8r3Os/An6USDzurYnKcn\n"
"5fL3Uf0tNda2VxyIjiYFAodcGpl/LP1BbFZWHKeya45sF96ho1F2A4I/tXfy+y6Z\n"
"6L9E5maCb34YB2a6xGvV8FmDs6/u1KLCmopdbDdK0aP3HPqb6L1NM5ReQEhYA+Fd\n"
"uHE3WkkaKUHV5jp7k60N\n"
"-----END PRIVATE KEY-----\n";

// =====================
// 3) Google Sheet ID
// =====================
const char spreadsheetId[] = "1AN5dqio-TRwGw7dryz--1B3ty0JxR1pJHKpm0mm-yOQ";

// =====================
// 4) Touch sensor pin
// =====================
const int touchPin = 5;   // change only if your working touch pin is different

bool lastTouchState = LOW;
unsigned long lastTouchMs = 0;

// token status callback
void tokenStatusCallback(TokenInfo info) {
  Serial.printf("Token status: %s\n", GSheet.getTokenStatus(info).c_str());
  if (info.status == token_status_error) {
    Serial.printf("Token error: %s\n", GSheet.getTokenError(info).c_str());
  }
}

// WiFi connection
void connectWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
}

// append one row to Google Sheet
bool appendRow(float latitude, float longitude, const String &mapsLink) {
  FirebaseJson response;
  FirebaseJson valueRange;

  valueRange.add("range", "Sheet1!A:E");
  valueRange.add("majorDimension", "ROWS");

  valueRange.set("values/[0]/[0]", String((unsigned long)millis()));
  valueRange.set("values/[0]/[1]", String(latitude, 6));
  valueRange.set("values/[0]/[2]", String(longitude, 6));
  valueRange.set("values/[0]/[3]", mapsLink);
  valueRange.set("values/[0]/[4]", "SOS Activated");

  bool success = GSheet.values.append(
      &response,
      spreadsheetId,
      "Sheet1!A:E",
      &valueRange,
      "USER_ENTERED"
  );

  if (!success) {
    Serial.println("Append failed:");
    Serial.println(GSheet.errorReason());
    return false;
  }

  Serial.println("Row appended to Google Sheets");
  return true;
}

void setup() {
  Serial.begin(115200);
  pinMode(touchPin, INPUT);
  randomSeed(micros());

  connectWiFi();

  GSheet.setTokenCallback(tokenStatusCallback);
  GSheet.begin(CLIENT_EMAIL, PROJECT_ID, PRIVATE_KEY);

  Serial.println("Women Safety System Ready");
  Serial.println("Waiting for trigger...");
}

void loop() {
  bool currentTouchState = digitalRead(touchPin);

  if (currentTouchState == HIGH && lastTouchState == LOW && millis() - lastTouchMs > 1000) {
    lastTouchMs = millis();

    float latitude  = 8.0000 + (random(0, 290000) / 10000.0);
    float longitude = 68.0000 + (random(0, 300000) / 10000.0);
    String mapsLink = "https://maps.google.com/?q=" + String(latitude, 6) + "," + String(longitude, 6);

    Serial.println("---------------");
    Serial.println("EMERGENCY ALERT");
    Serial.println("SOS ACTIVATED");
    Serial.print("Latitude: ");
    Serial.println(latitude, 6);
    Serial.print("Longitude: ");
    Serial.println(longitude, 6);
    Serial.print("Maps Link: ");
    Serial.println(mapsLink);
    Serial.println("---------------");

    appendRow(latitude, longitude, mapsLink);

    Serial.println("System Ready Again");
    Serial.println("Waiting for trigger...");
  }

  lastTouchState = currentTouchState;
  delay(100);
}