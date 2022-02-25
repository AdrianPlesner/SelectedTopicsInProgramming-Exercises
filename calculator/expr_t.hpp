//
// Created by adrian on 2/25/22.
//

#ifndef CALCULATOR_EXPR_T_HPP
#define CALCULATOR_EXPR_T_HPP
#include <memory>
#include "calculator.hpp"
#include "term_t.hpp"

using namespace std;

class expr_t {
public:
    shared_ptr<term_t> term;
    double operator()(calculator::state_t& s) const { return  (*term)(s);}
};

enum op_t { plus, minus, add, sub, assign, multiply, divide };

class const_t: term_t {
public:
    double value{};
private:
    double operator()(calculator::state_t&) const override {return value;}
};

class unary_t: term_t {
public:
    double operator()(calculator::state_t& s) const {
        if(!term){
            throw logic_error("Missing operand for unary term");
        }
        switch(op){
            case op_t::plus:
                return (*term)(s);
            case op_t::minus:
                return -(*term)(s);
            default:
                throw logic_error("Invalid operator for unary term");
        }
    }
private:
    shared_ptr<term_t> term;
    op_t op;
};

class binary_t: term_t {
private:
    shared_ptr<term_t> term1;
    shared_ptr<term_t> term2;
    op_t op;
public:
    double operator()(calculator::state_t& s) const override{
        if(!term1 || ! term2){
            throw logic_error("Missing operand");
        }
        auto &exp1 = *term1, &exp2 = *term2;
        switch (op) {
            case op_t::add:
                return exp1(s) + exp2(s);
            case op_t::sub:
                return exp1(s) - exp2(s);
            case op_t::multiply:
                return exp1(s) * exp2(s);
            case op_t::divide:
                if(exp2(s) == 0){
                    throw logic_error("Division by zero, not allowed, mister.");
                }
                return exp1(s) / exp2(s);
            default:
                throw logic_error("Gibberish, invalid operator!");
        }
    }
};

class var_t: term_t {
public:
    double operator()(calculator::state_t& s) const override{ return s[id];}
    var_t(const var_t&) = default;
    size_t get_id() const {return id;}
private:
    size_t id{};
};

class assign_t: term_t {
public:
    double operator()(calculator::state_t& s) const override{
        auto val = (*term)(s);
        s[var->get_id()] = val;
        return val;
    }
private:
    shared_ptr<var_t> var;
    shared_ptr<term_t> term;
    op_t op;


};

#endif //CALCULATOR_EXPR_T_HPP
