#include <iostream>

int main() {
    int i[] {1,2,3};
    for (auto k : i) {
        std::cout << k;
    }

    return 0;
}
