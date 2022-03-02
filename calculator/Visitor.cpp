//
// Created by Adrian Plesner on 01/03/2022.
//

#include "Visitor.h"

#include <utility>
#include "calculator.hpp"
using namespace calculator;

double Evalutor::visit(const_t &obj) {
    return obj.getValue();
}

Evalutor::Evalutor(vector<double> s) {
    state = std::move(s);
}

double Evalutor::visit(var_t &obj){
    return state[obj.get_id()];
}

double Evalutor::visit(binary_t& obj) {
    auto term1 = obj.getTerm1();
    auto term2 = obj.getTerm2();
    if(!term1 || ! term2){
        throw logic_error("Missing operand");
    }
    switch (obj.getOperator()) {
        case op_t::add:
            return term1->accept(*this) + term2->accept(*this);
        case op_t::sub:
            return term1->accept(*this) - term2->accept(*this);
        case op_t::multiply:
            return term1->accept(*this) * term2->accept(*this);
        case op_t::divide:
            if(term2->accept(*this) == 0){
                throw logic_error("Division by zero, not allowed, mister.");
            }
            return term1->accept(*this) / term2->accept(*this);
        default:
            throw logic_error("Gibberish, invalid operator!");
    }
}

double Evalutor::visit(unary_t &obj) {
    auto term = obj.getTerm();
    if(!term){
        throw logic_error("Missing operand for unary term");
    }
    switch(obj.getOperator()){
        case op_t::plus:
            return term->accept(*this);
        case op_t::minus:
            return -1 * term->accept(*this);
        default:
            throw logic_error("Invalid operator for unary term");
    }
}

double Evalutor::visit(assign_t &obj) {
    auto term = obj.getTerm();
    auto var = obj.getVar();
    auto val = term->accept(*this);
    state[var->get_id()] = val;
    return val;
}

