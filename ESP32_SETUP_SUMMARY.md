# ESP32 + HC-SR04 Integration Summary

## ✅ What's Been Set Up For You

### 1. **Arduino/C++ Firmware Code**
- File: `ESP32_Code.ino`
- Features:
  - Reads HC-SR04 distance sensor
  - Calculates fill percentage (0-100%)
  - Determines status: "empty", "medium", "full"
  - Sends data to Firebase every 5 seconds
  - Handles WiFi reconnection
  - Includes error handling and logging

### 2. **Dashboard Enhancement**
- Updated `src/views/Dashboard.vue`
- New columns display:
  - Distance (cm) — raw sensor reading
  - Fill % — calculated fill percentage
  - Status visualization — color bars
- Real-time updates from Firebase
- Automatic alerts when bin becomes full

### 3. **Documentation**
Four comprehensive guides created:
- **ESP32_GETTING_STARTED.md** ⭐ **START HERE** — 5-minute quickstart
- **ESP32_QUICK_REFERENCE.md** — Wiring, pinouts, troubleshooting
- **ESP32_INTEGRATION_GUIDE.md** — Full technical specs and advanced setup
- **FIREBASE_TROUBLESHOOTING.md** — Database connectivity issues

---

## 🚀 Quick Start (3 Steps)

### Step 1: Wire Your Hardware
```
HC-SR04 → ESP32
VCC    → 5V
GND    → GND
TRIG   → GPIO 5
ECHO   → GPIO 18
```

### Step 2: Update & Upload Code
1. Open `ESP32_Code.ino` in Arduino IDE
2. Change WiFi credentials:
   ```cpp
   #define WIFI_SSID "YourNetwork"
   #define WIFI_PASSWORD "YourPassword"
   ```
3. Match your bin ID:
   ```cpp
   #define BIN_ID "BIN-001"
   ```
4. Click Upload

### Step 3: Verify
- Open Serial Monitor (115200 baud)
- You should see: `✓ Distance: 25.3cm | Fill: 45% | Status: medium`
- Dashboard will show real-time data

---

## 📊 Data Structure

### What ESP32 Sends to Firebase
Every 5 seconds to `/bins/BIN-001/sensorData`:

```json
{
  "distance": 25.34,              // cm from sensor to bin surface
  "fillPercentage": 45.2,         // 0-100%
  "status": "medium",             // "empty", "medium", or "full"
  "timestamp": 123456789,         // milliseconds
  "deviceId": "ESP32_1234567"     // unique identifier
}
```

### Thresholds (Adjustable)
```
Distance ≤ 15cm  → Status = "full"   → Fill % = 100%
Distance 5-15cm  → Status = "medium" → Fill % = varies
Distance ≥ 5cm   → Status = "empty"  → Fill % = 0%
```

Change in `ESP32_Code.ino`:
```cpp
#define EMPTY_THRESHOLD 5    // cm
#define FULL_THRESHOLD 15    // cm
```

---

## 🎯 Key Features

### Real-Time Monitoring
- Dashboard updates automatically as data arrives
- No manual refresh needed
- Latency: sub-second to a few seconds

### Automatic Alerts
- When bin status = "full":
  - Toast notification in-app
  - Browser notification (if permitted)
  - Audio beep alert
- Prevents bin overflow

### Multiple Sensors
- Support for unlimited bins
- Each ESP32 sends to its own path: `/bins/BIN-002/sensorData`, etc.
- All visible on same Dashboard

### Error Handling
- WiFi reconnection automatic
- Firebase offline handling
- Serial Monitor debugging output

---

## 📝 Pre-Flight Checklist

Before first deployment:

- [ ] HC-SR04 wired correctly to GPIO 5 (TRIG) and GPIO 18 (ECHO)
- [ ] ESP32 powered via USB (or 5V power supply)
- [ ] WiFi SSID and password correct in code
- [ ] Bin ID in code matches a bin in Bin Management view
- [ ] Firebase Rules allow `.read: true` and `.write: true`
- [ ] Serial Monitor shows connection messages at 115200 baud
- [ ] `/bins/BIN-001/sensorData` path exists in Firebase after first reading
- [ ] Dashboard shows Distance and Fill % columns
- [ ] Test alert by manually setting a bin status to "full" in Firebase

---

## 🔧 Hardware Considerations

