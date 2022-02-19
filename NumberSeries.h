//
// Created by adrian on 2/18/22.
//
#include <vector>
#include <ostream>

using namespace std;
#ifndef STP_NUMBERSERIES_H
#define STP_NUMBERSERIES_H


class NumberSeries {
private:
    vector<int> values{};
    int minVal{}, maxVal{};
    int averages[12];
public:
    NumberSeries() = default;
    //Explicit gør at...
    explicit NumberSeries(const vector<int>&);
    NumberSeries(const NumberSeries&) = default;
    // Overloads assignment operator
    NumberSeries &operator=(const NumberSeries& other) = default;
    // Destructor, set to default
    ~NumberSeries() = default;
    // Introduces a static method, that takes an int as input
    static NumberSeries MakeRandom(int);
    //Gives ostream access to the private  attributes
    friend ostream& operator<<(ostream&, const NumberSeries&);
    // Overloads += operatoren
    NumberSeries& operator+=(const NumberSeries&);
    //Overloads the < operator
    bool operator<(const NumberSeries&);
    // Ved ikke helt hvad [[nodiscard]] delen gør, eller hvorfor const står til sidst.
    [[nodiscard]] int amp() const;
};


#endif //STP_NUMBERSERIES_H
