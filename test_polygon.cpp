#include "polygon.hpp"
#include <iostream>
#include <vector>

/**
 * Code to test the understanding of special member functions and references.
 * @author Marius Mikucionis <marius@cs.aau.dk>
 */

polygon polygon_factory(size_t count){ return polygon(count); }

void draw_value(polygon) { std::cout << "passed-by-value\n"; }
void draw(const polygon&) { std::cout << "passed-by-const-reference\n"; }
void draw(polygon&) { std::cout << "passed-by-lvalue-reference\n"; }
void draw(polygon&&) { std::cout << "passed-by-rvalue-reference\n"; }

int main()
{
    std::string ruler(40, '-');
    // TODO: Replace "???" with your predictions: what gets printed after each line?
    //       Note that some statements may print more than one line.
    // TODO: After all "???" are gone, step through the program in debugger and check your answers against output.
    // TODO: Answer the additional questions below.
    {   // for example:
        std::cout << ruler << std::endl;
        polygon poly;
        // default-constructor
        // destructor
    }
    {
        std::cout << ruler << std::endl;
        polygon poly(1);
        // custom-constructor(1)
        // destructor
    }
    {
        std::cout << ruler << std::endl;
        polygon poly = 1;
        // custom-constructor(1)
        // destructor
    }
    {
        std::cout << ruler << std::endl;
        const polygon poly0;
        // default constructor

        std::cout << ruler << std::endl;
        polygon poly1 = poly0;
        // copy-constructor

        std::cout << ruler << std::endl;
        polygon poly2 = polygon(2);
        // custom-constructor(2)

        std::cout << ruler << std::endl;
        polygon poly3{{1,2},{3,4},{5,6},{7,8}};
        // custom-constructor{{1,2},{3,4},{5,6},{7,8}}

        std::cout << ruler << std::endl;
        poly2 = poly1;
        // copy-assignment

        std::cout << ruler << std::endl;
        poly2 = polygon_factory(3);
        // custom-constructor(3)
        // move-assignment
        // destructor

        std::cout << ruler << std::endl;
        draw_value(poly0);
        // copy-constructor
        // passed-by-value
        // destructor

        std::cout << ruler << std::endl;
        draw(poly0);
        // passed-by-const-reference

        std::cout << ruler << std::endl;
        draw(poly1);
        // passed-by-lvalue-reference

        std::cout << ruler << std::endl;
        draw(polygon_factory(4));
        // custom-constructor(4)
        // passed-by-rvalue-reference
        // destructor

        std::cout << ruler << std::endl;
        std::vector<polygon> polies(4, poly3);
        // copy-constructor x4

        std::cout << ruler << std::endl;
        polies.push_back(poly3);
        // copy-constructor
        // something something move
        // TODO: Why are so many operations here?

        std::cout << ruler << std::endl;
        polies.push_back(poly3);
        // copy-constructor
        // TODO: Why is the number of operations fewer here than for the above one?
        // Dunno man måske allocater den mere end vi skal bruge /shrug

        std::cout << ruler << std::endl;
        for (polygon p : polies)
            std::cout << p << " at " << &p << '\n';
        // copy-constructor
        // print statement
        // destructor
        // x6
        // TODO: Can we make the loop above more efficient? Yes, use reference &


        // destructor x9
    }
    {
        std::cout << ruler << std::endl;
        //draw(1);
        // custom-constructor, passed-by-rvalue-reference, destructor
        // No more
    }
    {
        std::cout << ruler << std::endl;
        polygon poly = polygon(2);
        std::cout << poly << " at " << &poly << std::endl;
        draw_value(std::move(poly));
        // TODO: ???
        std::cout << poly << " at " << &poly << std::endl;
        // TODO: What was inside poly before draw_value call?
        // TODO: What is inside poly after draw_value call? Why?
    }
    {
        std::cout << ruler << std::endl;
        polygon poly = polygon(2);
        std::cout << poly << " at " << &poly << std::endl;
        draw(std::move(poly));
        // TODO: ???
        std::cout << poly << " at " << &poly << std::endl;
        // TODO: What was inside poly before draw call?
        // TODO: What is inside poly after draw call? Why?
    }
    std::cout << ruler << ruler << std::endl;
}
