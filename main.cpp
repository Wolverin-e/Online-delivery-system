#include<iostream>
#include<string>
#include<vector>

using namespace std;

// Vectors of Below
// User-List, Item-List, Order-List
class User;
class Item;
class Inventory;
class Order;
class DeliverySlot;

vector<User> user_list;
vector<Order> order_list;
vector<DeliverySlot> slot_list;

class Inventory{
    public:
        vector<int> quantity;
        vector<Item> item_list;
        void add(Item _item){
            item_list.push_back(_item);
            quantity.push_back(0);
        }
        //search_item(name)
        //display_inventory()
        //is_present(item)
        //filter(category)
};

Inventory inventory;


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
            user_list.push_back(*this);
        }
        string get_name() {return name;}
        void set_name(string _name) {name = _name;}
        string get_email_id() {return email_id;}
        void set_email_id(string _email) {email_id = _email;}
        bool validate(string _pass) {return (pass == _pass);}
        int get_user_id(){return user_id;}
        void set_password(string _pass){pass = _pass;};
        //////
        void print_user(){
            cout<<"ID: "<<user_id<<'\n'<<"NAME: "<<name<<'\n'<<"EMAIL: "<<email_id<<'\n'<<endl;
        }
        bool operator==(User another){
            return this->user_id == another.get_user_id();
        }
};
int User::total_users = 0;

class Customer : public User{
    protected:
        string address;
        int phone, type;
        bool is_registered;
        vector<int> orders; // orders-reference-list
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
        void set_registered() {is_registered = true;}
};

class Item{
    protected:
        string name, category, description;
        int price, vendor_id, discount, item_id;
    public:
        static int total_items;
        Item(string _name, string _category, string _description, int _price, int _vendor_id){
            name = _name;
            category = _category;
            description = _description;
            price = _price;
            vendor_id = _vendor_id;
            discount = 0;
            item_id = ++total_items;
            inventory.add(*this);
        }
        string get_name() {return name;}
        void set_name(string _name) {name = _name;}
        string get_category() {return category;}
        void set_category(string _category) {category = _category;}
        string get_description() {return description;}
        void set_description(string _description) {description = _description;}
        int get_price() {return price;}
        void set_price(int _price) {price = _price;}
        int get_vendor_id() {return vendor_id;}
        int get_discount() {return discount;}
        void set_discount(int _discount) {discount = _discount;}
        int get_item_id() {return item_id;}
        /////
        bool is_available(){}
};
int Item::total_items = 0;


class Order{
    private:
        int order_id, customer_id, vendor_id, item_id, quantity, netprice, slot_id;
        string status;
        //payment_reference
    public:
        static int total_orders;
        Order(int _customer_id, int _vendor_id, int _item_id, int _quantity, int _net_price, int _slot_id){
            customer_id = _customer_id;
            vendor_id = _vendor_id;
            item_id = _item_id;
            quantity = _quantity;
            netprice = _net_price;
            slot_id = _slot_id;
            status = "Docking";
            order_id = ++total_orders;
            order_list.push_back(*this);
        }
        void cancel(){status = "cancelation requested";}
        void confirm_cancellation(){status = "cancelled";}
        string get_status() { return status; }
        //void refund()
        //print_order()
};
int Order::total_orders = 0;

class Vendor : public User{
    protected:
        int bank_account, phone;
        string address;
        vector<int> items; //item-reference-list
        vector<int> orders; //order-reference-list
    public:
        Vendor(string _name, string _pass, string _email, int _account, int _phone, string _address):User(_name, _pass, _email){
            bank_account = _account;
            phone = _phone;
            address = _address;
        }
        void add_new_item(string _name, string _category, string _description, int _price){
            Item new_item(_name, _category, _description, _price, user_id);
            items.push_back(new_item.get_item_id());
        }
        //update_existing_item(){}
        //view_order_list(){}
        //view_item_list(){}
};

class DeliverySlot{
    private:
        int slot_id;
        string time_slot, name;
    public:
        static int total_slots;
        DeliverySlot(string _name, string _time_slot){
            name = _name;
            time_slot = _time_slot;
            slot_id = ++total_slots;
            slot_list.push_back(*this);
        }
        string get_time_slot(){return time_slot;}
};
int DeliverySlot::total_slots = 0;

class Admin : public User{
    public:
        void create_vendor(string _name, string _pass, string _email, int _account, int _phone, string _address){
            Vendor new_vendor(_name, _pass, _email, _account, _phone, _address);
        }
        void create_slot(string _name, string _time_slot){
            DeliverySlot new_slot(_name, _time_slot);
        }
};




int main(){
    User u1("Mitul", "alpha", "abc@bcd.com"), u2("jsj", "hs", "jsj");
    vector<User>::iterator it = find(user_list.begin(), user_list.end(), u2);
    cout<<(it-user_list.begin()+1)<<endl;

    Item i1("flexon", "medicine", "painkiller", 32, 22);
    cout<<inventory.item_list[0].get_name();
    return 0;
}