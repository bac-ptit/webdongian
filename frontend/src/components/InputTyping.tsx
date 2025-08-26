import React from "react";

interface InputTypingProps {
  label: string;
  value: string;
  onChange: (newValue: string) => void;
  placeholder?: string;
  name?: string; // để phân biệt nếu cần
  onlyNumber?: boolean; // nếu chỉ cho phép nhập số
  icon?: React.ReactNode; // nếu cần hiển thị icon
  type?: string;
}

const InputTyping = ({
  label,
  value,
  onChange,
  placeholder = "",
  name,
  icon,
  type = "text",
}: InputTypingProps) => {
  return (
    <div className="mb-4">
      <label
        htmlFor={name}
        className="block text-sm font-medium text-gray-700 mb-1"
      >
        {label}
      </label>
      <div>
        {icon && <div className="main-background">{icon}</div>}
        <input
          id={name}
          name={name}
          type={type}
          className="text-black w-full border border-gray-600 rounded px-3 py-2  focus:outline-none focus:ring focus:ring-blue-400"
          value={value}
          onChange={(e) => onChange(e.target.value)}
          placeholder={placeholder}
        />
      </div>
    </div>
  );
};

export default InputTyping;
