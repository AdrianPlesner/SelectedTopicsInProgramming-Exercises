//
// Created by Bruger on 08-02-2022.
//

#include "benchmark.h"
#include <chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;

void benchmark::mark() {
    auto t = high_resolution_clock::now();
    times.insert(times.end(), t);
}

void benchmark::report(){
    for(int i = 1; i < times.size(); i++){
        auto t = duration<double, milli>(times[i]-times[i-1]).count();
        cout << "Duration " << i << ": " << t << "ms" << endl;
    }
}

benchmark::benchmark() {
    times = {};
}
