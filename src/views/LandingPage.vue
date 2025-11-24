<template>
  <div class="relative min-h-screen flex items-center justify-center bg-cover bg-center" style="background-image: url('/src/assets/images/bg-campus.jpg');">
    <!-- Overlay -->
    <div class="absolute inset-0 bg-black bg-opacity-60"></div>

    <!-- Logos -->
    <div class="absolute top-6 left-6">
  <img src="/src/assets/images/logo-psu.png" alt="PSU Logo" class="w-28 h-28 cursor-pointer" @click="goToDashboard" />
    </div>
    <div class="absolute top-6 right-6 flex flex-col items-end">
      <img src="/src/assets/images/logo-ph.png" alt="Bagong Pilipinas Logo" class="w-28 h-28" />
    </div>

    <!-- Centered Content -->
    <div class="relative z-10 flex flex-col items-center justify-center">
      <h1 class="text-3xl md:text-4xl lg:text-5xl font-bold text-center text-white drop-shadow-lg mb-2">PARTIDO STATE UNIVERSITY<br />GENERAL SERVICES UNIT</h1>
  <button @click="goToDashboard" class="mt-8 px-8 py-3 bg-black text-white rounded-lg text-xl font-semibold shadow-lg hover:bg-gray-800 transition">Go To Dashboard</button>
    </div>
  </div>
</template>

<script>
export default {
  name: "LandingPage",
  methods: {
    goToDashboard() {
      this.$router.push({ name: 'dashboard' });
    },
  },
};
</script>

<style scoped>
</style>
