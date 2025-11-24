import { createStore } from 'vuex';

export default createStore({
  state: {
    userProfile: null,
  },
  mutations: {
    setUserProfile(state, userProfile) {
      state.userProfile = userProfile;
    },
  },
});
