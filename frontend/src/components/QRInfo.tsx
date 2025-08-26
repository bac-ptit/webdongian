export type QRInfoProps = {
  bank: string;
  accountNumber: string;
  accountName?: string;
  content?: string;
  note?: string;
};

type QRInfoPropsWithClass = QRInfoProps & {
  className?: string;
};

const QRInfo = ({
  qrInfo,
  className,
}: {
  qrInfo: QRInfoPropsWithClass;
  className?: string;
}) => {
  return (
    <div className={`text-black space-y-4 ${className}`}>
      <div className="font-semibold">{`Ngân hàng: ${qrInfo.bank}`}</div>
      <div className="font-semibold">{`Số tài khoản: ${qrInfo.accountNumber}`}</div>
      {qrInfo.accountName && (
        <div className="font-semibold">{`Tên tài khoản: ${qrInfo.accountName}`}</div>
      )}
      {qrInfo.content && (
        <div className="font-semibold">{`Nội dung: ${qrInfo.content}`}</div>
      )}
      {qrInfo.note && <div>{qrInfo.note}</div>}
    </div>
  );
};

export default QRInfo;
