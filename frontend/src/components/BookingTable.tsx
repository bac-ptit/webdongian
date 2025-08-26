/* eslint-disable @typescript-eslint/no-explicit-any */
import { useEffect, useState } from "react";
import BookingSelectElement, {
  type bookingType,
  type serverType,
  type EntityType,
  type serviceType,
} from "./BookingSelectionElement";
import InputTyping from "./InputTyping";
import Invoice from "./Invoice";
import MenuHeader from "./MenuHeader";
import api from "../api";

export default function BookingTable() {
  const [bookingLists, setBookingLists] = useState<bookingType[]>([]);

  const [selectedBooking, setSelectedBooking] = useState<bookingType>();

  const [selectedServiceList, setSelectedServiceList] = useState<
    serviceType[]
  >([]);

  const [selectedService, setSelectedService] = useState<serviceType>();

  const [selectedServerList, setSelectedServerList] = useState<serverType[]>(
    []
  );

  const [selectedServer, setSelectedServer] = useState<serverType>();

  const [linkOrId, setLinkOrId] = useState<string>("");
  const [quantity, setQuantity] = useState<string>("");

  const [price, setPrice] = useState<string>("0");
  const [priceForInteractions, setPriceForInteractions] = useState<string>("0");

  useEffect(() => {
    api.get("/booking/all").then((response) => {
      console.log(response.data);
      setBookingLists(response.data);
      setSelectedBooking(bookingLists[0]);
      setSelectedServiceList(bookingLists[0].services);
    });
  }, [bookingLists]);

  const handleOrder = () => {
      setSelectedServiceList(bookingLists[0].services);
    // fetch backend
  };

  //   const [selectedTypeServices, setSelectedTypeServices] = useState<string>();\

  //   const typeoptions = serviceOptions.map(item => item.value)

  // để tạm thời cho tới khi viết backend
  return (
    <div
      className="m-4 space-y-4 border border-gray-400 rounded-2xl "
      style={{ width: 700 }}
    >
      <MenuHeader text={"Đặt hàng"} />
      <div className="p-8 space-y-4">
        <BookingSelectElement
          label="Chọn dịch vụ"
          options={bookingLists}
          selected={selectedBooking}
          onChange={(value: EntityType) => {
            console.log(3);
            
            if ("services" in value) {
              setSelectedBooking(value);
              setSelectedServiceList(value.services);
              //reset 
              setSelectedService(undefined);
              setSelectedServer(undefined);
            }
          }}
        />
        <BookingSelectElement
          label="Chọn loại dịch vụ"
          options={selectedServiceList}
          selected={selectedService}
          onChange={(value) => {
            if ("servers" in value) {
              setSelectedService(value);
              setSelectedServerList(value.servers);

              //reset 
              setSelectedServer(undefined);
          }}}
        />
        <BookingSelectElement
          label="Chọn máy chủ"
          options={selectedServerList}
          selected={selectedServer}
          onChange={(value) => {

            setSelectedServer(value as serverType)
          }}
        />
        <InputTyping
          label="Nhập id hoặc link bài viết"
          value={linkOrId}
          onChange={setLinkOrId}
        />
        <InputTyping label="Số lượng" value={quantity} onChange={setQuantity} />
        <Invoice
          price={price}
          priceForInteractions={priceForInteractions}
          onclick={handleOrder}
        />
      </div>
    </div>
  );
}
