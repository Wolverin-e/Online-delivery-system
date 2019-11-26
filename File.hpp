#include <bits/stdc++.h>
#include<string>
#include<vector>
#include<iostream>
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
