// ============================================
// WasteWise: ESP32 + HC-SR04 Firebase Integration
// Version: 1.0
// ============================================
// This code reads an HC-SR04 ultrasonic sensor on an ESP32
// and sends the distance + fill level data to Firebase Realtime Database
// every 5 seconds.
//
// Required Libraries:
//   1. Firebase ESP32 Client (install via Arduino IDE)
//   2. Built-in WiFi (included with ESP32)

#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <time.h>

// ============ CONFIGURATION ============

// Firebase Connection
// Note: For the Firebase ESP32 Client library, when using a Realtime DB with
// public (test) rules you should leave the auth token as an empty string "".
// If you set it to the literal string "null" the library treats that as a
// token value and will fail. For production you must use a valid database
// secret / custom token or use a secure proxy.
// These values are safe to embed for client-side SDKs (the API key is public in web SDKs)
#define FIREBASE_HOST "https://wastewise-4aa13-default-rtdb.asia-southeast1.firebasedatabase.app/"

// WiFi Credentials
#define WIFI_SSID "YOUR_SSID"
#define WIFI_PASSWORD ""  // Leave empty for open networks (no password)

// HC-SR04 Sensor Pins
#define TRIG_PIN 4      // GPIO 4
#define ECHO_PIN 2     // GPIO 2

// Bin Configuration
#define BIN_ID "BIN-001"
#define EMPTY_DISTANCE 45    // cm - distance when bin is EMPTY (sensor farthest from trash)
#define FULL_DISTANCE 2      // cm - distance when bin is FULL (sensor closest to trash)
#define SEND_INTERVAL 5000   // milliseconds between Firebase updates

// ============ GLOBAL VARIABLES ============
// We'll use REST (HTTPS) calls instead of the FirebaseESP32 library to reduce binary size
unsigned long lastSendTime = 0;
float lastDistance = 0;
//FirebaseConfig fbConfig;
//FirebaseAuth fbAuth;

// ============ SETUP ============
void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\n\n========== WasteWise ESP32 Starting ==========");
  
  // Initialize pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Connect to WiFi
  connectToWiFi();

  // Initialize SNTP (non-blocking) so we can get a unix timestamp for lastSeen
  configTime(0, 0, "pool.ntp.org", "time.google.com");
  Serial.println("NTP initialized (time sync started)");
  
  // Using REST-only approach (no Firebase library initialization)
  restPingTest();
  
  // Quick REST startup ping already performed in restPingTest()
  
  Serial.println("Setup complete!");
}

// ============ MAIN LOOP ============
void loop() {
  // Check WiFi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi lost. Reconnecting...");
    connectToWiFi();
  }
  
  // Send data at intervals
  if (millis() - lastSendTime >= SEND_INTERVAL) {
    lastSendTime = millis();
    readAndSendData();
  }
  
  delay(100);
}

// ============ FUNCTIONS ============

void connectToWiFi() {
  Serial.print("Connecting to WiFi: ");
  Serial.println(WIFI_SSID);
  
  WiFi.mode(WIFI_STA);
  // If password is empty, connect without authentication (open network)
  if (strlen(WIFI_PASSWORD) == 0) {
    WiFi.begin(WIFI_SSID);
  } else {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  }
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 30) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✓ WiFi Connected!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\n✗ WiFi Failed!");
  }
}

float readDistance() {
  // Send 10 microsecond pulse to trigger pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Measure how long ECHO pin stays high
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  
  // Convert time to distance: distance (cm) = duration (µs) / 58
  float distance = duration / 58.0;
  
  // Reject invalid readings
  if (distance <= 0 || distance > 400) {
    distance = lastDistance;
  }
  
  return distance;
}

float calculateFillPercentage(float distance) {
  // EMPTY_DISTANCE (45cm) = 0% fill (sensor far from trash)
  // FULL_DISTANCE (2cm) = 100% fill (sensor close to trash)
  // As distance decreases, fill percentage increases
  
  if (distance >= EMPTY_DISTANCE) {
    return 0.0;  // Empty - too far
  } else if (distance <= FULL_DISTANCE) {
    return 100.0;  // Full - too close
  } else {
    // Linear interpolation: closer distance = higher fill %
    float percentage = ((EMPTY_DISTANCE - distance) / (EMPTY_DISTANCE - FULL_DISTANCE)) * 100.0;
    return constrain(percentage, 0, 100);
  }
}

