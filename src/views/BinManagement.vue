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

    <!-- Table + Add Bin Button -->
    <div class="flex justify-center mt-8">
      <div class="w-full max-w-3xl">
        <div class="flex justify-end mb-4">
          <button class="flex items-center px-5 py-2.5 bg-blue-600 text-white rounded-lg hover:bg-blue-700 transition-colors duration-200 shadow-md hover:shadow-lg font-semibold" @click="openAddModal">
            <svg class="w-5 h-5 mr-2" fill="none" stroke="currentColor" stroke-width="2" viewBox="0 0 24 24"><path d="M12 4v16m8-8H4" stroke="white"/></svg>
            Add Bin
          </button>
        </div>
        <!-- guidance moved to Help modal -->
        <table class="w-full border-collapse bg-white rounded-lg shadow-md overflow-hidden">
          <thead>
            <tr class="bg-gradient-to-r from-green-600 to-green-700 text-white">
              <th class="px-4 py-3 text-left font-semibold">Bin No.</th>
              <th class="px-4 py-3 text-left font-semibold">Bin ID</th>
              <th class="px-4 py-3 text-left font-semibold">Actions</th>
              <th class="px-4 py-3 text-left font-semibold">Bin Location</th>
              <th class="px-4 py-3 text-left font-semibold">Floor</th>
              <th class="px-4 py-3 text-left font-semibold">Personnel</th>
              <th class="px-4 py-3 text-left font-semibold">Bin Connection</th>
            </tr>
          </thead>
          <tbody>
            <tr v-for="(bin, idx) in bins" :key="bin.no" :class="idx % 2 === 0 ? 'bg-white' : 'bg-gray-50'" class="border-b border-gray-200 hover:bg-green-50 transition-colors duration-200">
              <td class="px-4 py-3 font-semibold text-gray-900">{{ bin.no }}</td>
              <td class="px-4 py-3 font-mono text-sm text-gray-700 truncate">{{ bin.id || bin.key }}</td>
              <td class="px-4 py-3 text-center">
                <button @click="openHistory(idx)" class="px-3 py-1 bg-gray-100 rounded hover:bg-gray-200 text-sm">History</button>
              </td>
              <td class="px-4 py-3 font-semibold text-gray-800">{{ bin.location }}</td>
              <td class="px-4 py-3 text-gray-700">{{ bin.floor || '-' }}</td>
              <td class="px-4 py-3 text-gray-700">{{ bin.personnel || '-' }}</td>
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
    </div>

    <!-- Add Bin Modal -->
    <div v-if="showAddModal" class="fixed inset-0 bg-black bg-opacity-40 flex items-center justify-center z-50">
      <div class="bg-white p-6 rounded shadow-lg w-80">
  <h2 class="text-lg font-bold mb-4">Add Bin (Manual)</h2>
  <p class="text-sm text-gray-600 mb-2">Bin ID is assigned automatically. Note: ESP32 devices typically create their own bin entries — use this form only to add a manual/bin-less device or to create a placeholder. To enrich device-created bins, use the Edit Bin page to add location, floor and personnel.</p>
        <label class="text-sm font-medium">Location</label>
        <select v-model="newBinLocation" @change="autoSelectPersonnel" class="border p-2 w-full mb-2">
          <option disabled value="">Select location</option>
          <option>Laboratory Building 2</option>
          <option>CAH AVR</option>
          <option>COS Building</option>
          <option>Laboratory Building 1</option>
          <option>Engineering Building</option>
          <option>Chapel</option>
          <option>RDE Building</option>
          <option>Dormitory (Male Wing)</option>
          <option>Registrar Building</option>
          <option>GAP Office</option>
          <option>Business Hub</option>
          <option>Commercial Building</option>
          <option>Entrepreneurial Building</option>
          <option>Landbank ATM Booth</option>
          <option>Waiting Shed</option>
          <option>Old Laboratory High School Buildings</option>
          <option>Classrooms</option>
          <option>COA Office</option>
          <option>Supply Office</option>
          <option>Gymnasium</option>
          <option>University Library</option>
          <option>Graduate School Building</option>
          <option>VPAA Office</option>
          <option>Geology Building</option>
          <option>Museo de Isarog</option>
          <option>Auditorium</option>
          <option>Covered Court</option>
          <option>Field</option>
          <option>Oval Stage</option>
          <option>Health Services Office</option>
          <option>Archive</option>
          <option>Lactation Room</option>
          <option>CED Buildings</option>
          <option>IIT Building</option>
          <option>CBM Building</option>
          <option>CBM Offices</option>
          <option>CBM Faculty Rooms</option>
          <option>CBM Canteen</option>
          <option>Ang-Chinto Building</option>
          <option>Alumni Building</option>
          <option>Dormitory (Female Wing)</option>
          <option>University Canteen</option>
          <option>Procurement Office</option>
          <option>BAC Office</option>
          <option>Internal Audit Unit</option>
          <option>NSTP Office</option>
        </select>
        <label class="text-sm font-medium">Floor</label>
        <input v-model.number="newBinFloor" type="number" min="0" class="border p-2 w-full mb-2" placeholder="Enter floor number" />
        <label class="text-sm font-medium">Assigned Personnel</label>
        <select v-model="newBinPersonnel" class="border p-2 w-full mb-4">
          <option disabled value="">Select personnel</option>
          <option>Alfredo C. Dominguez</option>
          <option>Romy A. Milante</option>
          <option>Rodolfo B. Adane Jr.</option>
          <option>Joel F. Atole</option>
          <option>Emmanuel B. Batanes</option>
          <option>Alessandro V. Cama</option>
          <option>Enrique R. Castro Jr.</option>
          <option>Ronald O. Cea</option>
          <option>Albert B. Claveria</option>
          <option>Alfredo B. Claveria</option>
          <option>Jonel S. Correa</option>
          <option>Aida A. Dulfo</option>
          <option>Bobby P. Galarce</option>
          <option>Gerry P. Huit</option>
          <option>Jonjo A. Milante</option>
          <option>Dan John B. Natividad</option>
          <option>Oscar M. Navarra Jr.</option>
          <option>Joebert R. Oriana</option>
          <option>Regina P. Pamada</option>
          <option>Rose J. Retome</option>
        </select>
        <div class="flex items-center mb-4">
          <label class="mr-2">Connected:</label>
          <input type="checkbox" v-model="newBinConnected" />
        </div>
        <div class="flex justify-end gap-2">
          <button @click="showAddModal = false" class="px-3 py-1 border rounded">Cancel</button>
          <button @click="addBin" class="px-3 py-1 bg-blue-600 text-white rounded">Add (Manual)</button>
        </div>
      </div>
    </div>

    <!-- Edit Bin Button -->
    <div class="flex justify-center mt-2">
      <button class="flex items-center px-4 py-2 border border-gray-400 rounded bg-white hover:bg-gray-100 text-gray-700 font-semibold" @click="goToEdit"> 
        <svg class="w-5 h-5 mr-2" fill="none" stroke="currentColor" stroke-width="2" viewBox="0 0 24 24"><path d="M12 20h9" stroke="black"/><path d="M16.5 3.5a2.121 2.121 0 113 3L7 19l-4 1 1-4 12.5-12.5z" stroke="black"/></svg>
        Edit Bin
      </button>
    </div>

    <!-- Firebase Connection Test Widget -->
    <FirebaseConnectionTest @close="closeConnectionTest" />

    <!-- History Modal -->
    <transition name="fade">
      <div v-if="showHistoryModal" class="fixed inset-0 bg-black/40 flex items-center justify-center z-50">
        <div class="bg-white rounded-lg shadow-2xl w-full max-w-xl mx-4 max-h-[70vh] overflow-auto">
          <div class="px-6 py-4 border-b flex items-center justify-between">
            <h3 class="font-bold">History — {{ historyBinKey }}</h3>
            <button @click="closeHistory" class="text-gray-600 hover:text-gray-800">✕</button>
          </div>
          <div class="p-6">
            <div v-if="historyData === null" class="text-sm text-gray-500">Loading...</div>
            <div v-else-if="historyData.length === 0" class="text-sm text-gray-600">No history found for this bin.</div>
            <div v-else class="space-y-3">
              <div v-for="(h, i) in historyData" :key="h.key" class="p-3 border rounded bg-gray-50">
                <div class="flex justify-between text-sm text-gray-700">
                  <div>
                    <div class="font-semibold">Snapshot {{ i + 1 }}</div>
                    <div class="text-xs text-gray-500">ID: {{ h.key }}</div>
                  </div>
              <div class="text-right text-xs text-gray-500">{{ formatSnapshotTime(h) }}</div>
                </div>
                <div class="mt-2 text-sm text-gray-800">
                  <div>distance: {{ h.distance !== undefined ? h.distance : 'N/A' }}</div>
                  <div>fillPercentage: {{ h.fillPercentage !== undefined ? h.fillPercentage : 'N/A' }}</div>
                  <div v-if="h.extra" class="text-xs text-gray-600">{{ h.extra }}</div>
                </div>
              </div>
            </div>
          </div>
        </div>
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
          <div class="sticky top-0 bg-gradient-to-r from-green-600 to-green-700 text-white px-6 py-4 flex items-center justify-between">
            <h2 class="text-xl font-bold">📚 Bin Management Guide</h2>
            <button @click="showHelp = false" class="text-2xl hover:text-green-100">✕</button>
          </div>
          
          <div class="px-6 py-6 space-y-6">
            <!-- Adding Bins Section -->
            <div class="border-l-4 border-green-500 pl-4">
              <h3 class="font-bold text-lg text-gray-900 mb-2">➕ Adding a New Bin</h3>
              <p class="text-gray-700 mb-2">Follow these steps to add a new bin:</p>
              <ol class="space-y-1 text-sm text-gray-600 list-decimal list-inside">
                <li>Click the <strong>"Add Bin"</strong> button in the top right</li>
                <li>Select <strong>Location</strong> from the dropdown (choose from all campus buildings)</li>
                <li><strong>Personnel auto-selects!</strong> When you choose a location, the assigned personnel is automatically selected based on their building assignment</li>
                <li>Enter the <strong>Floor</strong> number</li>
                <li>You can override the auto-selected personnel if needed by choosing a different staff member</li>
                <li>Click <strong>"Add"</strong> to create the bin</li>
              </ol>
              <p class="text-sm text-gray-600 mt-2 font-semibold">💡 Tips: 
                <br/>• The Bin ID is automatically assigned by the system
                <br/>• Each location has a dedicated utility personnel - check the auto-selection!
                <br/>• Some personnel manage multiple locations
              </p>
            </div>

            <!-- Bin List Section -->
            <div class="border-l-4 border-green-500 pl-4">
              <h3 class="font-bold text-lg text-gray-900 mb-2">📋 Viewing Your Bins</h3>
              <p class="text-gray-700 mb-2">The table shows all bins with:</p>
              <ul class="space-y-1 text-sm text-gray-600 list-disc list-inside">
                <li><strong>Bin No.</strong> - Sequential numbering (1, 2, 3...)</li>
                <li><strong>Bin ID</strong> - Unique system identifier</li>
                <li><strong>Bin Location</strong> - Campus location</li>
                <li><strong>Floor</strong> - Building floor number where bin is located</li>
                <li><strong>Personnel</strong> - Assigned utility staff member for that location</li>
                <li><strong>Bin Connection</strong> - Device connectivity status (Connected/Disconnected)</li>
              </ul>
            </div>

            <!-- Auto-Selection Feature -->
            <div class="border-l-4 border-purple-500 pl-4">
              <h3 class="font-bold text-lg text-gray-900 mb-2">🔄 Smart Personnel Auto-Selection</h3>
              <p class="text-gray-700 mb-2">When adding or editing a bin, the system automatically matches personnel to locations:</p>
              <ul class="space-y-1 text-sm text-gray-600 list-disc list-inside">
                <li>Each campus building/area has one assigned utility personnel</li>
                <li>Select a location → Personnel auto-fills instantly</li>
                <li>Personnel can manage multiple locations (e.g., Albert B. Claveria manages 5 areas)</li>
                <li>You can still manually change the personnel if needed</li>
                <li>All 20 utility personnel and their locations are pre-configured in the system</li>
              </ul>
            </div>

            <!-- Device Auto-Creation Section -->
            <div class="border-l-4 border-blue-500 pl-4">
              <h3 class="font-bold text-lg text-gray-900 mb-2">🤖 Device Auto-Creation</h3>
              <p class="text-gray-700 mb-2">ESP32 devices can automatically create bins:</p>
              <ul class="space-y-1 text-sm text-gray-600 list-disc list-inside">
                <li>When a device starts up, it automatically creates a bin entry in Firebase</li>
                <li>Most bins are automatically created by ESP32 devices when they first come online</li>
                <li>Use <strong>Add Bin</strong> only for manual entries or non-device bins</li>
                <li>After a device creates a bin, use <strong>Edit Bin</strong> page to add location, floor, and personnel details</li>
                <li>Personnel will auto-select based on the location you choose!</li>
              </ul>
            </div>

            <!-- Tips Section -->
            <div class="bg-green-50 border border-green-200 rounded-lg p-4">
              <h3 class="font-bold text-gray-900 mb-2">💡 Best Practices</h3>
              <ul class="space-y-1 text-sm text-gray-700 list-disc list-inside">
                <li><strong>Use auto-selection:</strong> Trust the system to pick the right personnel for each location</li>
                <li><strong>Keep locations consistent:</strong> Always use the exact location name from the dropdown</li>
                <li><strong>Update floor numbers:</strong> Accurate floor data helps maintenance staff locate bins quickly</li>
                <li><strong>Monitor connections:</strong> Disconnected bins may have power or network issues - investigate promptly</li>
                <li><strong>Edit device-created bins:</strong> Enhance auto-created bins with full location and personnel details</li>
              </ul>
            </div>
          </div>

          <div class="bg-gray-50 px-6 py-4 border-t border-gray-200 flex justify-end">
            <button @click="showHelp = false" class="px-6 py-2 bg-green-600 text-white rounded-lg hover:bg-green-700 transition-colors font-medium">
              Close
            </button>
          </div>
        </div>
      </div>
    </transition>
  </div>
