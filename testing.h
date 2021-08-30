// -------------------------------------------------------
//! @file testing.h
//! @brief Testing functions' prototypes and documentation.
//! @author kirilliliych (https://github.com/kirilliliych)
//! @date 2021-08-29
//! @copyright Copyright (c) 2021
// -------------------------------------------------------

/** @brief Contains data for testing.
 *
 *  @param first_coef  coefficient A
 *  @param second_coef coefficient B
 *  @param third_coef  coefficient C
 *  @param correct_number_of_roots correct number of roots
 *  @param correct_root_1 first correct root
 *  @param correct_root_2 second correct root
 *  @param number_of_test number of test
 */

struct TestData
    {
        int number_of_test;
        double first_coef;
        double second_coef;
        double third_coef;
        int correct_number_of_roots;
        bool correct_answer;
        double correct_root_1;
        double correct_root_2;
    };

/** @brief Tests SolveQuadraticEquation.
 *
 * @param struct TestData test collection of tests
 */
void TestSolveQuadraticEquation (struct TestData test);

/** @brief Tests SolveLinearEquation.
 *
 * @param struct TestData test collection of tests
 */
void TestSolveLinearEquation (struct TestData test);

/** @brief Tests IsEqualTo0.
 *
 * @param struct TestData test collection of tests
 */
void TestIsEqualTo0 (struct TestData test);

/** @brief Tests IsEqual.
 *
 * @param struct TestData test collection of tests
 */
void TestIsEqual (struct TestData test);

/** @brief Tests Swap.
 *
 * @param struct TestData collection of tests
 */
void TestSwap (struct TestData test);
