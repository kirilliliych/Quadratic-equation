#include <assert.h>
#include <math.h>
#include <stdio.h>

#define TEST_OK(number) printf ("Test %d passed\n", number);

const int INFINITY_ROOTS = -1;                                                                                                                 // signals about infinite number of roots
const double PRECISION = 0.001;                                                                                                                // a precision of comparison double to 0 and double to double
const int ERROR = -2;                                                                                                                          // signals about an error in switch

void ReadCoeffs                      (double *first_coef, double *second_coef, double *third_coef);

/*void TestCorrectInput              ();
void CheckTestCorrectInput           (double test_coef_double, char test_coef_char);*/
int  CorrectInput                    (double *coefficient, bool if_testing);

void TestSolveQuadraticEquation      ();
void CheckTestSolveQuadraticEquation (int number, double test_first_coef, double test_second_coef, double test_third_coef);
int  SolveQuadraticEquation          (double first_coef, double second_coef, double third_coef, double *ptr_first_root, double *ptr_second_root);

void TestSolveLinearEquation         ();
void CheckTestSolveLinearEquation    (int number, double test_second_coef, double test_third_coef);
int  SolveLinearEquation             (double second_coef, double third_coef, double *ptr_first_root);

void TestIsCloseTo0                  ();
void CheckTestIsCloseTo0             (int number, double test);
bool IsCloseTo0                      (double val);

void CheckTestPrintAnswer            (int number, int num_roots_test, double first_root_test, double second_root_test);
void TestPrintAnswer                 ();
int  PrintAnswer                     (int num_roots, double first_root, double second_root, bool if_testing);

bool CompareDouble                   (double val1, double val2);

int main ()
{
    printf ("\t\t\t///// QuadraticEquationSolver /////\n");
    printf ("\t\t\t\t(c) kirilliliych, 2021\n\n");

    double a = 0;
    double b = 0;
    double c = 0;

    TestIsCloseTo0  ();
    TestPrintAnswer ();
    TestSolveLinearEquation ();
    TestSolveQuadraticEquation ();

    ReadCoeffs (&a, &b, &c);

    double first_root  = 0;
    double second_root = 0;

    int num_roots = SolveQuadraticEquation (a, b, c, &first_root, &second_root);

    PrintAnswer (num_roots, first_root, second_root, false);

    return 0;
}

void ReadCoeffs (double *first_coef, double *second_coef, double *third_coef)
{
    assert (first_coef  != nullptr);
    assert (second_coef != nullptr);
    assert (third_coef  != nullptr);

    printf ("Enter coefficient A in Ax^2+Bx+C formula: ");

    CorrectInput (first_coef,  false);

    printf ("Enter coefficient B in Ax^2+Bx+C formula: ");

    CorrectInput (second_coef, false);

    printf ("Enter coefficient C in Ax^2+Bx+C formula: ");

    CorrectInput (third_coef,  false);

}

/*void TestCorrectInput ()
{
    double test_coef_double = 0;

    char test_coef_char = 'a';

    CheckTestCorrectInput (test_coef_double, test_coef_char);

}

void CheckTestCorrectInput (double test_coef_double, char test_coef_char)
{
    assert (isfinite (test_coef_double));

    int number = 1;

    bool result_of_test = CorrectInput (&test_coef_double, true);
    bool right_result = isfinite (test_coef_double);

    if (result_of_test != right_result)
    {
        printf ("Test %d failed line (%d)\nInput: %lg\nOutput: %d\nOutput expected: %d", number, __LINE__, test_coef_double, result_of_test, right_result);
    }

    else
    {
        TEST_OK(number);
    }

    number++;

     result_of_test = CorrectInput (&test_coef_char, true);

     right_result = 0;

     if (result_of_test != right_result)
     {
         printf ("Test %d failed line (%d)\nInput: %lg\nOutput: %d\nOutput expected: %d", number, __LINE__, test_coef_double, result_of_test, right_result);
     }
}*/

int CorrectInput (double *coefficient, bool if_testing)
{
    assert (coefficient != nullptr);

    while (scanf ("%lg", coefficient) == 0)
    {
        printf ("Invalid input. Please, enter a number!\n");

        while (getchar () != '\n');

        if (if_testing)
        {
            return 0;
        }

    }
    return 1;
}

void TestSolveQuadraticEquation ()
{
    printf ("Testing function SolveQuadraticEquation\n\n");
    double test_first_coef  = 1;
    double test_second_coef = 2;
    double test_third_coef  = 2;
    int number = 1;

    CheckTestSolveQuadraticEquation (number, test_first_coef, test_second_coef, test_third_coef);

    number++;

    test_first_coef  = 1;
    test_second_coef = 2;
    test_third_coef  = 1;

    CheckTestSolveQuadraticEquation (number, test_first_coef, test_second_coef, test_third_coef);

    number++;

    test_first_coef  = 2;
    test_second_coef = 5;
    test_third_coef  = 3;

    CheckTestSolveQuadraticEquation (number, test_first_coef, test_second_coef, test_third_coef);

    printf ("\n");
}

