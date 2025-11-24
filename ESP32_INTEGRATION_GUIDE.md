# ESP32 + HC-SR04 Ultrasonic Sensor to Firebase Integration

## Overview
This guide shows how to connect an ESP32 microcontroller with an HC-SR04 ultrasonic sensor to monitor trash bin fill levels and send data to your Firebase Realtime Database in real-time.

---

## Hardware Components

| Component | Quantity | Notes |
|-----------|----------|-------|
| ESP32 Development Board | 1 | WiFi + Bluetooth enabled |
| HC-SR04 Ultrasonic Sensor | 1 | Measures distance 2cm-400cm |
| Breadboard | 1 | For prototyping |
| Jumper Wires | 10+ | Male-to-male for connections |
| Micro USB Cable | 1 | For power and programming |
| Power Supply (Optional) | 1 | 5V for long-term deployment |

---

## Wiring Diagram

```
HC-SR04 Sensor:
  VCC    ──→  5V (ESP32)
  GND    ──→  GND (ESP32)
  TRIG   ──→  GPIO 5 (D5)
  ECHO   ──→  GPIO 18 (D18)

Note: HC-SR04 ECHO pin outputs 5V, but ESP32 GPIO is 3.3V tolerant.
Use a voltage divider (optional but recommended):
  ECHO → [10kΩ resistor] → GPIO 18 → [20kΩ resistor to GND]
  This reduces 5V to ~3.3V safely.
```

---

## Sensor Specifications

**HC-SR04 Ultrasonic Sensor:**
- Operating Voltage: 5V DC
- Range: 2cm to 400cm (1.97 inches to 15.75 feet)
- Accuracy: ±3mm
- Frequency: 40kHz
- Trigger Signal: 10µs pulse
- Echo Time: Proportional to distance

**Distance to Duration Conversion:**
```
Distance (cm) = (Duration in µs) / 58
or
Distance (cm) = (Duration in µs * Speed of Sound) / 2
```

---

## Software: ESP32 Arduino Code

Create a new Arduino sketch with this code:

```cpp
// ============================================
// WasteWise: ESP32 + HC-SR04 Firebase Integration
// ============================================

#include <WiFi.h>
#include <FirebaseESP32.h>

// ============ CONFIGURATION ============
#define FIREBASE_HOST "wastewise-4aa13-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "null"  // No auth key for public database

// WiFi Credentials
#define WIFI_SSID "YOUR_SSID"
#define WIFI_PASSWORD "YOUR_PASSWORD"

// HC-SR04 Pins
#define TRIG_PIN 5
#define ECHO_PIN 18

// Bin Configuration
#define BIN_ID "BIN-001"  // Match your Firebase bin ID
#define BIN_LOCATION "Library"  // Optional: for logging
#define CONTAINER_HEIGHT 50  // Height of trash bin in cm (adjust to your bin)
#define EMPTY_THRESHOLD 5    // Distance when empty (in cm from sensor)
#define FULL_THRESHOLD 15    // Distance when full (in cm from sensor)

// Timing
#define SEND_INTERVAL 5000   // Send data every 5 seconds (milliseconds)

// ============ GLOBAL VARIABLES ============
FirebaseData firebaseData;
unsigned long lastSendTime = 0;
float lastDistance = 0;

// ============ SETUP ============
void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\n\n");
  Serial.println("========== WasteWise ESP32 Startup ==========");
  
  // Initialize sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Connect to WiFi
  connectToWiFi();
  
  // Initialize Firebase
  initializeFirebase();
  
  Serial.println("Setup complete!");
}

// ============ MAIN LOOP ============
void loop() {
  // Check WiFi connection
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected! Attempting to reconnect...");
    connectToWiFi();
  }
  
  // Send data at regular intervals
  if (millis() - lastSendTime >= SEND_INTERVAL) {
    lastSendTime = millis();
    readAndSendData();
  }
  
  delay(100);  // Small delay to prevent overwhelming the loop
}

// ============ FUNCTIONS ============

// Connect to WiFi
void connectToWiFi() {
  Serial.print("Connecting to WiFi: ");
  Serial.println(WIFI_SSID);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
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
    Serial.println("\n✗ WiFi Connection Failed!");
  }
}

// Initialize Firebase connection
void initializeFirebase() {
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Serial.println("Firebase initialized");
}

// Read ultrasonic sensor and calculate distance
float readDistance() {
  // Send trigger pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Measure echo pulse duration
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);  // 30ms timeout
  
  // Calculate distance: distance = (duration in µs) / 58
  float distance = duration / 58.0;
  
  // Validate reading (must be within reasonable range)
  if (distance <= 0 || distance > 400) {
    distance = lastDistance;  // Use last valid reading
  }
  
  return distance;
}

// Calculate fill percentage (0-100%)
float calculateFillPercentage(float distance) {
  // Inverted: closer to sensor = higher fill level
  // At EMPTY_THRESHOLD (5cm) → 0%
  // At FULL_THRESHOLD (15cm) → 100%
  
  if (distance <= FULL_THRESHOLD) {
    return 100.0;  // Full
  } else if (distance >= EMPTY_THRESHOLD) {
    return 0.0;  // Empty (or sensor too far)
  } else {
    // Linear interpolation between empty and full
    float percentage = ((EMPTY_THRESHOLD - distance) / (EMPTY_THRESHOLD - FULL_THRESHOLD)) * 100.0;
    return constrain(percentage, 0, 100);
  }
}

// Determine bin status based on fill percentage
String getStatus(float fillPercentage) {
  if (fillPercentage >= 90) {
    return "full";
  } else if (fillPercentage >= 50) {
    return "medium";
  } else {
    return "empty";
  }
}

// Read sensor and send data to Firebase
void readAndSendData() {
  // Read distance from sensor (take average of 3 readings)
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
  
  // Create JSON payload
  String jsonData = "{";
  jsonData += "\"distance\":" + String(distance, 2) + ",";
  jsonData += "\"fillPercentage\":" + String(fillPercentage, 1) + ",";
  jsonData += "\"status\":\"" + status + "\",";
  jsonData += "\"timestamp\":\"" + getTimestamp() + "\",";
  jsonData += "\"deviceId\":\"ESP32_" + String(ESP.getChipId()) + "\"";
  jsonData += "}";
  
  // Send to Firebase
  String path = "/bins/" + String(BIN_ID) + "/sensorData";
  if (Firebase.setJSON(firebaseData, path, jsonData)) {
    Serial.print("✓ Data sent - Distance: ");
    Serial.print(distance);
    Serial.print("cm, Fill: ");
    Serial.print(fillPercentage);
    Serial.print("%, Status: ");
    Serial.println(status);
  } else {
    Serial.print("✗ Firebase Error: ");
    Serial.println(firebaseData.errorReason());
  }
  
  // Also update the bin status in the parent bin object
  String statusPath = "/bins/" + String(BIN_ID) + "/status";
  Firebase.setString(firebaseData, statusPath, status);
}

// Get formatted timestamp (simple version)
String getTimestamp() {
  // For a more complete timestamp, you'd need to sync time via NTP
  // This is a simple millis-based timestamp
  return String(millis());
}
```

