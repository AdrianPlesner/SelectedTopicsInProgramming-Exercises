//
// Created by Bruger on 08-02-2022.
//

#ifndef STP_BENCHMARK_H
#define STP_BENCHMARK_H
#include <chrono>
#include <vector>
using namespace std;
using namespace std::chrono;

class benchmark{
public:
    void mark();
    void report();
    benchmark();
private:
    vector<typeof(high_resolution_clock::now())> times;
};


#endif //STP_BENCHMARK_H
