//
// Created by Bruger on 08-02-2022.
//

#include "lehmer.h"
#include <climits>

using namespace std;

unsigned int lehmer::operator()() {
    state *= 0xda942042e4dd58b5;
    return state >> sizeof(unsigned int) * 2;
}

unsigned int lehmer::min() {
    return 0;
}

unsigned int lehmer::max() {
    return UINT_MAX;
}
