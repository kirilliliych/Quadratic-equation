
// TestSolve (struct Test test)
void TestSolveQuadraticEquation (double first_coef, double second_coef, double third_coef, int correct_number_of_roots,
                                 double correct_root_1, double correct_root_2, int number_of_test)
{
    assert (isfinite (first_coef));
    assert (isfinite (second_coef));
    assert (isfinite (third_coef));
    assert (isfinite (correct_root_1));
    assert (isfinite (correct_root_2));
    assert ((correct_number_of_roots >= INFINITE_ROOTS_NUM) && (correct_number_of_roots < 3));

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

void TestSolveLinearEquation (double linear_coef, double constant_of_free_term, int correct_number_of_roots,
                              double correct_root, int number_of_test)
{
    assert (isfinite (linear_coef));
    assert (isfinite (constant_of_free_term));
    assert (isfinite (correct_root));
    assert ((correct_number_of_roots < 2) && (correct_number_of_roots >= INFINITE_ROOTS_NUM));

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

void TestAll ()
{
    int number_of_test = 1;

    printf ("Testing function SolveQuadraticEquation\n\n");

    struct TestDataForQuadraticEquation test_solve_quadratic_equation[] = {{ 0,  0,  0, INFINITE_ROOTS_NUM, 0, 0, number_of_test++},
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

    struct TestDataForLinearEquation test_solve_linear_equation[] = {{ 0, 0, INFINITE_ROOTS_NUM, 0, number_of_test++},
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

    struct TestDataForIsEqualTo0 tests_is_equal_to_0[] = {{ 0.001,  0, number_of_test++},
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

    struct TestDataForIsEqual tests_is_equal[] = {{0.69, 0.69001, 1, number_of_test++},
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

    struct TestDataForSwap tests_swap[] = {{3.14, 2.718, 2.718, 3.14, number_of_test++},
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
