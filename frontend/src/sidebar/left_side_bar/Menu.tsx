import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import MenuSideBarItem from "../../components/MenuSideBarItem";
import {
  faBarsStaggered,
  faEarthAsia,
  faMagnifyingGlass,
  faPenNib,
  faRightToBracket,
  faUser,
  faUserPlus,
} from "@fortawesome/free-solid-svg-icons";
import { faScrewdriverWrench } from "@fortawesome/free-solid-svg-icons";
import { faFacebook } from "@fortawesome/free-brands-svg-icons";
import { useState } from "react";
import { Link } from "react-router-dom";

const Menu = () => {
  const [open, setOpen] = useState(false);

  return (
    <div className="p-2">
      <Link to="/">
        <MenuSideBarItem
          icon={<FontAwesomeIcon icon={faBarsStaggered} />}
          content="Đặt mua"
        />
      </Link>

      <Link to="/deposit">
        <MenuSideBarItem
          icon={<FontAwesomeIcon icon={faBarsStaggered} />}
          content="Nạp tiền"
        />
      </Link>
      <div onClick={() => setOpen(!open)}>
        <MenuSideBarItem
          icon={<FontAwesomeIcon icon={faScrewdriverWrench} />}
          content="Tiện ích hỗ trợ"
        />
        <div
          className="overflow-hidden transition-all duration-300"
          style={{ maxHeight: open ? "1000px" : "0px" }}
        >
          <div className="ml-3">
            <a target="_blank" href="https://dongvanfb.net/check_live_uid/">
              <MenuSideBarItem
                icon={<FontAwesomeIcon icon={faMagnifyingGlass} />}
                content="Check UID Live"
                className="sub-text"
              />
            </a>
            <a target="_blank" href="https://dongvanfb.net/get2fa/">
              <MenuSideBarItem
                icon={<FontAwesomeIcon icon={faFacebook} />}
                content="Lấy mã 2FA Facebook"
                className="sub-text"
              />
            </a>
            <a
              target="_blank"
              href="https://toolquangcao.com/convert-uid-facebook"
            >
              <MenuSideBarItem
                icon={<FontAwesomeIcon icon={faUser} />}
                content="Lấy UID Facebook"
                className="sub-text"
              />
            </a>
            <a target="_blank" href="https://toolquangcao.com/tool-text">
              <MenuSideBarItem
                icon={<FontAwesomeIcon icon={faPenNib} />}
                content="Tool edit text"
                className="sub-text"
              />
            </a>
            <a
              target="_blank"
              href="https://toolquangcao.com/check-han-ten-mien"
            >
              <MenuSideBarItem
                icon={<FontAwesomeIcon icon={faEarthAsia} />}
                content="Chech hạn SD tên miền"
                className="sub-text"
              />
            </a>
          </div>
        </div>
      </div>

      <Link to="/login">
        <MenuSideBarItem
          icon={<FontAwesomeIcon icon={faRightToBracket} />}
          content="Đăng nhập"
        />{" "}
      </Link>

      <Link to="/register">
        <MenuSideBarItem
          icon={<FontAwesomeIcon icon={faUserPlus} />}
          content="Đăng ký"
        />
      </Link>
    </div>
  );
};

export default Menu;
