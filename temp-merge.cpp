#include "definations.h"
Customer *current_user = NULL;
Vendor *current_Vendor = NULL;
Admin *current_admin = NULL;
void home_page();
void login();
void register_page();
#define cls system("clear")
void delete_from_cart() {
    system("clear");
    current_user->get_cart().print_cart();
    int item_id;
    cout << "Enter the Item id of Item you want to delete from above: ";cin >> item_id;
    current_user->get_cart().delete_item(item_id);
    current_user->get_cart().print_cart();
    cout<<"DELETING... "<<item_id<<"\n";
    system("sleep 1");
    system("clear");
}


void clear_cart()
{
    system("clear");
    current_user->get_cart().clear_cart();
    cout<<"CLEARING...\n";
    system("sleep 1");
    system("clear");
}


void change_quantity() {
    int item_id, new_q;
    cout << "Enter the Item id of Item and its new quantity: ";cin >> item_id >> new_q;
    if(current_user->get_cart().change_quantity(item_id, new_q)) {
        cout<<"CHANGING...";
        current_user->get_cart().print_cart();
        system("sleep 3");
        system("clear");
        return;
    }
    cout<<"INVALID ITEM ID";
    system("sleep 2");
    system("clear");
}


void checkout() {
    system("clear");
    if(! current_user->get_cart().is_empty()) {
        current_user->get_cart().print_cart();
        cout<<"1.Online payment\n"
            <<"2.COD\n"
            <<"3.Cancel\n";
        char option;cin>>option;
        system("clear");
        //
        Cart cart = current_user->get_cart();
        vector<int> items = cart.get_items();
        vector<int> quantity = cart.get_quantity();
        map<int, int> payments;
        int user_id = current_user->get_user_id();
        COD empty_cod;
        OnlineTransaction empty_online;
        if(option == '1'){
            for(auto it = slot_list.begin(); it != slot_list.end(); ++it){
                it->display_slot();
            }
            cout<<"ENTER SLOT-ID: ";
            int slot_id;cin>>slot_id;
            //
            for(int i=0; i<items.size(); i++){
                int bank_id = vendor_list[inventory.item_list[items[i]].get_vendor_id()].get_bank_account();
                payments[bank_id] = (inventory.item_list[items[i]].get_price())*quantity[i];
            }
            OnlineTransaction online(cart, 1, payments);
            for(int i=0; i<items.size();i++){
                Order order(user_id, items[i], quantity[i], slot_id, empty_cod, online);
            }
        } else if(option == '2'){

            for(auto it = slot_list.begin(); it != slot_list.end(); ++it){
                it->display_slot();
            }
            cout<<"ENTER SLOT-ID: ";
            int slot_id;cin>>slot_id;
            COD cod(cart);
            for(int i=0; i<items.size();i++){
                Order order(user_id,  items[i], quantity[i], slot_id, cod, empty_online);
            }
        }
        current_user->get_cart().clear_cart();
        system("clear");
        return;
    }
    return;
}


void cart_operations() {
    int item_id,new_quant;
    char option = 0;
    cout << "1.Delete Item from Cart\n"
       << "2.Clear Cart\n"
       << "3.Change Quantity\n"
       << "4.Checkout\n"
       << "5.Clear Console\n"
       << "6.Return to inventory\n"
       << "\nENTER CHOICE: ";
    cin>>option;
    switch(option) {
        case '1': delete_from_cart(); cart_operations();break;
        case '2': clear_cart(); cart_operations(); break;
        case '3': change_quantity();cart_operations(); break;
        case '4': checkout();cart_operations();break;
        case '5': system("clear"); cart_operations(); break;
        case '6': system("clear"); return;
        default: cout<<"Incorrect Choice\nEnter Again \n"; getchar(); cart_operations(); break;
    }
}


