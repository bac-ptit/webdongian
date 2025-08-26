import { useEffect, useState } from "react";
import Authform from "../components/Authform";
import InputTyping from "../components/InputTyping";
import { Link, useNavigate } from "react-router-dom";
import api from "../api";
import { toast, ToastContainer } from "react-toastify";
import { useAuth } from "../hook/AuthContext";

const LoginPage = () => {
  const [username, setUsername] = useState<string>("");
  const [password, setPassword] = useState<string>("");

  const navigate = useNavigate();
  const auth = useAuth();

  useEffect(() => {
    if (auth.isAuthenticated === true) {
      navigate("/");
    }
  }, [auth.isAuthenticated, navigate]);

  const handleLogin = () => {
    api
      .post(
        "/auth/login",
        {
          username: username,
          password: password,
        },
        { withCredentials: true }
      )
      .then((response) => {
        console.log(response + "ok  ");
        auth.refetch();
        navigate("/");
      })
      .catch((error) => {
        console.log(error);
        const message =
          error.response?.data?.error || // dùng .error vì backend trả lỗi ở đây
          error.message ||
          "Đã xảy ra lỗi không xác định.";

        toast.error(message);
      });
  };

  return (
    <>
      <ToastContainer
        position="top-right"
        autoClose={5000}
        newestOnTop={true}
        closeOnClick={true}
        hideProgressBar={true}
        pauseOnHover={true}
        rtl={true}
        limit={3}
      />

      <div className="flex items-center justify-center min-h-screen flex-col">
        <Authform
          header="Đăng nhập"
          onClick={handleLogin}
          typeButton="Đăng nhập"
        >
          <InputTyping
            label="Tên đăng nhập"
            placeholder="Email hoặc số điện thoại"
            name="username"
            onChange={setUsername}
            value={username}
          />
          <InputTyping
            label="Mật khẩu"
            placeholder="Nhập mật khẩu"
            name="password"
            type="password"
            onChange={setPassword}
            value={password}
          />
        </Authform>
        <Link to="/register" className="text-black cursor-pointer">
          Chưa có tài khoản?
        </Link>
      </div>
    </>
  );
};

export default LoginPage;
