# Getting Started with ESP32 + HC-SR04 (5-Minute Setup)

## What You'll Have After This

A smart trash bin that:
- ✅ Measures how full it is every 5 seconds
- ✅ Sends real-time data to Firebase
- ✅ Shows on your WasteWise Dashboard
- ✅ Alerts you when it's full

---

## Prerequisites

**Hardware:**
- ESP32 Development Board
- HC-SR04 Ultrasonic Sensor
- Jumper wires
- Breadboard
- Micro USB cable

**Software:**
- Arduino IDE (https://www.arduino.cc/en/software)
- Firebase account (already set up)
- WiFi network credentials

---

## Step 1: Connect Hardware (2 minutes)

### Wiring

Follow this exactly:

```
HC-SR04 Pin    →  ESP32 Pin
─────────────────────────────
VCC (red)      →  5V
GND (black)    →  GND
TRIG (yellow)  →  GPIO 5
ECHO (green)   →  GPIO 18
```

**That's it!** No breadboard needed if using jumper wires.

---

## Step 2: Install Arduino IDE & Libraries (3 minutes)

### Install Arduino IDE
1. Download from: https://www.arduino.cc/en/software
2. Install and launch

### Add ESP32 Board Support
1. **File → Preferences**
2. Paste in "Additional Boards Manager URLs":
   ```
   https://dl.espressif.com/dl/package_esp32_index.json
   ```
3. **Tools → Board → Boards Manager**
4. Search "esp32", click "Install"

### Install Firebase Library
1. **Sketch → Include Library → Manage Libraries**
2. Search "FirebaseESP32"
3. Click "Install" (by Mobizt)

---

## Step 3: Get the Code (1 minute)

1. Open Arduino IDE
2. **File → New Sketch**
3. Delete everything
4. Copy and paste code from: `ESP32_Code.ino` (in your project folder)
5. Modify only these 2 lines:
   ```cpp
   #define WIFI_SSID "YourNetworkName"        // ← Your WiFi name
   #define WIFI_PASSWORD "YourPassword"        // ← Your WiFi password
   #define BIN_ID "BIN-001"                    // ← Must match a bin in Firebase
   ```

---

## Step 4: Upload to ESP32 (2 minutes)

1. Connect ESP32 to computer via USB
2. **Tools → Board → ESP32 Dev Module**
3. **Tools → Port → COM3** (or your COM port)
4. Click **Upload** ⬆️
5. Wait for "Done uploading"

---

## Step 5: Verify It Works (1 minute)

1. **Tools → Serial Monitor**
2. Set baud rate to **115200** (bottom right)
3. You should see:
   ```
   WiFi Connected!
   IP: 192.168.1.100
   ✓ Distance: 25.3cm | Fill: 45% | Status: medium
   ✓ Distance: 25.2cm | Fill: 45% | Status: medium
   ...
   ```

✅ **If you see this, you're done!**

---

## Step 6: Check Your Dashboard

1. Open: http://localhost:5174/
2. Go to **Dashboard**
3. You should see your bins with:
   - Distance (cm)
   - Fill %
   - Status (empty/medium/full)

🎉 **All working!**

---

## Troubleshooting

### Serial Monitor shows nothing
- Check USB cable (try different port)
- Verify board: **Tools → Board → ESP32 Dev Module**
- Set baud to **115200**

### "WiFi Connected" but "✗ Firebase Error"
- Check Firebase Rules in Console
- Should be: `.read: true, .write: true`

### Distance always 0
- Check ECHO pin (GPIO 18) wiring
- Add voltage divider if needed (see full guide)

### "Unknown BIN_ID"
- Verify BIN ID matches a bin in Bin Management
- Make sure you've created at least one bin first

---

## What Happens Next

Every 5 seconds, your ESP32:
1. Measures distance with HC-SR04
2. Calculates fill percentage
3. Sends to Firebase: `/bins/BIN-001/sensorData`
4. Dashboard updates automatically
5. Alert triggers if full

---

## Next: Multiple Sensors

To add more bins:
1. Flash another ESP32 with **different BIN_ID** (e.g., "BIN-002")
2. Create that bin in Bin Management
3. Wire another HC-SR04
4. Done!

---

## Files Reference

- `ESP32_Code.ino` — Arduino sketch (copy to Arduino IDE)
- `ESP32_QUICK_REFERENCE.md` — Wiring diagram & common issues
- `ESP32_INTEGRATION_GUIDE.md` — Full technical documentation

---

**Need help?** Check Serial Monitor (Tools → Serial Monitor, 115200 baud) for error messages.

Good luck! 🚀
