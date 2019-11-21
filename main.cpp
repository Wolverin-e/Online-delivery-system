#include"def.h"

int main(){
    User u1("Mitul", "alpha", "abc@bcd.com"), u2("jsj", "hs", "jsj");
    vector<User>::iterator it = find(user_list.begin(), user_list.end(), u2);
    cout<<(it-user_list.begin()+1)<<endl;

    Item i1("flexon", "medicine", "painkiller", 32, 22);
    cout<<inventory.item_list[0].get_name();
    return 0;
}