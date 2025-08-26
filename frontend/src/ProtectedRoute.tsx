import { Navigate } from "react-router-dom";
import { useAuth } from "./hook/AuthContext"; // hoặc đúng path bạn dùng
import type { JSX } from "react";

interface Props {
  children: JSX.Element;
}

export default function ProtectedRoute({ children }: Props) {

  return children
  const { isAuthenticated, loading } = useAuth();

  if (loading) {
    // hoặc bạn có thể show spinner/blank page
    return <div>Loading...</div>;
  }

  if (isAuthenticated !== true) {
    return <Navigate to="/login" replace />;
  }

  return children;
}
