#include <bits/stdc++.h>
#include<string>
#include<vector>
#include<iostream>
#include "getpass.h"

using namespace std;


class User;
class Item;
class Inventory;
class Order;
class Customer;
class DeliverySlot;
class Admin;
class Vendor;
class Transaction;
vector<Customer> customer_list;
vector<Admin> admin_list;
vector<Vendor> vendor_list;
vector<Order> order_list;
vector<DeliverySlot> slot_list;


class Inventory{
    
    public:
        vector<int> quantity;
        vector<Item> item_list;
        ////////////////////////
        void add(Item _item);
        void view_items_inv();
        void update_in_inventory(int item_id,int price);
        // {
        //     for(int i=0;i<item_list.size();i++)
        //     {
        //         cout<<item_list[i];
        //     }
        // }
        // void update_in_inventory(int item_id);
        // // {
        //     for(int i=0;i<item_list.size();i++)
        //     {

        //     }
        // }
        //search_item(name)
        //display_inventory()
        //is_present(item)
        //filter(category)
};

Inventory inventory;

class Item{
    
    protected:
        string name, category, description;
        int price, vendor_id, discount, item_id;
    public:
        static int total_items;
        Item() {}
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
        ////////////////////////
        void display_item() {}
        ////////////////////////
        bool is_available() {return inventory.quantity[item_id] != 0;}
        ////////////////////////
        friend ostream & operator << (ostream &out, const Item &item) {
            out<<item.item_id<<" "<<item.price<<" "<<item.vendor_id<<" "<<item.discount<<endl;
            out<<item.name<<endl<<item.category<<endl<<item.description<<endl;
            return out;
        }
        friend istream & operator >> (istream &in, Item &item) {
            in>>item.item_id>>item.price>>item.vendor_id>>item.discount;
            in.get();
            string _temp;
            getline(in,_temp); item.set_name(_temp);
            getline(in,_temp); item.set_category(_temp);
            getline(in,_temp); item.set_description(_temp);
            return in;
        }
};
int Item::total_items = 0;


class Cart{
    
    private:
        vector<int> items;
        vector<int> quantity;
        vector<Item> view;
        int total_price;
    public:
        Cart(){
            total_price = 0;
        }
        int get_total_price() { return total_price;}
        vector<int> get_items() {return items;}
        vector<int> get_quantity() {return quantity;}
        ////////////////////////
        void add_to_cart(int _item_id, int _quantity){
            // vector<int>::iterator it = find(inventory.item_list.begin(), inventory.item_list.end(), _item_id);
            for(auto it = inventory.item_list.begin(); it != inventory.item_list.end(); ++it)
            {

                if((*it).get_item_id()==_item_id)
                {
                    items.push_back(_item_id);
                    quantity.push_back(_quantity);
                    // total_price += inventory.item_list[_item_id].get_price()*_quantity;
                    return;
                }
            }
            cout<<"invalid item id\n";
            
        }
        void clear_cart(){
            items.clear();
            quantity.clear();
            total_price = 0;
        }
        void delete_item(int _item_id){
            vector<int>::iterator it = find(items.begin(), items.end(), _item_id);
            if(it != items.end()){
                items.erase(it);
                return;
            }
            cout<<"Invalid item id";
        }
        void change_quantity(int _item_id, int _quantity){
            vector<int>::iterator it = find(items.begin(), items.end(), _item_id);
            *it = _quantity;
        }
        // void checkout(){}
        // void print_cart(){}
        ////////////////////////
        friend ostream & operator << (ostream &out, const Cart &cart) {
            for(auto it = cart.items.begin(); it != cart.items.end(); ++it)
                out<<*it<<" ";
            for(auto it = cart.quantity.begin(); it != cart.quantity.end(); ++it)
                out<<*it<<" ";
            out<<cart.total_price<<endl;
        }
        friend istream & operator >> (istream &in, Cart &cart) {
            for(auto it = cart.items.begin(); it != cart.items.end(); ++it)
                in>>*it;
            for(auto it = cart.quantity.begin(); it != cart.quantity.end(); ++it)
                in>>*it;
            in>>cart.total_price;
        }
};


class User{
    