### Sensor Placement
- Mount ESP32 + HC-SR04 directly above trash bin opening
- Sensor must point straight down into bin
- Distance to empty bin = ~5cm, to full bin = ~15cm (adjust thresholds)

### Power Options
- **Development**: USB cable to laptop or USB charger
- **Deployment**: 5V power bank or wall adapter
  - Current draw: ~50-100mA (very low)
  - Can run on single 2200mAh USB battery for ~24 hours

### Environmental Factors
- Sensor works best indoors
- Avoid direct sunlight on sensor
- Keep sensor clean (dust/debris affects readings)
- Operates in temperature range: -10°C to +60°C

---

## 🐛 Common Issues & Fixes

| Problem | Cause | Solution |
|---------|-------|----------|
| Distance always shows 0 | ECHO pin not connected | Check GPIO 18 wiring |
| WiFi won't connect | Wrong SSID/password | Verify credentials, use 2.4GHz network |
| Firebase write fails | Rules too restrictive | Set `.write: true` in Rules |
| No Serial output | Wrong baud rate | Set to **115200** in Serial Monitor |
| Erratic readings | Loose ground connection | Check all GND wires, add solder if needed |
| Sensor too sensitive | Mounting angle | Adjust angle to face bin opening directly |

---

## 📈 Next Steps

### Phase 1: Testing (Today)
1. Wire hardware and upload code
2. Verify Serial Monitor output
3. Check Firebase for incoming data
4. View on Dashboard

### Phase 2: Calibration (Tomorrow)
1. Place ESP32 at actual bin height
2. Measure distance to empty bin (adjust `EMPTY_THRESHOLD`)
3. Measure distance to full bin (adjust `FULL_THRESHOLD`)
4. Test fill percentage accuracy

### Phase 3: Deployment (Next Week)
1. Mount ESP32 + HC-SR04 permanently on bin
2. Connect to 5V power supply
3. Test in production environment
4. Monitor logs for issues

### Phase 4: Scale (Future)
1. Replicate for additional bins (BIN-002, BIN-003, etc.)
2. Create monitoring dashboard
3. Integrate with waste collection schedule
4. Add IoT analytics

---

## 📚 File Reference

| File | Purpose |
|------|---------|
| `ESP32_Code.ino` | Arduino sketch — copy/paste into Arduino IDE |
| `ESP32_GETTING_STARTED.md` | **5-minute quickstart guide** |
| `ESP32_QUICK_REFERENCE.md` | Pinouts, wiring, troubleshooting cheat sheet |
| `ESP32_INTEGRATION_GUIDE.md` | Full technical documentation |
| `FIREBASE_TROUBLESHOOTING.md` | Database connectivity issues |
| `src/views/Dashboard.vue` | Updated UI to show sensor data |
| `src/services/firebase.js` | Firebase initialization & helpers |

---

## 💡 Tips & Tricks

### Debugging
- Enable Serial output: `Arduino IDE → Tools → Serial Monitor`
- Add breakpoints with `Serial.println("[INFO] Message here");`
- Check Firebase Console in real-time to see raw data

### Optimization
- Reduce `SEND_INTERVAL` from 5000ms to 1000ms for more frequent updates
- Use `.2f` to format floats: `String(distance, 2)` = 2 decimal places
- Add low-battery detection by reading ESP32 ADC pin

### Security (Production)
- Currently: `.read: true, .write: true` (open for testing)
- For production, restrict to specific bins or add authentication
- Consider rate-limiting to prevent spam writes

---

## 🎓 Learning Resources

- **HC-SR04 Datasheet**: https://cdn.shopify.com/s/files/1/0174/1751/files/HCSR04.pdf
- **ESP32 Pinout**: https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
- **Firebase ESP32 Library**: https://github.com/mobizt/Firebase-ESP32
- **Arduino IDE**: https://www.arduino.cc/en/Guide

---

## 📞 Support

**If something goes wrong:**
1. Check Serial Monitor for error messages (F12 console on web)
2. Verify hardware wiring matches diagram
3. Check Firebase Console for data appearing/failing
4. Look up error code in troubleshooting guide
5. Review the appropriate documentation file above

**Contact info**: See project README for support contacts

---

**You're all set! Start with ESP32_GETTING_STARTED.md and enjoy real-time bin monitoring! 🚀**