void CheckTestSolveQuadraticEquation (int number, double test_first_coef, double test_second_coef, double test_third_coef)
{
    assert (isfinite (number));
    assert (isfinite (test_first_coef));
    assert (isfinite (test_second_coef));
    assert (isfinite (test_third_coef));

    int right_number_of_roots = 0;
    double first_calculated_root  = 0;
    double second_calculated_root = 0;
    double first_right_root  = 0;
    double second_right_root = 0;
    int number_of_roots = SolveQuadraticEquation (test_first_coef, test_second_coef, test_third_coef, &first_calculated_root, &second_calculated_root);

    if (IsCloseTo0 (fabs (test_first_coef)))
    {
        right_number_of_roots = SolveLinearEquation (test_second_coef, test_third_coef, &first_calculated_root);
    }

    else
    {
        double discriminant = test_second_coef * test_second_coef - 4 * test_first_coef * test_third_coef;

        if (discriminant > 0)
        {
            double discriminant_square_root = sqrt (discriminant);

            first_right_root  = (-test_second_coef - discriminant_square_root) / (2 * test_first_coef);
            second_right_root = (-test_second_coef + discriminant_square_root) / (2 * test_first_coef);

            right_number_of_roots = 2;
        }

        else if (IsCloseTo0 (fabs (discriminant)))
        {
            first_right_root = -test_second_coef / (2 * test_first_coef);

            right_number_of_roots = 1;
        }

        else
        {
            right_number_of_roots = 0;
        }
    }

    if (!((CompareDouble (number_of_roots, right_number_of_roots)) && CompareDouble (first_calculated_root, first_right_root) && CompareDouble (second_calculated_root, second_right_root)))
    {
        printf ("Test %d failed line(%d)\nInput:\ncoefficient A %lg\ncoefficient B %lg\ncoefficient C %lg\nOutput:\nnumber of roots ", number, __LINE__, test_first_coef, test_second_coef, test_third_coef);

        if (number_of_roots != INFINITY_ROOTS)
        {
            printf ("%d\nOutput expected:\nnumber of roots %d", number_of_roots, right_number_of_roots);
        }
    }

    else
    {
        TEST_OK(number);
    }
}

int SolveQuadraticEquation (double first_coef, double second_coef, double third_coef, double *ptr_first_root, double *ptr_second_root)
{
    assert (isfinite (first_coef));
    assert (isfinite (second_coef));
    assert (isfinite (third_coef));
    assert (ptr_first_root  != nullptr);
    assert (ptr_second_root != nullptr);

    if (IsCloseTo0 (fabs (first_coef)))
    {
        return SolveLinearEquation (second_coef, third_coef, ptr_first_root);
    }

    else
    {
        double discriminant = second_coef * second_coef - 4 * first_coef * third_coef;

        if (discriminant > 0)
        {
            double discriminant_square_root = sqrt (discriminant);

            *ptr_first_root  = (-second_coef - discriminant_square_root) / (2 * first_coef);
            *ptr_second_root = (-second_coef + discriminant_square_root) / (2 * first_coef);

            return 2;
        }

        if (IsCloseTo0 (fabs (discriminant)))
        {
            *ptr_first_root = -second_coef / (2 * first_coef);

            return 1;
        }

        else
        {
            return 0;
        }

    }
}

void TestSolveLinearEquation ()
{
    printf ("Testing function SolveLinearEquation:\n\n");

    double test_second_coef = 0;
    double test_third_coef  = 0;
    int number = 1;

    CheckTestSolveLinearEquation (number, test_second_coef, test_third_coef);

    number++;

    test_second_coef = 0;
    test_third_coef  = 1;

    CheckTestSolveLinearEquation (number, test_second_coef, test_third_coef);

    number++;

    test_second_coef = 2;
    test_third_coef  = 4;

    CheckTestSolveLinearEquation (number, test_second_coef, test_third_coef);

    printf ("\n");
}

void CheckTestSolveLinearEquation (int number, double test_second_coef, double test_third_coef)
{
    assert (isfinite (number));
    assert (isfinite (test_second_coef));
    assert (isfinite (test_third_coef));

    double calculated_root = 0;
    double right_root = 0;
    int right_number_of_roots = 0;
    int number_of_roots = SolveLinearEquation (test_second_coef, test_third_coef, &calculated_root);

    if (IsCloseTo0 (fabs (test_second_coef)))
    {
        if (IsCloseTo0 (fabs (test_third_coef)))
        {
            right_number_of_roots = INFINITY_ROOTS;
        }

        else
        {
            right_number_of_roots = 0;
        }

    }

    else
    {
        right_number_of_roots = 1;
        right_root = -test_third_coef / test_second_coef;
    }

    if ((CompareDouble (calculated_root, right_root)) && (number_of_roots == right_number_of_roots))
    {
        TEST_OK(number);
    }

    else
    {
        printf ("Test %d failed line (%d)\nInput:\ncoefficient B %lg\n coefficient C %lg\nOutput:\nnumber of roots ", number, __LINE__, test_second_coef, test_third_coef);

        if (number_of_roots > -1)
        {
            printf ("%d\nOutput expected:\nnumber of roots ", number_of_roots);
        }

        else
        {
            printf ("infinite number of roots\nOutput expected:\nnumber of roots ");
        }

        if (right_number_of_roots != INFINITY_ROOTS)
        {
            printf ("%d\n", right_number_of_roots);
        }

        else
        {
            printf ("infinite number of roots\n");
        }
    }

}

