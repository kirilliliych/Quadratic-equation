// -------------------------------------------------------
//! @file main.cpp
//! @brief Main function.
//! @author kirilliliych (https://github.com/kirilliliych)
//! @date 2021-08-29
//! @copyright Copyright (c) 2021
// -------------------------------------------------------

#include "quadratic_equation.h"
#include "testing.h"
#include "quadratic_equation.cpp"
#include "testing.cpp"

int main ()
{
    #ifdef TEST_MODE_ACTIVATED
        printf ("\t\t\tTesting program\n");

        TestAll ();

        return 0;
    #endif

    printf ("\t\t\t///// QuadraticEquationSolver /////\n");
    printf ("\t\t\t\t(c) kirilliliych, 2021\n\n");

    double a = 0;
    double b = 0;
    double c = 0;

    ReadCoeffs (&a, &b, &c);

    double first_root  = 0;
    double second_root = 0;

    int number_of_roots = SolveQuadraticEquation (a, b, c, &first_root, &second_root);

    PrintAnswer (number_of_roots, first_root, second_root);

    return 0;
}
