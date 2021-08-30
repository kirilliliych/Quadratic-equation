// -------------------------------------------------------
//! @file testing.cpp
//! @brief Realization of testing functions.
//! @author kirilliliych (https://github.com/kirilliliych)
//! @date 2021-08-29
//! @copyright Copyright (c) 2021
// -------------------------------------------------------

void TestSolveQuadraticEquation (struct TestData test)
{
    assert (isfinite (test.first_coef));
    assert (isfinite (test.second_coef));
    assert (isfinite (test.third_coef));
    assert (isfinite (test.correct_root_1));
    assert (isfinite (test.correct_root_2));
    assert ((test.correct_number_of_roots >= INFINITE_ROOTS_NUM) && (test.correct_number_of_roots < 3));

    if (test.correct_root_1 > test.correct_root_2)
    {
        Swap (&test.correct_root_1, &test.correct_root_2);
    }

    double root_1 = 0;
    double root_2 = 0;
    int number_of_roots = SolveQuadraticEquation (test.first_coef, test.second_coef, test.third_coef, &root_1, &root_2);

    if (root_1 > root_2)
    {
        Swap (&root_1, &root_2);
    }

    bool is_passed = true;

    if (test.correct_number_of_roots != number_of_roots)
    {
        is_passed = false;
    }
    else if ((test.correct_number_of_roots == 2) &&
            ((!IsEqual (test.correct_root_1, root_1)) || (!IsEqual (test.correct_root_2, root_2))))
    {
        is_passed = false;
    }
    else if ((test.correct_number_of_roots == 1) && (!IsEqual (test.correct_root_1, root_1)))
    {
        is_passed = false;
    }

    if (!is_passed)
    {
        printf ("Test %d failed line(%d)\n"
                "Input: A = %lg, B = %lg, C = %lg\n"
                "Output: number of roots = %d, root 1 = %lg, root 2 = %lg\n"
                "Output expected: number of roots = %d, root 1 = %lg, root 2 = %lg\n",
                test.number_of_test, __LINE__, test.first_coef, test.second_coef,
                test.third_coef, number_of_roots,root_1, root_2, test.correct_number_of_roots,
                test.correct_root_1, test.correct_root_2);
    }
    else
    {
        TEST_OK(test.number_of_test);
    }
}

void TestSolveLinearEquation (struct TestData test)
{
    assert (isfinite (test.first_coef));
    assert (isfinite (test.second_coef));
    assert (isfinite (test.correct_root_1));
    assert ((test.correct_number_of_roots < 2) && (test.correct_number_of_roots >= INFINITE_ROOTS_NUM));

    double root = 0;

    int number_of_roots = SolveLinearEquation (test.first_coef, test.second_coef, &root);

    if ((test.correct_number_of_roots != number_of_roots) ||
       (!IsEqual (test.correct_root_1, root) && (test.correct_number_of_roots == 1)))
    {
        printf ("Test %d failed line(%d)\n"
                "Input: k = %lg, b = %lg\n"
                "Output: number of roots = %d, root = %lg\n"
                "Output expected: number of roots = %d, root = %lg\n",
                test.number_of_test, __LINE__, test.first_coef, test.second_coef,
                number_of_roots, root, test.correct_number_of_roots, test.correct_root_1);
    }
    else
    {
        TEST_OK(test.number_of_test);
    }
}

void TestIsEqualTo0 (struct TestData test)
{
    assert (isfinite (test.first_coef));

    bool answer = IsEqualTo0 (test.first_coef);

    if (test.correct_answer != answer)
    {
        printf ("Test %d failed line(%d)\n"
                "Input: value = %lg\n"
                "Output: %d\n"
                "Output expected: %d\n",
                test.number_of_test, __LINE__, test.first_coef, answer, test.correct_answer);
    }
    else
    {
        TEST_OK(test.number_of_test);
    }
}

void TestIsEqual (struct TestData test)
{
    assert (isfinite (test.first_coef));
    assert (isfinite (test.second_coef));

    bool answer = IsEqual (test.first_coef, test.second_coef);

    if (test.correct_answer != answer)
    {
        printf ("Test %d failed line(%d)\n"
                "Input: value_1 = %lg, value_2 = %lg\n"
                "Output: %d\n"
                "Output expected: %d\n",
                test.number_of_test, __LINE__, test.first_coef, test.second_coef, answer, test.correct_answer);
    }
    else
    {
        TEST_OK(test.number_of_test);
    }
}

