import "./assets/style.css";

import { createApp } from "vue";
import App from "./App.vue";
import apiRequest from "@/services/APIRequest.js";
import store from "@/services/Store";
import { createRouter, createWebHistory } from 'vue-router';

import LandingPage from '@/views/LandingPage.vue';
import EditBin from '@/views/EditBin.vue';
import NotFoundPage from '@/views/NotFoundPage.vue';
import Dashboard from "@/views/Dashboard.vue";
import BinManagement from "@/views/BinManagement.vue";
import BinHistory from "@/views/BinHistory.vue";

const routes = [
  { path: '/', name: 'home', component: LandingPage },
  { path: '/landing', name: 'landing', component: LandingPage },
  {path: '/edit-bin', name: 'EditBin', component: EditBin },
  { path: '/bin_management', name: 'bin_management', component: BinManagement },
  { path: '/bin_history', name: 'bin_history', component: BinHistory },
  { path: '/dashboard', name: 'dashboard', component: Dashboard },
  { path: '/404', name: '404', component: NotFoundPage }, 
];

// Create the router instance
const router = createRouter({
    history: createWebHistory(),
    routes,
});

router.beforeEach((to, from, next) => {
  // Check if the target route exists
  if (router.hasRoute(to.name)) {
    next();
  } else {
    next('/404'); // Redirect to 404 page if the route doesn't exist
  }
  /*
  // Check if the user is logged in
  const isLoggedIn = store.state.userProfile !== null;
  if (to.path === '/' && isLoggedIn) {
    // If the user is logged in and tries to access the landing page, redirect them to their home page
    next('/student'); // or '/faculty' depending on the user type
  } else {
    // Otherwise, allow the navigation
    next();
  } */
});

const app = createApp(App);
app.config.globalProperties.$api = apiRequest;
app.use(router).use(store).mount("#app");
