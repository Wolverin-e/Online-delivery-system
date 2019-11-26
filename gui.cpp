//vendor_id should be included in vendor class
//check chanange quantity function if mitul(*it =quantity???)
//Something is wrong in Constructor of transaction!!
#include <bits/stdc++.h>
#include <stdio.h>
#include "startup.h"
#include "login_vendor.h"
#include "login_admin.h"
#include "login_user.h"
using namespace std;
// unordered_map<int, string> Map_ItemId;
// unordered_map<int, int> Map_ItemVendorId;
// Item list[100000]
// unordered_map<User(class), Cart(class)> Map_CustomerCart;
// unordered_map<User(class), Order(class)> Map_CustomerOrder;
// unordered_map<int, string> Map_NameItemId;
int main()
{
  startup();
  current_customer = current_vendor = NULL;
  printf("1. Customer\n2.Admin\n3.Vendor\n");
  int option;
  cin >> option;
  switch (option)
  {
  case 1:
  {
    login_customer();
    break;
  }
  case 2:
  {
    login_admin();
    break;
  }
  case 3:
  {
    login_vendor();
    break;
  }
  }
  return 0;
}