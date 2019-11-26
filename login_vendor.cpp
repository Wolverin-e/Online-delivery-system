#include "definations.h"
Vendor *current_Vendor = NULL;
void add_new_item()
{
    string name, category, description;
    int price, vendor_id, discount;
    char choice;
    cout << "Enter Item Name: "; cin >> name;
    cout << "Choose Category: "; cin >> category;fflush(stdin);
    cout << "Enter description: ";cout.flush();getline(cin, description);
    cout << "Enter Item Price: ";cin >> price;
    cout << "Would you like to keep discount on such item(Y/N): ";cin >> choice;
    if (choice == 'Y'||choice=='y') cout << "Enter Discount(%): ", cin >> discount;
    else discount = 0;
    fflush(stdin);
    current_Vendor->add_new_item(name,category,description,price);
}
void update_exisiting_item()
{
    string name;
    int item_id,new_price;
    cout << "Enter Item Name: "; cin >> name;
    cout << "Enter Item id: "; cin >> item_id;
    cout<<"Enter the new price: ";cin>>new_price;
    current_Vendor->update_item(item_id,new_price);
}
void view_item_list()
{
    current_Vendor->view_item_list();
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

void vendor_page()
{
    // system("clear");
    cout << "1.Add New Item\n"
         << "2.Update Existing Item\n"
         << "3.View Order List\n"
         << "4.View Item List\n"
         << "5.Update Info\n"
         << "6.Logout\n";
    int _option = 0;
    cin>>_option;
    switch(_option) {
        case 1: add_new_item(); vendor_page();break;
        case 2: update_exisiting_item(); vendor_page(); break;
        // case 3: view_order_list(); break;
        case 4: view_item_list();vendor_page();break;
        case 5: update_info();vendor_page();break;
        case 6: break;
        default: cout<<"Incorrect Choice\nEnter Again \n"; getchar(); vendor_page(); break;
    }
}
int main()
{
    string s = "abcd";
    Vendor v2(s,s,s,123,1234,s);
    current_Vendor=&v2;
    vendor_page();
}