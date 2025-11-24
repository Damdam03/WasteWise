import axios from 'axios';

/* POST REQUEST API URL */
const POST_SIGNIN = 'https://af8874b5167344fdbd8e3ef198dbdf52.api.mockbin.io/';
const POST_REGISTRATION = 'https://af8874b5167344fdbd8e3ef198dbdf52.api.mockbin.io/';

/* GET REQUEST API URL */
const GET_PAPERS = 'ADD LATER';

export default {
  signIn: (username, password) => 
    axios.post(`${POST_SIGNIN}`, { username, password }),
  
  register: (username, password, email) => 
    axios.post(`${POST_REGISTRATION}`, { username, password, email }),

  /* Add more API calls as needed */
};
