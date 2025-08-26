
type MenuHeaderProps = {
    text: string
} 

const MenuHeader = ({ text}: MenuHeaderProps) => {
    return (
        <div className={"main-text py-4 px-8 main-background border-b rounded-t-2xl border-gray-900"}>
            {text}
        </div>
    );
}

export default MenuHeader;
