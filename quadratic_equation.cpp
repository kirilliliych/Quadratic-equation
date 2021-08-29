// -------------------------------------------------------
//! @brief QuadraticEquationSolver
//! @author kirilliliych (https://github.com/kirilliliych)
//! @file quadratic_equation.cpp
//! @date 2021-08-28
//! @copyright Copyright (c) 2021
// -------------------------------------------------------

#include "quadratic_equation.h"

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

void ReadCoeffs (double *first_coef, double *second_coef, double *third_coef)
{
    assert (first_coef  != nullptr);
    assert (second_coef != nullptr);
    assert (third_coef  != nullptr);

    printf ("Enter coefficient A in Ax^2+Bx+C formula: ");

    GetRightInput (first_coef);

    printf ("Enter coefficient B in Ax^2+Bx+C formula: ");

    GetRightInput (second_coef);

    printf ("Enter coefficient C in Ax^2+Bx+C formula: ");

    GetRightInput (third_coef);

}

void GetRightInput (double *coefficient)
{
    assert (coefficient != nullptr);

    while (scanf ("%lg", coefficient) != 1)
    {
        printf ("Invalid input. Please, enter a number!\n");

        while (getchar () != '\n');

    }
}

void TestSolveQuadraticEquation (double first_coef, double second_coef, double third_coef, int correct_number_of_roots,
                                 double correct_root_1, double correct_root_2, int number_of_test)
{
    assert (isfinite (first_coef));
    assert (isfinite (second_coef));
    assert (isfinite (third_coef));
    assert (isfinite (correct_root_1));
    assert (isfinite (correct_root_2));
    assert ((correct_number_of_roots >= INFINITE_NUMBER_OF_ROOTS) && (correct_number_of_roots < 3));

    if (correct_root_1 > correct_root_2)
    {
        Swap (&correct_root_1, &correct_root_2);
    }

    double root_1 = 0;
    double root_2 = 0;
    int number_of_roots = SolveQuadraticEquation (first_coef, second_coef, third_coef, &root_1, &root_2);

    if (root_1 > root_2)
    {
        Swap (&root_1, &root_2);
    }

    bool is_passed = true;

    if (correct_number_of_roots != number_of_roots)
    {
        is_passed = false;
    }

    else if ((correct_number_of_roots == 2) &&
            ((!IsEqual (correct_root_1, root_1)) || (!IsEqual (correct_root_2, root_2))))
    {
        is_passed = false;
    }

    else if ((correct_number_of_roots == 1) && (!IsEqual (correct_root_1, root_1)))
    {
        is_passed = false;
    }

    if (!is_passed)
    {
        printf ("Test %d failed line(%d)\n"
                "Input: A = %lg, B = %lg, C = %lg\n"
                "Output: number of roots = %d, root 1 = %lg, root 2 = %lg\n"
                "Output expected: number of roots = %d, root 1 = %lg, root 2 = %lg\n",
                number_of_test, __LINE__, first_coef, second_coef, third_coef, number_of_roots,
                root_1, root_2, correct_number_of_roots, correct_root_1, correct_root_2);
    }

    else
    {
        TEST_OK(number_of_test);
    }
}

int SolveQuadraticEquation (double first_coef, double second_coef, double third_coef,
                            double *ptr_first_root, double *ptr_second_root)
{
    assert (isfinite (first_coef));
    assert (isfinite (second_coef));
    assert (isfinite (third_coef));
    assert (ptr_first_root  != nullptr);
    assert (ptr_second_root != nullptr);

    if (IsEqualTo0 (first_coef))
    {
        return SolveLinearEquation (second_coef, third_coef, ptr_first_root);
    }

    else
    {
        double discriminant = second_coef * second_coef - 4 * first_coef * third_coef;

        if (IsEqualTo0 (discriminant))
        {
            *ptr_first_root = -second_coef / (2 * first_coef);

            return 1;
        }

        if (discriminant > PRECISION)
        {
            double discriminant_square_root = sqrt (discriminant);

            *ptr_first_root  = (-second_coef - discriminant_square_root) / (2 * first_coef);
            *ptr_second_root = (-second_coef + discriminant_square_root) / (2 * first_coef);

            return 2;
        }

        return 0;
    }
}

