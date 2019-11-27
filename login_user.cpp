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



int main()
{
    string s = "nishant";
    Vendor new_vend(s,s,s,123,9586,s);
    Customer c2(s,s,s,s,9686,1);
    current_user=&c2;
    new_vend.add_new_item("shampoo","cosmetics","good", 20, 50);
    current_user->get_cart().add_to_cart(0,3);
    init(1);
}