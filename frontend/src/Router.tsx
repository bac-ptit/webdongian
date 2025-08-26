import { createBrowserRouter } from "react-router-dom";
import FullLayout from "./layouts/FullLayout";
import HomePage from "./pages/HomePage";
import LoginPage from "./pages/LoginPage";
import RegisterPage from "./pages/RegisterPage";
import ProtectedRoute from "./ProtectedRoute";
import DepositPage from "./pages/DepositPage";

const router = createBrowserRouter([
  {
    path: "/",
    element: (
      <ProtectedRoute>
        <FullLayout />
      </ProtectedRoute>
    ),
    children: [
      {
        index: true, // <- dùng cái này để route mặc định
        element: <HomePage />,
      },
      {
        path: "/deposit",
        element: <DepositPage />,
      }
    ],
  },
  {
    path: "/",
    element: null,
    children: [
      {
        path: "/login",
        element: <LoginPage />,
      },
      {
        path: "/register",
        element: <RegisterPage />,
      },
    ],
  },
]);

export default router;
