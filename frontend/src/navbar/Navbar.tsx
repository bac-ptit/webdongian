import { forwardRef } from "react";
import { useAuth } from "../hook/AuthContext";
import BubbleMenu from "../components/BubbleMenu";
import { useNavigate } from "react-router-dom";
import api from "../api";

type NavbarProps = { children?: React.ReactNode };

const Navbar = forwardRef<HTMLDivElement, NavbarProps>(({ children }, ref) => {
  const {user, reset } = useAuth();

  const navigate = useNavigate();

  const handleSignOut = () => {
    api.post("/auth/logout",undefined, {
      withCredentials: true,
    }).then(() => {
      console.log("Sign out successful");
      reset();
      navigate("/login");
    }).catch((error) => {
      console.error("Sign out failed", error);
    })
  }

  return (
    <div
      ref={ref}
      className="p-2 pr-10 h-16 w-full border-b border-gray-200 flex justify-end bg-white align-center items-center space-x-3"
    >
      <div className="text-black font-semibold ml-12">{user?.balance}</div>
      <BubbleMenu
        icon={
          <img
            src="/src/assets/img/profile.jpg"
            alt="coin"
            className="w-full h-full"
          />
        }
      >
        <div className="flex flex-col w-full">
          <div onClick={handleSignOut} className="text-black cursor-pointer flex h-9 justify-center items-center">
            Đăng xuất
          </div>
        </div>
      </BubbleMenu>
    </div>
  );
});

export default Navbar;
