#ifndef INCLUDE_ALGEBRA_HPP
#define INCLUDE_ALGEBRA_HPP

#include <utility>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <stdexcept>
#include "Visitor.h"

using namespace std;

namespace calculator
{
    /** Type to capture the state of entire calculator (one number per variable): */
    using state_t = std::vector<double>;

    class term_t {
    public:
        virtual double operator()(state_t&) const =0;
        virtual ~term_t() = default;
        virtual void accept(Visitor&)=0;
    };
    enum op_t { plus, minus, add, sub, assign, multiply, divide, add_assign };

    class const_t: public term_t {
    public:
        double value{};
        const_t(double d){
            value = d;
        }
        double getValue() const {return value;}
        ~const_t() override = default;
        void accept(Visitor& v) override{
            v.visit(*this);
        }
    };

    class unary_t: public term_t {
    public:
        unary_t(const shared_ptr<term_t>& a, op_t opr){
            term = a;
            op = opr;
        }
        const op_t getOperator() {return op;}
        ~unary_t() override = default;
        void accept(Visitor& v) override {v.accept(*this);}
        const shared_ptr<term_t> getTerm(){return term;}
    private:
        shared_ptr<term_t> term;
        op_t op;
    };

    class binary_t: public term_t {
    private:
        shared_ptr<term_t> term1;
        shared_ptr<term_t> term2;
        op_t op;
    public:
        // Constructor for binary_t which allows
        binary_t(const shared_ptr<term_t>& a, const shared_ptr<term_t>& b, op_t opr){
            term1 = a;
            term2 = b;
            op = opr;
        }
        void accept(Visitor& v) override {v.visit(*this);}
        const op_t getOperator(){return opr;}
        const shared_ptr<term_t> getTerm1(){return term1;}
        const shared_ptr<term_t> getTerm2(){return term2;}
        ~binary_t() override = default;
    };

    class var_t: public term_t {
    public:
        double operator()(state_t& s) const override{ return s[id];}
        var_t(const var_t&) = default;
        explicit var_t(size_t id): id{id} {}
        size_t get_id() const {return id;}
        ~var_t() override = default;
    private:
        size_t id{};
    };

    class assign_t: public term_t {
    public:
        assign_t(const var_t& a, const shared_ptr<term_t>& b, op_t opr){
            var = make_shared<var_t>(a);
            term = b;
            op = opr;
        }
        double operator()(state_t& s) const override{
            auto val = (*term)(s);
            s[var->get_id()] = val;
            return val;
        }
        ~assign_t() override = default;
    private:
        shared_ptr<var_t> var;
        shared_ptr<term_t> term;
        op_t op;


    };

    class expr_t {
    public:
        shared_ptr<term_t> term;
        double operator()(state_t& s) const { return  (*term)(s);}
        expr_t(const expr_t& e){
            term = e.term;
        }
        expr_t(const var_t& v){
            term = dynamic_pointer_cast<term_t>(make_shared<var_t>(v));
        }
        expr_t(const expr_t& a, const expr_t& b, op_t op){
            term = dynamic_pointer_cast<term_t>( make_shared<binary_t>(a.term, b.term, op));
        }
        expr_t(const expr_t& expr, op_t op){
            term = dynamic_pointer_cast<term_t>(make_shared<unary_t>(expr.term, op));
        }
        expr_t(const var_t& v, const expr_t& e, op_t op){
            term = dynamic_pointer_cast<term_t>(make_shared<assign_t>(v, e.term, op));
        }
        expr_t(const double& d){
            term = dynamic_pointer_cast<term_t>(make_shared<const_t>(d));
        }
        ~expr_t() = default;
    };

    class symbol_table_t
    {
        std::vector<std::string> names;
        std::vector<double> initial;
    public:
        [[nodiscard]] var_t var(std::string name, double init = 0) {
            auto res = names.size();
            names.push_back(std::move(name));
            initial.push_back(init);
            return var_t{res};
        }
        [[nodiscard]] state_t state() const { return {initial}; }
    };

    /** assignment operation */
    //inline double var_t::operator()(state_t& s, const expr_t& e) const { return s[id] = e(s); }

    /** unary operators: */
    inline expr_t operator+(const expr_t& e) { return expr_t{e, plus}; }
    inline expr_t operator-(const expr_t& e) { return expr_t{e, minus}; }

    /** binary operators: */
    inline expr_t operator+(const expr_t& e1, const expr_t& e2) { return expr_t{e1, e2, add}; }
    inline expr_t operator-(const expr_t& e1, const expr_t& e2) { return expr_t{e1, e2, sub}; }
    inline expr_t operator*(const expr_t& e1, const expr_t& e2) { return expr_t{e1, e2, multiply}; }
    inline expr_t operator/(const expr_t& e1, const expr_t& e2) { return expr_t{e1, e2, divide}; }
    inline expr_t operator<<=(const var_t& v, const expr_t& e) { return expr_t{v, e, assign}; }
    inline expr_t operator+=(const var_t& v, const expr_t& e) { return expr_t{v, expr_t{expr_t{v}, e, add}, assign};}
    inline expr_t operator-=(const var_t& v, const expr_t& e) { return expr_t{v, expr_t{expr_t{v}, e, sub}, assign};}
    inline expr_t operator*=(const var_t& v, const expr_t& e) { return expr_t{v, expr_t{expr_t{v}, e, multiply}, assign};}
    inline expr_t operator/=(const var_t& v, const expr_t& e) { return expr_t{v, expr_t{expr_t{v}, e, divide}, assign};}


}

#endif // INCLUDE_ALGEBRA_HPP

