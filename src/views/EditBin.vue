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

    <!-- Back Button -->
    <div class="px-6 mt-6">
      <button 
        @click="goToBinManagement"
        class="flex items-center px-4 py-2.5 bg-gray-50 border border-gray-300 rounded-lg hover:bg-gray-100 hover:border-gray-400 transition-all duration-200 text-gray-700 font-semibold shadow-sm hover:shadow-md"
      >
        <svg class="w-5 h-5 mr-2" fill="none" stroke="currentColor" stroke-width="2" viewBox="0 0 24 24"><path d="M15 19l-7-7 7-7" stroke="currentColor"/></svg>
        Back to Bin Management
      </button>
    </div>
    <!-- Table -->
    <div class="flex justify-center mt-8 px-6 pb-8">
      <div class="w-full max-w-3xl overflow-visible">
        <table class="w-full border-collapse bg-white rounded-lg shadow-md">
          <thead>
            <tr class="bg-gradient-to-r from-purple-600 to-purple-700 text-white">
              <th class="px-4 py-3 text-left font-semibold">Bin No.</th>
              <th class="px-4 py-3 text-left font-semibold">Bin Location</th>
              <th class="px-4 py-3 text-left font-semibold">Floor</th>
              <th class="px-4 py-3 text-left font-semibold">Personnel</th>
              <th class="px-4 py-3 text-left font-semibold">Bin Connection</th>
              <th class="px-4 py-3 text-center font-semibold">Actions</th>
            </tr>
          </thead>
          <tbody>
            <tr v-for="(bin, idx) in bins" :key="bin.key" :class="idx % 2 === 0 ? 'bg-white' : 'bg-gray-50'" class="border-b border-gray-200 hover:bg-purple-50 transition-colors duration-200">
              <td class="px-4 py-3 font-semibold text-gray-900">{{ idx + 1 }}</td>
              <td class="px-4 py-3 font-semibold text-gray-800">{{ bin.location }}</td>
              <td class="px-4 py-3 text-gray-700">{{ bin.floor !== undefined && bin.floor !== null ? bin.floor : '-' }}</td>
              <td class="px-4 py-3 text-gray-700">{{ bin.personnel || '-' }}</td>
              <td class="px-4 py-3">
                <div class="flex items-center space-x-2">
                  <span :class="['font-semibold', bin.connected ? 'text-green-700' : 'text-red-700']">{{ bin.connected ? 'Connected' : 'Disconnected' }}</span>
                  <span :class="['inline-block w-3 h-3 rounded-full', bin.connected ? 'bg-green-500' : 'bg-red-500']"></span>
                </div>
              </td>
              <td class="px-4 py-3 text-center">
                <div class="relative inline-block">
                  <button @click="toggleDropdown(idx)" class="p-1 hover:bg-gray-300 rounded-full transition-colors duration-200">
                    <svg class="w-5 h-5 text-gray-600" fill="currentColor" viewBox="0 0 20 20"><circle cx="4" cy="10" r="2"/><circle cx="10" cy="10" r="2"/><circle cx="16" cy="10" r="2"/></svg>
                  </button>
                  <transition
                    enter-active-class="transition ease-out duration-100"
                    enter-from-class="opacity-0 transform scale-95"
                    enter-to-class="opacity-100 transform scale-100"
                    leave-active-class="transition ease-in duration-75"
                    leave-from-class="opacity-100 transform scale-100"
                    leave-to-class="opacity-0 transform scale-95"
                  >
                    <div v-if="dropdownIndex === idx" class="absolute right-0 top-full mt-1 w-48 bg-white border border-gray-200 rounded-lg shadow-xl z-50 min-w-max">
                      <button class="block w-full text-left px-4 py-3 hover:bg-gray-100 transition-colors duration-200 font-medium" @click="openEditModal(idx)">✏️ Edit Bin</button>
                      <div class="border-t border-gray-100"></div>
                      <button class="block w-full text-left px-4 py-3 hover:bg-red-50 text-red-600 transition-colors duration-200 font-medium" @click="openDeleteModal(idx)">🗑️ Delete Bin</button>
                    </div>
                  </transition>
                </div>
              </td>
            </tr>
          </tbody>
        </table>
      </div>
    </div>

    <!-- Edit Bin Modal -->
    <div v-if="showEditModal" class="fixed inset-0 bg-black bg-opacity-40 flex items-center justify-center z-50">
      <div class="bg-white p-6 rounded shadow-lg w-80">
        <h2 class="text-lg font-bold mb-4">Edit Bin</h2>
        <label class="text-sm font-medium">Location</label>
        <select v-model="editLocation" @change="autoSelectPersonnelEdit" class="border p-2 w-full mb-2">
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
        <input v-model.number="editFloor" type="number" min="0" class="border p-2 w-full mb-2" placeholder="Enter floor number" />
        <label class="text-sm font-medium">Assigned Personnel</label>
        <select v-model="editPersonnel" class="border p-2 w-full mb-4">
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
        <div class="flex justify-end gap-2">
          <button @click="showEditModal = false" class="px-3 py-1 border rounded">Cancel</button>
          <button @click="saveEdit" class="px-3 py-1 bg-blue-600 text-white rounded">Save</button>
        </div>
      </div>
    </div>

    <!-- Delete Bin Modal -->
    <div v-if="showDeleteModal" class="fixed inset-0 bg-black bg-opacity-40 flex items-center justify-center z-50">
      <div class="bg-white p-6 rounded shadow-lg w-80">
        <h2 class="text-lg font-bold mb-4 text-red-600">Delete Bin</h2>
        <p class="mb-4">Are you sure you want to delete this bin?</p>
        <div class="flex justify-end gap-2">
          <button @click="showDeleteModal = false" class="px-3 py-1 border rounded">Cancel</button>
          <button @click="deleteBin" class="px-3 py-1 bg-red-600 text-white rounded">Delete</button>
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
      <div v-if="showHelp" class="fixed inset-0 bg-black/40 backdrop-blur-sm flex items-center justify-center z-50">
        <div class="bg-white rounded-xl shadow-2xl w-full max-w-2xl mx-4 max-h-96 overflow-y-auto">
          <div class="sticky top-0 bg-gradient-to-r from-purple-600 to-purple-700 text-white px-6 py-4 flex items-center justify-between">
            <h2 class="text-xl font-bold">📚 Edit Bin Guide</h2>
            <button @click="showHelp = false" class="text-2xl hover:text-purple-100">✕</button>
          </div>
          
          <div class="px-6 py-6 space-y-6">
            <!-- Overview Section -->
            <div class="border-l-4 border-purple-500 pl-4">
              <h3 class="font-bold text-lg text-gray-900 mb-2">📋 Edit Bin Overview</h3>
              <p class="text-gray-700 mb-2">This page allows you to manage and update all bin details and metadata:</p>
              <ul class="space-y-1 text-sm text-gray-600 list-disc list-inside">
                <li><strong>Bin No.</strong> - Sequential numbering for easy reference</li>
                <li><strong>Bin Location</strong> - Campus location (46+ locations available)</li>
                <li><strong>Floor</strong> - Building floor number where bin is located</li>
                <li><strong>Personnel</strong> - Utility staff member assigned to maintain this bin</li>
                <li><strong>Bin Connection</strong> - Real-time device connectivity status</li>
              </ul>
            </div>

            <!-- How to Edit Section -->
            <div class="border-l-4 border-purple-500 pl-4">
              <h3 class="font-bold text-lg text-gray-900 mb-2">✏️ How to Edit a Bin</h3>
              <ol class="space-y-2 text-sm text-gray-600 list-decimal list-inside">
                <li>Find the bin you want to edit in the table</li>
                <li>Click the <strong>3-dot menu button</strong> (⋯) in the Actions column</li>
                <li>Select <strong>"Edit Bin"</strong> from the dropdown</li>
                <li>Modify the desired fields:
                  <ul class="list-disc list-inside ml-4 mt-1">
                    <li><strong>Location</strong> - Select from all 46+ campus locations</li>
                    <li><strong>Personnel auto-selects!</strong> When you change location, the assigned personnel updates automatically</li>
                    <li><strong>Floor</strong> - Enter the floor number (0 for ground floor)</li>
                    <li>You can override the auto-selected personnel if needed</li>
                  </ul>
                </li>
                <li>Click <strong>"Save"</strong> to save all changes</li>
              </ol>
            </div>

            <!-- Auto-Selection Feature -->
            <div class="border-l-4 border-indigo-500 pl-4">
              <h3 class="font-bold text-lg text-gray-900 mb-2">🔄 Smart Personnel Auto-Selection</h3>
              <p class="text-gray-700 mb-2"><strong>Change location and see personnel update instantly!</strong></p>
              <ul class="space-y-1 text-sm text-gray-600 list-disc list-inside">
                <li>Each campus building/area has one assigned utility personnel</li>
                <li>When you select a location, the correct personnel is <strong>automatically populated</strong></li>
                <li>One personnel can manage multiple locations (e.g., Albert B. Claveria manages 5 areas)</li>
                <li>All 20 utility personnel and their location assignments are pre-configured</li>
                <li>You can still manually override if needed</li>
              </ul>
              <p class="text-xs text-gray-500 mt-2">💡 This feature saves time and ensures correct staff assignments!</p>
            </div>

            <!-- How to Delete Section -->
            <div class="border-l-4 border-red-500 pl-4">
              <h3 class="font-bold text-lg text-gray-900 mb-2">🗑️ How to Delete a Bin</h3>
              <ol class="space-y-1 text-sm text-gray-600 list-decimal list-inside">
                <li>Click the <strong>3-dot menu button</strong> (⋯) on the bin row</li>
                <li>Select <strong>"Delete Bin"</strong> from the dropdown</li>
                <li>Confirm the deletion when prompted</li>
              </ol>
              <p class="text-sm text-red-600 font-semibold mt-2">⚠️ Warning: Deletion cannot be undone!</p>
            </div>

            <!-- Tips Section -->
            <div class="bg-purple-50 border border-purple-200 rounded-lg p-4">
              <h3 class="font-bold text-gray-900 mb-2">💡 Pro Tips</h3>
              <ul class="space-y-1 text-sm text-gray-700 list-disc list-inside">
                <li><strong>Trust auto-selection:</strong> The system knows which personnel is assigned to each location</li>
                <li><strong>Update device-created bins:</strong> When devices create bins, add location + floor immediately</li>
                <li><strong>Keep locations consistent:</strong> Use exact location names from the dropdown</li>
                <li><strong>Monitor connections:</strong> Regularly check for disconnected devices</li>
                <li><strong>Accuracy matters:</strong> Correct floor numbers help maintenance staff locate bins quickly</li>
              </ul>
            </div>
          </div>

          <div class="bg-gray-50 px-6 py-4 border-t border-gray-200 flex justify-end">
            <button @click="showHelp = false" class="px-6 py-2 bg-purple-600 text-white rounded-lg hover:bg-purple-700 transition-colors font-medium">
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
import { ref as dbRef, onValue, update, remove } from 'firebase/database';

