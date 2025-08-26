import MenuTable from "./MenuTable";
import QRInfo, { type QRInfoProps } from "./QRInfo";

const bank: QRInfoProps = {
  bank: "MB",
  accountNumber: "0326708373",
  content: "chuyen tien",
  note: "Nạp tối thiểu 2.000đ",
};

type QRBankProps = {
  className?: string;
};

const QRBank = ({ className }: QRBankProps) => {
  return (
    <MenuTable
      className={`p-4 w-full flex flex-row align-center space-x-4 ${className}`}
    >
      <img src="/src/assets/qr/QRPay.jpg" alt="" className="w-9/12 max-w-md rounded-3xl" />
      <QRInfo className="mt-2"  qrInfo={bank} />
    </MenuTable>
  );
};

export default QRBank;
