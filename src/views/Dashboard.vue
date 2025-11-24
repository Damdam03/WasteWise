<template>
  <div class="min-h-screen bg-gradient-to-br from-gray-50 to-gray-100 relative">
    <!-- Header -->
    <div class="bg-white border-b border-gray-200 shadow-sm">
      <div class="flex items-center justify-between px-6 py-4">
        <div class="flex items-center space-x-4">
          <img src="/src/assets/images/logo-psu.png" alt="PSU Logo" class="w-12 h-12 cursor-pointer hover:opacity-80 transition-opacity" @click="goToDashboard" />
          <div>
            <div class="font-bold text-lg text-gray-900">PARTIDO STATE UNIVERSITY</div>
            <div class="font-semibold text-sm text-gray-600">GENERAL SERVICES UNIT</div>
          </div>
        </div>
        <button @click="showHelp = true" class="p-2 rounded-lg hover:bg-gray-100 transition-colors duration-200" title="Help">
          <svg xmlns="http://www.w3.org/2000/svg" class="h-6 w-6 text-gray-700" fill="none" viewBox="0 0 24 24" stroke="currentColor"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M13 16h-1v-4h-1m1-4h.01M21 12a9 9 0 11-18 0 9 9 0 0118 0z" /></svg>
        </button>
      </div>
    </div>

    <!-- Hamburger -->
    <div class="px-6 mt-4">
      <button 
        @click="showMenu = !showMenu"
        class="group relative w-10 h-10 flex flex-col justify-center items-center rounded-lg hover:bg-gray-100 transition-colors duration-200"
      >
        <div class="w-6 h-0.5 bg-black rounded-full transition-all duration-300 transform"
             :class="{ 'rotate-45 translate-y-2': showMenu }"></div>
        <div class="w-6 h-0.5 bg-black rounded-full transition-all duration-300 transform mt-1.5"
             :class="{ 'opacity-0': showMenu }"></div>
        <div class="w-6 h-0.5 bg-black rounded-full transition-all duration-300 transform mt-1.5"
             :class="{ '-rotate-45 -translate-y-2': showMenu }"></div>
      </button>
    </div>

    <!-- Sidebar Menu -->
    <transition 
      name="slide-fade"
      enter-active-class="transition ease-out duration-300"
      enter-from-class="opacity-0 transform -translate-x-full"
      enter-to-class="opacity-100 transform translate-x-0"
      leave-active-class="transition ease-in duration-200"
      leave-from-class="opacity-100 transform translate-x-0"
      leave-to-class="opacity-0 transform -translate-x-full"
    >
      <div v-if="showMenu" class="absolute top-20 left-0 w-64 bg-white z-40 shadow-2xl rounded-r-2xl border-r-2 border-gray-200" style="min-height: 200px;">
        <div class="flex flex-col">
          <div 
            :class="['flex items-center py-4 px-6 cursor-pointer transition-all duration-200 border-l-4', 
              selectedMenu === 'dashboard' ? 'bg-blue-50 border-blue-500 text-blue-700' : 'border-transparent hover:bg-gray-50']" 
            @click="goToDashboard"
          >
            <svg class="w-5 h-5 mr-3" fill="currentColor" viewBox="0 0 24 24"><path d="M3 13h2v8H3zm4-8h2v16H7zm4-2h2v18h-2zm4 4h2v14h-2zm4-2h2v16h-2z"/></svg>
            <span class="font-semibold text-base">Dashboard</span>
          </div>
          <div 
            :class="['flex items-center py-4 px-6 cursor-pointer transition-all duration-200 border-l-4', 
              selectedMenu === 'bin' ? 'bg-green-50 border-green-500 text-green-700' : 'border-transparent hover:bg-gray-50']" 
            @click="goToBinManagement"
          >
            <svg class="w-5 h-5 mr-3" fill="currentColor" viewBox="0 0 24 24"><path d="M6 19c0 1.1.9 2 2 2h8c1.1 0 2-.9 2-2V7H6v12zM19 4h-3.5l-1-1h-9l-1 1H5v2h14V4z"/></svg>
            <span class="font-semibold text-base">Bin Management</span>
          </div>
          <div 
            :class="['flex items-center py-4 px-6 cursor-pointer transition-all duration-200 border-l-4', 
              selectedMenu === 'history' ? 'bg-indigo-50 border-indigo-500 text-indigo-700' : 'border-transparent hover:bg-gray-50']" 
            @click="goToHistory"
          >
            <svg class="w-5 h-5 mr-3" fill="currentColor" viewBox="0 0 24 24"><path d="M3 3v18h18V3H3zm16 16H5V5h14v14zM7 8h10v2H7V8zm0 4h7v2H7v-2z"/></svg>
            <span class="font-semibold text-base">Bin History</span>
          </div>
        </div>
      </div>
    </transition>

    <!-- Overlay -->
    <transition 
      name="fade"
      enter-active-class="transition ease-out duration-300"
      enter-from-class="opacity-0"
      enter-to-class="opacity-100"
      leave-active-class="transition ease-in duration-200"
      leave-from-class="opacity-100"
      leave-to-class="opacity-0"
    >
      <div 
        v-if="showMenu"
        @click="showMenu = false"
        class="fixed inset-0 bg-black/20 z-30 backdrop-blur-sm"
      ></div>
    </transition>

    <!-- Table -->
    <div class="flex justify-center mt-8 px-6 pb-8">
      <table class="w-full max-w-4xl border-collapse bg-white rounded-lg shadow-md overflow-hidden">
        <thead>
          <tr class="bg-gradient-to-r from-blue-600 to-blue-700 text-white">
            <th class="px-4 py-3 text-left font-semibold">Bin No.</th>
            <th class="px-4 py-3 text-left font-semibold">Bin Location</th>
            <th class="px-4 py-3 text-left font-semibold">Floor</th>
            <th class="px-4 py-3 text-left font-semibold">Personnel</th>
            <th class="px-4 py-3 text-left font-semibold">Fill %</th>
            <th class="px-4 py-3 text-left font-semibold">Bin Status</th>
            <th class="px-4 py-3 text-left font-semibold">Bin Connection</th>
          </tr>
        </thead>
        <tbody>
            <tr v-for="(bin, idx) in bins" :key="bin.no" :class="idx % 2 === 0 ? 'bg-white' : 'bg-gray-50'" class="border-b border-gray-200 hover:bg-blue-50 transition-colors duration-200">
              <td class="px-4 py-3 font-semibold text-gray-900">{{ bin.no }}</td>
              <td class="px-4 py-3 font-semibold text-gray-800">{{ bin.location }}</td>
              <td class="px-4 py-3 text-gray-700">{{ bin.floor || '-' }}</td>
              <td class="px-4 py-3 text-gray-700">{{ bin.personnel || '-' }}</td>
              <td class="px-4 py-3 text-center text-gray-700">{{ bin.fillPercentage != null ? (bin.fillPercentage.toFixed(0) + '%') : 'N/A' }}</td>
            <td class="px-4 py-3">
              <div class="relative w-full bg-gray-200 rounded h-6 overflow-hidden">
                <div 
                  class="h-full rounded transition-all duration-300"
                  :style="{ 
                    width: (bin.fillPercentage != null ? bin.fillPercentage : 0) + '%',
                    backgroundColor: getFillColor(bin.fillPercentage != null ? bin.fillPercentage : 0)
                  }"
                ></div>
              </div>
            </td>
            <td class="px-4 py-3">
              <div class="flex items-center space-x-2">
                <span :class="['font-semibold', bin.connected ? 'text-green-700' : 'text-red-700']">{{ bin.connected ? 'Connected' : 'Disconnected' }}</span>
                <span :class="['inline-block w-3 h-3 rounded-full', bin.connected ? 'bg-green-500' : 'bg-red-500']"></span>
              </div>
            </td>
          </tr>
        </tbody>
      </table>
    </div>
    <!-- Alert Toast -->
    <transition name="fade">
      <div v-if="alertVisible" class="fixed bottom-8 right-8 bg-gradient-to-r from-red-600 to-red-700 text-white px-6 py-4 rounded-lg shadow-2xl flex items-start space-x-4 max-w-sm border-l-4 border-red-400">
        <div class="flex-shrink-0 mt-0.5">
          <svg class="w-6 h-6" fill="currentColor" viewBox="0 0 20 20"><path fill-rule="evenodd" d="M10 18a8 8 0 100-16 8 8 0 000 16zM8.707 7.293a1 1 0 00-1.414 1.414L8.586 10l-1.293 1.293a1 1 0 101.414 1.414L10 11.414l1.293 1.293a1 1 0 001.414-1.414L11.414 10l1.293-1.293a1 1 0 00-1.414-1.414L10 8.586 8.707 7.293z" clip-rule="evenodd"/></svg>
        </div>
        <div class="flex-1">
          <div class="font-bold text-lg mb-1">⚠️ Bin Alert</div>
          <div class="text-sm leading-relaxed">{{ alertMessage }}</div>
        </div>
        <button @click="dismissAlert" class="flex-shrink-0 ml-2 text-red-200 hover:text-white transition-colors">
          <svg class="w-5 h-5" fill="currentColor" viewBox="0 0 20 20"><path fill-rule="evenodd" d="M4.293 4.293a1 1 0 011.414 0L10 8.586l4.293-4.293a1 1 0 111.414 1.414L11.414 10l4.293 4.293a1 1 0 01-1.414 1.414L10 11.414l-4.293 4.293a1 1 0 01-1.414-1.414L8.586 10 4.293 5.707a1 1 0 010-1.414z" clip-rule="evenodd"/></svg>
        </button>
      </div>
    </transition>

    <!-- Help Modal -->
    <transition
      enter-active-class="transition ease-out duration-300"
      enter-from-class="opacity-0"
      enter-to-class="opacity-100"
      leave-active-class="transition ease-in duration-200"
      leave-from-class="opacity-100"
      leave-to-class="opacity-0"
    >
      <div v-if="showHelp" class="fixed inset-0 bg-black/40 backdrop-blur-sm flex items-center justify-center z-50">
        <div class="bg-white rounded-xl shadow-2xl w-full max-w-2xl mx-4 max-h-96 overflow-y-auto">
          <div class="sticky top-0 bg-gradient-to-r from-blue-600 to-blue-700 text-white px-6 py-4 flex items-center justify-between">
            <h2 class="text-xl font-bold">📚 How to Use WasteWise</h2>
            <button @click="showHelp = false" class="text-2xl hover:text-blue-100">✕</button>
          </div>
          
          <div class="px-6 py-6 space-y-6">
            <!-- Dashboard Section -->
            <div class="border-l-4 border-blue-500 pl-4">
              <h3 class="font-bold text-lg text-gray-900 mb-2">🎯 Dashboard Overview</h3>
              <p class="text-gray-700 mb-2">The Dashboard displays real-time information about all waste bins on campus:</p>
              <ul class="space-y-1 text-sm text-gray-600 list-disc list-inside">
                <li><strong>Bin No.</strong> - Sequential bin numbering</li>
                <li><strong>Bin Location</strong> - Campus building/area where the bin is located</li>
                <li><strong>Floor</strong> - Building floor number (helps maintenance locate bins quickly)</li>
                <li><strong>Personnel</strong> - Assigned utility staff member responsible for this location</li>
                <li><strong>Fill %</strong> - Percentage of bin filled (visual progress bar)</li>
                <li><strong>Bin Status</strong> - Color-coded indicator: Green (empty) → Yellow (medium) → Red (full)</li>
                <li><strong>Bin Connection</strong> - Shows if device is connected or disconnected to network</li>
              </ul>
            </div>

            <!-- Bin Management Section -->
            <div class="border-l-4 border-green-500 pl-4">
              <h3 class="font-bold text-lg text-gray-900 mb-2">📦 Bin Management (with Smart Auto-Selection)</h3>
              <p class="text-gray-700 mb-2">Manage and organize your waste bins with intelligent features:</p>
              <ul class="space-y-1 text-sm text-gray-600 list-disc list-inside">
                <li><strong>Add Bin</strong> - Create new bins with location, floor, and personnel (auto-selects the right staff!)</li>
                <li><strong>Edit Bin</strong> - Modify bin details; personnel auto-updates when you change location</li>
                <li><strong>Auto-created Bins</strong> - Devices automatically create bins; admin can edit them later</li>
                <li><strong>Smart Auto-Selection:</strong> Pick a location → assigned personnel fills in instantly</li>
              </ul>
            </div>

            <!-- Smart Auto-Selection Feature -->
            <div class="border-l-4 border-purple-500 pl-4">
              <h3 class="font-bold text-lg text-gray-900 mb-2">🔄 Smart Personnel Auto-Selection</h3>
              <p class="text-gray-700 mb-2">New system feature for faster, more accurate bin setup:</p>
              <ul class="space-y-1 text-sm text-gray-600 list-disc list-inside">
                <li><strong>46+ locations</strong> pre-configured with assigned utility personnel</li>
                <li><strong>Select location → Personnel auto-fills</strong> with the correct staff member</li>
                <li><strong>One-to-many mapping:</strong> Some personnel manage multiple locations</li>
                <li><strong>All 20 utility personnel</strong> from the Campus Services are in the system</li>
                <li><strong>Manual override available:</strong> You can still select a different person if needed</li>
              </ul>
              <p class="text-xs text-gray-500 mt-2">💡 This saves time and reduces personnel assignment errors!</p>
            </div>

            <!-- Edit Bin Section -->
            <div class="border-l-4 border-indigo-500 pl-4">
              <h3 class="font-bold text-lg text-gray-900 mb-2">✏️ Edit Bin Details</h3>
              <p class="text-gray-700 mb-2">Go to Bin Management → Edit Bin page to:</p>
              <ul class="space-y-1 text-sm text-gray-600 list-disc list-inside">
                <li>Click the <strong>3-dot menu</strong> (⋯) on any bin row to open options</li>
                <li><strong>Edit</strong> - Change location, floor, and personnel (personnel auto-updates!)</li>
                <li><strong>Delete</strong> - Remove bins from the system (cannot be undone)</li>
              </ul>
            </div>

            <!-- Status Indicators Section -->
            <div class="border-l-4 border-red-500 pl-4">
              <h3 class="font-bold text-lg text-gray-900 mb-2">🚨 Understanding Status Colors</h3>
              <div class="space-y-2 text-sm">
                <div class="flex items-center space-x-2">
                  <div class="w-4 h-4 bg-green-500 rounded"></div>
                  <span class="text-gray-700"><strong>Green (0-49%)</strong> - Bin is empty or nearly empty</span>
                </div>
                <div class="flex items-center space-x-2">
                  <div class="w-4 h-4 bg-yellow-400 rounded"></div>
                  <span class="text-gray-700"><strong>Yellow (50-89%)</strong> - Bin is medium full, consider emptying soon</span>
                </div>
                <div class="flex items-center space-x-2">
                  <div class="w-4 h-4 bg-red-500 rounded"></div>
                  <span class="text-gray-700"><strong>Red (90-100%)</strong> - Bin is nearly full, empty immediately</span>
                </div>
              </div>
            </div>

            <!-- Tips Section -->
            <div class="bg-blue-50 border border-blue-200 rounded-lg p-4">
              <h3 class="font-bold text-gray-900 mb-2">💡 Pro Tips</h3>
              <ul class="space-y-1 text-sm text-gray-700 list-disc list-inside">
                <li>Check the Dashboard regularly for red status bins</li>
                <li>Assign personnel to bins for accountability</li>
                <li>Monitor "Disconnected" bins in connection status</li>
                <li>Use Edit Bin to keep location and personnel data up-to-date</li>
              </ul>
            </div>
          </div>

          <div class="bg-gray-50 px-6 py-4 border-t border-gray-200 flex justify-end">
            <button @click="showHelp = false" class="px-6 py-2 bg-blue-600 text-white rounded-lg hover:bg-blue-700 transition-colors font-medium">
              Close
            </button>
          </div>
        </div>
      </div>
    </transition>
  </div>
