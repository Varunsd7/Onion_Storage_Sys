// ================= BLYNK DETAILS =================
#define BLYNK_TEMPLATE_ID "TMPL3w-l9fPsn"
#define BLYNK_TEMPLATE_NAME "IoT Onion Storage"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"

// ================= TELEGRAM =================
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

// 🔴 TELEGRAM DETAILS
#define BOT_TOKEN "8775180330:AAFc4sFMVqZEZYcVOCi6kqhU4AijsGmIWBM"
#define CHAT_ID   "5472052074"

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

unsigned long lastTelegramUpdateId = 0;

// ================= WIFI & BLYNK =================
const char auth[] = "cG6v0Ew3Jw1SjbaMgCGYzz6kaZr3NGhM";
const char ssid[] = "vinit";
const char pass[] = "12345677";

// ================= SENSORS =================
#define DHTPIN 22
#define DHTTYPE DHT11
const int gasSensorPin = 34;

DHT dht(DHTPIN, DHTTYPE);

// ================= MOTOR PINS (L293D) =================
#define EN_A 25
#define IN1 26
#define IN2 27

#define EN_B 14
#define IN3 12
#define IN4 13

// ================= PWM SETTINGS =================
#define PWM_CH_A 0
#define PWM_CH_B 1
#define PWM_FREQ 1000
#define PWM_RES 10   // 0–1023

int SPEED = 1023;

// ================= SETUP =================
void setup() {
  Serial.begin(115200);

  // Sensors
  dht.begin();
  pinMode(gasSensorPin, INPUT);

  // Motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopMotor();

  // Blynk
  Blynk.begin(auth, ssid, pass);

  // Telegram
  secured_client.setInsecure();   // REQUIRED
}

// ================= BLYNK MOTOR CONTROL =================
BLYNK_WRITE(V4) {
  int motorState = param.asInt();
  if (motorState == 1)
    motorON();
  else
    stopMotor();
}

// ================= LOOP =================
void loop() {
  Blynk.run();

  // Read sensors
  int gasValue = analogRead(gasSensorPin);
  int gasPercent = map(gasValue, 0, 4095, 0, 100);

  float temp = dht.readTemperature();
  float hum  = dht.readHumidity();

  if (!isnan(temp) && !isnan(hum)) {
    Blynk.virtualWrite(V0, gasPercent);
    Blynk.virtualWrite(V1, temp);
    Blynk.virtualWrite(V2, hum);
  }

  handleTelegram();

  delay(1000);
}

// ================= TELEGRAM HANDLER =================
void handleTelegram() {
  int numNewMessages = bot.getUpdates(lastTelegramUpdateId + 1);

  for (int i = 0; i < numNewMessages; i++) {
    lastTelegramUpdateId = bot.messages[i].update_id;

    String text = bot.messages[i].text;
    String chat_id = bot.messages[i].chat_id;

    Serial.println("Telegram: " + text);

    if (chat_id != CHAT_ID) {
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }

    if (text == "/start") {
      bot.sendMessage(chat_id,
        "👋 *Welcome to Onion Storage Bot*\n\n"
        "Send *hi* to get sensor readings.",
        "Markdown");
    }

    if (text == "hi" || text == "Hi" || text == "HI") {
      int gasValue = analogRead(gasSensorPin);
      int gasPercent = map(gasValue, 0, 4095, 0, 100);

      float temp = dht.readTemperature();
      float hum  = dht.readHumidity();

      String msg = "📦 *Onion Storage Status*\n\n";
      msg += "🌡 Temperature: " + String(temp) + " °C\n";
      msg += "💧 Humidity: " + String(hum) + " %\n";
      msg += "🧪 Gas Level: " + String(gasPercent) + " %";

      bot.sendMessage(chat_id, msg, "Markdown");
    }
  }
}

// ================= MOTOR FUNCTIONS =================
void motorON() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  ledcWrite(PWM_CH_A, SPEED);
  ledcWrite(PWM_CH_B, SPEED);
}

void stopMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  ledcWrite(PWM_CH_A, 0);
  ledcWrite(PWM_CH_B, 0);
}
