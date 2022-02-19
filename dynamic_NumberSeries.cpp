//
// Created by adrian on 2/18/22.
//

#include "dynamic_NumberSeries.h"
#include <memory>
#include <vector>
#include <memory>
#include <random>

using namespace std;

dynamic_NumberSeries::dynamic_NumberSeries(vector<int> & vec) {
    ptr = make_unique<NumberSeries>(vec);

}

dynamic_NumberSeries &dynamic_NumberSeries::operator=(dynamic_NumberSeries && other)  noexcept {
    ptr = move(other.ptr);
    return *this;
}

dynamic_NumberSeries& dynamic_NumberSeries::operator=(const dynamic_NumberSeries &other) {
    ptr = make_unique<NumberSeries>(*other.ptr);
    return *this;
}

dynamic_NumberSeries::dynamic_NumberSeries(const NumberSeries& other) {
    ptr = make_unique<NumberSeries>(other);
}

dynamic_NumberSeries dynamic_NumberSeries::MakeRandom(int n) {
    random_device rd;
    auto engine = default_random_engine{rd()};
    auto dist = uniform_int_distribution<> {};
    vector<int> numbers(n);
    for(auto& v: numbers){
        v = dist(engine);
    }
    return dynamic_NumberSeries(numbers);
}

dynamic_NumberSeries &dynamic_NumberSeries::operator+=(const dynamic_NumberSeries & other) {
    ptr->operator+=(*other.ptr);
    return *this;
}

dynamic_NumberSeries dynamic_NumberSeries::operator+(const dynamic_NumberSeries& other){
    auto result = *ptr;
    result += *other.ptr;
    return dynamic_NumberSeries(result);
}

bool dynamic_NumberSeries::operator<(const dynamic_NumberSeries& other){
    return (ptr->amp()) < (other.ptr->amp());
}

dynamic_NumberSeries::dynamic_NumberSeries() {
    ptr = nullptr;
}

dynamic_NumberSeries::dynamic_NumberSeries(const dynamic_NumberSeries &other) {
    ptr = make_unique<NumberSeries>(*other.ptr);
}