int SolveLinearEquation (double second_coef, double third_coef, double *ptr_first_root)
{
    assert (isfinite (second_coef));
    assert (isfinite (third_coef));
    assert (ptr_first_root != nullptr);

    if (IsCloseTo0 (fabs (second_coef)))
    {
        if (IsCloseTo0 (fabs (third_coef)))
        {
            return INFINITY_ROOTS;
        }

        else
        {
            return 0;
        }
    }

    else
    {
        *ptr_first_root = -third_coef / second_coef;

        return 1;
    }
}

void TestIsCloseTo0 ()
{
    printf ("Testing function IsCloseTo0:\n\n");

    int number = 1;
    double test = 0.000999;

    CheckTestIsCloseTo0 (number, test);

    number++;

    test = 0.001;

    CheckTestIsCloseTo0 (number, test);

    printf ("\n");
}

void CheckTestIsCloseTo0 (int number, double test)
{
    assert (isfinite (number));
    assert (isfinite (test));

    bool right_answer = test < PRECISION;
    bool result_of_test = IsCloseTo0 (fabs (test));

    if (right_answer != result_of_test)
    {
        printf ("Test %d failed line(%d)\nInput: %lg\nOutput: %d\nOutput expected: %d", number, __LINE__, test, result_of_test, right_answer);
    }

    else
    {
        TEST_OK(number);
    }
}

bool IsCloseTo0 (double val)
{
    assert (isfinite (val));

    return fabs (val) < PRECISION;
}

void TestPrintAnswer ()
{
    printf ("Testing function PrintAnswer: \n\n");

    int number = 1;
    int num_roots_test = 0;

    CheckTestPrintAnswer (number, num_roots_test, NULL, NULL);

    number++;

    num_roots_test = 1;

    double first_root_test = 10;

    CheckTestPrintAnswer (number, num_roots_test, first_root_test, NULL);

    number++;

    num_roots_test = 2;

    double second_root_test = 20;

    CheckTestPrintAnswer (number, num_roots_test, first_root_test, second_root_test);

    number++;

    num_roots_test = INFINITY_ROOTS;

    CheckTestPrintAnswer (number, num_roots_test, NULL, NULL);

    number++;

    num_roots_test = ERROR;

    CheckTestPrintAnswer (number, num_roots_test, NULL, NULL);

    printf ("\n");
}

void CheckTestPrintAnswer (int number, int num_roots_test, double first_root_test, double second_root_test)
{
    assert (isfinite (number));
    assert (isfinite (num_roots_test));
    assert (isfinite (first_root_test));
    assert (isfinite (second_root_test));
    int result_of_test = PrintAnswer (num_roots_test, first_root_test, second_root_test, true);

    if (result_of_test != num_roots_test)
    {
        printf("Test %d failed line(%d)\nInput:\nnumber of roots %d\nfirst root %lg\nsecond root %lg\nOutput:\nnumber of roots %d\nOutput expected: %d\n\n", number, __LINE__, num_roots_test, first_root_test, second_root_test, PrintAnswer (first_root_test, second_root_test, result_of_test, false), PrintAnswer (first_root_test, second_root_test, num_roots_test, false));

    }

    else
    {
        TEST_OK(number);
    }
}

int PrintAnswer (int num_roots, double first_root, double second_root, bool if_testing)
{
    assert (isfinite (first_root));
    assert (isfinite (second_root));
    assert (isfinite (num_roots));


    switch (num_roots)
    {
        case 0:
            if (!if_testing)
            {
                printf ("No solutions\n");
            }

            return 0;

        case 1:
            if (!if_testing)
            {
                printf ("%s %lg %s", "The only root: ", first_root, "\n");
            }

            return 1;

        case 2:
            if (!if_testing)
            {
                printf ("%s %lg %s %lg\n", "First root: ", first_root, "Second root: ", second_root);
            }

            return 2;

        case INFINITY_ROOTS:
            if (!if_testing)
            {
                printf ("Infinity number of roots\n");
            }

            return INFINITY_ROOTS;

        default:
            if (!if_testing)
            {
                printf ("%s %d\n", "Error, unknown value of num_roots: ", num_roots);
            }

            return ERROR;

    }
}

bool CompareDouble (double val1, double val2)
{
    return (fabs (val1 - val2)) < PRECISION;
}

