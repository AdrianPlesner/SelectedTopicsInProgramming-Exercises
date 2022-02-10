//
// Created by Bruger on 08-02-2022.
//
#include <iostream>
#include <string>
#include <cfloat>
#include <bitset>
#include <cmath>
#include <random>
#include <array>
#include "benchmark.h"
#include "lehmer.h"

using namespace std;
using namespace std::chrono;

void size_print(const string& name, int size, const string& min, const string& max, int tabs = 3){
    cout << "The size of " << name << " is " << size << " byte(s).";
    for(int i = 0; i < tabs;i++){
        cout << "\t";
    }
    cout << "Value range is "<< min << " <-> " << max << endl;
}

void ex2_1(){
    cout << "Exercise 2.1" << endl;
    size_print("bool", sizeof(bool), "0", "1");
    size_print("char", sizeof(char), to_string(CHAR_MIN), to_string(CHAR_MAX));
    size_print("unsigned char", sizeof(unsigned char), "0", to_string(UCHAR_MAX), 2);
    size_print("short", sizeof(short), to_string(SHRT_MIN), to_string(SHRT_MAX));
    size_print("unsigned short", sizeof(unsigned short), "0", to_string(USHRT_MAX), 1);
    size_print("int", sizeof(int), to_string(INT_MIN), to_string(INT_MAX));
    size_print("unsigned int", sizeof(unsigned int), "0", to_string(UINT_MAX), 2);
    size_print("long", sizeof(long), to_string(LONG_MIN), to_string(LONG_MAX));
    size_print("unsigned long", sizeof(unsigned long), "0", to_string(ULONG_MAX), 2);
    size_print("long long", sizeof(long long), to_string(LONG_LONG_MIN), to_string(LONG_LONG_MAX), 2);
    size_print("unsigned long long", sizeof(unsigned long long), "0", to_string(ULONG_LONG_MAX), 1);
    size_print("float", sizeof(float), "10^" + to_string(FLT_MIN_10_EXP), "10^" + to_string(FLT_MAX_10_EXP));
    size_print("double", sizeof(double), "10^" + to_string(DBL_MIN_10_EXP), "10^" +to_string(DBL_MAX_10_EXP), 2);
    size_print("long double", sizeof(long double), "10^" + to_string(LDBL_MIN_10_EXP), "10^" +to_string(LDBL_MAX_10_EXP), 2);

}

void ex2_2(){
    union mem_fuck{
        float f;
        unsigned int i;
        char c[4];
    };
    cout << "\n\n\nExercise 2.2" << endl;
    mem_fuck a{};
    a.i = 16;
    cout << "When i is " << a.i << " with bit pattern: " + bitset<32>(a.i).to_string() << " c is:[" << a.c[0] << "," << a.c[1] << "," << a.c[2] << "," << a.c[3] << "]" << endl;
    a.f = 1;
    cout << "When f is 1" << " with bit pattern: " + bitset<32>(a.i).to_string() << " i is: " << a.i << endl;
    a.f = 2;
    cout << "When f is 2" << " with bit pattern: " + bitset<32>(a.i).to_string() << " i is: " << a.i << endl;
    a.f = 4;
    cout << "When f is 4" << " with bit pattern: " + bitset<32>(a.i).to_string() << " i is: " << a.i << endl;
    a.f = 8;
    cout << "When f is 8" << " with bit pattern: " + bitset<32>(a.i).to_string() << " i is: " << a.i << endl;
}

// exercise 2_3:
double* max(double *a, double *b){
    return *a < *b ? b : a;
}

double& max(double &a, double &b){
    return a < b ? b : a;
}

const double& max(const double &a, const double &b){
    return a < b ? b : a;
}

// You cannot!
/*double* max(double &*a, double &*b){
    return *a < *b ? a : b;
}*/

double* max(double *&a, double *&b){
    return *a < *b ? b: a;
}

const double* max(const double *&a, const double *&b){
    return *a < *b ? b : a;
}

void ex2_4(){
    benchmark b {};
    b.mark();
    int a {0};
    b.mark();
    a++;
    b.mark();
    int* c = &a;
    b.mark();
    *c +=1;
    b.mark();
    cout << a;
    b.mark();
    b.report();
}

void ex2_5(){
    benchmark b {};
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> mt_dis(0, 1000);
    lehmer leh {};
    uniform_real_distribution<> lh_dis(0,1000);
    const int size = 10000000;
    array<int, size> mt {};
    array<int, size> lh {};
    b.mark();
    for(int i = 0; i < size; i++){
        mt[i] = mt_dis(gen);
    }
    b.mark();
    for(int i = 0; i < size; i++){
        mt[i] = lh_dis(leh);
    }
    b.mark();
    b.report();
}

int main(){
    //ex2_1();
    //ex2_2();
    //ex2_4();
    ex2_5();
    return 0;
}