void TestSwap (struct TestData test)
{
    assert (isfinite (test.first_coef));
    assert (isfinite (test.second_coef));
    assert (isfinite (test.correct_root_1));
    assert (isfinite (test.correct_root_2));

    double previous_value_1 = test.first_coef;
    double previous_value_2 = test.second_coef;

    Swap (&test.first_coef, &test.second_coef);

    if ((!IsEqual (test.first_coef, test.correct_root_1)) ||
        (!IsEqual (test.second_coef, test.correct_root_2)))
    {
        printf ("Test %d failed line(%d)\n"
                "Input: value_1 = %lg, value_2 = %lg\n"
                "Output: new value_1 = %lg, new value_2 = %lg\n"
                "Output expected: new value_1 = %lg, new value_2 = %lg\n",
                test.number_of_test, __LINE__, previous_value_1,         previous_value_2,
                                               test.first_coef,             test.second_coef,
                                               test.correct_root_1, test.correct_root_2);
    }
    else
    {
        TEST_OK(test.number_of_test);
    }
}

void TestAll ()
{
    int number_of_test = 1;

    printf ("Testing function SolveQuadraticEquation\n\n");

    struct TestData test_solve_quadratic_equation[] = {{number_of_test++,  0,  0,  0, INFINITE_ROOTS_NUM, 0, 0, 0},
                                                       {number_of_test++,  0,  0,  1, 0, 0,  0, 0},
                                                       {number_of_test++,  0,  1,  0, 1, 0,  0, 0},
                                                       {number_of_test++,  0,  1,  0, 1, 0,  0, 0},
                                                       {number_of_test++,  0,  1,  4, 1, 0, -4, 0},
                                                       {number_of_test++,  1,  2,  2, 0, 0,  0, 0},
                                                       {number_of_test++,  1,  2,  1, 1, 0, -1, 0},
                                                       {number_of_test++,  1, -4,  3, 2, 0,  3, 1},
                                                       {number_of_test++, -1,  2, -1, 1, 0,  1, 0}};

    for (int i = 0; i < number_of_test - 1; ++i)
    {
        TestSolveQuadraticEquation (test_solve_quadratic_equation[i]);
    }

    number_of_test = 1;

    printf ("\nTesting function SolveLinearEquation\n\n");

    struct TestData test_solve_linear_equation[] = {{number_of_test++,  0, 0, 0, INFINITE_ROOTS_NUM, 0, 0, 0},
                                                    {number_of_test++,  0, 1, 0,  0,  0,  0, 0},
                                                    {number_of_test++,  1, 3, 0,  1,  0, -3, 0},
                                                    {number_of_test++, -2, 4, 0,  1,  0,  2, 0}};

    for (int i = 0; i < number_of_test - 1; ++i)
    {
        TestSolveLinearEquation (test_solve_linear_equation[i]);
    }

    number_of_test = 1;

    printf ("\nTesting function IsEqualTo0\n\n");

    struct TestData test_is_equal_to_0[] = {{number_of_test++,   0.001, 0, 0, 0, 0, 0, 0},
                                            {number_of_test++, -0.0009, 1, 0, 0, 1, 0, 0},
                                            {number_of_test++,    1.68, 0, 0, 0, 0, 0, 0}};

    for (int i = 0; i < number_of_test - 1; ++i)
    {
        TestIsEqualTo0 (test_is_equal_to_0[i]);
    }

    number_of_test = 1;

    printf ("\nTesting function IsEqual\n\n");

    struct TestData test_is_equal[] = {{number_of_test++, 0.69, 0.69001,  0, 0, 1, 0, 0},
                                       {number_of_test++,  -10,       1,  0, 0, 0, 0, 0},
                                       {number_of_test++,   22,       10, 0, 0, 0, 0, 0}};

    for (int i = 0; i < number_of_test - 1; ++i)
    {
        TestIsEqual (test_is_equal[i]);
    }

    number_of_test = 1;

    printf ("\n" "Testing function Swap\n\n");

    struct TestData test_swap[] = {{number_of_test++, 3.14, 2.718, 0, 0, 0, 2.718, 3.14},
                                   {number_of_test++, 2.66, 3.512, 0, 0, 0, 3.512, 2.66}};

    for (int i = 0; i < number_of_test - 1; ++i)
    {
       TestSwap (test_swap[i]);
    }
}
