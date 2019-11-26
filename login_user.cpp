#include "definations.h"
Customer *current_user = NULL;
void display_cart()
{
    vector<int> item = current_user->get_cart().get_items();
    int count=1;
    for(auto it = item.begin(); it != item.end(); ++it)
    {
        for(auto zt = inventory.item_list.begin(); zt != inventory.item_list.end(); ++zt)
        {
            if((*zt).get_item_id()==(*it))
            {
                cout<<count<<". "<<endl;
                cout<<(*zt);
            }
            count++;
        }
    }
}
void delete_from_cart()
{
    display_cart();
    int item_id;
    cout << "Enter the Item id of Item you want to delete from above: ";cin >> item_id;
    current_user->get_cart().delete_item(item_id);
    display_cart();
}
void clear_cart()
{
    current_user->get_cart().clear_cart();
}
void chang_quantity()
{
    int item_id, new_q;
    cout << "Enter the Item id of Item and its new quantity: ";cin >> item_id >> new_q;
    current_user->get_cart().change_quantity(item_id, new_q);
    display_cart();
}
void cart_operations()
{
    int item_id,new_quant,option = 0;
    cout << "1.Delete Item from Cart\n"
       << "2.Clear Cart\n"
       << "3.Change Quantity\n"
       << "4.Checkout\n"
       << "5.Return to inventory\n";
    cin>>option;
    switch(option)
    {
        case 1: delete_from_cart(); cart_operations();break;
        case 2: clear_cart(); cart_operations(); break;
        case 3: chang_quantity();cart_operations(); break;
        // case 4: checkout();cart_operations();break;
        case 5:return;
        default: cout<<"Incorrect Choice\nEnter Again \n"; getchar(); cart_operations(); break;
    }
}
void Search_by_name()
{
    string name;
    char c;
    int count=1,flag=0;
    cout << "Enter the name of item you want to search :";cin >> name;
    for(auto it = inventory.item_list.begin(); it != inventory.item_list.end(); ++it)
    {
        if((*it).get_name()==name)
        {
            flag=1;
            cout<<count<<". "<<endl;
            cout<<(*it);
        }
        count++;
    }
    if(flag)
    {
        cout << "Do you want to add any item to your cart?(Y/N): "; cin>>c;
        if(c=='Y'||c=='y')
        {
            int add_id, quant;
            cout << "Enter the item id(from above) and quantity of that item u want to add (id quantity): "; cin >> add_id >> quant;
            current_user->get_cart().add_to_cart(add_id, quant);
            return;
        }
    }
    cout<<"Name not found"<<endl;
}
void Search_by_id()
{
    int item_id,flag=0;
    char c;
    cout << "Enter the id of item you want to search :";cin >> item_id;
    for(auto it = inventory.item_list.begin(); it != inventory.item_list.end(); ++it)
    {
        if((*it).get_item_id()==item_id)
        {
            cout<<(*it);
            flag=1;
            if((*it).is_available()!=1)
            cout<<"Not Available\n";
            break;
        }
    }
    if(flag)
    {
        cout << "Do you want to add this item to your cart?(Y/N): ";cin >> c;
        if (c == 'Y'||c=='y')
        {
            int quant;
            cout << "Enter the quantity u want to add (quantity): ";cin >> quant;
            current_user->get_cart().add_to_cart(item_id, quant);return;
        }
    }
    cout<<"Id not found"<<endl;
}
void view_shopping_cart()
{
    display_cart();
    cart_operations();
}
void user_page()
{
    cout << "1.Search Item by Name\n"
       << "2.Search Item by id\n"
       << "3.View Order List\n"
       << "4.View Shopping Cart\n"
       << "5.Checkout\n"
       << "6.View Full Inventory\n"
       << "7.Logout\n";
    int _option = 0;
    cin>>_option;
    switch(_option) {
        case 1: Search_by_name(); user_page();break;
        case 2: Search_by_id(); user_page(); break;
        // case 3: view_order_list();user_page(); break;
        case 4: view_shopping_cart();user_page();break;
        // case 5: update_info();user_page();break;
        case 7: break;
        default: cout<<"Incorrect Choice\nEnter Again \n"; getchar(); user_page(); break;
    }
}
int main()
{
    string s = "nishant";
    Customer c2(s,s,s,s,9686,1);
    current_user=&c2;
    Item v1("shampoo","cosmetics","good",20,0);
    // inventory.view_items_inv();
    user_page();
}