</template>

<script>
import { db, logDbError } from '@/services/firebase';
import { ref as dbRef, onValue, push, get, child } from 'firebase/database';
import FirebaseConnectionTest from '@/components/FirebaseConnectionTest.vue';

export default {
  name: "HomePageStudent",
  components: {
    FirebaseConnectionTest
  },
  data() {
    return {
      showMenu: false,
      selectedMenu: 'dashboard',
      bins: [],
  showAddModal: false,
  newBinId: '',
  newBinLocation: '',
  newBinFloor: 1,
  newBinPersonnel: '',
  newBinConnected: true,
  showHistoryModal: false,
  historyData: null,
  historyBinKey: null,
  showHelp: false,
  locationPersonnelMap: {
    'Laboratory Building 2': 'Rodolfo B. Adane Jr.',
    'CAH AVR': 'Rodolfo B. Adane Jr.',
    'COS Building': 'Joel F. Atole',
    'Laboratory Building 1': 'Joel F. Atole',
    'Engineering Building': 'Emmanuel B. Batanes',
    'Chapel': 'Emmanuel B. Batanes',
    'RDE Building': 'Alessandro V. Cama',
    'Dormitory (Male Wing)': 'Enrique R. Castro Jr.',
    'Registrar Building': 'Ronald O. Cea',
    "GAP Office": 'Ronald O. Cea',
    'Business Hub': 'Albert B. Claveria',
    'Commercial Building': 'Albert B. Claveria',
    'Entrepreneurial Building': 'Albert B. Claveria',
    'Landbank ATM Booth': 'Albert B. Claveria',
    'Waiting Shed': 'Albert B. Claveria',
    'Old Laboratory High School Buildings': 'Alfredo B. Claveria',
    'Classrooms': 'Alfredo B. Claveria',
    'COA Office': 'Alfredo B. Claveria',
    'Supply Office': 'Alfredo B. Claveria',
    'Gymnasium': 'Jonel S. Correa',
    'University Library': 'Aida A. Dulfo',
    'Graduate School Building': 'Bobby P. Galarce',
    'VPAA Office': 'Bobby P. Galarce',
    'Geology Building': 'Bobby P. Galarce',
    'Museo de Isarog': 'Gerry P. Huit',
    'Auditorium': 'Gerry P. Huit',
    'Covered Court': 'Jonjo A. Milante',
    'Field': 'Jonjo A. Milante',
    'Oval Stage': 'Jonjo A. Milante',
    'Health Services Office': 'Jonjo A. Milante',
    'Archive': 'Jonjo A. Milante',
    'Lactation Room': 'Jonjo A. Milante',
    'CED Buildings': 'Dan John B. Natividad',
    'IIT Building': 'Oscar M. Navarra Jr.',
    'CBM Building': 'Joebert R. Oriana',
    'CBM Offices': 'Joebert R. Oriana',
    'CBM Faculty Rooms': 'Joebert R. Oriana',
    'CBM Canteen': 'Joebert R. Oriana',
    'Ang-Chinto Building': 'Joebert R. Oriana',
    'Alumni Building': 'Joebert R. Oriana',
    'Dormitory (Female Wing)': 'Regina P. Pamada',
    'University Canteen': 'Rose J. Retome',
    'Procurement Office': 'Rose J. Retome',
    'BAC Office': 'Rose J. Retome',
    'Internal Audit Unit': 'Rose J. Retome',
    'NSTP Office': 'Rose J. Retome'
  },
    };
  },
  methods: {
    goToDashboard() {
      this.selectedMenu = 'dashboard';
      this.$router.push({ name: 'dashboard' });
      this.showMenu = false;
    },
    goToBinManagement() {
      this.selectedMenu = 'bin';
      this.showMenu = false;
    },
    goToHistory() {
      this.selectedMenu = 'history';
      this.showMenu = false;
      this.$router.push({ name: 'bin_history' });
    },
    goToEdit() {
      this.selectedMenu = 'EditBin';
      this.$router.push({ name: 'EditBin' });
      this.showMenu = false;
    },
    autoSelectPersonnel() {
      // Auto-select personnel based on location
      if (this.newBinLocation && this.locationPersonnelMap[this.newBinLocation]) {
        this.newBinPersonnel = this.locationPersonnelMap[this.newBinLocation];
      }
    },
    openAddModal() {
      this.newBinId = '';
      this.newBinLocation = '';
      this.newBinFloor = 1;
      this.newBinPersonnel = '';
      this.newBinConnected = true;
      this.showAddModal = true;
    },
    addBin() {
      // Allow manual adds even if metadata is incomplete. Log a note for admins.
      if (!this.newBinLocation || !this.newBinPersonnel) {
        // eslint-disable-next-line no-console
        console.info('[addBin] Manual add: metadata incomplete. You can enrich this entry later via Edit Bin.');
      }
      const binData = {
        location: this.newBinLocation,
        floor: this.newBinFloor,
        personnel: this.newBinPersonnel,
        connected: this.newBinConnected
      };
      // eslint-disable-next-line no-console
      console.log('[addBin] Attempting to add bin:', binData);
      try {
        // initialize metadata: connected=false and lastSeen null until device reports
        binData.connected = false;
        binData.lastSeen = null;
        push(dbRef(db, 'bins'), binData).then((ref) => {
          // After push, set the generated key as the bin id so devices/users can reference it
          update(dbRef(db, `bins/${ref.key}`), { id: ref.key }).catch(logDbError);
          // eslint-disable-next-line no-console
          console.log('[addBin] ✓ Bin added successfully with key:', ref.key);
        }).catch((err) => {
          // eslint-disable-next-line no-console
          console.error('[addBin] ✗ Failed to add bin:', err.message, err.code);
          logDbError(err);
        });
      } catch (err) {
        // eslint-disable-next-line no-console
        console.error('[addBin] Exception caught:', err.message);
        logDbError(err);
      }
      this.showAddModal = false;
    },
    openHistory(idx) {
      const bin = this.bins[idx];
      if (!bin) return;
      this.historyBinKey = bin.key;
      this.historyData = null;
      this.showHistoryModal = true;
      // Set up realtime listener for sensorData under this bin
      const ref = dbRef(db, `bins/${bin.key}/sensorData`);
      if (this._historyListenerRef) {
        // remove previous listener
        try { this._historyOff && this._historyOff(); } catch(e) {}
      }
      this._historyListenerRef = ref;
      this._historyListener = (snapshot) => {
        const data = snapshot.val();
        if (!data) {
          this.historyData = [];
          return;
        }
        const arr = Object.entries(data).map(([k, v]) => {
          // Normalize timestamp and tag its type so UI can decide how to present it.
          // Possible timestamp types:
          // - 'ms'      : already in milliseconds since epoch (>= 1e12)
          // - 's'       : seconds since epoch (>= 1e9 and < 1e12) -> converted to ms
          // - 'counter' : small integer probably a device counter or uptime (keep raw)
          const raw = v.timestamp;
          const n = Number(raw);
          let timestamp = null;
          let timestampType = null;
          if (Number.isFinite(n)) {
            if (n >= 1e12) {
              // milliseconds
              timestamp = n;
              timestampType = 'ms';
            } else if (n >= 1e9) {
              // seconds -> convert to milliseconds
              timestamp = n * 1000;
              timestampType = 's';
            } else {
              // small values — likely a device counter/uptime
              timestamp = n;
              timestampType = 'counter';
            }
          }
          return { key: k, ...v, timestamp, timestampType, rawTimestamp: raw };
        });
        arr.sort((a, b) => (b.timestamp || 0) - (a.timestamp || 0));
        this.historyData = arr.slice(0, 50);
      };
      onValue(ref, this._historyListener);
      // store off function for cleanup
      this._historyOff = () => { try { ref && ref.off && ref.off('value', this._historyListener); } catch(e) {} };
    },
    formatSnapshotTime(h) {
      // h is the history entry that may contain timestamp, timestampType, rawTimestamp
      if (!h || (h.timestamp === null || h.timestamp === undefined) ) {
        // If there is a rawTimestamp but not parsed, show it as-is
        if (h && h.rawTimestamp !== undefined && h.rawTimestamp !== null) return String(h.rawTimestamp);
        return 'No timestamp';
      }
      // If timestampType indicates a counter, show a labeled value rather than a date
      if (h.timestampType === 'counter') {
        return `${h.timestamp} (device counter)`;
      }
      try {
        return new Date(h.timestamp).toLocaleString();
      } catch (e) {
        return String(h.rawTimestamp || h.timestamp);
      }
    },
    closeHistory() {
      this.showHistoryModal = false;
      // remove listener
      if (this._historyListenerRef && this._historyListener) {
        try { this._historyOff && this._historyOff(); } catch(e) {}
      }
      this.historyData = null;
      this.historyBinKey = null;
      this._historyListenerRef = null;
      this._historyListener = null;
      this._historyOff = null;
    },
    closeConnectionTest() {
      // method to handle closing test widget if needed
    }
  },
  mounted() {
    const binsRef = dbRef(db, "bins");
    onValue(binsRef, (snapshot) => {
      const data = snapshot.val();
      if (data) {
        const nowSec = Math.floor(Date.now() / 1000);
        this.bins = Object.entries(data).map(([key, value], idx) => {
          let lastSeen = null;
          let connected = false;
          if (value.lastSeen !== undefined && value.lastSeen !== null) {
            lastSeen = Number(value.lastSeen);
            connected = (nowSec - lastSeen) <= 60;
          } else if (value.connected !== undefined) {
            connected = value.connected;
          }

          return {
            key,
            id: value.id || '',
            no: idx + 1,
            location: value.location,
            floor: value.floor !== undefined ? value.floor : '',
            personnel: value.personnel || '',
            lastSeen,
            connected,
          };
        });
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
table {
  border-collapse: collapse;
}
</style>
  
