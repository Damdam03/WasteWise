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

    <!-- Main Content -->
    <div class="flex justify-center mt-8 px-6 pb-8">
      <div class="w-full max-w-4xl">
        <h1 class="text-3xl font-bold mb-6 text-gray-900">Bin Connectivity History</h1>

        <!-- Filter Section -->
        <div class="bg-white p-4 rounded-lg shadow-md mb-6">
          <label for="binSelect" class="block font-semibold mb-2 text-gray-700">Filter by Bin:</label>
          <select v-model="selectedBinId" @change="applyFilter" class="border border-gray-300 p-2 rounded w-full md:w-64 focus:outline-none focus:ring-2 focus:ring-indigo-500">
            <option value="">All Bins</option>
            <option v-for="bin in bins" :key="bin.key" :value="bin.key">
              {{ bin.location }} ({{ bin.id || bin.key }})
            </option>
          </select>
        </div>

        <!-- History Table -->
        <div class="bg-white rounded-lg shadow-md overflow-hidden">
          <table class="w-full border-collapse">
            <thead>
              <tr class="bg-gradient-to-r from-indigo-600 to-indigo-700 text-white">
                <th class="px-4 py-3 text-left font-semibold">Bin ID</th>
                <th class="px-4 py-3 text-left font-semibold">Location</th>
                <th class="px-4 py-3 text-left font-semibold">Timestamp</th>
                <th class="px-4 py-3 text-left font-semibold">Status</th>
              </tr>
            </thead>
            <tbody>
              <tr v-for="(entry, index) in paginatedHistory" :key="index" class="border-b border-gray-200 hover:bg-indigo-50 transition-colors duration-200">
                <td class="px-4 py-3 font-mono text-sm text-gray-700 truncate">{{ entry.binId }}</td>
                <td class="px-4 py-3 text-gray-800 font-semibold">{{ entry.location }}</td>
                <td class="px-4 py-3 text-gray-700">{{ formatTimestamp(entry.timestamp) }}</td>
                <td class="px-4 py-3">
                  <span :class="['font-semibold px-2 py-1 rounded', entry.connected ? 'bg-green-100 text-green-700' : 'bg-red-100 text-red-700']">
                    {{ entry.connected ? 'Connected' : 'Disconnected' }}
                  </span>
                </td>
              </tr>
              <tr v-if="filteredHistory.length === 0">
                <td colspan="4" class="text-center py-6 text-gray-500">No connectivity history found.</td>
              </tr>
            </tbody>
          </table>
        </div>

        <!-- Pagination -->
        <div class="mt-6 flex items-center justify-between">
          <div class="text-sm text-gray-600">
            Showing {{ Math.min(pageSize, filteredHistory.length) }} of {{ filteredHistory.length }} entries
          </div>
          <div class="flex space-x-2">
            <button 
              v-if="currentPage > 1"
              @click="previousPage"
              class="px-4 py-2 bg-indigo-600 text-white rounded hover:bg-indigo-700 transition-colors duration-200 font-semibold"
            >
              Previous
            </button>
            <button 
              v-if="hasNextPage"
              @click="nextPage"
              class="px-4 py-2 bg-indigo-600 text-white rounded hover:bg-indigo-700 transition-colors duration-200 font-semibold"
            >
              Next
            </button>
          </div>
        </div>
      </div>
    </div>

    <!-- Help Modal -->
    <transition
      enter-active-class="transition ease-out duration-300"
      enter-from-class="opacity-0"
      enter-to-class="opacity-100"
      leave-active-class="transition ease-in duration-200"
      leave-from-class="opacity-100"
      leave-to-class="opacity-0"
    >
      <div v-if="showHelp" class="fixed inset-0 bg-black bg-opacity-50 flex items-center justify-center z-50">
        <div class="bg-white p-6 rounded-lg shadow-xl max-w-md">
          <h2 class="text-xl font-bold mb-4 text-gray-900">Help - Bin Connectivity History</h2>
          <p class="text-sm text-gray-700 leading-relaxed mb-4">
            This page displays the real-time connectivity history of waste bins across campus. You can filter by specific bins to see their connection status changes over time.
          </p>
          <button 
            @click="showHelp = false"
            class="w-full px-4 py-2 bg-indigo-600 text-white rounded hover:bg-indigo-700 transition-colors duration-200 font-semibold"
          >
            Close
          </button>
        </div>
      </div>
    </transition>
  </div>
</template>

<script>
import { db } from '@/services/firebase';
import { ref as dbRef, onValue, off } from 'firebase/database';

