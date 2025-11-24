import { initializeApp, getApps } from "firebase/app";
import { getDatabase, ref as dbRef, get, set, onValue } from "firebase/database";

const firebaseConfig = {
  apiKey: "AIzaSyCF90aGhcQyeQuuDycuUdTjVbOxxcrnSVA",
  authDomain: "wastewise-4aa13.firebaseapp.com",
  databaseURL: "https://wastewise-4aa13-default-rtdb.asia-southeast1.firebasedatabase.app",
  projectId: "wastewise-4aa13",
  storageBucket: "wastewise-4aa13.firebasestorage.app",
  messagingSenderId: "537976577759",
  appId: "1:537976577759:web:411beb739af1a28ccb136a",
  measurementId: "G-388BE1VXKK"
};

// eslint-disable-next-line no-console
console.log('[firebase] Config loaded:', { projectId: firebaseConfig.projectId, databaseURL: firebaseConfig.databaseURL });

// Initialize app only if not already initialized (helps in HMR / dev mode)
let app;
if (!getApps().length) {
  app = initializeApp(firebaseConfig);
  // eslint-disable-next-line no-console
  console.log('[firebase] App initialized');
} else {
  app = getApps()[0];
  // eslint-disable-next-line no-console
  console.log('[firebase] App already initialized, reusing existing app');
}

const db = getDatabase(app);
// eslint-disable-next-line no-console
console.log('[firebase] Database reference obtained:', db);

function logDbError(err) {
  // simple helper to centralize DB error logging
  // eslint-disable-next-line no-console
  console.error('[firebase][db] ', err);
}

// Diagnostic function to test Firebase connection and read/write permissions
async function testFirebaseConnection() {
  const results = {
    connected: false,
    canRead: false,
    canWrite: false,
    errors: []
  };

  try {
    // Test 1: Check connection state using a short-lived listener on .info/connected
    // .info/connected is ephemeral and best observed with onValue; a one-time GET
    // can return stale or missing data depending on timing. We'll listen for a
    // small window (1.5s) and treat the client as connected if the server reports true.
    // eslint-disable-next-line no-console
    console.log('[firebase] Testing connection (.info/connected) with onValue listener...');

    const connRef = dbRef(db, '.info/connected');
    let unsubscribe = null;
    const connectedResult = await new Promise((resolve) => {
      let settled = false;
      try {
        unsubscribe = onValue(connRef, (snap) => {
          try {
            const v = snap.val();
            // snap.val() is boolean true/false. We only consider connected when true.
            if (v === true && !settled) {
              settled = true;
              resolve(true);
            }
          } catch (e) {
            // ignore per-listen parse errors and wait for timeout
          }
        }, (err) => {
          if (!settled) {
            settled = true;
            resolve(false);
          }
        });
      } catch (e) {
        // if onValue itself throws (unlikely), resolve false
        if (!settled) {
          settled = true;
          resolve(false);
        }
      }

      // timeout fallback: if we don't see a true value in 1500ms, assume not connected
      setTimeout(() => {
        if (!settled) {
          settled = true;
          resolve(false);
        }
      }, 1500);
    });

    // clean up listener if present
    try {
      if (typeof unsubscribe === 'function') unsubscribe();
    } catch (e) {
      // ignore
    }

    if (connectedResult) {
      results.connected = true;
      // eslint-disable-next-line no-console
      console.log('[firebase] ✓ .info/connected reported true within timeout');
    } else {
      // eslint-disable-next-line no-console
      console.log('[firebase] .info/connected did not report true within timeout');
    }
  } catch (readErr) {
    // eslint-disable-next-line no-console
    console.warn('[firebase] Read test partial (expected for .info path):', readErr.message);
  }

  try {
    // Test 2: Try to read from bins
    // eslint-disable-next-line no-console
    console.log('[firebase] Testing bins read access...');
    const binsTestRef = dbRef(db, 'bins');
    const snapshot = await get(binsTestRef);
    results.canRead = true;
    // eslint-disable-next-line no-console
    console.log('[firebase] ✓ Can read from /bins');
  } catch (readErr) {
    results.canRead = false;
    results.errors.push(`Read failed: ${readErr.message}`);
    logDbError(readErr);
  }

  try {
    // Test 3: Try to write a test record
    // eslint-disable-next-line no-console
    console.log('[firebase] Testing write access...');
    const testWriteRef = dbRef(db, 'connectionTest/' + Date.now());
    await set(testWriteRef, {
      timestamp: new Date().toISOString(),
      status: 'test'
    });
    results.canWrite = true;
    // eslint-disable-next-line no-console
    console.log('[firebase] ✓ Can write to database');
  } catch (writeErr) {
    results.canWrite = false;
    results.errors.push(`Write failed: ${writeErr.message}`);
    logDbError(writeErr);
  }

  // eslint-disable-next-line no-console
  console.log('[firebase] Connection test results:', results);
  return results;
}

export { db, logDbError, testFirebaseConnection };