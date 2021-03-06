//
// Created by Adrian Plesner on 01/03/2022.
//


#ifndef CALCULATOR_VISITOR_H
#define CALCULATOR_VISITOR_H
#include "calculator.hpp"
#include <vector>

class Visitor {
    virtual void visit(const_t&) = 0;
    virtual void visit(var_t&) = 0;
    virtual void visit(assign_t&) = 0;
    virtual void visit(unary_t&) = 0;
    virtual void visit(binary_t&) = 0;
};

class Evalutor : public Visitor {
public:
    Evalutor(const Evalutor&) = delete;

    Evalutor(vector<double> vector1);

    double visit(const_t&) override;
    double visit(var_t&) override;
    double visit(assign_t&) override;
    double visit(unary_t&) override;
    double visit(binary_t&) override;
private:
    state_t state;

};

class Printer : public Visitor {
    void visit(const_t&) override;
    void visit(var_t&) override;
    void visit(assign_t&) override;
    void visit(unary_t&) override;
};


#endif //CALCULATOR_VISITOR_H
