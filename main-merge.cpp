#include "definations.h"
Customer *current_user = NULL;

void delete_from_cart()
{
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


void change_quantity()
{
    int item_id, new_q;
    cout << "Enter the Item id of Item and its new quantity: ";cin >> item_id >> new_q;
    if(current_user->get_cart().change_quantity(item_id, new_q)){
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


void checkout()
{
    system("clear");
    if(! current_user->get_cart().is_empty()){
        current_user->get_cart().print_cart();
        cout<<"1.Online payment\n"
            <<"2.COD\n"
            <<"3.Cancel\n";
        int option;cin>>option;
        system("clear");
        //
        Cart cart = current_user->get_cart();
        vector<int> items = cart.get_items();
        vector<int> quantity = cart.get_quantity();
        map<int, int> payments;
        int user_id = current_user->get_user_id();
        COD empty_cod;
        OnlineTransaction empty_online;
        if(option == 1){
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
        } else if(option == 2){

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
        system("clear");
        return;
    }
    return;
}


void cart_operations()
{
    int item_id,new_quant,option = 0;
    cout << "1.Delete Item from Cart\n"
       << "2.Clear Cart\n"
       << "3.Change Quantity\n"
       << "4.Checkout\n"
       << "5.Clear Console\n"
       << "6.Return to inventory\n"
       << "\nENTER CHOICE: ";
    cin>>option;
    switch(option)
    {
        case 1: delete_from_cart(); cart_operations();break;
        case 2: clear_cart(); cart_operations(); break;
        case 3: change_quantity();cart_operations(); break;
        case 4: checkout();cart_operations();break;
        case 5: system("clear"); cart_operations(); break;
        case 6: system("clear"); return;
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
}


void search_by_id()
{
    system("clear");
    int item_id,flag=0;
    cout << "Enter the id of item you want to search :";cin >> item_id;
    if(inventory.quantity[item_id]){
        inventory.item_list[item_id].display_item();
        flag = 1;
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
    system("sleep 5");
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
    int _option = 0; cin>>_option;
    system("clear");
    switch(_option) {
        case 1: search_by_name(); init(1); break;
        case 2: search_by_id(); init(1); break;
        case 3: view_order_list(); init(0); break;
        case 4: view_shopping_cart(); init(1); break;
        case 5: checkout(); init(1); break;
        case 6: view_full_inventory(); init(0); break;
        case 7: init(1);
        case 8: return;
        default: cout<<"Incorrect Choice\nEnter Again \n"; getchar(); break;
    }
}


Vendor *current_Vendor = NULL;
void add_new_item()
{
    string name, category, description;
    int price, vendor_id, discount;
    char choice;
    cout << "Enter Item Name: "; cin >> name;
    cout << "Choose Category: "; cin >> category;
    getline(cin, description);
    cout << "Enter description: ";cout.flush();getline(cin, description);
    cout << "Enter Item Price: ";cin >> price;
    cout << "Would you like to keep discount on such item(Y/N): ";cin >> choice;
    if (choice == 'Y'||choice=='y') cout << "Enter Discount(%%): ", cin >> discount;
    else discount = 0;
    current_Vendor->add_new_item(name, category, description, price, 0);
}
void update_exisiting_item()
{
    string name;
    int _item_id, _new_price;
    cout << "Enter Item id: "; cin >> _item_id;
    vector<int>& items = current_Vendor->get_items();
    auto it = find(items.begin(), items.end(), _item_id);
    if(it != items.end()){
        cout<<"1.Change Price\n"
            <<"2.Change Quantity\n"
            <<"3.Change Discount\n"
            <<"4.Change Description\n"
            <<"\nENTER CHOICE: ";
        int _option; cin>>_option;
        //
        system("clear");
        Item *current = &inventory.item_list[_item_id];
        string _description;
        switch(_option){
            case 1: cout<<"Enter Price: "; int _price; cin>>_price; current->set_price(_price); break;
            case 2: cout<<"Enter Quantity: "; int _quantity; cin>>_quantity; current->set_quantity(_quantity); break;
            case 3: cout<<"Enter Discount: "; int _discount; cin>>_discount; current->set_discount(_discount); break;
            case 4: cout<<"Enter Description: "; getline(cin, _description); getline(cin, _description); current->set_description(_description);
            default: break;
        }
    }
}
void view_item_list_vendor()
{
    system("clear");
    current_Vendor->view_item_list();
    system("sleep 2");
}
void update_info()
{
    cout<<"1.Change name\n";
    cout<<"2.Change password\n";
    cout<<"3.Change email\n";
    cout<<"4.Back to admin page\n";
    string _name, _pass, _email; 
    int _option = 0;
    cin>>_option;
    switch(_option) {
        case 1:
            cout<<"Enter name: \n"; cin>>_name;
            cout<<"Name Changed!!!\n";
            current_Vendor->set_name(_name);
            break;
        // case 2:
        //     getchar();
        //     _pass = getpass("Enter old password:",true);
        //     if(current_Vendor->validate(_pass)) {
        //         _pass = getpass("Enter new password:",true);
        //         cout<<"Password Changed!!!\n";
        //         current_Vendor->set_password(_pass);
        //     }
        //     break;
        case 3:
            cout<<"Enter email: \n"; cin>>_email;
            cout<<"Email Changed!!!\n";
            current_Vendor->set_email_id(_email);
            break;
        case 4:
            break;
        default:
            cout<<"Incorrect Option. Enter Again\n"; getchar(); update_info(); break;
    }
    return;
}

void view_order_list_vendor(){
    vector<int> orders = current_Vendor->get_orders();
    for(auto it=orders.begin(); it!=orders.end(); ++it){
        order_list[*it].print_order();
    }
}

void init_vendor(int clr)
{
    if(clr) system("clear");
    cout << "1.Add New Item\n"
         << "2.Update Existing Item\n"
         << "3.View Order List\n"
         << "4.View Item List\n"
         << "5.Update Info\n"
         << "6.Logout\n";
    int _option = 0;
    cin>>_option;
    switch(_option) {
        case 1: add_new_item(); init_vendor(1);break;
        case 2: update_exisiting_item(); init_vendor(1); break;
        case 3: view_order_list_vendor(); break;
        case 4: view_item_list_vendor();init_vendor(0);break;
        case 5: update_info();init_vendor(1);break;
        case 6: break;
        default: cout<<"Incorrect Choice\nEnter Again \n"; getchar(); init_vendor(1); break;
    }
}

void login(){
    string uname, pass;
    cout<<"EMAIL-ID: ";
    cin>>uname;
    cout<<"PASSWORD: ";
    cin>>pass;

    for(auto it = customer_list.begin(); it != customer_list.end(); ++it){
        if(it->get_email_id() == uname && it->validate(pass)){
            current_user = &(*it);
            init(1);
            login();
        }
    }
    for(auto it = vendor_list.begin(); it != vendor_list.end(); ++it){
        if(it->get_email_id() == uname && it->validate(pass)){
            current_Vendor = &(*it);
            init_vendor(1);
            login();
        }
    }
}

int main()
{
    string s = "abcd";
    Vendor v2(s,s,s,123,1234,s);
    Customer c1(s, s, "abc", s, 0, 0);
    v2.add_new_item("shampoo", "cosmetics", "sexy", 50, 35);
    login();
}