void search_by_name()
{
    system("clear");
    string name;
    char c;
    cout << "Enter the name/category of item you want to search :";cin >> name;
    int flag = inventory.search_item(name);
    if(flag)
    {
        cout<<"---------------------\n";
        cout << "Do you want to add any item to your cart?(Y/N): "; cin>>c;
        if(c=='Y'||c=='y')
        {
            int _item_id, quant;
            cout << "Enter the item id(from above) and quantity of that item u want to add (id quantity): "; cin >> _item_id >> quant;
            quant = current_user->get_cart().add_to_cart(_item_id, quant);
            if(quant == 2){
                cout<<"Enter a valid choice.\n";
                system("sleep 3");
                search_by_name();
            } else if(quant == 1){
                cout<<"Quantity Not Abvailable.\n";
                system("sleep 3");
                search_by_name();
            }
            return;
        }
    }
    cout<<"Name not found"<<endl;
    system("sleep 1");
}


void search_by_id()
{
    system("clear");
    int item_id,flag=0;
    cout << "Enter the id of item you want to search :";cin >> item_id;
    if(inventory.item_list.size()>0)
    {
        if(inventory.quantity[item_id]){
            inventory.item_list[item_id].display_item();
            cout<<"---------------------\n";
            flag = 1;
        }
    }
    else
    {
        cout<<"Item id not Found"<<endl;
        system("sleep 1");
        return;
    }
    
    char c;
    if(flag)
    {
        cout << "Do you want to add this item to your cart?(Y/N): ";cin >> c;
        if (c == 'Y'||c=='y')
        {
            int quant;
            cout << "Enter the quantity u want to add (quantity): ";cin >> quant;
            quant = current_user->get_cart().add_to_cart(item_id, quant);
            if(quant == 2){
                cout<<"Enter a valid choice.\n";
                system("sleep 3");
                search_by_id();
            } else if(quant == 1){
                cout<<"Quantity Not Abvailable.\n";
                system("sleep 3");
                search_by_id();
            }
            return;
        }
    }
}

void view_full_inventory(){
    inventory.display_inventory();
    cout<<"---------------------\n";
    system("sleep 3");
}

void view_shopping_cart()
{
    current_user->get_cart().print_cart();
    cart_operations();
}

void view_order_list()
{
    vector<int> orders = customer_list[current_user->get_user_id()].get_orders();
    for(int i=0;i<orders.size();i++){
        order_list[orders[i]].print_order();
    }
    system("sleep 1");
}

void init(int clr)
{
    if(clr) system("clear");
    cout << "1.Search Item by Name\n"
       << "2.Search Item by id\n"
       << "3.View Order List\n"
       << "4.View Shopping Cart\n"
       << "5.Checkout\n"
       << "6.View Full Inventory\n"
       << "7.Clear Console\n"
       << "8.Logout\n"
       << "\nENTER CHOICE: ";
    char _option = 0; cin>>_option;
    system("clear");
    switch(_option) {
        case '1': search_by_name(); init(1); break;
        case '2': search_by_id();init(1); break;
        case '3': view_order_list(); init(0); break;
        case '4': view_shopping_cart(); init(1); break;
        case '5': checkout(); init(1); break;
        case '6': view_full_inventory(); init(0); break;
        case '7': init(1);
        case '8': return;
        default: cout<<"Incorrect Choice\nEnter Again \n"; getchar(); break;
    }
}