void TestSolveLinearEquation (double linear_coef, double constant_of_free_term, int correct_number_of_roots,
                              double correct_root, int number_of_test)
{
    assert (isfinite (linear_coef));
    assert (isfinite (constant_of_free_term));
    assert (isfinite (correct_root));
    assert ((correct_number_of_roots < 2) && (correct_number_of_roots >= INFINITE_NUMBER_OF_ROOTS));

    double root = 0;

    int number_of_roots = SolveLinearEquation (linear_coef, constant_of_free_term, &root);

    if ((correct_number_of_roots != number_of_roots) ||
       (!IsEqual (correct_root, root) && (correct_number_of_roots == 1)))
    {
        printf ("Test %d failed line(%d)\n"
                "Input: B = %lg, C = %lg\n"
                "Output: number of roots = %d, root = %lg\n"
                "Output expected: number of roots = %d, root = %lg\n",
                number_of_test, __LINE__, linear_coef, constant_of_free_term,
                number_of_roots, root, correct_number_of_roots, correct_root);
    }

    else
    {
        TEST_OK(number_of_test);
    }
}

int SolveLinearEquation (double linear_coef, double constant_of_free_term, double *ptr_root)
{
    assert (isfinite (linear_coef));
    assert (isfinite (constant_of_free_term));
    assert (ptr_root != nullptr);

    if (IsEqualTo0 (linear_coef))
    {
        if (IsEqualTo0 (constant_of_free_term))
        {
            return INFINITE_NUMBER_OF_ROOTS;
        }

        else
        {
            return 0;
        }
    }

    else
    {
        *ptr_root = -constant_of_free_term / linear_coef;

        return 1;
    }
}

void TestIsEqualTo0 (double value, bool correct_answer, int number_of_test)
{
    assert (isfinite (value));

    bool answer = IsEqualTo0 (value);

    if (correct_answer != answer)
    {
        printf ("Test %d failed line(%d)\n"
                "Input: value = %lg\n"
                "Output: %d\n"
                "Output expected: %d\n",
                number_of_test, __LINE__, value, answer, correct_answer);
    }

    else
    {
        TEST_OK(number_of_test);
    }
}

bool IsEqualTo0 (double value)
{
    assert (isfinite (value));

    return fabs (value) < PRECISION;
}

void PrintAnswer (int number_of_roots, double first_root, double second_root)
{
    assert (isfinite (first_root));
    assert (isfinite (second_root));

    switch (number_of_roots)
    {
        case 0:
            printf ("No solutions\n");

            break;

        case 1:
            printf ("%s %lg %s", "The only root: ", first_root, "\n");

            break;

        case 2:
            printf ("%s %lg %s %lg\n", "First root: ", first_root, "Second root: ", second_root);

            break;

        case INFINITE_NUMBER_OF_ROOTS:
            printf ("Infinity number of roots\n");

            break;

        default:
            printf ("%s %d\n", "Error, unknown value of number_of_roots: ", number_of_roots);

            break;

    }
}

void TestIsEqual (double value_1, double value_2, bool correct_answer, int number_of_test)
{
    assert (isfinite (value_1));
    assert (isfinite (value_2));

    bool answer = IsEqual (value_1, value_2);

    if (correct_answer != answer)
    {
        printf ("Test %d failed line(%d)\n"
                "Input: value_1 = %lg, value_2 = %lg\n"
                "Output: %d\n"
                "Output expected: %d\n",
                number_of_test, __LINE__, value_1, value_2, answer, correct_answer);
    }

    else
    {
        TEST_OK(number_of_test);
    }
}

bool IsEqual (double value_1, double value_2)
{
    assert (isfinite (value_1));
    assert (isfinite (value_1));

    return fabs(value_1 - value_2) < PRECISION;
}

void TestSwap (double value_1, double value_2, double correct_new_value_1, double correct_new_value_2, int number_of_test)
{
    assert (isfinite (value_1));
    assert (isfinite (value_2));
    assert (isfinite (correct_new_value_1));
    assert (isfinite (correct_new_value_2));

    double previous_value_1 = value_1;
    double previous_value_2 = value_2;

    Swap (&value_1, &value_2);

    if ((!IsEqual (value_1, correct_new_value_1)) || (!IsEqual (value_2, correct_new_value_2)))
    {
        printf ("Test %d failed line(%d)\n"
                "Input: value_1 = %lg, value_2 = %lg\n"
                "Output: new value_1 = %lg, new value_2 = %lg\n"
                "Output expected: new value_1 = %lg, new value_2 = %lg\n",
                number_of_test, __LINE__, previous_value_1, previous_value_2, value_1, value_2, correct_new_value_1, correct_new_value_2);
    }

    else
    {
        TEST_OK(number_of_test);
    }
}

