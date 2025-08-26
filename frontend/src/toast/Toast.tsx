import { ToastContainer } from 'react-toastify';

const Toast = () => {
    return (
        <ToastContainer position='top-right' autoClose={3000} newestOnTop={true} closeOnClick={true} pauseOnHover={true} rtl={true} limit={3}/>
        // You can customize the ToastContainer with additional props if needed
        // For example, you can set autoClose, hideProgressBar, etc.
        // <ToastContainer autoClose={5000} hideProgressBar={false} newestOnTop={false} closeOnClick rtl={false} pauseOnFocusLoss draggable pauseOnHover />
    );
}

export default Toast;
