import React, { useState } from "react";
import Authform from "../components/Authform";
import InputTyping from "../components/InputTyping";
import { Link } from "react-router-dom";

const RegisterPage = () => {
  const [phoneNumber, setPhoneNumber] = useState<string>("");
  const [email, setEmail] = useState<string>("");
  const [password, setPassword] = useState<string>("");

  

  const handleRegister = () => {};

  return (
    <div className="flex items-center justify-center min-h-screen flex-col">
      <Authform
        header="Đăng ký"
        onClick={handleRegister}
        typeButton="Đăng ký"
      >
        <InputTyping
          label="Số điện thoại"
          placeholder="10 chữ số"
          name="phoneNumber"
          onChange={setPhoneNumber}
          value={phoneNumber}
        />
        <InputTyping
          label="Email"
          placeholder="...@gmail.com"
          name="email"
          onChange={setEmail}
          value={email}
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
      <Link to="/login" className="text-black cursor-pointer">
        Đã có tài khoản?
      </Link>
    </div>
  );
};

export default RegisterPage;