void Swap (double *value_1, double *value_2)
{
    assert (value_1 != nullptr);
    assert (value_2 != nullptr);

    double temp = *value_1;

    *value_1 = *value_2;
    *value_2 = temp;
}

void TestAll ()
{
    int number_of_test = 1;

    printf ("Testing function SolveQuadraticEquation\n\n");

    struct TestDataForQuadraticEquation test_solve_quadratic_equation[9] = {{ 0,  0,  0, INFINITE_NUMBER_OF_ROOTS, 0, 0, number_of_test++},
                                                                            { 0,  0,  1, 0,  0, 0, number_of_test++},
                                                                            { 0,  1,  0, 1,  0, 0, number_of_test++},
                                                                            { 0,  1,  0, 1,  0, 0, number_of_test++},
                                                                            { 0,  1,  4, 1, -4, 0, number_of_test++},
                                                                            { 1,  2,  2, 0,  0, 0, number_of_test++},
                                                                            { 1,  2,  1, 1, -1, 0, number_of_test++},
                                                                            { 1, -4,  3, 2,  3, 1, number_of_test++},
                                                                            {-1,  2, -1, 1,  1, 0, number_of_test++}};

    for (int i = 0; i < number_of_test - 1; ++i)
    {
        TestSolveQuadraticEquation (test_solve_quadratic_equation[i].first_coef,
                                    test_solve_quadratic_equation[i].second_coef,
                                    test_solve_quadratic_equation[i].third_coef,
                                    test_solve_quadratic_equation[i].correct_number_of_roots,
                                    test_solve_quadratic_equation[i].correct_root_1,
                                    test_solve_quadratic_equation[i].correct_root_2,
                                    test_solve_quadratic_equation[i].number_of_test);
    }

    number_of_test = 1;

    printf ("\nTesting function SolveLinearEquation\n\n");

    struct TestDataForLinearEquation test_solve_linear_equation[4] = {{ 0, 0, INFINITE_NUMBER_OF_ROOTS, 0, number_of_test++},
                                                                      { 0, 1, 0,  0, number_of_test++},
                                                                      { 1, 3, 1, -3, number_of_test++},
                                                                      {-2, 4, 1,  2, number_of_test++}};

    for (int i = 0; i < number_of_test - 1; ++i)
    {
        TestSolveLinearEquation (test_solve_linear_equation[i].linear_coef,
                                 test_solve_linear_equation[i].constant_of_free_term,
                                 test_solve_linear_equation[i].correct_number_of_roots,
                                 test_solve_linear_equation[i].correct_root,
                                 test_solve_linear_equation[i].number_of_test);
    }

    number_of_test = 1;

    printf ("\nTesting function IsEqualTo0\n\n");

    struct TestDataForIsEqualTo0 tests_is_equal_to_0[3] = {{ 0.001,  0, number_of_test++},
                                                           {-0.0009, 1, number_of_test++},
                                                           {1.68,    0, number_of_test++}};

    for (int i = 0; i < number_of_test - 1; ++i)
    {
        TestIsEqualTo0 (tests_is_equal_to_0[i].value,
                        tests_is_equal_to_0[i].correct_answer,
                        tests_is_equal_to_0[i].number_of_test);
    }

    number_of_test = 1;

    printf ("\nTesting function IsEqual\n\n");

    struct TestDataForIsEqual tests_is_equal[3] = {{0.69, 0.69001, 1, number_of_test++},
                                                   { -10,       1, 0, number_of_test++},
                                                   {   1,      22, 0, number_of_test++}};

    for (int i = 0; i < number_of_test - 1; ++i)
    {
        TestIsEqual (tests_is_equal[i].value_1,
                     tests_is_equal[i].value_2,
                     tests_is_equal[i].correct_answer,
                     tests_is_equal[i].number_of_test);
    }

    number_of_test = 1;

    printf ("\nTesting function Swap\n\n");

    struct TestDataForSwap tests_swap[2] = {{3.14, 2.718, 2.718, 3.14, number_of_test++},
                                            {2.66, 3.512, 3.512, 2.66, number_of_test++}};

    for (int i = 0; i < number_of_test - 1; ++i)
    {
       TestSwap (tests_swap[i].value_1,
                 tests_swap[i].value_2,
                 tests_swap[i].correct_value_1,
                 tests_swap[i].correct_value_2,
                 tests_swap[i].number_of_test);
    }
}

