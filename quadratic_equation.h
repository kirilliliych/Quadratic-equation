// -------------------------------------------------------
//! @file quadratic_equation.h
//! @brief Non-testing functions' prototypes and documentations.
//! @author kirilliliych (https://github.com/kirilliliych)
//! @date 2021-08-29
//! @copyright Copyright (c) 2021
// -------------------------------------------------------

#include <assert.h>
#include <math.h>
#include <stdio.h>

#define TEST_OK(number_of_test) printf ("Test %d passed\n", number_of_test)

#define TEST_MODE_ACTIVATED

const int INFINITE_ROOTS_NUM = -1;                   // signals about infinite number of roots
const double PRECISION = 0.001;                      // a precision of comparison of double to 0 and double to double

void TestAll ();

/** @brief Inputs coefficients.
 *
 *  @param [out] *first_coef  pointer to coefficient A
 *  @param [out] *second_coef pointer to coefficient B
 *  @param [out] *third_coef  pointer to coefficient C
 */
void ReadCoeffs (double *first_coef,
                 double *second_coef,
                 double *third_coef);

/** @brief Tries to read a coefficient until it is correctly input (a real number).
 *
 *  @param [out] *coefficient pointer to coefficient (A, B or C)
 */
void EquationCoefGetRightInput (double *coefficient);

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
 *  @note If there is infinite number of roots, returns INFINITE_ROOTS_NUM.
 *  If there is only one root, puts it to *ptr_first_root.
 *  Does not put any roots to *ptr_first_root and *ptr_second_root if roots are absent/infinite number of them.
 */
int SolveQuadraticEquation (double first_coef,
                            double second_coef,
                            double third_coef,
                            double *ptr_first_root,
                            double *ptr_second_root);

/** @brief Solves linear equation.
 *
 *  @param [in]  linear_coef            coefficient B
 *  @param [in]  constant_of_free_term  coefficient C
 *  @param [out] *ptr_root pointer to root
 *
 *  @return number of roots.
 *
 *  @note If there is infinite number of roots, returns INFINITE_ROOTS_NUM.
 *  Does not put a to *ptr_root if it is absent/infinite number of them.
 */
int SolveLinearEquation (double linear_coef,
                         double constant_of_free_term,
                         double *ptr_root);

/** @brief Decides if double variable is equal to 0 (with 0.001 precision).
 *
 *  @param [in] value double variable
 *
 *  @return Whether the fact that the variable is equal to 0 (with 0.001 precision) is correct or not.
 */
bool IsEqualTo0 (double value);

/** @brief Prints answer.
 *
 *  @param [in] number_of_roots number of roots
 *  @param [in] first_root  first root  of quadratic equation
 *  @param [in] second_root second root of quadratic equation
 *
 *  @note Number of printed roots depends of number_of_roots.
 */
void PrintAnswer (int number_of_roots,
                  double first_root,
                  double second_root);

/** @brief Decides if two double variables are equal (with 0.001 precision).
 *
 *  @param [in] value_1 first  double variable
 *  @param [in] value_2 second double variable
 *
 *  @return Whether the fact that two variables are equal to each other (with 0.001 precision) is correct or not.
 */
bool IsEqual (double value_1,
              double value_2);

/** @brief Swaps two variables (numbers).
 *
 *  @param [out] *value_1 pointer to first  double variable
 *  @param [out] *value_2 pointer to second double variable
 */
void Swap (double *value_1,
           double *value_2);