    protected:
        string name, pass, email_id;
        int user_id;
    public:
        static int total_users;
        User() {}
        User(string _name, string _pass, string _email){
            name = _name;
            pass = _pass;
            email_id = _email;
            ++User::total_users;
        }
        string get_name() {return name;}
        void set_name(string _name) {name = _name;}
        string get_email_id() {return email_id;}
        void set_email_id(string _email) {email_id = _email;}
        bool validate(string _pass) {return (pass == _pass);}
        int get_user_id(){return user_id;}
        void set_password(string _pass){pass = _pass;};
        ////////////////////////
        void print_user(){
            cout<<"ID: "<<user_id<<'\n'<<"NAME: "<<name<<'\n'<<"EMAIL: "<<email_id<<'\n'<<endl;
        }
        bool operator==(User another){
            return this->user_id == another.get_user_id();
        }
        ////////////////////////
        friend ostream & operator<< (ostream &out, const User &user) {
            out<<user.user_id<<"\n";
            out<<user.name<<"\n"<<user.pass<<"\n"<<user.email_id;
            return out;
        }
        friend istream & operator>> (istream &in, User &user) {
            in>>user.user_id;
            in.get();
            string _temp;
            getline(in,_temp); user.set_name(_temp);
            getline(in,_temp); user.set_password(_temp);
            getline(in,_temp); user.set_email_id(_temp);
            return in;
        }
};
int User::total_users = 0;


class Customer : public User{
    
    protected:
        string address;
        int phone, type;
        bool is_registered;
        vector<int> orders; // orders-reference-list
        Cart cart;
    public:
        static int total_customers;
        Customer() {}
        Customer(string _name, string _pass, string _email, string _address, int _phone, int _type):User(_name, _pass, _email)
        {
            address = _address;
            phone = _phone;
            type = _phone;
            is_registered = false; //email-verification
            user_id = ++Customer::total_customers;
            customer_list.push_back(*this);
        }
        string get_address() {return address;}
        void set_address(string _address) {address = _address;}
        int get_phone() {return phone;}
        void set_phone(int _phone) {phone = _phone;}
        void set_registered() {is_registered = true;}
        Cart& get_cart(){return cart;}
        ////////////////////////
        friend ostream & operator << (ostream &out, const Customer &customer) {
            out<<static_cast<const User &>(customer)<<endl;
            out<<customer.phone<<" "<<customer.type<<" ";
            for(auto it = customer.orders.begin(); it != customer.orders.end(); ++it)
                out<<*it<<" ";
            out<<customer.address<<"\n";
            out<<customer.cart;
            return out;
        }
        friend istream & operator >> (istream &in, Customer & customer) {
            in>>static_cast<User &>(customer);
            in>>customer.phone>>customer.type;
            for(auto it = customer.orders.begin(); it != customer.orders.end(); ++it)
                in>>*it;
            string _temp; getline(in,_temp); customer.set_address(_temp);
            in>>customer.cart;
            return in;
        }
};
int Customer::total_customers = 0;

void Inventory::add(Item _item){
    item_list.push_back(_item);
    quantity.push_back(0);
}
void Inventory::view_items_inv()
{
    // cout<<item_list.size();
    for(auto it = item_list.begin(); it != item_list.end(); ++it)
        cout<<*it<<endl;
}
void Inventory::update_in_inventory(int item_id,int new_price)
{
    for(int i=0;i<item_list.size();i++)
    {
        if(item_list[i].get_item_id()==item_id)
        {
            item_list[i].set_price(new_price);
            break;
        }
    }
}
class Order{
    
    private:
        int order_id, customer_id, vendor_id, item_id, quantity, netprice, slot_id;
        string status;
        //payment_reference
    public:
        static int total_orders;
        Order() {}
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
        int get_order_id() {return order_id;}
        int get_customer_id() {return customer_id;}
        int get_vendor_id() {return vendor_id;}
        int get_item_id() {return item_id;}
        int get_quantity() {return quantity;}
        int get_netprice() {return netprice;}
        int get_slot_id() {return slot_id;}
        string get_status() {return status;}
        ////////////////////////
        void cancel(){status = "cancelation requested";}
        void confirm_cancellation(){status = "cancelled";}
        //void refund()
        //print_order()
        ////////////////////////
        friend ostream & operator << (ostream &out, const Order &order) {
            out<<order.order_id<<" "<<order.customer_id<<" "<<order.item_id<<" "<<order.vendor_id<<" "<<order.quantity<<" ";
            out<<order.netprice<<" "<<order.slot_id<<" "<<order.status;
            return out;
        }
        friend istream & operator >> (istream &in, Order &order) {
            in>>order.order_id>>order.customer_id>>order.item_id>>order.vendor_id>>order.quantity;
            in>>order.netprice>>order.slot_id;
            getline(in,order.status);
            return in;
        }

};
int Order::total_orders = 0;


class Vendor : public User{
    
