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
      <div class="w-full max-w-6xl">
        <h1 class="text-3xl font-bold mb-6 text-gray-900">Complete Bin History & Sensor Data</h1>

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
                <th class="px-4 py-3 text-center font-semibold">Fill %</th>
                <th class="px-4 py-3 text-center font-semibold">Distance (cm)</th>
                <th class="px-4 py-3 text-left font-semibold">Status</th>
                <th class="px-4 py-3 text-left font-semibold">Connection</th>
              </tr>
            </thead>
            <tbody>
              <tr v-for="(entry, index) in paginatedHistory" :key="index" class="border-b border-gray-200 hover:bg-indigo-50 transition-colors duration-200">
                <td class="px-4 py-3 font-mono text-sm text-gray-700 truncate">{{ entry.binId }}</td>
                <td class="px-4 py-3 text-gray-800 font-semibold">{{ entry.location }}</td>
                <td class="px-4 py-3 text-gray-700 text-sm">{{ formatTimestamp(entry.timestamp) }}</td>
                <td class="px-4 py-3 text-center font-semibold">
                  <div class="flex items-center justify-center space-x-2">
                    <span :class="['px-3 py-1 rounded font-bold text-white', getFillColor(entry.fillPercentage)]">
                      {{ entry.fillPercentage !== undefined ? entry.fillPercentage + '%' : 'N/A' }}
                    </span>
                  </div>
                </td>
                <td class="px-4 py-3 text-center text-gray-700">
                  {{ entry.distance !== undefined ? entry.distance.toFixed(2) : 'N/A' }}
                </td>
                <td class="px-4 py-3">
                  <span :class="['font-semibold px-2 py-1 rounded text-xs', getStatusColor(entry.status)]">
                    {{ entry.status || 'unknown' }}
                  </span>
                </td>
                <td class="px-4 py-3">
                  <span :class="['font-semibold px-2 py-1 rounded text-xs', entry.connected ? 'bg-green-100 text-green-700' : 'bg-red-100 text-red-700']">
                    {{ entry.connected ? '✓ Connected' : '✗ Disconnected' }}
                  </span>
                </td>
              </tr>
              <tr v-if="filteredHistory.length === 0">
                <td colspan="7" class="text-center py-6 text-gray-500">No history found.</td>
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

        <!-- Stats Card -->
        <div class="mt-8 grid grid-cols-1 md:grid-cols-4 gap-4">
          <div class="bg-white p-4 rounded-lg shadow">
            <div class="text-sm text-gray-600">Total Readings</div>
            <div class="text-3xl font-bold text-indigo-600">{{ filteredHistory.length }}</div>
          </div>
          <div class="bg-white p-4 rounded-lg shadow">
            <div class="text-sm text-gray-600">Current Fill</div>
            <div class="text-3xl font-bold" :class="getCurrentFillColor()">
              {{ getCurrentFill() }}%
            </div>
          </div>
          <div class="bg-white p-4 rounded-lg shadow">
            <div class="text-sm text-gray-600">Status</div>
            <div class="text-lg font-semibold capitalize">{{ getCurrentStatus() }}</div>
          </div>
          <div class="bg-white p-4 rounded-lg shadow">
            <div class="text-sm text-gray-600">Last Update</div>
            <div class="text-sm font-semibold">{{ getLastUpdate() }}</div>
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
        <div class="bg-white p-6 rounded-lg shadow-xl max-w-2xl max-h-96 overflow-y-auto">
          <h2 class="text-xl font-bold mb-4 text-gray-900">📊 Complete Bin History Guide</h2>
          
          <div class="space-y-4 text-sm text-gray-700">
            <!-- Overview -->
            <div>
              <h3 class="font-bold text-gray-900 mb-2">📋 What You See Here</h3>
              <p class="mb-2">This page shows comprehensive historical data for all bins including:</p>
              <ul class="list-disc list-inside space-y-1 ml-2">
                <li><strong>Fill Level (%)</strong> - Waste level from 0-100%</li>
                <li><strong>Distance (cm)</strong> - Raw sensor reading from ultrasonic sensor</li>
                <li><strong>Status</strong> - empty, medium, or full</li>
                <li><strong>Connection</strong> - Device connectivity status</li>
                <li><strong>Timestamp</strong> - Exact date/time of reading with seconds precision</li>
              </ul>
            </div>

            <!-- Color Coding -->
            <div>
              <h3 class="font-bold text-gray-900 mb-2">🎨 Color Coding</h3>
              <ul class="space-y-1 ml-2">
                <li><span class="inline-block w-3 h-3 bg-green-600 rounded mr-2"></span>Green 0-49%: Empty bin</li>
                <li><span class="inline-block w-3 h-3 bg-yellow-500 rounded mr-2"></span>Yellow 50-89%: Medium fill</li>
                <li><span class="inline-block w-3 h-3 bg-red-600 rounded mr-2"></span>Red 90-100%: Full/Alert</li>
              </ul>
            </div>

            <!-- Stats Card -->
            <div>
              <h3 class="font-bold text-gray-900 mb-2">📈 Stats Card (Bottom)</h3>
              <ul class="list-disc list-inside space-y-1 ml-2">
                <li><strong>Total Readings</strong> - Number of sensor readings recorded</li>
                <li><strong>Current Fill</strong> - Latest fill percentage</li>
                <li><strong>Status</strong> - Current bin status</li>
                <li><strong>Last Update</strong> - When the bin last reported data</li>
              </ul>
            </div>

            <!-- Filtering -->
            <div>
              <h3 class="font-bold text-gray-900 mb-2">🔍 Filter & Search</h3>
              <p>Use the dropdown to filter by specific bin. Shows all sensor readings and connectivity changes for that bin in chronological order (newest first).</p>
            </div>
          </div>

          <button 
            @click="showHelp = false"
            class="w-full mt-4 px-4 py-2 bg-indigo-600 text-white rounded hover:bg-indigo-700 transition-colors duration-200 font-semibold"
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
      if (!timestamp) return 'N/A';
      // Convert seconds to milliseconds (Firebase stores timestamps in seconds)
      const date = new Date(timestamp * 1000);
      return date.toLocaleString('en-US', {
        year: 'numeric',
        month: 'short',
        day: 'numeric',
        hour: '2-digit',
        minute: '2-digit',
        second: '2-digit',
      });
    },
    getFillColor(fillPercentage) {
      if (fillPercentage === undefined || fillPercentage === null) return 'bg-gray-400';
      if (fillPercentage >= 90) return 'bg-red-600';
      if (fillPercentage >= 50) return 'bg-yellow-500';
      return 'bg-green-600';
    },
    getStatusColor(status) {
      switch (status) {
        case 'full': return 'bg-red-100 text-red-700';
        case 'medium': return 'bg-yellow-100 text-yellow-700';
        case 'empty': return 'bg-green-100 text-green-700';
        default: return 'bg-gray-100 text-gray-700';
      }
    },
    getCurrentFill() {
      if (this.filteredHistory.length === 0) return 'N/A';
      const latest = this.filteredHistory[0];
      return latest.fillPercentage !== undefined ? Math.round(latest.fillPercentage) : 'N/A';
    },
    getCurrentFillColor() {
      if (this.filteredHistory.length === 0) return 'text-gray-600';
      const latest = this.filteredHistory[0];
      return this.getFillColor(latest.fillPercentage).replace('bg-', 'text-');
    },
    getCurrentStatus() {
      if (this.filteredHistory.length === 0) return 'unknown';
      const latest = this.filteredHistory[0];
      return latest.status || 'unknown';
    },
    getLastUpdate() {
      if (this.filteredHistory.length === 0) return 'Never';
      const latest = this.filteredHistory[0];
      return this.formatTimestamp(latest.timestamp);
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
        // Load sensor data history from all bins
        const binsRef = dbRef(db, 'bins');
        onValue(binsRef, (snapshot) => {
          if (snapshot.exists()) {
            const binsData = snapshot.val();
            const now = Math.floor(Date.now() / 1000);
            const entries = [];

            // For each bin, load its sensorData history
            Object.entries(binsData).forEach(([binKey, binData]) => {
              const location = binData.location || 'Unknown';
              const sensorData = binData.sensorData || {};
              
              // Convert sensorData to array of entries
              Object.entries(sensorData).forEach(([deviceId, readings]) => {
                // readings can have multiple timestamps
                if (readings && typeof readings === 'object') {
                  // If readings has timestamp property, it's a single reading
                  if (readings.timestamp) {
                    entries.push({
                      binId: binKey,
                      location: location,
                      timestamp: readings.timestamp,
                      distance: readings.distance,
                      fillPercentage: readings.fillPercentage,
                      status: readings.status || 'unknown',
                      connected: true,
                      deviceId: readings.deviceId || deviceId,
                      type: 'sensor'
                    });
                  }
                }
              });

              // Also add connectivity status
              const lastSeen = binData.lastSeen || 0;
              const wasConnected = now - lastSeen <= 60;
              entries.push({
                binId: binKey,
                location: location,
                timestamp: lastSeen,
                distance: undefined,
                fillPercentage: undefined,
                status: binData.status || 'unknown',
                connected: binData.connected === true || wasConnected,
                type: 'connectivity'
              });
            });

            // Sort by timestamp descending (most recent first)
            this.allHistoryEntries = entries.sort((a, b) => (b.timestamp || 0) - (a.timestamp || 0));
            this.applyFilter();
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
