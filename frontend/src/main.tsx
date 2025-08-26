import "./index.css";
import ReactDOM from "react-dom/client";
import React from "react";
import { RouterProvider } from "react-router-dom";
import router from "./Router.tsx";
import { AuthProvider } from "./hook/AuthContext.tsx";

ReactDOM.createRoot(document.getElementById("root")!).render(
  <React.StrictMode>
    <AuthProvider>
      <RouterProvider router={router} />
    </AuthProvider>
  </React.StrictMode>
);