    protected:
        int bank_account, phone;
        string address;
        vector<int> items; //item-reference-list
        vector<Item> view;
        vector<int> orders; //order-reference-list
    public:
        static int total_vendors;
        Vendor() {}
        Vendor(string _name, string _pass, string _email, int _account, int _phone, string _address):User(_name, _pass, _email){
            bank_account = _account;
            phone = _phone;
            address = _address;
            user_id = ++Vendor::total_vendors;
            vendor_list.push_back(*this);
        }
        int get_bank_account() {return bank_account;}
        void set_bank_account(int _bank_account) {bank_account = _bank_account;}
        string get_address() {return address;}
        void set_address(string _address) {address = _address;}
        ////////////////////////
        void add_new_item(string _name, string _category, string _description, int _price){
            Item new_item(_name, _category, _description, _price, user_id);
            items.push_back(new_item.get_item_id());
            view.push_back(new_item);
        }
        void view_item_list(){
            for(int i=0;i<view.size();i++)cout<<view[i];
        }
        void update_item(int item_id,int new_price)
        {
            for(int i=0;i<items.size();i++)
            {
                if(items[i]==item_id)
                {
                    view[i].set_price(new_price);
                    inventory.update_in_inventory(item_id,new_price);
                    return;
                }
            }
            cout<<"can't update"<<endl;
        }
        ////////////////////////
        friend ostream & operator << (ostream &out, const Vendor &vendor) {
            out<<static_cast<const User &>(vendor)<<endl;
            out<<vendor.bank_account<<" "<<vendor.phone<<" ";
            for(auto it = vendor.items.begin(); it != vendor.items.end(); ++it)
                out<<*it<<" ";
            for(auto it = vendor.orders.begin(); it != vendor.orders.end(); ++it)
                out<<*it<<" ";   
            out<<vendor.address;
            return out;
        }
        friend istream & operator >> (istream &in, Vendor &vendor) {
            in>>static_cast<User &>(vendor);
            in>>vendor.bank_account>>vendor.phone;
            for(auto it = vendor.items.begin(); it != vendor.items.end(); ++it)
                in>>*it;
            for(auto it = vendor.orders.begin(); it != vendor.orders.end(); ++it)
                in>>*it;
            string _temp;
            getline(in,_temp); vendor.set_address(_temp);
            return in;
        }
};
int Vendor::total_vendors = 0;

class DeliverySlot{
    
    private:
        int slot_id;
        string time_slot, name;
    public:
        static int total_slots;
        DeliverySlot() {}
        DeliverySlot(string _name, string _time_slot){
            name = _name;
            time_slot = _time_slot;
            slot_id = ++total_slots;
            slot_list.push_back(*this);
        }
        string get_name() {return name;}
        string set_name(string _name) {name = _name;}
        string get_time_slot() {return time_slot;}
        void set_time_slot(string _time_slot) {time_slot = _time_slot;}
        ////////////////////////
        friend ostream & operator << (ostream &out, const DeliverySlot &slot) {
            out<<slot.slot_id<<"\n";
            out<<slot.time_slot<<"\n"<<slot.name;
            return out;
        }
        friend istream & operator >> (istream &in, DeliverySlot &slot) {
            in>>slot.slot_id;
            in.get();
            string _temp;
            getline(in,_temp); slot.set_time_slot(_temp);
            getline(in,_temp); slot.set_time_slot(_temp);
            return in;
        }
};
int DeliverySlot::total_slots = 0;


class Admin : public User{
    
    public:
        static int total_admins;
        Admin() {}
        Admin(string _name,string _pass,string _email):User(_name,_pass,_email) {
            user_id = ++Admin::total_admins;
            admin_list.push_back(*this);
        }
        void create_vendor(string _name, string _pass, string _email, int _account, int _phone, string _address){
            Vendor new_vendor(_name, _pass, _email, _account, _phone, _address);
        }
        void create_slot(string _name, string _time_slot){
            DeliverySlot new_slot(_name, _time_slot);
        }
        ////////////////////////
        friend ostream & operator << (ostream &out, const Admin &admin) {out<<static_cast<const User &>(admin); return out;}
        friend istream & operator >> (istream &in, Admin &admin) {in>>static_cast<User &>(admin); return in;}
};
int Admin::total_admins = 0;

class Transaction{
    
    protected:
        int transaction_id;
        Cart ordered_cart;
        bool is_confirmed;
    public:
        Transaction(int _order_id, Cart _ordered_cart){
            ordered_cart = _ordered_cart;
        }
        void confirm_payment(){ is_confirmed = true; }
        // void view_receipt(){}
};


class COD: public Transaction{
    
    public:
        void collect_cash(){
            confirm_payment();
        }
};


class OnlineTransaction: public Transaction{
    
    private:
        int transaction_provider_id, bank_id;
    public:
        void call_online_transaction(){}
};