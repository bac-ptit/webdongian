import { Popover, PopoverButton, PopoverPanel } from "@headlessui/react";
import React from "react";

type BubbleMenuProps = {
  icon: React.ReactNode;
  children: React.ReactNode;
};

const BubbleMenu = ({ icon, children }: BubbleMenuProps) => {
  return (
    <Popover>
      <PopoverButton className="flex w-12 h-12 !rounded-full overflow-hidden !p-0 border-none !bg-transparent ">
        {icon}
      </PopoverButton>
      <PopoverPanel className="absolute z-10 mt-2 right-0 w-48 rounded-lg shadow-xl bg-white border border-gray-200">
        {children}
      </PopoverPanel>
    </Popover>
  );
};

export default BubbleMenu;
