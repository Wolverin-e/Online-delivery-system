#include "definations.h"
Admin *current_admin = NULL;
void admin_page();
void add_new_vendor() {
    string _name, _pass, _email, _address;
    int _account, _phone;
    cout<<"Enter name: \n"; cin>>_name; getchar();
    _pass = getpass("Enter password: ",true);
    cout<<"Enter phone number: \n"; cin>>_phone;
    cout<<"Enter email: \n"; cin>>_email;
    cout<<"Enter account number: \n"; cin>>_account;
    cout<<"Enter address: \n"; getchar(); getline(cin,_address);
    Vendor vendor(_name,_pass,_email,_account,_phone,_address);
    admin_page();
    return;
}
void add_new_slot() {
    string _name, _time_slot;
    cout<<"Enter name for slot: \n"; cin>>_name;
    cout<<"Enter time slot: \n"; cin>>_time_slot;
    DeliverySlot slot(_name,_time_slot);
    admin_page();
    return;
}
void update_info() {
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
            current_admin->set_name(_name);
            break;
        case 2:
            getchar();
            _pass = getpass("Enter old password:",true);
            if(current_admin->validate(_pass)) {
                _pass = getpass("Enter new password:",true);
                cout<<"Password Changed!!!\n";
                current_admin->set_password(_pass);
            }
            break;
        case 3:
            cout<<"Enter email: \n"; cin>>_email;
            cout<<"Email Changed!!!\n";
            current_admin->set_email_id(_email);
            break;
        case 4:
            break;
        default:
            cout<<"Incorrect Option. Enter Again\n"; getchar(); update_info(); break;
    }
    admin_page();
    return;
}
void admin_page() {
    system("clear");
    cout<<"1.Add New Vendor\n";
    cout<<"2.Add New Delivery Slot\n";
    cout<<"3.Update Info\n";
    cout<<"4.Logout\n";
    int _option = 0;
    cin>>_option;
    switch(_option) {
        case 1: add_new_vendor(); break;
        case 2: add_new_slot(); break;
        case 3: update_info(); break;
        case 4: break;
        default: cout<<"Incorrect Choice\nEnter Again "; getchar();  admin_page(); break;
    }
}
void login_admin() {
    string _login, _pass;
    bool found = false;
    cout<<"Enter Admin Login: \n";
    cin>>_login;
    getchar();
    _pass = getpass("Enter Admin Password: ", true);
    for(auto it = admin_list.begin(); it != admin_list.end(); ++it) {
        if(it->get_name() == _login) {
            if(it->validate(_pass)) {
                cout<<"Validated"<<endl;
                found = true;
                current_admin = &(*it);
                break;
            }
        }
    }
    if(found)
        admin_page();
    else {
        cout<<"Invalid Username or Password"<<endl;
        return;
    }
}
int main() {
    Admin ad("abcd","def","ghi");
    login_admin();
}
