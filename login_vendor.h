#include "definations.h"
Vendor *current_vendor = NULL;
// void go(vendor)
void go()
{
  system("cls");
  cout << "1.Add New Item\n"
       << "2.Update Existing Item\n"
       << "3.View Order List\n"
       << "4.View Item List\n"
       << "5.Update Info\n"
       << "6.Back to Home page\n"
       << "7.Logout\n";
  int option;
  cin >> option;
  switch (option)
  {
  case 1:
  {
    string name, category, description;
    int price, vendor_id, discount;

    cout << "Enter Item Name: ";
    cin >> name;

    cout << "Choose Category: ";
    // category = Category()
    cin >> category;

    fflush(stdin);
    cout << "Enter description: ";
    getline(cin, description);

    cout << "Enter Item Price: ";
    cin >> price;

    cout << "Your Id: ";
    cin >> vendor_id;

    cout << "Would you like to keep discount on such item(Y/N): ";
    char choice;
    cin >> choice;
    if (choice == 'Y')
    {
      cout << "Enter Discount(%): ";
      cin >> discount;
    }
    else
    {
      discount = 0;
    }
    fflush(stdin);
    // vendor.add_new_item(name,category,description,price,vendor_id,discount);//slight change in arguments of above function

    // Item new_item(name,category,description,price,vendor_id,discount);

    /*
    Map_ItemId[new_item.get_item_id()]=name;
    Map_NameItemId[name]=new_item.get_item_id();
    list[new_item.get_item_id()] = new_item;//no need of member items
    
    Map_ItemVendorId[new_item.get_item_id()]=vendor_id;
    */
    go();
    break;
  }
  case 2:
  {
    int item_id;
    cout << "Enter the Item Id uwant to update: ";
    cin >> item_id;

    // if (Map_ItemVendorId[item_id]==vendor_id)
    // {
    //   cout<<"1.Update price\n"
    //       <<"2.Update discount\n";
    //
    //   int choice;
    //   cin>>choice;
    //
    //   switch(choice)
    //   {
    //     case 1:
    //     {
    //       int cost;
    //
    //       cout<<"Enter the newprice: ";
    //       cin>>cost;
    //
    //       list[item_id].set_price(cost);//price should be public
    //       break;
    //     }
    //     case 2:
    //     {
    //       int disc;
    //
    //       cout<<"Enter the new discount: ";
    //       cin>>disc;
    //
    //       list[item_id].set_discount(disc);//disco should be public
    //       break;
    //     }
    //   }
    // }
    // else
    // {
    //   cout<<"You can't update this item";
    // }
    go();
    break;
  }
  case 3:
  {
    // vendor.get_order_list();//a new function has to be made in class vendor
    go();
    break;
  }
  case 4:
  {
    // vendor.get_item_list();//a new function has to be made in class vendor
    go();
    break;
  }
  case 5:
  {
    string address;

    cout << "Enter the new address: ";
    cin >> address;

    // vendor.set_address(address);
    go();
    break;
  }
  case 6:
  {
    go();
    break;
  }
  case 7:
  {
    exit(0);
    break;
  }
  default:
  {
    go();
    break;
  }
  }
}
void login_vendor()
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
  go();
}
