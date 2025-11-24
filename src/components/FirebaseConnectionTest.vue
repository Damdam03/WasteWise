<template>
  <transition
    enter-active-class="transition ease-out duration-300"
    enter-from-class="opacity-0 transform translate-y-4"
    enter-to-class="opacity-100 transform translate-y-0"
    leave-active-class="transition ease-in duration-200"
    leave-from-class="opacity-100 transform translate-y-0"
    leave-to-class="opacity-0 transform translate-y-4"
  >
    <div v-if="!closed" class="fixed bottom-6 right-6 bg-white border border-gray-200 rounded-lg shadow-xl p-5 max-w-sm z-40">
      <div class="flex items-center justify-between mb-4">
        <h3 class="font-bold text-lg text-gray-900">🔧 Connection Test</h3>
        <button 
          @click="closeTest" 
          class="text-gray-400 hover:text-gray-600 transition-colors"
        >
          <svg class="w-6 h-6" fill="currentColor" viewBox="0 0 20 20"><path fill-rule="evenodd" d="M4.293 4.293a1 1 0 011.414 0L10 8.586l4.293-4.293a1 1 0 111.414 1.414L11.414 10l4.293 4.293a1 1 0 01-1.414 1.414L10 11.414l-4.293 4.293a1 1 0 01-1.414-1.414L8.586 10 4.293 5.707a1 1 0 010-1.414z" clip-rule="evenodd"/></svg>
        </button>
      </div>
      
      <button 
        @click="runTest" 
        class="w-full px-4 py-2.5 bg-blue-600 text-white rounded-lg mb-4 hover:bg-blue-700 transition-colors font-medium disabled:opacity-50 disabled:cursor-not-allowed"
        :disabled="testing"
      >
        {{ testing ? '⏳ Testing...' : '▶ Run Test' }}
      </button>

      <div v-if="testResults" class="space-y-3 text-sm">
        <!-- Connected Status -->
        <div class="flex items-center gap-3 p-2 rounded bg-gray-50">
          <span :class="['text-lg', testResults.connected ? 'text-green-600' : 'text-red-600']">
            {{ testResults.connected ? '✓' : '✗' }}
          </span>
          <div>
            <p class="font-semibold text-gray-900">Connected to DB</p>
            <p :class="['text-xs', testResults.connected ? 'text-green-600' : 'text-red-600']">
              {{ testResults.connected ? 'YES - Database is reachable' : 'NO - Cannot connect' }}
            </p>
          </div>
        </div>
        
        <!-- Can Read Status -->
        <div class="flex items-center gap-3 p-2 rounded bg-gray-50">
          <span :class="['text-lg', testResults.canRead ? 'text-green-600' : 'text-red-600']">
            {{ testResults.canRead ? '✓' : '✗' }}
          </span>
          <div>
            <p class="font-semibold text-gray-900">Can Read</p>
            <p :class="['text-xs', testResults.canRead ? 'text-green-600' : 'text-red-600']">
              {{ testResults.canRead ? 'YES - Read access works' : 'NO - Read failed' }}
            </p>
          </div>
        </div>

        <!-- Can Write Status -->
        <div class="flex items-center gap-3 p-2 rounded bg-gray-50">
          <span :class="['text-lg', testResults.canWrite ? 'text-green-600' : 'text-red-600']">
            {{ testResults.canWrite ? '✓' : '✗' }}
          </span>
          <div>
            <p class="font-semibold text-gray-900">Can Write</p>
            <p :class="['text-xs', testResults.canWrite ? 'text-green-600' : 'text-red-600']">
              {{ testResults.canWrite ? 'YES - Write access works' : 'NO - Write failed' }}
            </p>
          </div>
        </div>

        <!-- Error Messages -->
        <div v-if="testResults.errors.length > 0" class="bg-red-50 border border-red-200 p-3 rounded">
          <p class="font-semibold text-red-700 mb-1">⚠️ Errors:</p>
          <ul class="text-red-600 text-xs space-y-1">
            <li v-for="(err, idx) in testResults.errors" :key="idx">• {{ err }}</li>
          </ul>
        </div>

        <!-- Success Message -->
        <div v-if="testResults.connected && testResults.canRead && testResults.canWrite" class="bg-green-50 border border-green-200 p-3 rounded">
          <p class="font-semibold text-green-700">✓ All systems operational!</p>
        </div>
      </div>
    </div>
  </transition>
</template>

<script setup>
import { ref } from 'vue'
import { testFirebaseConnection } from '@/services/firebase'

const testing = ref(false)
const testResults = ref(null)
const closed = ref(false)

const runTest = async () => {
  testing.value = true
  try {
    testResults.value = await testFirebaseConnection()
  } catch (err) {
    // eslint-disable-next-line no-console
    console.error('Test execution error:', err)
    testResults.value = {
      connected: false,
      canRead: false,
      canWrite: false,
      errors: [err.message]
    }
  } finally {
    testing.value = false
  }
}

const closeTest = () => {
  closed.value = true
}

defineEmits(['close'])
</script>

<style scoped>
/* Smooth transitions are handled by Tailwind's transition classes in the template */
</style>
