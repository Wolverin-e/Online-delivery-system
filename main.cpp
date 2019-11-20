#include<iostream>
#include<string>

using namespace std;

class User{
    protected:
        string name, pass, email_id;
        int user_id;
    public:
        static int total_users;
        User(string _name, string _pass, string _email){
            name = _name;
            pass = _pass;
            email_id = _email;
            user_id = ++total_users;
        }
        void print_user(){
            cout<<"ID: "<<user_id<<'\n'<<"NAME: "<<name<<'\n'<<"EMAIL: "<<email_id<<'\n'<<endl;
        }
        string get_name() {return name;}
        void set_name(string _name) {name = _name;}
        string get_email_id() {return email_id;}
        void set_email_id(string _email) {email_id = _email;}
        bool validate(string _pass) {return (pass == _pass);}
        int get_user_id(){return user_id;}
};
int User::total_users = 0;

class Customer : public User{
    protected:
        string address;
        int phone, type;
        bool is_registered;
    public:
        Customer(string _name, string _pass, string _email, string _address, int _phone, int _type):User(_name, _pass, _email)
        {
            address = _address;
            phone = _phone;
            type = _phone;
            is_registered = false; //email-verification
        }
        string get_address() {return address;}
        void set_address(string _address) {address = _address;}
        int get_phone() {return phone;}
        void set_phone(int _phone) {phone = _phone;}
        bool set_registered() {is_registered = true;}
};

class Vendor : public User{
    protected:
        int bank_account, phone;
        string address;
        //ItemList
    public:
        Vendor(string _name, string _pass, string _email, int _account, int _phone, string _address):User(_name, _pass, _email){
            bank_account = _account;
            phone = _phone;
            address = _address;
        }
};

// class Admin : public User{
//     public:
//         void
// };

int main(){
    User u1("Mitul", "alpha", "abc@bcd.com"), u2("jsj", "hs", "jsj");
    return 0;
}