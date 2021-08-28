#ifndef quadratic_equation_announcement.h_INCLUDED

#define quadratic_equation_announcement.h_INCLUDED

#include <assert.h>
#include <math.h>
#include <stdio.h>

#define TEST_OK(number) printf ("Test %d passed\n", number)
//#define TEST_MODE_ACTIVATED

const int INFINITE_NUMBER_OF_ROOTS = -1;                   // signals about infinite number of roots
const double PRECISION = 0.001;                            // a precision of comparison double to 0 and double to double

void TestAll                    ();

/** @brief Inputs coefficients.
 *
 * @param [out] *first_coef  pointer to coefficient A
 * @param [out] *second_coef pointer to coefficient B
 * @param [out] *third_coef  pointer to coefficient C
 */
void ReadCoeffs                 (double *first_coef, double *second_coef, double *third_coef);

/** @brief Tries to read coefficient until it is correctly input (a real number).
 *
 * @param [out] *coefficient pointer to coefficient (A, B or C)
 */
void GetRightInput              (double *coefficient);

/** @brief Tests SolveQuadraticEquation.
 *
 * @param [in] first_coef  coefficient A
 * @param [in] second_coef coefficient B
 * @param [in] third_coef  coefficient C
 * @param [in] correct_number_of_roots correct number of roots
 * @param [in] correct_root_1 correct first root
 * @param [in] correct_root_2 correct second root
 * @param [in] number number of test
 */
void TestSolveQuadraticEquation (double first_coef, double second_coef, double third_coef, int correct_number_of_roots,
                                 double correct_root_1, double correct_root_2, int number);

/** @brief Solves quadratic equation.
 *
 * @param [in]  first_coef  coefficient A
 * @param [in]  second_coef coefficient B
 * @param [in]  third_coef  coefficient C
 * @param [out] *ptr_first_root  pointer to first root
 * @param [out] *ptr_second_root pointer to second root
 *
 * @return number of roots.
 *
 * @note If there is infinite number of roots, returns INFINITE_NUMBER_OF_ROOTS.
 * If there is only one root, puts it to *ptr_first_root.
 * Does not put any roots to *ptr_first_root and *ptr_second_root if roots are absent/infinite number of them.
 */
int  SolveQuadraticEquation     (double first_coef, double second_coef, double third_coef, double *ptr_first_root,
                                 double *ptr_second_root);

/** @brief Tests SolveLinearEquation.
 *
 * @param [in] linear_coef linear coefficient
 * @param [in] constant_of_free_term constant of free term
 * @param [in] correct_number_of_roots correct number of roots
 * @param [in] correct_root correct root
 * @param [in] number number of test
 */
void TestSolveLinearEquation    (double linear_coef, double constant_of_free_term, int correct_number_of_roots,
                                 double correct_root, int number);

/** @brief Solves linear equation.
 *
 * @param [in]  linear_coef coefficient B
 * @param [in]  constant_of_free_term  coefficient C
 * @param [out] *ptr_root pointer to root
 *
 * @return number of roots.
 *
 * @note If there is infinite number of roots, returns INFINITE_NUMBER_OF_ROOTS.
 * Does not put a to *ptr_root if it is absent/infinite number of them.
 */
int  SolveLinearEquation        (double linear_coef, double constant_of_free_term, double *ptr_root);

/** @brief Tests IsEqualTo0.
 *
 * @param [in] value double variable being checked
 * @param [in] correct_answer correct answer (true or false)
 * @param [in] number number of test
 */
void TestIsEqualTo0             (double value, bool correct_answer, int number);

/** @brief Decides if double variable equal to 0 (with 0.001 precision).
 *
 * @param [in] value value of double variable
 *
 * @return Whether the fact that the variable is equal to 0 (with 0.001 precision) correct or not.
 */
bool IsEqualTo0                 (double value);

/** @brief Prints answer.
 *
 * @param [in] number_of_roots number of roots
 * @param [in] first_root  first  root of quadratic equation
 * @param [in] second_root second root of quadratic equation
 *
 * @note Number of printed roots depends of number_of_roots.
 */
void PrintAnswer                (int number_of_roots, double first_root, double second_root);

/** @brief Tests IsEqual.
 *
 * @param [in] value_1 first  double variable being checked
 * @param [in] value_2 second double variable being checked
 * @param [in] correct_answer correct answer (true or false)
 * @param [in] number number of test
 */
void TestIsEqual                (double value_1, double value_2, bool correct_answer, int number);

/** @brief Decides if two double variables are equal (with 0.001 precision).
 *
 * @param [in] value_1 first  double variable
 * @param [in] value_2 second double variable
 *
 * @return Whether the fact that two variables are equal (with 0.001 precision) correct or not.
 */
bool IsEqual                    (double value_1, double value_2);

/** @brief Tests Swap.
 *
 * @param [in] value_1 first  value before swap
 * @param [in] value_2 second value before swap
 * @param [in] correct_new_value_1 after swap
 * @param [in] correct_new_value_2 after swap
 * @param [in] number number of test
 */
void TestSwap                   (double value_1, double value_2, double correct_new_value_1,
                                 double correct_new_value_2, int number);

/** @brief Swaps two variables (numbers).
 *
 * @param [out] *value_1 pointer to first  double variable
 * @param [out] *value_2 pointer to second double variable
 */
void Swap                       (double *value_1, double *value_2);

#endif