String getStatus(float fillPercentage) {
  if (fillPercentage >= 90) {
    return "full";
  } else if (fillPercentage >= 50) {
    return "medium";
  } else {
    return "empty";
  }
}

void readAndSendData() {
  // Take average of 3 readings
  float distance = 0;
  for (int i = 0; i < 3; i++) {
    distance += readDistance();
    delay(100);
  }
  distance /= 3.0;
  lastDistance = distance;
  
  // Calculate fill level
  float fillPercentage = calculateFillPercentage(distance);
  String status = getStatus(fillPercentage);
  
  // We'll send JSON body in restSendSensorData

  // Send to Firebase via REST
  if (restSendSensorData(distance, fillPercentage, status)) {
    Serial.print("✓ Distance: ");
    Serial.print(distance, 1);
    Serial.print("cm | Fill: ");
    Serial.print(fillPercentage, 0);
    Serial.print("% | Status: ");
    Serial.println(status);
  } else {
    Serial.println("✗ REST write failed");
  }

  // Update status and heartbeat metadata via REST
  restUpdateMetadata(status);
}

bool restSendSensorData(float distance, float fillPercentage, String status) {
  WiFiClientSecure client;
  client.setInsecure();
  HTTPClient https;
  String macStr = String((uint64_t)ESP.getEfuseMac());
  String url = String(FIREBASE_HOST) + "bins/" + String(BIN_ID) + "/sensorData/" + macStr + ".json";
  if (!https.begin(client, url)) return false;
  https.addHeader("Content-Type", "application/json");
  String body = "{";
  body += "\"distance\":" + String(distance, 2) + ",";
  body += "\"fillPercentage\":" + String(fillPercentage, 1) + ",";
  body += "\"status\":\"" + status + "\",";
  body += "\"timestamp\":" + String(millis()) + ",";
  body += "\"deviceId\":\"ESP32_" + String((uint64_t)ESP.getEfuseMac()) + "\"";
  body += "}";
  int code = https.PUT(body);
  String resp = https.getString();
  https.end();
  return (code >= 200 && code < 300);
}

void restUpdateMetadata(String status) {
  WiFiClientSecure client;
  client.setInsecure();
  HTTPClient https;
  String macStr = String((uint64_t)ESP.getEfuseMac());
  // lastSeen
  time_t now = time(nullptr);
  long lastSeenVal = (now > 100000) ? (long)now : (long)(millis() / 1000);
  String lastSeenUrl = String(FIREBASE_HOST) + "bins/" + String(BIN_ID) + "/lastSeen.json";
  if (https.begin(client, lastSeenUrl)) {
    https.addHeader("Content-Type", "application/json");
    https.PUT(String(lastSeenVal));
    https.end();
  }
  // connected
  String connectedUrl = String(FIREBASE_HOST) + "bins/" + String(BIN_ID) + "/connected.json";
  if (https.begin(client, connectedUrl)) {
    https.addHeader("Content-Type", "application/json");
    https.PUT("true");
    https.end();
  }
  // status
  String statusUrl = String(FIREBASE_HOST) + "bins/" + String(BIN_ID) + "/status.json";
  if (https.begin(client, statusUrl)) {
    https.addHeader("Content-Type", "application/json");
    https.PUT("\"" + status + "\"");
    https.end();
  }
}

// Perform an HTTPS PUT to the REST endpoint to test direct DB access
void restPingTest() {
  Serial.println("[restTest] Starting REST ping test...");
  WiFiClientSecure client;
  client.setInsecure(); // NOTE: for production, install CA root or fingerprint

  HTTPClient https;
  String macStr = String((uint64_t)ESP.getEfuseMac());
  String url = String(FIREBASE_HOST) + "connectionPing/esp32_rest_" + macStr + ".json";
  // If your DB requires an auth token, append ?auth=TOKEN
  Serial.print("[restTest] PUT ");
  Serial.println(url);

  if (https.begin(client, url)) {
    https.addHeader("Content-Type", "application/json");
    String body = "{\"ts\": \"" + String(millis() / 1000) + "\"}";
    int code = https.PUT(body);
    Serial.print("[restTest] HTTP code: ");
    Serial.println(code);
    String resp = https.getString();
    Serial.print("[restTest] Resp: ");
    Serial.println(resp);
    https.end();
  } else {
    Serial.println("[restTest] HTTPS begin failed");
  }
}