export default {
  name: "EditBin",
  data() {
    return {
      showMenu: false,
      selectedMenu: 'bin',
      bins: [],
  showEditModal: false,
  showDeleteModal: false,
  editLocation: '',
    editFloor: '',
    editPersonnel: '',
      editIndex: null,
      dropdownIndex: null,
      deleteIndex: null,
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
      this.$router.push({ name: 'bin_management' });
      this.showMenu = false;
    },
    goToHistory() {
      this.selectedMenu = 'history';
      this.showMenu = false;
      this.$router.push({ name: 'bin_history' });
    },
    autoSelectPersonnelEdit() {
      // Auto-select personnel based on location
      if (this.editLocation && this.locationPersonnelMap[this.editLocation]) {
        this.editPersonnel = this.locationPersonnelMap[this.editLocation];
      }
    },
    toggleDropdown(idx) {
      this.dropdownIndex = this.dropdownIndex === idx ? null : idx;
    },
    openEditModal(idx) {
      this.editIndex = idx;
      this.editLocation = this.bins[idx].location;
      this.editFloor = this.bins[idx].floor !== undefined ? this.bins[idx].floor : '';
      this.editPersonnel = this.bins[idx].personnel || '';
      this.showEditModal = true;
      this.dropdownIndex = null;
    },
    saveEdit() {
      if (this.editIndex === null) return;
      const binKey = this.bins[this.editIndex].key;
      try {
        update(dbRef(db, `bins/${binKey}`), {
          location: this.editLocation,
          floor: this.editFloor === '' ? null : Number(this.editFloor),
          personnel: this.editPersonnel || null
        }).catch(logDbError);
      } catch (err) {
        logDbError(err);
      }
      this.showEditModal = false;
    },
    openDeleteModal(idx) {
      this.deleteIndex = idx;
      this.showDeleteModal = true;
      this.dropdownIndex = null;
    },
    deleteBin() {
      if (this.deleteIndex === null) return;
      const binKey = this.bins[this.deleteIndex].key;
      try {
        remove(dbRef(db, `bins/${binKey}`)).catch(logDbError);
      } catch (err) {
        logDbError(err);
      }
      this.showDeleteModal = false;
    },
  },
  mounted() {
    const binsRef = dbRef(db, 'bins');
    const nowSec = Math.floor(Date.now() / 1000);
    onValue(binsRef, (snapshot) => {
      const data = snapshot.val();
      if (data) {
        this.bins = Object.entries(data).map(([key, value]) => {
          const lastSeen = value.lastSeen || 0;
          const connected = nowSec - lastSeen <= 60;
          return {
            key,
            location: value.location || '-',
            floor: value.floor !== undefined ? value.floor : null,
            personnel: value.personnel || null,
            connected: connected,
          };
        });
      } else {
        this.bins = [];
      }
    }, (err) => {
      // capture listener errors
      logDbError(err);
    });
  },
};
</script>

<style scoped>

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