void add_new_item()
{
    system("clear");
    string name, category, description;
    int price, vendor_id, discount,quant;
    char choice;
    cout << "Enter Item Name: "; cin >> name;
    cout << "Choose Category: "; cin >> category;
    getline(cin, description);
    cout << "Enter description: ";cout.flush();getline(cin, description);
    cout << "Enter Item Price: ";cin >> price;
    cout <<"Enter the quantity you would like to add: "; cin>>quant;
    cout << "Would you like to keep discount on such item(Y/N): ";cin >> choice;
    if (choice == 'Y'||choice=='y') cout << "Enter Discount(%%): ", cin >> discount;
    else discount = 0;
    current_Vendor->add_new_item(name, category, description, price, quant);
}
void view_item_list_vendor()
{
    system("clear");
    if(current_Vendor->get_items().size()>0){
    current_Vendor->view_item_list();
    cout<<"---------------------\n";
    system("sleep 2");
    } else {
        cout<<"Empty Item List\n";
        system("sleep 1");
        system("clear");
    }
    

}
void update_exisiting_item()
{
    if(current_Vendor->get_items().size()>0) {
        view_item_list_vendor();
        string name;
        int _item_id, _new_price;
        cout << "Enter Item id of item you would like to update (from above list): "; cin >> _item_id;
        vector<int>& items = current_Vendor->get_items();
        auto it = find(items.begin(), items.end(), _item_id);
        if(it != items.end()) {
            cout<<"1.Change Price\n"
                <<"2.Change Quantity\n"
                <<"3.Change Discount\n"
                <<"4.Change Description\n"
                <<"\nENTER CHOICE: ";
            char _option; cin>>_option;
            //
            system("clear");
            Item *current = &inventory.item_list[_item_id];
            string _description;
            switch(_option) {
                case '1': cout<<"Enter Price: "; int _price; cin>>_price; current->set_price(_price); break;
                case '2': cout<<"Enter Quantity: "; int _quantity; cin>>_quantity; current->set_quantity(_quantity); break;
                case '3': cout<<"Enter Discount: "; int _discount; cin>>_discount; current->set_discount(_discount); break;
                case '4': cout<<"Enter Description: "; getline(cin, _description); getline(cin, _description); current->set_description(_description);
                default: break;
            }
        }
        else {
            system("clear");
            cout<<"Invalid Item id/Can't update item of this id\n";
            cout<<"Select id from following list: \n";
            system("sleep 3");
            update_exisiting_item();
        }
    } else {
        cout<<"Empty item list. To update, First add an item\n";
        system("sleep 2");
    }
    
    
}
void update_info()
{
    cout<<"1.Change name\n";
    cout<<"2.Change password\n";
    cout<<"3.Change email\n";
    cout<<"4.Back to Vendor page\n";
    string _name, _pass, _email; 
    char _option = 0;
    cin>>_option;
    switch(_option) {
        case '1':
            cout<<"Enter name: \n"; cin>>_name;
            cout<<"Name Changed!!!\n";
            current_Vendor->set_name(_name);
            break;
        case 2:
            getchar();
            _pass = getpass("Enter old password: ",true);
            if(current_Vendor->validate(_pass)) {
                _pass = getpass("Enter new password: ",true);
                cout<<"Password Changed!!!\n";
                current_Vendor->set_password(_pass);
            }
            break;
        case '3':
            cout<<"Enter email: \n"; cin>>_email;
            cout<<"Email Changed!!!\n";
            current_Vendor->set_email_id(_email);
            break;
        case '4':
            break;
        default:
            cout<<"Incorrect Option. Enter Again\n"; getchar(); update_info(); break;
    }
    return;
}

void view_order_list_vendor(){
    system("clear");
    vector<int> orders = current_Vendor->get_orders();
    if(orders.size()) {
        for(auto it=orders.begin(); it!=orders.end(); ++it){
            order_list[*it].print_order();
        }
        system("sleep 2");
    }
    else {
        cout<<"Empty Order List\n";
        system("sleep 1");
        system("clear");
    }
}

