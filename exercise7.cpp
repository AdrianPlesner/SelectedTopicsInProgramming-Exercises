//
// Created by Adrian Plesner on 04/03/2022.
//
#include <vector>
#include <iostream>
using namespace std;
void print(vector<int> v){
    cout << "{";
    for(auto i = v.begin(); i != v.end(); i++){
        cout << *i;
        if(i != v.end() -1){
            cout << ", ";
        }
    }
    cout << "}" << endl;
}

int main(){
    auto v = vector{1,2,3};
    print(v);
    return 0;
}
