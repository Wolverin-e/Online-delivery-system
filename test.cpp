#include "definations.h"
class A {
public:
    int a;
    int b;
    A(int _a = 0, int _b = 0) {a = _a; b = _b;}
    friend ostream & operator << (ostream &out, const A &c); 
    friend istream & operator >> (istream &in,  A &c); 
};
ostream & operator << (ostream &out, const A &c) {out<<c.a<<" "<<c.b; return out;}
istream & operator >> (istream &in,  A &c) {in>>c.a>>c.b; return in;}
template <typename T>
int writeToFile(vector<T> a, string file) {
    ofstream fout;
    fout.open(file);
    if(fout) {
        for(auto it = a.begin(); it != a.end(); ++it) 
            fout<<*it<<endl;
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
            a.push_back(_a);
        }
        fin.close();
        return 1;
    }
    return 0;
}
int main() { 
    vector<A> a;
    for(int i = 0; i < 3; i++) {
        A c;
        cin>>c;
        a.push_back(c);
    }
    writeToFile(a,"sample");
    vector<A> b;
    readFromFile(b,"sample");
    for(auto it = b.begin(); it != b.end(); ++it)
        cout<<*it<<endl;
    return 0; 
} 