void init_vendor(int clr) {
    if(clr) system("clear");
    cout << "1.Add New Item\n"
         << "2.Update Existing Item\n"
         << "3.View Order List\n"
         << "4.View Item List\n"
         << "5.Update Info\n"
         << "6.Logout\n"
         << "ENTER CHOICE: ";
    char _option = 0;
    cin>>_option;
    switch(_option) {
        case '1': add_new_item(); init_vendor(1);break;
        case '2': update_exisiting_item(); init_vendor(1); break;
        case '3': view_order_list_vendor(); init_vendor(0); break;
        case '4': view_item_list_vendor();init_vendor(0);break;
        case '5': update_info();init_vendor(1);break;
        case '6': system("clear"); break;
        default: cout<<"Incorrect Choice\nEnter Again \n";system("sleep 0"); getchar(); init_vendor(1); break;
    }
}
void init_admin();
void add_new_vendor() {
    system("clear");
    bool valid = true;
    string _name, _pass, _email, _address;
    int _account, _phone;
    cout<<"Enter email: "; cin>>_email;
    for(auto it = vendor_list.begin(); it != vendor_list.end(); ++it)
        if(_email == it->get_email_id()) {
            valid = false;
            break;
        }
    if(valid) {
        cout<<"Enter name: "; cin>>_name; getchar();
        _pass = getpass("Enter password: ",true);
        cout<<"Enter phone number: "; cin>>_phone;
        cout<<"Enter account number: "; cin>>_account;
        cout<<"Enter address: "; getchar(); getline(cin,_address);
        Vendor vendor(_name,_pass,_email,_account,_phone,_address);
    } else {
        cout<<"Email already in use. Please use a new one.\n"
            <<"Do you want to continue?(Y/N): ";
        char ch; cin>>ch;
        if(ch == 'y' || ch == 'Y') 
            add_new_vendor();
    }
    init_admin();
    return;
}
void add_new_slot() {
    system("clear");
    string _name, _time_slot;
    cout<<"Enter name for slot: \n"; cin>>_name;
    cout<<"Enter time slot: \n"; cin>>_time_slot;
    DeliverySlot slot(_name,_time_slot);
    init_admin();
    return;
}
void update_admin_info() {
    system("clear");
    cout<<"1.Change name\n";
    cout<<"2.Change password\n";
    cout<<"3.Change email\n";
    cout<<"4.Back to admin page\n";
    cout<<"ENTER CHOICE: ";
    string _name, _pass, _email; 
    char _option = 0;
    cin>>_option;
    switch(_option) {
        case '1':
            cout<<"Enter name: "; cin>>_name;
            cout<<"Name Changed!!!\n";
            current_admin->set_name(_name);
            break;
        case '2':
            getchar();
            _pass = getpass("Enter old password: ",true);
            if(current_admin->validate(_pass)) {
                _pass = getpass("Enter new password: ",true);
                cout<<"Password Changed!!!\n";
                current_admin->set_password(_pass);
            }
            break;
        case '3':
            cout<<"Enter email: "; cin>>_email;
            cout<<"Email Changed!!!\n";
            current_admin->set_email_id(_email);
            break;
        case '4':
            break;
        default:
            cout<<"Incorrect Option. Enter Again\n"; getchar(); update_admin_info(); break;
    }
    init_admin();
    return;
}
void init_admin() {
    system("clear");
    cout<<"1.Add New Vendor\n";
    cout<<"2.Add New Delivery Slot\n";
    cout<<"3.Update Info\n";
    cout<<"4.Logout\n";
    cout<<"ENTER CHOICE: ";
    char _option = 0;
    cin>>_option;
    switch(_option) {
        case '1': add_new_vendor(); break;
        case '2': add_new_slot(); break;
        case '3': update_admin_info(); break;
        case '4': break;
        default: cout<<"Incorrect Choice\nEnter Again "; getchar();  init_admin(); break;
    }
}
void register_user() {
    cls;
    string _name, _pass, _email, _address;
    int _phone, _type;
    bool flag = false;
    cout<<"Enter Email: "; cin>>_email;
    for(auto it = customer_list.begin(); it != customer_list.end() && !flag; ++it)
        if(_email == it->get_email_id()) {
            flag = true;
            break;
        }
    if(!flag) {
        cout<<"Enter Name: "; cin>>_name; getchar();
        _pass = getpass("Enter Password: ", true);
        cout<<"Enter Address with City and State: "; getline(cin,_address);
        cout<<"Enter Contact Number: "; cin>>_phone;
        cout<<"Enter Type (Faculty/Student): "; cin>>_type;
        Customer cust(_name,_pass,_email,_address,_phone,_type);
        cout<<"Redirecting to homepage\n";
        system("sleep 1");
        return;
    } else {
        cout<<"Email already in use!!!\n"
            <<"Want to try again(Y/N)?: ";
        char c; cin>>c;
        if(c == 'Y' || c == 'y') 
            register_user();
        else {
            system("sleep 1");
            return;
        }

    }
}
void home_page() {
    system("clear");
    cout<<"1. Login\n"
        <<"2. Register\n"
        <<"3. Exit\n"
        <<"ENTER CHOICE: ";
    fflush(stdin);
    char option = 0; cin>>option;
    switch(option) {
        case '1': login();break;
        case '2': register_user();home_page();break;
        case '3': return;
        default: cout<<"Incorrect Choice\nEnter Again \n"; system("sleep 1"); home_page(); break;
    }
}
void login(){
    string _email, _pass;
    bool flag = false;
    cout<<"EMAIL-ID: "; cin>>_email; getchar();
    _pass = getpass("PASSWORD: ",true);
    for(auto it = customer_list.begin(); it != customer_list.end() && !flag; ++it){
        if(it->get_email_id() == _email && it->validate(_pass)){
            current_user = &(*it);
            flag = true;
            init(1);
        }
    }
    for(auto it = vendor_list.begin(); it != vendor_list.end() && !flag; ++it){
        if(it->get_email_id() == _email && it->validate(_pass)){
            current_Vendor = &(*it);
            flag = true;
            init_vendor(1);
        }
    }
    for(auto it = admin_list.begin(); it != admin_list.end() && !flag; ++it){
        if(it->get_email_id() == _email && it->validate(_pass)){
            current_admin = &(*it);
            flag = true;
            init_admin();
        }
    }
    if(!flag) {
        cout<<"Username or password is invalid\n";
        system("sleep 1");
        system("clear");
    }
    home_page();
}

