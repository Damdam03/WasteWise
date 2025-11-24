import { mapState } from 'vuex';

export default {
  computed: {
    ...mapState(['userProfile']),
    isLoggedIn() {
      return this.userProfile !== null;
    }
  },
};