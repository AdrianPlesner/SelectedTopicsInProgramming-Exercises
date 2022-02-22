//
// Created by adrian on 2/18/22.
//
#include "NumberSeries.h"
#include <memory>
#ifndef STP_DYNAMIC_NUMBERSERIES_H
#define STP_DYNAMIC_NUMBERSERIES_H

using namespace std;
class dynamic_NumberSeries {
private:
    unique_ptr<NumberSeries> ptr;
public:
    //Constructor, see implementation
    dynamic_NumberSeries();
    explicit dynamic_NumberSeries(vector<int>&);
    dynamic_NumberSeries(const dynamic_NumberSeries&);
    explicit dynamic_NumberSeries(const NumberSeries&);
    dynamic_NumberSeries& operator=(const dynamic_NumberSeries&);
    dynamic_NumberSeries& operator=(dynamic_NumberSeries&&) noexcept;
    // Destructor, set to default
    ~dynamic_NumberSeries() = default;
    static dynamic_NumberSeries MakeRandom(int);
    dynamic_NumberSeries& operator+=(const dynamic_NumberSeries& );
    dynamic_NumberSeries operator+(const dynamic_NumberSeries&);
    bool operator<(const dynamic_NumberSeries&);
};


#endif //STP_DYNAMIC_NUMBERSERIES_H
