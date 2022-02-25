#ifndef INCLUDE_ALGEBRA_HPP
#define INCLUDE_ALGEBRA_HPP

#include <utility>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <stdexcept>

using namespace std;

namespace calculator
{
    /** Type to capture the state of entire calculator (one number per variable): */
    using state_t = std::vector<double>;


    class term_t {
    public:
        virtual double operator()(state_t&) const =0;
        virtual ~term_t() = default;
    };
    enum op_t { plus, minus, add, sub, assign, multiply, divide };

    class const_t: public term_t {
    public:
        double value{};
        const_t(double d){
            value = d;
        }
        ~const_t() override = default;
    private:
        double operator()(state_t&) const override {return value;}
    };

    class unary_t: public term_t {
    public:
        unary_t(const shared_ptr<term_t>& a, op_t opr){
            term = a;
            op = opr;
        }
        double operator()(state_t& s) const override {
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
        ~unary_t() override = default;
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
        double operator()(state_t& s) const override{
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
        assign_t(const var_t& a, const shared_ptr<term_t>& b){
            var = make_shared<var_t>(a);
            term = b;
            op = op_t::plus;
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
        expr_t(const var_t& v, const expr_t& e){
            term = dynamic_pointer_cast<term_t>(make_shared<assign_t>(v, e.term));
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
    inline expr_t operator<<=(const var_t& v, const expr_t& e) { return expr_t{v, e}; }
}

#endif // INCLUDE_ALGEBRA_HPP

