import { createContext, useContext, useEffect, useState } from "react";
import api from "../api";

type ProfileProps = {
  phoneNumber: string;
  email: string;
  balance: string;
  registerDate: string;
};

interface AuthContextType {
  user: ProfileProps | null;
  isAuthenticated: boolean;
  loading: boolean;
  refetch: () => void;
  reset: () => void;
}

const AuthContext = createContext<AuthContextType | undefined>(undefined);

export const AuthProvider = ({ children }: { children: React.ReactNode }) => {
  const [user, setUser] = useState<ProfileProps | null>(null);
  const [isAuthenticated, setIsAuthenticated] = useState(false);
  const [loading, setLoading] = useState(true);

  const fetchUser = async () => {
    try {
      setLoading(true);
      const response = await api.get<ProfileProps>("/client/profile", {
        withCredentials: true,
      });
      console.log(response.data);

      setUser(response.data);
      setIsAuthenticated(true);
    } catch (error) {
      setUser(null);
      setIsAuthenticated(false);
    } finally {
      setLoading(false);
    }
  };

  const reset = () => {
    setUser(null);
    setIsAuthenticated(false);
  }

  useEffect(() => {
    fetchUser(); // gọi một lần khi app load
  }, []);

  return (
    <AuthContext.Provider
      value={{ user, isAuthenticated, loading, refetch: fetchUser, reset: reset }}
    >
      {children}
    </AuthContext.Provider>
  );
};

export const useAuth = (): AuthContextType => {
  const context = useContext(AuthContext);
  if (!context) {
    throw new Error("useAuth must be used within an AuthProvider");
  }
  return context;
};
