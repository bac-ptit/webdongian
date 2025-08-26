import { type ReactNode } from "react";

type MenuTableProps = {
  children: ReactNode;
  className?: string;
};

const MenuTable = ({ children, className }: MenuTableProps) => {
  return (
    <div
      className={`m-4 space-y-4 border border-gray-400 rounded-2xl ${className}`}
    >
      {children}
    </div>
  );
};

export default MenuTable;
