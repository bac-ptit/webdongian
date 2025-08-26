import React from "react";

type MenuSideBarItemProps = {
  icon: React.ReactNode;
  content: string;
  className?: string;
};

const MenuSideBarItem = ({
  icon,
  content,
  className,
}: MenuSideBarItemProps) => {
  const baseClass =
    "select-none py-3 px-4 group flex items-center space-x-3 cursor-pointer hover:bg-gray-600 transition-colors duration-200 rounded-lg";
  const combinedClass = `${className ?? "main-text"} ${baseClass}`;

  return (
    <div>
      <div className={combinedClass}>
        <div className="text-white/60 group-hover:text-white transition-colors">
          {icon}
        </div>
        <span className="text-white/80 group-hover:text-white font-semibold">
          {content}
        </span>
      </div>
    </div>
  );
};

export default MenuSideBarItem;
