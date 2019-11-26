#include "definations.h"
Customer *current_customer = NULL;
void display_cart(Cart *c) // Check karna hai ise
{
  vector<int> items = c->get_items();
  cout << "\n"
       << "Total Price: " << c->get_total_price() << endl;
  for (int j = 1; j <= items.size(); i++)
  {
    cout << j << ".\n";
    i = items[j];
    cout << "Name: " << list[i].get_name() << "\n"
         << "Price: " << list[i].get_price() << "\n"
         << "Discount: " << list[i].get_discount() << "\n"
         << "Category: " << list[i].get_category() << "\n"
         << "Description: " << list[i].get_description() << "\n"
         << "Item id: " << list[i].get_item_id() << "\n"
         << "Vendor id: " << list[i].get_vendor_id() << "\n";
  }
}
void cart_operations(Cart *c, Customer *customer) //Check karna hai ise
{
  int option;

  cout << "1.Delete Item from Cart\n"
       << "2.Clear Cart\n"
       << "3.Change Quantity\n"
       << "4.Checkout\n";

  cin >> option;
  // switch (option)
  // {
  // case 1:
  // {
  //   int item_id;

  //   cout << "Enter the Item id of Item you want to delete from above: ";
  //   cin >> item_id;

  //   c->delete_item(item_id);
  //   display_cart(c);
  //   break;
  // }
  // case 2:
  // {
  //   c->clear_cart();
  //   display_cart(c);
  //   break;
  // }
  // case 3:
  // {
  //   int item_id, new_q;

  //   cout << "Enter the Item id of Item and its new quantity: ";
  //   cin >> item_id >> new_q;

  //   c->change_quantity(item_id, new_q);
  //   display_cart(c);
  //   break;
  // }
  // case 4:
  // {
  //   string name, time_slot;
  //   if (c->get_total_price() != 0)
  //   {
  //     cout << "Enter the name of person who will pick the deivery: ";
  //     cin >> name;

  //     cout << "Enter the time of delivery: ";
  //     cin >> time_slot;
  //     A /*object of admin*/.create_slot(name, time_slot);
  //     cout << "DELIVERY DETAILS: " << endl;
  //     cout << "Price: " << c->get_total_price() << endl
  //          << "Address of delivery: " << customer /*object*/->get_address() << endl
  //          << "Will be delivered in maximum of 4 days\n"
  //          << "Time: " << time_slot << endl
  //          << "Phone: " << Customer /*object*/.get_phone() << endl;

  //     cout << "Choose Your Delivery option : " << endl
  //          << "C. Cash On delivery" << endl
  //          << "O. Online Payment" << endl;
  //     char ch;
  //     switch (ch)
  //     {
  //       case 'C':
  //       {
  //         COD new_order(Order Id /*how will this work?*/, *c);
  //         new_order.collect_cash();
  //         break;
  //       }
  //       case 'O':
  //       {

  //       }
  //     }
  //   }
  //   break;
  // }
  // }
}
void goss2()
{
  cout << "1.Search Item by Name\n"
       << "2.View Order List\n"
       << "3.View Shopping Cart\n"
       << "4.Checkout\n"
       << "5.Back to Home page\n"
       << "6.Logout\n"
       << "7.Search Item by id\n"
       << "8.View Full Inventory\n";
  int choice;
  cin >> choice;
  switch (choice)
  {
  case 1:
  {
    string name;
    char c;

    cout << "Enter the name of item you want to search :";
    cin >> name;

    int count = 1;

    // for (int i = 0; i < 1000000; i++) //problem full list
    // {
    //   if (strcmp(list[i].get_name(), name) == 0)
    //   {
    //     cout << count << ". \n";
    //     cout << "Name: " << list[i].get_name() << "\n"
    //          << "Price: " << list[i].get_price() << "\n"
    //          << "Discount: " << list[i].get_discount() << "\n"
    //          << "Category: " << list[i].get_category() << "\n"
    //          << "Description: " << list[i].get_description() << "\n"
    //          << "Item id: " << list[i].get_item_id() << "\n"
    //          << "Vendor id: " << list[i].get_vendor_id() << "\n";
    //     if (!list[i].is_available())
    //       cout << "Not available\n";
    //     count++;
    //   }
    // }

    // cout << "Do you want to add any item to your cart?(Y/N): ";
    // cin << c;

    // if (c == 'Y')
    // {
    //   int add_id, quant;

    //   cout << "Enter the item id and quantity u want to add from details(id quantity): ";
    //   cin >> add_id >> quant;

    //   Customer(/*object*/).cart.add_to_cart(add_id, quant); //gives the cart associated with customer
    // }
    break;
  }
  case 2:
  {
    break;
  }
  case 3:
  {
    // display_cart(&Customer(/*object*/).cart);
    // cart_operation(&Customer(/*object*/).cart,&Customer(/*object*/));
    break;
  }
  case 4:
  {
    string name, time_slot;
    if (c->get_total_price() != 0)
    {
      cout << "Enter the name of person who will pick the deivery: ";
      cin >> name;

      cout << "Enter the time of delivery: ";
      cin >> time_slot;
      A /*object of admin*/.create_slot(name, time_slot);
      cout << "DELIVERY DETAILS: " << endl;
      cout << "Price: " << c->get_total_price() << endl
           << "Address of delivery: " << customer /*object*/->get_address() << endl
           << "Will be delivered in maximum of 4 days\n"
           << "Time: " << time_slot << endl
           << "Phone: " << Customer /*object*/.get_phone() << endl;

      cout << "Choose Your Delivery option : " << endl
           << "C. Cash On delivery" << endl
           << "O. Online Payment" << endl;
      char ch;
      switch (ch)
      {
      case 'C':
      {
        COD new_order(Order Id /*how will this work?*/, *c);
        new_order.collect_cash();
        break;
      }
      case 'O':
      {
        break;
      }
      }
    }
    break;
  }
  case 7:
  {
    int item_id;
    char c;

    cout << "Enter the id of item you want to search :";
    cin >> item_id;

    int i = item_id;
    // cout << "Name: " << list[i].get_name() << "\n"
    //      << "Price: " << list[i].get_price() << "\n"
    //      << "Discount: " << list[i].get_discount() << "\n"
    //      << "Category: " << list[i].get_category() << "\n"
    //      << "Description: " << list[i].get_description() << "\n"
    //      << "Item id: " << list[i].get_item_id() << "\n"
    //      << "Vendor id: " << list[i].get_vendor_id() << "\n";
    // if (!list[i].is_available())
    //   cout << "Not available\n";

    // cout << "Do you want to add this item to your cart?(Y/N): ";
    // cin << c;
    // if (c == 'Y')
    // {
    //   int quant;
    //   cout << "Enter the quantity u want to add (quantity): ";
    //   cin >> quant;

    //   Customer(/*object*/).cart.add_to_cart(item_id, quant); //gives the cart associated with customer
    // }
    break;
  }
  case 8:
  {
    break;
  }
  }
}
void login_customer()
{
  string username, password;
  printf("ENTER USERNAME: ");
  cin >> username;
  printf("ENTER PASSWORD: ");
  cin >> password;
  // if validate(vendor):
  // {
  //   go(vendor)
  // }
  goss2();
}