</template>
<script>
import { db } from '@/services/firebase';
import { ref as dbRef, onValue } from 'firebase/database';

export default {
  name: "HomePageFaculty",
  data() {
    return {
      showMenu: false,
      selectedMenu: 'dashboard',
      bins: [],
      alertVisible: false,
      alertMessage: '',
      showHelp: false,
    };
  },
  methods: {
    goToDashboard() {
      this.selectedMenu = 'dashboard';
      this.$router.push({ name: 'dashboard' });
      this.showMenu = false;
    },
      goToHistory() {
        this.selectedMenu = 'history';
        this.showMenu = false;
        this.$router.push({ name: 'bin_history' });
      },
    goToBinManagement() {
      this.selectedMenu = 'bin';
      this.$router.push({ name: 'bin_management' });
      this.showMenu = false;
    },
    getFillColor(fillPercentage) {
      // Convert fill percentage to hue (0-360)
      // 0% = green (120), 50% = yellow (60), 100% = red (0)
      const hue = Math.max(0, 120 - (fillPercentage * 1.2));
      return `hsl(${hue}, 100%, 50%)`;
    },
    showAlert(message) {
      this.alertMessage = message;
      this.alertVisible = true;
      // Try Web Notification
      if (window.Notification && Notification.permission === 'granted') {
        new Notification('WasteWise Alert', { body: message });
      } else if (window.Notification && Notification.permission !== 'denied') {
        Notification.requestPermission().then((perm) => {
          if (perm === 'granted') new Notification('WasteWise Alert', { body: message });
        });
      }
      // play beep
      try {
        const ctx = new (window.AudioContext || window.webkitAudioContext)();
        const o = ctx.createOscillator();
        const g = ctx.createGain();
        o.type = 'sine';
        o.frequency.value = 880;
        o.connect(g);
        g.connect(ctx.destination);
        o.start();
        g.gain.exponentialRampToValueAtTime(0.00001, ctx.currentTime + 0.7);
        setTimeout(()=>{o.stop();}, 700);
      } catch (e) {
        // ignore audio errors
      }
    },
    dismissAlert() {
      this.alertVisible = false;
      this.alertMessage = '';
    },
  },
  mounted() {
    const binsRef = dbRef(db, "bins");
    onValue(binsRef, (snapshot) => {
      const data = snapshot.val();
      if (data) {
        const nowSec = Math.floor(Date.now() / 1000);
        const entries = Object.entries(data).map(([key, value], idx) => {
          // Prefer explicit fillPercentage from device; otherwise derive from distance.
          let distance = null;
          let fillPercentage = null;
          let lastSeen = null;
          let connected = false;

          // Helper to extract latest sensor snapshot
          const extractLatestSensor = (sd) => {
            if (sd == null) return { distance: null, fillPercentage: null };
            if (typeof sd.distance === 'number' || typeof sd.fillPercentage === 'number') {
              return { distance: sd.distance ?? null, fillPercentage: sd.fillPercentage ?? null };
            }
            if (typeof sd === 'object') {
              const sdEntries = Object.entries(sd);
              if (sdEntries.length === 0) return { distance: null, fillPercentage: null };
              if (sdEntries.length === 1) {
                const single = sdEntries[0][1];
                return { distance: single.distance ?? null, fillPercentage: single.fillPercentage ?? null };
              }
              // Choose snapshot with highest timestamp if present
              let best = null;
              let bestTs = 0;
              sdEntries.forEach(([k, v]) => {
                const ts = v && v.timestamp ? Number(v.timestamp) : 0;
                if (ts > bestTs) { bestTs = ts; best = v; }
              });
              if (!best) best = sdEntries[sdEntries.length - 1][1];
              return { distance: best.distance ?? null, fillPercentage: best.fillPercentage ?? null };
            }
            return { distance: null, fillPercentage: null };
          };

          if (value.sensorData) {
            const latest = extractLatestSensor(value.sensorData);
            distance = latest.distance;
            fillPercentage = latest.fillPercentage;
            // Debug log
            console.log(`[Bin ${key}] sensorData found:`, { distance, fillPercentage });
          } else {
            console.log(`[Bin ${key}] No sensorData in Firebase`);
          }

          // If device provided no explicit fillPercentage but provided distance, compute it.
          // For computation we need two calibration points: emptyDistance and fullDistance. Use sensible defaults
          // but allow per-bin overrides via value.emptyDistance / value.fullDistance if present.
          if ((fillPercentage === null || fillPercentage === undefined) && distance != null) {
            const emptyDistance = value.emptyDistance !== undefined ? Number(value.emptyDistance) : 2; // distance when bin is empty (cm)
            const fullDistance = value.fullDistance !== undefined ? Number(value.fullDistance) : 45; // distance when bin is full (cm)
            // Constrain and compute: if distance >= fullDistance => 100% full; if distance <= emptyDistance => 0%.
            const clamped = Math.max(Math.min(distance, fullDistance), emptyDistance);
            const pct = ((clamped - emptyDistance) / Math.max(fullDistance - emptyDistance, 1)) * 100;
            // Invert if sensor measures distance from top (larger distance means emptier) — detect typical HC-SR04 setup where
            // smaller distance -> fuller. If fullDistance > emptyDistance then smaller distances are fuller, so invert.
            // Our formula above assumes distance increases with fullness; invert if that's not the case.
            // Determine direction: if fullDistance < emptyDistance, sensor reports smaller values when full.
            if (fullDistance < emptyDistance) {
              fillPercentage = (1 - ((clamped - fullDistance) / Math.max(emptyDistance - fullDistance, 1))) * 100;
            } else {
              fillPercentage = pct;
            }
            // clamp and normalize
            fillPercentage = Math.max(0, Math.min(100, fillPercentage));
            console.log(`[Bin ${key}] Computed fillPercentage from distance:`, { distance, emptyDistance, fullDistance, fillPercentage });
          } else if (fillPercentage === null && distance === null) {
            console.log(`[Bin ${key}] No distance or fillPercentage available - will show N/A`);
          }

          if (value.lastSeen !== undefined && value.lastSeen !== null) {
            lastSeen = Number(value.lastSeen);
            connected = (nowSec - lastSeen) <= 60;
          }

          // Determine rawStatus from fillPercentage (fallback to value.status)
          let rawStatus = value.status || 'empty';
          if (fillPercentage !== null && fillPercentage !== undefined) {
            if (fillPercentage >= 90) rawStatus = 'full';
            else if (fillPercentage >= 50) rawStatus = 'medium';
            else rawStatus = 'empty';
          }

          return {
            key,
            no: idx + 1,
            id: value.id,
            location: value.location,
            floor: value.floor || '-',
            distance,
            fillPercentage,
            rawStatus,
            lastSeen,
            connected,
            personnel: value.personnel || ''
          };
        });
        this.bins = entries;
        
        // Check for full bins and trigger alert
        const fullBins = entries.filter(e => e.rawStatus === 'full');
        if (fullBins.length) {
          const msg = fullBins.map(b => `${b.id || b.key || b.no}: ${b.location} is full`).join('; ');
          this.showAlert(msg);
        }
      } else {
        this.bins = [];
      }
    }, (err) => {
      // log DB listener errors
      // eslint-disable-next-line no-console
      console.error('[firebase][db listener] ', err);
    });
  },
};
</script>
<style scoped>
table {
  border-collapse: collapse;
}
.slide-enter-active, .slide-leave-active {
  transition: all 0.3s ease;
}
.slide-enter, .slide-leave-to {
  transform: translateY(-100%);
  opacity: 0;
}
</style>
  