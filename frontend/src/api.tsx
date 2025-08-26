import axios from "axios";
import { apiUrl } from "./config";

const api = axios.create({
  baseURL: apiUrl, // sửa theo API của bạn
  timeout: 5000,
  headers: {
    "Content-Type": "application/json",
  },
});

export default api;