// -------------------------------------------------------
//! @brief QuadraticEquationSolver
//! @author kirilliliych (https://github.com/kirilliliych)
//! @file quadratic_equation.cpp
//! @date 2021-08-28
//! @copyright Copyright (c) 2021
// -------------------------------------------------------

#include <assert.h>
#include <math.h>
#include <stdio.h>

#define TEST_OK(number) printf ("Test %d passed\n", number)
#define TEST_MODE_ACTIVATED

const int INFINITE_NUMBER_OF_ROOTS = -1;                                                                                                                                             // signals about infinite number of roots
const double PRECISION = 0.001;                                                                                                                                                      // a precision of comparison double to 0 and double to double

void TestAll                    ();

void ReadCoeffs                 (double *first_coef, double *second_coef, double *third_coef);

void GetRightInput              (double *coefficient);

void TestSolveQuadraticEquation (double first_coef, double second_coef, double third_coef, int correct_number_of_roots,
                                 double correct_root_1, double correct_root_2, int number);

int  SolveQuadraticEquation     (double first_coef, double second_coef, double third_coef, double *ptr_first_root,
                                 double *ptr_second_root);

void TestSolveLinearEquation    (double linear_coef, double constant_of_free_term, int correct_number_of_roots,
                                 double correct_root, int number);
int  SolveLinearEquation        (double linear_coef, double constant_of_free_term, double *ptr_root);


void TestIsEqualTo0             (double value, bool correct_answer, int number);
bool IsEqualTo0                 (double value);

void PrintAnswer                (int num_roots, double first_root, double second_root);


void TestIsEqual                (double value_1, double value_2, bool correct_answer, int number);
bool IsEqual                    (double value_1, double value_2);


void TestSwap                   (double value_1, double value_2, double correct_new_value_1,
                                 double correct_new_value_2, int number);
void Swap                       (double *value_1, double *value_2);

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

    int num_roots = SolveQuadraticEquation (a, b, c, &first_root, &second_root);

    PrintAnswer (num_roots, first_root, second_root);
    return 0;
}

/** @brief Inputs coefficients.
 *
 *  @param [out] *first_coef  pointer to coefficient A
 *  @param [out] *second_coef pointer to coefficient B
 *  @param [out] *third_coef  pointer to coefficient C
 */
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

/** @brief Tries to read coefficient until it is correctly input (a real number).
 *
 *  @param [out] *coefficient pointer to coefficient (A, B or C)
 *
 */
void GetRightInput (double *coefficient)
{
    assert (coefficient != nullptr);

    while (scanf ("%lg", coefficient) == 0)
    {
        printf ("Invalid input. Please, enter a number!\n");

        while (getchar () != '\n');

    }
}

void TestSolveQuadraticEquation (double first_coef, double second_coef, double third_coef, int correct_number_of_roots,
                                 double correct_root_1, double correct_root_2, int number)
{
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
                number, __LINE__, first_coef, second_coef, third_coef, number_of_roots,
                root_1, root_2, correct_number_of_roots, correct_root_1, correct_root_2);
    }

    else
    {
        TEST_OK(number);
    }
}

/** @brief Solves quadratic equation.
 *
 *  @param [in]  first_coef  coefficient A
 *  @param [in]  second_coef coefficient B
 *  @param [in]  third_coef  coefficient C
 *  @param [out] *ptr_first_root  pointer to first root
 *  @param [out] *ptr_second_root pointer to second root
 *
 *  @return number of roots.
 *
 *  @note If there is infinite number of roots, returns INFINITE_NUMBER_OF_ROOTS.
 *  If there is only one root, puts it to *ptr_first_root.
 *  Does not put any roots to *ptr_first_root and *ptr_second_root if roots are absent/infinite number of them.
 */
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

        if (discriminant > 0)
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
                              double correct_root, int number)
{
    assert (isfinite (linear_coef));
    assert (isfinite (constant_of_free_term));
    assert (isfinite (correct_root));

    double root = 0;

    int number_of_roots = SolveLinearEquation (linear_coef, constant_of_free_term, &root);

    if ((correct_number_of_roots != number_of_roots) ||
       (!IsEqual (correct_root, root) && (correct_number_of_roots == 1)))
    {
        printf ("Test %d failed line(%d)\n"
                "Input: B = %lg, C = %lg\n"
                "Output: number of roots = %d, root = %lg\n"
                "Output expected: number of roots = %d, root = %lg\n",
                number, __LINE__, linear_coef, constant_of_free_term,
                number_of_roots, root, correct_number_of_roots, correct_root);
    }

    else
    {
        TEST_OK(number);
    }
}

/** @brief Solves linear equation.
 *
 *  @param [in]  linear_coef coefficient B
 *  @param [in]  constant_of_free_term  coefficient C
 *  @param [out] *ptr_root pointer to root
 *
 *  @return number of roots.
 *
 *  @note If there is infinite number of roots, returns INFINITE_NUMBER_OF_ROOTS.
 *  Does not put a to *ptr_root if it is absent/infinite number of them.
 */
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

