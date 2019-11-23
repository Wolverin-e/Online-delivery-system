#include "definations.h"
class A {
public:
    int a;
    int b;
    string str;
    A(int _a = 0, int _b = 0) {a = _a; b = _b;}
    friend ostream & operator << (ostream &out, const A &c); 
    friend istream & operator >> (istream &in,  A &c); 
};
ostream & operator << (ostream &out, const A &c) {out<<c.a<<" "<<c.b<<c.str; return out;}
istream & operator >> (istream &in,  A &c) {in>>c.a>>c.b; getline(in,c.str); return in;}
template <typename T>
int writeToFile(const vector<T> &a, string file) {
    ofstream fout;
    fout.open(file);
    if(fout) {
        for(auto it = a.begin(); it != a.end(); ++it) {
            fout<<*it<<endl;
            // cout<<*it<<endl;
        }
        fout.close();
        return 1;
    }
    return 0;
}
template <typename T>
int readFromFile(vector<T> &a, string file) {
    ifstream fin(file);
    if(fin) {
        while(fin) {
            T _a; fin>>_a;
            if(fin.eof())
                break;
            cout<<_a<<endl;
            a.push_back(_a);
        }
        fin.close();
        return 1;
    }
    return 0;
}
int main() { 
    vector<Item> a;
    for(int i = 0; i < 3; i++) {
        Item c("abcd","def","ghijk",12,24);
        a.push_back(c);
    }
    writeToFile(a,"sample");
    vector<Item> b;
    readFromFile(b,"sample");
    // cout<<"*"<<b.size()<<"*"<<endl;
    // for(auto it = b.begin(); it != b.end(); ++it)
    //     cout<<*it<<endl;
    return 0; 
} 