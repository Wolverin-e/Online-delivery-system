#include "definations.h"
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
void view_item_list()
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

void view_order_list(){
    vector<int> orders = current_Vendor->get_orders();
    for(auto it=orders.begin(); it!=orders.end(); ++it){
        order_list[*it].print_order();
    }
}

void init(int clr)
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
        case 1: add_new_item(); init(1);break;
        case 2: update_exisiting_item(); init(1); break;
        case 3: view_order_list(); break;
        case 4: view_item_list();init(0);break;
        case 5: update_info();init(1);break;
        case 6: break;
        default: cout<<"Incorrect Choice\nEnter Again \n"; getchar(); init(1); break;
    }
}
int main()
{
    string s = "abcd";
    Vendor v2(s,s,s,123,1234,s);
    v2.add_new_item("shampoo", "cosmetics", "sexy", 50, 35);
    current_Vendor=&v2;
    init(1);
}