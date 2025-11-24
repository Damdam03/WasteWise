# Firebase Connection Troubleshooting Guide

## ✅ Step 1: Check Your Database URL (You can verify this)

Your current config has:
```
databaseURL: "https://wastewise-4aa13-default-rtdb.asia-southeast1.firebasedatabase.app"
```

**Verify it's correct:**
1. Go to [Firebase Console](https://console.firebase.google.com/)
2. Select project: **wastewise-4aa13**
3. Go to **Realtime Database**
4. Look at the URL bar at the top — it should match your databaseURL above
5. If different, we need to update it

---

## ✅ Step 2: Check Security Rules (Most Common Issue!)

**This is likely your problem.** Firebase Realtime Database by default **blocks all reads and writes**.

1. Go to [Firebase Console](https://console.firebase.google.com/)
2. Select **wastewise-4aa13** project
3. Click **Realtime Database** (left sidebar)
4. Click the **Rules** tab at the top
5. Look at the current rules — they probably look like:
   ```json
   {
     "rules": {
       ".read": false,
       ".write": false
     }
   }
   ```

**To fix (for development/testing):**
1. Replace with:
   ```json
   {
     "rules": {
       ".read": true,
       ".write": true
     }
   }
   ```
2. Click **Publish** button
3. Confirm when prompted
4. Wait 1-2 seconds for the change to apply

**For production (later):**
```json
{
  "rules": {
    "bins": {
      ".read": true,
      ".write": true
    },
    "connectionTest": {
      ".write": true
    }
  }
}
```

---

## ✅ Step 3: Test Your Connection Again

1. Refresh your app at `http://localhost:5174/`
2. Go to **Bin Management** page
3. Click the **"Run Connection Test"** button (bottom-right corner)
4. You should now see:
   - ✓ Connected to DB: **YES**
   - ✓ Can Read: **YES**
   - ✓ Can Write: **YES**

---

## ✅ Step 4: Try Adding a Bin

1. Click **Add Bin** button
2. Fill in the form:
   - Bin ID: `BIN-001`
   - Location: `Library`
   - Floor: `1`
   - Personnel: `Maria Santos`
   - Connected: ✓ (checked)
3. Click **Add**
4. **Check browser console (F12 key)** for messages:
   - ✓ Success: `[addBin] ✓ Bin added successfully with key: ...`
   - ✗ Error: `[addBin] ✗ Failed to add bin: ...` (tell me the error code)

---

## ✅ Step 5: Verify Data in Firebase

1. Go to [Firebase Console](https://console.firebase.google.com/)
2. Select **wastewise-4aa13** project
3. Click **Realtime Database**
4. You should see a `bins` folder with your new bin data
5. You should also see a `connectionTest` folder (from our test)

---

## 🚨 Common Error Messages & Fixes

| Error | Meaning | Fix |
|-------|---------|-----|
| `PERMISSION_DENIED` | Rules don't allow access | Update rules to `.read: true, .write: true` |
| `Network Error` | Can't reach Firebase servers | Check internet; verify databaseURL |
| `Invalid API Key` | Config is wrong | Copy fresh config from Firebase Console |
| `Database URL mismatch` | Regional database selected | Make sure databaseURL matches console URL |

---

## 📞 If You're Still Stuck

Post these screenshots/info:
1. Your current Firebase Rules (from Rules tab)
2. Browser console output when clicking "Run Connection Test" (press F12)
3. Browser console output when clicking "Add Bin" (press F12)
4. Your actual databaseURL from Firebase Console > Realtime Database
