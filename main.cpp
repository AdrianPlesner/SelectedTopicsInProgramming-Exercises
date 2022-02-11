#include <iostream>
#include <string>
using namespace std;
int main() {
    string a{"abc"};
    cout << (a.find('h') == string::npos);

    return 0;
}
