//
// Created by adrian on 2/18/22.
//

#include "NumberSeries.h"
#include <vector>
#include <random>
#include <array>
#include <iostream>

using namespace std;

// Adds a method to the NumberSeries class, it takes a vector of type int (cannot be changed)
// The method iterates through every number, and finds the maxvalue og minvalue.
NumberSeries::NumberSeries(const vector<int>& input) {
    values = input;
    minVal = values[0];
    maxVal = values[0];
    for(const auto& v : values){
        minVal = min(minVal, v);
        maxVal = max(maxVal, v);
    }

}

// Adds a method to the NumberSeries class, it takes a vector of type int
// The method makes a random distribution of
NumberSeries NumberSeries::MakeRandom(int length) {
    random_device rd;
    auto engine = default_random_engine{rd()};
    auto dist = uniform_int_distribution<> {};
    vector<int> numbers(length);
    for(auto& v: numbers){
        v = dist(engine);
    }
    return NumberSeries(numbers);
}

// Overloads the << operator for the NumberSeries class
// It now prints all the numbers, inside two "[" "]" brackets, as well as the maximum and minimum values.
ostream &operator<<(ostream& os, const NumberSeries& n) {
    cout << "[";
    for(const auto& v: n.values){
        cout << v << ", ";
    }
    cout << "]" << endl;
    cout << "Min: " << n.minVal << " Max: " << n.maxVal << endl;
    return os;
}

// Overloads the += operator for the NumberSeries class
// It now compares the size with the other object, if the other object has a larger amount of values, it resizes the value vector to be able to house more numbers.
// Then it adds each of the number of the other object, to the corresponding number in the value attribute.
//Question: Hvorfor "NumberSeries &NumberSeries::operator" og ikke bare "NumberSeries operator+="
NumberSeries &NumberSeries::operator+=(const NumberSeries& other) {
    if(other.values.size() > values.size()){
        //Question: When the value attribute is resized, what are the new values of the vector initialized to? Are they even initialized?
        values.resize(other.values.size());
    }
    transform(values.begin(), values.end(), other.values.begin(), values.begin(), plus<>{});
    return *this;
}

int NumberSeries::amp() const {
    return maxVal - minVal;
}

// Overloads the + operator for the NumberSeries class
// Uses the += operator (overloaded)
NumberSeries operator+(const NumberSeries& a, const NumberSeries& b){
    return NumberSeries{a} += b;
}

//Overloads the < operator in the NumberSeries class
// returns a boolean that compares the max and min value of each of the objects.
bool NumberSeries::operator<(const NumberSeries& other){
    return (maxVal - minVal) < (other.maxVal - other.minVal);
}
