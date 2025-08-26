import React, { type ReactNode } from "react";

type AuthformProps = {
  header: string;
  children: ReactNode;
  onClick: () => void;
  typeButton: string;
};

const Authform = ({ header, children, onClick, typeButton }: AuthformProps) => {
  const handleSubmit = (event: React.FormEvent<HTMLFormElement>) => {
    event.preventDefault();
    onClick();
  }
  return (
    <form onSubmit={handleSubmit}  className="text-black flex flex-col p-6 w-3/6">
      <span className="text-5xl text-center font-semibold">{header}</span>
      <div className="space-y-4 w-full">{children}</div>
      <button
        className="!bg-black flex items-center justify-center text-white"
        type="submit"
      >
        {typeButton}
      </button>
    </form>
  );
};

export default Authform;
