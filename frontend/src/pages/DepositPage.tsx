import MenuTable from "../components/MenuTable";
import MenuHeader from "../components/MenuHeader";
import QRBank from "../components/QRBank";

const DepositPage = () => {
  return (
    <MenuTable className="mr-16">
      <MenuHeader text={"Nạp tiền"}/>
      <div className="w-11/12"> 
        <QRBank className="w-9/12" />
      </div>
    </MenuTable>
  );
};

export default DepositPage;