void TestIsEqualTo0 (double value, bool correct_answer, int number)
{
    bool answer = IsEqualTo0 (value);

    if (correct_answer != answer)
    {
        printf ("Test %d failed line(%d)\n"
                "Input: value = %lg\n"
                "Output: %d\n"
                "Output expected: %d\n",
                number, __LINE__, value, answer, correct_answer);
    }

    else
    {
        TEST_OK(number);
    }
}

/** @brief Decides if double variable equal to 0 (with 0.001 precision).
 *
 *  @param [in] value value of double variable
 *
 *  @return Whether the fact that the variable is equal to 0 (with 0.001 precision) correct or not.
 *
 */
bool IsEqualTo0 (double value)
{
    assert (isfinite (value));

    return fabs (value) < PRECISION;
}

/** @brief Prints answer.
 *
 *  @param [in] num_roots number of roots
 *  @param [in] first_root  first root
 *  @param [in] second_root second root
 *
 *  @note Number of printed roots depends of num_roots.
 *
 */
void PrintAnswer (int num_roots, double first_root, double second_root)
{
    assert (isfinite (first_root));
    assert (isfinite (second_root));
    assert (isfinite (num_roots));

    switch (num_roots)
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
            printf ("%s %d\n", "Error, unknown value of num_roots: ", num_roots);

            break;

    }
}

void TestIsEqual (double value_1, double value_2, bool correct_answer, int number)
{
    bool answer = IsEqual (value_1, value_2);

    if (correct_answer != answer)
    {
        printf ("Test %d failed line(%d)\n"
                "Input: value_1 = %lg, value_2 = %lg\n"
                "Output: %d\n"
                "Output expected: %d\n",
                number, __LINE__, value_1, value_2, answer, correct_answer);
    }

    else
    {
        TEST_OK(number);
    }
}

 /** @brief Decides if two double variables are equal (with 0.001 precision).
  *
  *  @param [in] value_1 first  double variable
  *  @param [in] value_2 second double variable
  *
  *  @return Whether the fact that two variables are equal (with 0.001 precision) correct or not.
  *
  */
bool IsEqual (double value_1, double value_2)
{
    return fabs(value_1 - value_2) < PRECISION;
}

void TestSwap (double value_1, double value_2, double correct_new_value_1, double correct_new_value_2, int number)
{
    double previous_value_1 = value_1;
    double previous_value_2 = value_2;

    Swap (&value_1, &value_2);

    if ((!IsEqual (value_1, correct_new_value_1)) || (!IsEqual (value_2, correct_new_value_2)))
    {
        printf ("Test %d failed line(%d)\n"
                "Input: value_1 = %lg, value_2 = %lg\n"
                "Output: new value_1 = %lg, new value_2 = %lg\n"
                "Output expected: new value_1 = %lg, new value_2 = %lg\n",
                number, __LINE__, previous_value_1, previous_value_2, value_1, value_2, correct_new_value_1, correct_new_value_2);
    }

    else
    {
        TEST_OK(number);
    }
}

/** @brief Swaps two variables (numbers).
  *
  *  @param [in] *value_1 pointer to first double variable
  *  @param [in] *value_2 pointer to second double variable
  *
  *
  *
  */
void Swap (double *value_1, double *value_2)
{
    double temp = *value_1;

    *value_1 = *value_2;
    *value_2 = temp;
}

void TestAll ()
{
    printf ("Testing function SolveQuadraticEquation\n\n");

    TestSolveQuadraticEquation ( 0,  0,  0, INFINITE_NUMBER_OF_ROOTS, 0, 0, 1);
    TestSolveQuadraticEquation ( 0,  0,  1, 0,  0, 0, 2);
    TestSolveQuadraticEquation ( 0,  1,  0, 1,  0, 0, 3);
    TestSolveQuadraticEquation ( 0,  1,  4, 1, -4, 0, 4);
    TestSolveQuadraticEquation ( 1,  2,  2, 0,  0, 0, 5);
    TestSolveQuadraticEquation ( 1,  2,  1, 1, -1, 0, 6);
    TestSolveQuadraticEquation ( 1, -4,  3, 2,  3, 1, 7);
    TestSolveQuadraticEquation (-1,  2, -1, 1,  1, 0, 8);

    printf ("\nTesting function SolveLinearEquation\n\n");

    TestSolveLinearEquation (0, 0, INFINITE_NUMBER_OF_ROOTS, 0, 1);
    TestSolveLinearEquation (0, 1, 0,  0, 2);
    TestSolveLinearEquation (1, 3, 1, -3, 3);

    printf ("\nTesting function IsEqualTo0\n\n");

    TestIsEqualTo0 (0.001,  0, 1);
    TestIsEqualTo0 (0.0009, 1, 2);
    TestIsEqualTo0 (1.68,   0, 3);

    printf ("\nTesting function IsEqual\n\n");

    TestIsEqual (0.69, 0.69001, 1, 1);
    TestIsEqual (10, 1, 0, 2);
    TestIsEqual (1, 10, 0, 3);

    printf ("\nTesting function Swap\n\n");

    TestSwap (3.14, 2.718, 2.718, 3.14, 1);
    TestSwap (2.66, 3.512, 3.512, 2.66, 2);
}