---

## Setup Instructions

### 1. Install Arduino IDE
- Download: https://www.arduino.cc/en/software
- Install Arduino IDE 2.0 or later

### 2. Add ESP32 Board Support
1. Open Arduino IDE
2. Go to **File → Preferences**
3. Add to "Additional Boards Manager URLs":
   ```
   https://dl.espressif.com/dl/package_esp32_index.json
   ```
4. Go to **Tools → Board → Boards Manager**
5. Search for "esp32" and install "ESP32 by Espressif Systems"

### 3. Install Firebase Library
1. Go to **Sketch → Include Library → Manage Libraries**
2. Search for "FirebaseESP32"
3. Install "Firebase ESP32 Client" by Mobizt
4. Alternative: Search for "Firebase" and install the official one

### 4. Configure Your Code
In the sketch, change these values:
```cpp
#define WIFI_SSID "YOUR_NETWORK_NAME"
#define WIFI_PASSWORD "YOUR_NETWORK_PASSWORD"
#define BIN_ID "BIN-001"  // Must match a bin in your Firebase database
```

### 5. Select Board and Port
1. **Tools → Board → ESP32 Dev Module** (or your specific board)
2. **Tools → Port → COM3** (or whichever port your ESP32 is on)

### 6. Upload
1. Click **Upload** button or press **Ctrl+U**
2. Watch the Serial Monitor for output

### 7. Monitor Output
1. **Tools → Serial Monitor**
2. Set baud rate to **115200**
3. You should see:
   ```
   WiFi Connected!
   IP: 192.168.1.100
   Firebase initialized
   ✓ Data sent - Distance: 25.34cm, Fill: 45.2%, Status: medium
   ```

---

## Real-Time Monitoring in Dashboard

Once your ESP32 is running, you'll see:
- **Distance**: Raw cm reading from HC-SR04
- **fillPercentage**: 0-100% calculated fill level
- **status**: "empty", "medium", or "full"
- **timestamp**: When the reading was taken
- **deviceId**: Unique ESP32 identifier

These values appear in Firebase at:
```
/bins/BIN-001/sensorData/
```

Your Vue Dashboard already listens for these changes and will display them in real-time!

---

## Troubleshooting

| Issue | Cause | Solution |
|-------|-------|----------|
| Can't upload | Wrong board/port selected | Check Tools → Board and Tools → Port |
| Serial monitor shows nothing | Baud rate mismatch | Set to 115200 in Serial Monitor |
| WiFi won't connect | Wrong SSID/password | Verify credentials |
| Firebase errors | Database URL wrong or rules block writes | Check Firebase Rules (set to `.write: true`) |
| Distance readings wrong | HC-SR04 angle or obstruction | Ensure sensor faces bin opening directly |
| Erratic readings | Ground connection loose | Check all GND connections |
| Distance always 0 | ECHO pin not wired | Verify ECHO_PIN (GPIO 18) connection |

---

## Next Steps

1. **Wire** your ESP32 + HC-SR04 according to the diagram
2. **Update** the sketch with your WiFi credentials and BIN_ID
3. **Upload** to your ESP32
4. **Check** Firebase Console to see `/bins/BIN-001/sensorData/` appearing in real-time
5. **View** on your Dashboard at `http://localhost:5174/`

---

## Advanced: Multiple Bins

To add multiple ESP32 devices for multiple bins, simply:
1. Flash each ESP32 with the same code but change `BIN_ID` to match each bin
2. Wire each one with its own HC-SR04 sensor
3. Each will send to its own path: `/bins/BIN-001/sensorData`, `/bins/BIN-002/sensorData`, etc.

---

## References

- HC-SR04 Datasheet: https://cdn.shopify.com/s/files/1/0174/1751/files/HCSR04.pdf
- ESP32 Pinout: https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
- Firebase ESP32: https://github.com/mobizt/Firebase-ESP32
