//
// Created by adrian on 2/25/22.
//

#ifndef CALCULATOR_TERM_T_HPP
#define CALCULATOR_TERM_T_HPP
#include "calculator.hpp"
#include "term_t.hpp"

class term_t {
    public:
        virtual double operator()(calculator::state_t&) const =0;
        virtual ~term_t();
};


#endif //CALCULATOR_TERM_T_HPP
