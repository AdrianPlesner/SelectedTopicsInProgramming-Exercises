//
// Created by Adrian Plesner on 01/03/2022.
//

#include "Visitor.h"
#include "calculator.hpp"
using namespace calculator;

double Evalutor::visit(const_t &obj) {
    return result = obj.getValue();
}

double Evalutor::visit(var_t &obj){
    return result = state[obj.get_id()];
}

double Evalutor::visit(unary_t &obj) {
    auto term = obj.getTerm();
    if(!term){
        throw logic_error("Missing operand for unary term");
    }
    switch(obj.getOperator()){
        case op_t::plus:
            return result = term->accept(*this);
        case op_t::minus:
            return result = -1 * term->accept(*this);
        default:
            throw logic_error("Invalid operator for unary term");
    }
}

double Evalutor::visit(binary_t& obj){
    auto term1 = obj.getTerm1();
    auto term2 = obj.getTerm2();
    if(!term1 || ! term2){
        throw logic_error("Missing operand");
    }
    switch (obj.getOperator()) {
        case op_t::add:
            return result = term1->accept(*this) + term2->accept(*this);
        case op_t::sub:
            return result = term1->accept(*this) - term2->accept(*this);
        case op_t::multiply:
            return result = term1->accept(*this) * term2->accept(*this);
        case op_t::divide:
            if(term2->accept(*this) == 0){
                throw logic_error("Division by zero, not allowed, mister.");
            }
            return result = term1->accept(*this) / term2->accept(*this);
        default:
            throw logic_error("Gibberish, invalid operator!");
    }
}