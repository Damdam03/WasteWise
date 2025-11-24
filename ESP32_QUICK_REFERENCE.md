# ESP32 + HC-SR04 Quick Reference

## 🔧 Hardware Wiring (Most Important!)

```
HC-SR04          →  ESP32
─────────────────────────
VCC (3V)         →  3V
GND              →  GND
TRIG             →  GPIO 5
ECHO             →  GPIO 18

⚠️ IMPORTANT: ECHO outputs 5V but ESP32 GPIO is 3.3V
Use a voltage divider or the reading may be unreliable:
  ECHO ──[10kΩ]──┬──→ GPIO 18
                  │
                 [20kΩ]
                  │
                 GND
```

---

## 📝 Arduino Code Setup (3 Steps)

### Step 1: Update WiFi Credentials
In `ESP32_Code.ino`, change:
```cpp
#define WIFI_SSID "YOUR_SSID"
#define WIFI_PASSWORD "YOUR_PASSWORD"
```

### Step 2: Match Your Bin ID
```cpp
#define BIN_ID "BIN-001"  // Must exist in Firebase bins
```

### Step 3: Calibrate Thresholds (Optional)
Adjust these based on your trash bin size:
```cpp
#define EMPTY_THRESHOLD 5    // Distance when completely empty (cm)
#define FULL_THRESHOLD 15    // Distance when completely full (cm)
```

---

## 📤 Data Flow

```
ESP32 + HC-SR04
    ↓
    Measures distance every 5 seconds
    ↓
    Calculates: distance → fillPercentage → status (empty/medium/full)
    ↓
    Sends to Firebase: /bins/BIN-001/sensorData
    ↓
    Vue Dashboard listens for changes in real-time
    ↓
    Shows distance, fillPercentage, status
    ↓
    Alerts when status = "full"
```

---

## ✅ What Gets Sent to Firebase

Every 5 seconds, your ESP32 sends this to `/bins/BIN-001/sensorData`:

```json
{
  "distance": 25.34,
  "fillPercentage": 45.2,
  "status": "medium",
  "timestamp": 123456789,
  "deviceId": "ESP32_1234567"
}
```

And updates `/bins/BIN-001/status` to the latest status.

---

## 🧪 Testing Checklist

- [ ] HC-SR04 wired correctly (VCC, GND, TRIG, ECHO)
- [ ] ESP32 connected to WiFi (check Serial Monitor at 115200 baud)
- [ ] Arduino code compiled and uploaded
- [ ] Serial Monitor shows "✓ Data sent" messages
- [ ] Firebase Console shows `/bins/BIN-001/sensorData/` with real data
- [ ] Dashboard displays Distance and Fill % columns
- [ ] Alert triggers when you test with `status: "full"`

---

## 🔄 Real-World Usage

1. **Mount the ESP32 + HC-SR04** above the trash bin (sensor pointing down)
2. **Power via USB** or a 5V power bank
3. **ESP32 connects to WiFi** and starts sending data
4. **View on Dashboard** at `http://localhost:5174/` (or your server URL)
5. **Get alerts** when bin becomes full

---

## 📊 Database Structure After Setup

```
Firebase Realtime Database
└── bins/
    ├── BIN-001/
    │   ├── id: "BIN-001"
    │   ├── location: "Library"
    │   ├── floor: 1
    │   ├── personnel: "Maria Santos"
    │   ├── connected: true
    │   ├── status: "medium"  ← Updated by ESP32
    │   └── sensorData/       ← Updated by ESP32 every 5s
    │       ├── distance: 25.34
    │       ├── fillPercentage: 45.2
    │       ├── status: "medium"
    │       ├── timestamp: 123456789
    │       └── deviceId: "ESP32_1234567"
    │
    └── BIN-002/
        └── ... (same structure)
```

---

## 🐛 Common Issues

| Issue | Fix |
|-------|-----|
| Serial Monitor shows garbage | Set baud to **115200** |
| "WiFi Failed" | Check SSID/password, make sure 2.4GHz network |
| "Firebase Error" | Ensure Firebase Rules allow `.write: true` |
| Distance always 0 | Check ECHO pin wiring, add voltage divider |
| Erratic readings | Ensure HC-SR04 faces bin opening, check GND connections |
| No data in Firebase | Check if `/bins/BIN-001` exists first |

---

## 📞 Support

- Check serial output with: **Arduino IDE → Tools → Serial Monitor** (115200 baud)
- Verify data in: **Firebase Console → Realtime Database**
- View on dashboard: **http://localhost:5174/bin_management**
