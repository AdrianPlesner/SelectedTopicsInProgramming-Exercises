//
// Created by adrian on 2/22/22.
//
#include "Base.h"
#include "Derived.h"
#include <vector>
#include <memory>
#include "benchmark.h"

using namespace std;

int main(){
    unsigned int size{10000000};
    benchmark b{};
    vector<unique_ptr<Base>> vec(size);
    vector<Derived> newVec{size, Derived{}};
    for(auto& p: vec){
        p = make_unique<Derived>();
    }
    b.mark();
    for(auto& p : vec){
        p->increment();
    }
    b.mark();
    for(auto& p: vec){
        p->decrement();
    }
    b.mark();



    for(auto& p : newVec){
        p.increment();
    }
    b.mark();
    for(auto& p: newVec){
        p.decrement();
    }
    b.mark();
    b.report();
    return 0;
}
