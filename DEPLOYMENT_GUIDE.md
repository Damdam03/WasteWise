# WasteWise Deployment Guide - Vercel Hosting

## 🚀 Complete Step-by-Step Deployment

### STEP 1: GitHub Setup (Already Prepared)
- ✅ `.env.production` file created
- ✅ `.gitignore` updated to protect sensitive files
- Next: Push code to GitHub

### STEP 2: Create GitHub Repository
1. Go to https://github.com/new
2. Repository name: `WasteWise`
3. Description: `Waste Management System with ESP32 IoT Sensors`
4. Visibility: **Public**
5. Click **Create repository**

### STEP 3: Push Code to GitHub
Use GitHub Desktop (easiest method):
1. Download: https://desktop.github.com/
2. File → Clone Repository
3. Paste your repo HTTPS URL
4. Choose location: `C:\Users\velas\Desktop\WasteWise`
5. Wait for sync
6. Bottom left: Write commit message
7. Click **Commit to main**
8. Top center: Click **Push origin**
9. Wait for completion

### STEP 4: Deploy to Vercel
1. Go to https://vercel.com
2. Click **Sign up** → Choose **GitHub**
3. Authorize Vercel to access your GitHub account
4. Click **New Project**
5. Select `WasteWise` repository
6. Configure settings:
   - **Framework Preset:** Vite (auto-detected)
   - **Build Command:** `npm run build`
   - **Output Directory:** `dist`
   - **Install Command:** `npm install`

7. **Add Environment Variables:**
   Click **Environment Variables** and add:
   ```
   VITE_FIREBASE_API_KEY = AIzaSyC_YOUR_API_KEY
   VITE_FIREBASE_AUTH_DOMAIN = wastewise-4aa13.firebaseapp.com
   VITE_FIREBASE_PROJECT_ID = wastewise-4aa13
   VITE_FIREBASE_STORAGE_BUCKET = wastewise-4aa13.appspot.com
   VITE_FIREBASE_MESSAGING_SENDER_ID = YOUR_SENDER_ID
   VITE_FIREBASE_APP_ID = YOUR_APP_ID
   VITE_FIREBASE_DATABASE_URL = https://wastewise-4aa13-default-rtdb.asia-southeast1.firebasedatabase.app
   ```

8. Click **Deploy**
9. Wait 2-3 minutes for build to complete
10. You'll get a URL like: `https://wastewise.vercel.app`

### STEP 5: Test Your Deployment
- Open the Vercel URL in your browser
- Test all features:
  - ✅ Dashboard loads
  - ✅ Bins display with data
  - ✅ Real-time updates work
  - ✅ Hamburger menu works
  - ✅ Help buttons work
  - ✅ Add bin, edit bin, delete bin functions
  - ✅ Bin history shows connectivity

### STEP 6: Security - Update Firebase Rules (IMPORTANT!)
1. Go to Firebase Console: https://console.firebase.google.com
2. Select **wastewise-4aa13** project
3. Go to **Realtime Database**
4. Click **Rules** tab
5. Replace the test rules with:

```json
{
  "rules": {
    "bins": {
      ".read": true,
      ".write": "auth != null"
    },
    "bins_connectivity_history": {
      ".read": true,
      ".write": "auth != null"
    },
    "connectionPing": {
      ".read": true,
      ".write": true
    },
    "connectionTest": {
      ".read": true,
      ".write": true
    }
  }
}
```

6. Click **Publish**

### STEP 7: Update ESP32 Firebase URL (if needed)
Your ESP32 already points to the correct Firebase URL, so no changes needed!

### STEP 8: Custom Domain (Optional)
1. In Vercel dashboard, click your project
2. Go to **Settings → Domains**
3. Add your custom domain (e.g., wastewise.com)
4. Follow Vercel's DNS instructions
5. Point domain to Vercel nameservers

---

## 📊 Your Live System
- **Frontend URL:** `https://wastewise.vercel.app`
- **Backend:** Firebase Realtime Database (already online)
- **ESP32 Devices:** Connect directly to Firebase (no changes needed)
- **Cost:** $0/month (free tier)
- **Uptime:** 99.9% guaranteed

---

## 🔧 Troubleshooting

### Issue: Vercel build fails
- Check build logs in Vercel dashboard
- Ensure all environment variables are set
- Run locally: `npm run build` to test

### Issue: Firebase connection error
- Verify environment variables are correct
- Check Firebase rules allow read access
- Check ESP32 can reach Firebase URL

### Issue: Real-time updates not working
- Clear browser cache (Ctrl+Shift+Delete)
- Check browser console for errors (F12)
- Verify Firebase listener is active

---

## 📞 Need Help?
After deployment, share your Vercel URL and I can help debug any issues!

