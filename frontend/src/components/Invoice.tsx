type InvoiceProps = {
  price: string;
  priceForInteractions: string;
  onclick: () => void;
};

const Invoice = ({ price, priceForInteractions, onclick }: InvoiceProps) => {
  return (
    <div className="flex flex-col items-center justify-center main-background border border-gray-300 rounded-lg shadow-lg w-full">
      <span className="main-text py-4 px-2 h-10 space-y-4 w-full flex justify-center items-center border border-gray-600">
        Chi tiết đơn hàng 
      </span>
      <div className="main-text p-4 flex flex-col items-center justify-center space-y-4">
        <span className="font-bold text-5xl">{price}</span>
        <span>{`Bạn đang buff tương tác với giá ${priceForInteractions}/1 tương tác`}</span>
      </div>
      <div className="py-4 px-2">
        <button
          className="!bg-purple-500 w-full flex items-center justify-center text-white"
          onClick={onclick}
        >
          <span className="text-lg font-semibold">Đặt hàng</span>
        </button>
      </div>
    </div>
  );
};

export default Invoice;
