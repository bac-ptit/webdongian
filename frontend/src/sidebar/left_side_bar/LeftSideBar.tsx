import { forwardRef } from "react";
import Header from "./Header";
import Menu from "./Menu";

const LeftSideBar = forwardRef<HTMLDivElement>((_, ref) => {
  return (
    <div ref={ref} className="fixed top-0 left-0 h-full w-64 bg-gray-800">
      <Header />
      <Menu />
    </div>
  );
});

export default LeftSideBar;