export default {
  name: 'BinHistory',
  data() {
    return {
      bins: [],
      selectedBinId: '',
      allHistoryEntries: [],
      filteredHistory: [],
      pageSize: 50,
      currentPage: 1,
      binsListener: null,
      historyListener: null,
      showMenu: false,
      selectedMenu: 'history',
      showHelp: false,
    };
  },
  computed: {
    paginatedHistory() {
      const start = (this.currentPage - 1) * this.pageSize;
      const end = start + this.pageSize;
      return this.filteredHistory.slice(start, end);
    },
    hasNextPage() {
      return this.currentPage * this.pageSize < this.filteredHistory.length;
    },
  },
  watch: {
    selectedBinId() {
      this.currentPage = 1;
      this.applyFilter();
    },
  },
  methods: {
    goToDashboard() {
      this.selectedMenu = 'dashboard';
      this.$router.push({ name: 'dashboard' });
      this.showMenu = false;
    },
    goToBinManagement() {
      this.selectedMenu = 'bin';
      this.$router.push({ name: 'bin_management' });
      this.showMenu = false;
    },
    goToHistory() {
      this.selectedMenu = 'history';
      this.$router.push({ name: 'bin_history' });
      this.showMenu = false;
    },
    formatTimestamp(timestamp) {
      // Accept timestamps in various formats:
      // - milliseconds (>= 1e12)
      // - seconds (>= 1e9 && < 1e12)
      // - small counters/uptime (< 1e9) -> show as counter
      if (timestamp === null || timestamp === undefined) return 'N/A';
      const n = Number(timestamp);
      if (!Number.isFinite(n)) return String(timestamp);
      // milliseconds
      if (n >= 1e12) {
        return new Date(n).toLocaleString('en-US', {
          year: 'numeric', month: 'short', day: 'numeric',
          hour: '2-digit', minute: '2-digit', second: '2-digit',
        });
      }
      // seconds
      if (n >= 1e9) {
        return new Date(n * 1000).toLocaleString('en-US', {
          year: 'numeric', month: 'short', day: 'numeric',
          hour: '2-digit', minute: '2-digit', second: '2-digit',
        });
      }
      // small numbers likely device counters
      return `${n} (device counter)`;
    },
    applyFilter() {
      if (this.selectedBinId === '') {
        this.filteredHistory = [...this.allHistoryEntries];
      } else {
        this.filteredHistory = this.allHistoryEntries.filter(
          (entry) => entry.binId === this.selectedBinId
        );
      }
      this.currentPage = 1;
    },
    nextPage() {
      if (this.hasNextPage) {
        this.currentPage += 1;
      }
    },
    previousPage() {
      if (this.currentPage > 1) {
        this.currentPage -= 1;
      }
    },
    loadBins() {
      const binsRef = dbRef(db, 'bins');
      this.binsListener = onValue(binsRef, (snapshot) => {
        if (snapshot.exists()) {
          const binsData = snapshot.val();
          this.bins = Object.keys(binsData).map((key) => ({
            key,
            id: binsData[key].id || key,
            location: binsData[key].location || 'Unknown',
          }));
        }
      });
    },
    loadConnectivityHistory() {
      try {
        // Load current bin connection status from bins data
        const binsRef = dbRef(db, 'bins');
        onValue(binsRef, (snapshot) => {
          if (snapshot.exists()) {
            const binsData = snapshot.val();
            const now = Math.floor(Date.now() / 1000);
            
            // Create history entries from current bin status
            const entries = [];
            Object.entries(binsData).forEach(([key, binData]) => {
              const lastSeen = binData.lastSeen || 0;
              const wasConnected = now - lastSeen <= 60;
              const location = binData.location || 'Unknown';

              // Add latest connectivity snapshot based on lastSeen
              entries.push({
                binId: key,
                location: location,
                timestamp: lastSeen || 0,
                connected: binData.connected === true || wasConnected,
                status: binData.status || 'unknown',
                source: 'lastSeen'
              });

              // If sensorData exists, add all sensor snapshots
              if (binData.sensorData) {
                Object.entries(binData.sensorData).forEach(([snapKey, snap]) => {
                  // normalize timestamp like in BinManagement
                  const raw = snap.timestamp;
                  const n = Number(raw);
                  let ts = null;
                  if (Number.isFinite(n)) {
                    if (n >= 1e12) ts = n; // ms
                    else if (n >= 1e9) ts = n * 1000; // s -> ms
                    else ts = n; // counter
                  }
                  entries.push({
                    binId: key,
                    location: location,
                    timestamp: ts,
                    connected: true,
                    status: snap.status || 'snapshot',
                    source: 'sensorData',
                    snapshotId: snapKey,
                    snapshot: snap,
                  });
                });
              }
            });
            
            // Sort by timestamp descending (most recent first)
            this.allHistoryEntries = entries.sort((a, b) => (b.timestamp || 0) - (a.timestamp || 0));
            this.applyFilter();
          }
        });

        // Also listen to connectionPing for real-time connection updates
        const pingRef = dbRef(db, 'connectionPing');
        onValue(pingRef, (snapshot) => {
          if (snapshot.exists()) {
            const pingData = snapshot.val();
            console.log('[BinHistory] Connection ping data received:', pingData);
            
            // Parse device IDs and create entries
            Object.entries(pingData).forEach(([deviceKey, pingData]) => {
              // Extract device ID from key (e.g., "esp32_rest_132135346616224" -> "132135346616224")
              const deviceMatch = deviceKey.match(/esp32_rest_(\d+)$/);
              if (deviceMatch) {
                console.log('[BinHistory] Device ping updated:', deviceMatch[1]);
              }
            });
          }
        });
      } catch (error) {
        console.error('Error loading connectivity history:', error);
      }
    },
  },
  mounted() {
    this.loadBins();
    this.loadConnectivityHistory();
  },
  beforeUnmount() {
    if (this.binsListener) {
      off(dbRef(db, 'bins'));
    }
    if (this.historyListener) {
      off(dbRef(db, 'connectionPing'));
    }
  },
};
</script>

<style scoped>
.slide-fade-enter-active {
  transition: all 0.3s ease-out;
}

.slide-fade-leave-active {
  transition: all 0.2s ease-in;
}

.slide-fade-enter-from {
  transform: translateX(-100%);
  opacity: 0;
}

.slide-fade-leave-to {
  transform: translateX(-100%);
  opacity: 0;
}

.fade-enter-active,
.fade-leave-active {
  transition: opacity 0.3s ease;
}

.fade-enter-from,
.fade-leave-to {
  opacity: 0;
}
</style>