void init_flush() {
    readFromFile(customer_list,"customer");
    readFromFile(admin_list,"admin");
    readFromFile(vendor_list,"vendor");
    readFromFile(order_list,"order");
    readFromFile(slot_list,"slot");
    readFromFile(inventory.item_list,"item");
    i32readFromFile(inventory.quantity,"quantity");
}

void exit_flush() {
    writeToFile(customer_list,"customer");
    writeToFile(admin_list,"admin");
    writeToFile(vendor_list,"vendor");
    writeToFile(order_list,"order");
    writeToFile(slot_list,"slot");
    writeToFile(inventory.item_list,"item");
    writeToFile(inventory.quantity,"quantity");
}
void init_Lists() {
    for(auto it = inventory.item_list.begin(); it != inventory.item_list.end(); ++it) {
        vendor_list[it->get_vendor_id()].get_items().push_back(it->get_item_id());
    }
}

int main() {
    init_flush();
    // cout<<inventory.quantity.size()<<" "<<endl;
    string s = "abcd";
    // Vendor v2("Manav","san01","man@",12345,958698,"randikhana");
    // Customer c1("nishant","jain","nish@","kotha",97823,0);
    init_Lists();
    // v2.add_new_item("shampoo", "cosmetics", "sexy", 50, 35);
    // Admin a("Boss","boobs","acid@");
    home_page();
    // cout<<vendor_list[0].get_items().size()<<endl;
    // cout<<admin_list.size();
    // cout<<customer_list.size();
    // cout<<vendor_list.size();
    // cout<<inventory.item_list.size()<<" "<<Item::total_items<<endl;
    // cout<<inventory.quantity.size()<<" "<<endl;
    exit_flush();
    return 0;
}