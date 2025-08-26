import { useRef, useEffect, useState } from "react";
import { Outlet } from "react-router-dom";
import LeftSideBar from "../sidebar/left_side_bar/LeftSideBar";
import Navbar from "../navbar/Navbar";
import api from "../api";

type ProfileProps = {
  phoneNumber: string;
  email: string;
  balance: string;
  registerDate: string

}

const FullLayout = () => {
  const sidebarRef = useRef<HTMLDivElement>(null);
  const [sidebarWidth, setSidebarWidth] = useState(0);

  const [navbarWidth, setNavbarWidth] = useState(0);
  const navbarRef = useRef<HTMLDivElement>(null);

  const [profile, setProfile] = useState<ProfileProps>()

  const updateProfile = () => {
    const token = localStorage.getItem("accessToken");
    api.get("/client/profile", {
      headers: {
        Authorization: `Bearer ${token}`,
        
      },
    })
  }
  

  useEffect(() => {
    if (sidebarRef.current) {
      setSidebarWidth(sidebarRef.current.offsetWidth);
    }

    // Nếu sidebar có thể resize thì nghe luôn resize event
    const handleResize = () => {
      if (sidebarRef.current) {
        setSidebarWidth(sidebarRef.current.offsetWidth);
      }
    };

    if (navbarRef.current) {
      setNavbarWidth(navbarRef.current.offsetHeight);
    }

    window.addEventListener("resize", handleResize);
    return () => window.removeEventListener("resize", handleResize);

    // get profile from localStorage

  }, []);

  return (
    <div className="flex min-h-screen relative w-full">
      <div className="hidden md:flex fixed top-0 left-0 h-screen z-50">
        <LeftSideBar ref={sidebarRef} />
      </div>
      <div
        className="flex flex-col w-full bg-white min-h-screen"
        style={{ marginLeft: sidebarWidth }}
      >
        <div className="fixed top-0 z-50" style={{
          left: sidebarWidth,
          right: 0
        }}>
          <Navbar ref={navbarRef} />
        </div>
        <div
          className="flex-1 px-4 py-6"
          style={{ paddingTop: navbarWidth }}
        >
          <Outlet />
        </div>
      </div>
    </div>
  );
};

export default FullLayout;
