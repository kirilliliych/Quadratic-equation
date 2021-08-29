
/** @brief Contains data for testing SolveQuadraticEquation.
 *
 * @param first_coef  coefficient A
 * @param second_coef coefficient B
 * @param third_coef  coefficient C
 * @param correct_number_of_roots correct number of roots
 * @param correct_root_1 first correct root
 * @param correct_root_2 second correct root
 * @param number_of_test number of test
 */
struct TestDataForQuadraticEquation
    {
        double first_coef;
        double second_coef;
        double third_coef;
        int correct_number_of_roots;
        double correct_root_1;
        double correct_root_2;
        int number_of_test;
    };

/** @brief Contains data for testing SolveLinearEquation.
 *
 * @param linear_coef linear coefficient
 * @param constant_of_free_term constant of free term
 * @param correct_number_of_roots correct number of roots
 * @param correct_root correct root
 * @param number_of_test number of test
 */
struct TestDataForLinearEquation
    {
        double linear_coef;
        double constant_of_free_term;
        int correct_number_of_roots;
        double correct_root;
        int number_of_test;
    };

/** @brief Contains data for testing IsEqualTo0.
 *
 * @param value double   variable being checked
 * @param correct_answer correct answer (true or false)
 * @param number_of_test number of test
 */
struct TestDataForIsEqualTo0
    {
        double value;
        bool correct_answer;
        int number_of_test;
    };

/** @brief Contains data for testing IsEqual.
 *
 * @param value_1 first  double variable being checked
 * @param value_2 second double variable being checked
 * @param correct_answer correct answer (true or false)
 * @param number_of_test number of test
 */
struct TestDataForIsEqual
    {
        double value_1;
        double value_2;
        bool correct_answer;
        int number_of_test;
    };

/** @brief Contains data for testing Swap.
 *
 * @param value_1 first  double variable before swap
 * @param value_2 second double variable before swap
 * @param correct_value_1 first  double variable after swap
 * @param correct_value_2 second double variable after swap
 * @param number_of_test number of test
 */
struct TestDataForSwap
    {
        double value_1;
        double value_2;
        double correct_new_value_1;
        double correct_new_value_2;
        int number_of_test;
    };

/** @brief Tests SolveQuadraticEquation.
 *
 * @param struct TestDataForQuadraticEquation test collection of tests
 */
void TestSolveQuadraticEquation (struct TestDataForQuadraticEquation test);

/** @brief Tests SolveLinearEquation.
 *
 * @param struct TestDataForLinearEquation test collection of tests
 */
void TestSolveLinearEquation (struct TestDataForLinearEquation test);

/** @brief Tests IsEqualTo0.
 *
 * @param struct TestDataForIsEqualTo0 test collection of tests
 */
void TestIsEqualTo0 (struct TestDataForIsEqualTo0 test);

/** @brief Tests IsEqual.
 *
 * @param struct TestDataForIsEqual test collection of tests
 */
void TestIsEqual (struct TestDataForIsEqual test);

/** @brief Tests Swap.
 *
 * @param struct TestDataForSwap collection of tests
 */
void TestSwap (struct TestDataForSwap test);
