import { Fragment } from "react";
import {
  Listbox,
  ListboxButton,
  ListboxOption,
  ListboxOptions,
  Transition,
} from "@headlessui/react";
import { CheckIcon, ChevronUpDownIcon } from "@heroicons/react/20/solid";

export type serverType = {
  id: number,
  name: string,
  host: string,
  numberOfDayInEffect: number,
  quntity: number,
  priceForInteraction: string
}

export type serviceType = {
  id: number,
  name: string,
  servers: serverType[],
}

export type bookingType = {
  id: number;
  name: string
  services: serviceType[];
}

export type EntityType = bookingType | serviceType | serverType;



interface Props {
  options: EntityType[];
  selected?: EntityType;
  onChange: (option: EntityType) => void;
  label?: string;
}

export default function BookingSelectElement({
  options,
  selected,
  onChange,
  label = "Chọn dịch vụ",
}: Props) {
  return (
    <div className="w-full">
      <label className="block text-sm font-medium text-gray-700 mb-1 ">
        {label}
      </label>

      <Listbox value={selected || null} onChange={onChange}>
        <div className="relative mt-4">
          <ListboxButton className="relative w-full cursor-default rounded border border-blue-400 !bg-white py-2 pl-3 pr-10 text-left shadow-sm focus:outline-none focus:ring-2 focus:ring-blue-500 sm:text-sm">
            <span className="h-5 w-full flex items-center gap-2">
              {/* {selected && selected.iconUrl && (
                <img
                  src={selected.iconUrl}
                  alt=""
                  className="h-5 w-5 rounded-full"
                />
              )} */}
              <span className="text-green-600 font-semibold w-full">
                {selected && selected.name}
              </span>
            </span>
            <span className="pointer-events-none absolute inset-y-0 right-0 flex items-center pr-2">
              <ChevronUpDownIcon className="h-5 w-5 text-gray-400" />
            </span>
          </ListboxButton>

          <Transition
            as={Fragment}
            leave="transition ease-in duration-100"
            leaveFrom="opacity-100"
            leaveTo="opacity-0"
          >
            <ListboxOptions className="absolute z-10 mt-1 max-h-60 w-full overflow-auto rounded bg-white py-1 text-base shadow-lg ring-1 ring-black ring-opacity-5 focus:outline-none sm:text-sm">
              {options.map((option) => (
                <ListboxOption
                  key={option.name}
                  className={({ active }) =>
                    `relative cursor-default select-none py-2 pl-10 pr-4 ${
                      active ? "bg-blue-100 text-blue-900" : "text-gray-900"
                    }`
                  }
                  value={option}
                >
                  {({ selected: isSelected }) => (
                    <>
                      <span className="flex items-center gap-2">
                        {/* {option.iconUrl && (
                          <img
                            src={option.iconUrl}
                            alt=""
                            className="h-5 w-5 rounded-full"
                          />
                        )} */}
                        <span
                          className={`block truncate ${
                            isSelected ? "font-semibold" : ""
                          }`}
                        >
                          {option.name}
                        </span>
                      </span>
                      {isSelected ? (
                        <span className="absolute inset-y-0 left-0 flex items-center pl-3 text-blue-600">
                          <CheckIcon className="h-5 w-5" />
                        </span>
                      ) : null}
                    </>
                  )}
                </ListboxOption>
              ))}
            </ListboxOptions>
          </Transition>
        </div>
      </Listbox>
    </div>
  );
}
