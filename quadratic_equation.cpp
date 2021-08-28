#include <assert.h>
#include <math.h>
#include <stdio.h>

#define TEST_OK(number) printf ("Test %d passed\n", number);
#define TEST_MODE_ACTIVATED -2;
const int INFINITY_ROOTS = -1;                                                                                                                 // signals about infinite number of roots
const double PRECISION = 0.001;                                                                                                                // a precision of comparison double to 0 and double to double

void TestAll                         ();

void ReadCoeffs                      (double *first_coef, double *second_coef, double *third_coef);

void GetRightInput                   (double *coefficient);

void TestSolveQuadraticEquation      (double first_coef, double second_coef, double third_coef, int correct_number_roots, double correct_root_1, double correct_root_2, int number);
int  SolveQuadraticEquation          (double first_coef, double second_coef, double third_coef, double *ptr_first_root, double *ptr_second_root);

void TestSolveLinearEquation         (double second_coef, double third_coef, int correct_number_roots, double correct_root, int number);
int  SolveLinearEquation             (double second_coef, double third_coef, double *ptr_first_root);

void TestIsCloseTo0                  (double val, bool correct_answer, int number);
bool IsCloseTo0                      (double val);

void  PrintAnswer                    (int num_roots, double first_root, double second_root);

bool CompareDouble                   (double val1, double val2);

int main ()
{
    #ifndef TEST_MODE_ACTIVATED
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

    while (scanf ("%lg", coefficient) == 0)
    {
        printf ("Invalid input. Please, enter a number!\n");

        while (getchar () != '\n');

    }
}

void TestSolveQuadraticEquation (double first_coef, double second_coef, double third_coef, int correct_number_roots, double correct_root_1, double correct_root_2, int number)
{
    if (correct_root_1 > correct_root_2)
    {
        double temp = correct_root_1;

        correct_root_1 = correct_root_2;
        correct_root_2 = temp;
    }

    double root_1 = 0;
    double root_2 = 0;
    int number_roots = SolveQuadraticEquation (first_coef, second_coef, third_coef, &root_1, &root_2);

    if (!CompareDouble (correct_number_roots, number_roots) || ((!CompareDouble (correct_root_1, root_1) || !CompareDouble (correct_root_2, root_2)) && ((correct_number_roots != INFINITY_ROOTS) || (correct_number_roots != 0))))
    {
        printf ("Test %d failed line(%d)\n"
                "Input: A = %lg, B = %lg, C = %lg\n"
                "Output: number of roots = %d, root 1 = %lg, root 2 = %lg\n"
                "Output expected: number of roots = %d, root 1 = %lg, root 2 = %lg\n",
                number, __LINE__, first_coef, second_coef, third_coef, number_roots, root_1, root_2, correct_number_roots, correct_root_1, correct_root_2);
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

void TestSolveLinearEquation (double second_coef, double third_coef, int correct_number_roots, double correct_root, int number)
{
  assert (isfinite (second_coef));
  assert (isfinite (third_coef));
  assert (isfinite (correct_root));

  double root = 0;

  int number_roots = SolveLinearEquation (second_coef, third_coef, &root);

  if (!CompareDouble (correct_number_roots, number_roots) || (!CompareDouble (correct_root, root) && (correct_number_roots != INFINITY_ROOTS) && (correct_number_roots != 0)))
  {
      printf ("Test %d failed line(%d)\n"
              "Input: B = %lg, C = %lg\n"
              "Output: number of roots = %d, root = %lg\n"
              "Output expected: number of roots = %d, root = %lg\n",
              number, __LINE__, second_coef, third_coef, number_roots, root, correct_number_roots, correct_root);
  }

  else
  {
      TEST_OK(number);
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

void TestIsCloseTo0 (double val, bool correct_answer, int number)
{
    bool answer = IsCloseTo0 (val);

    if (correct_answer != answer)
    {
        printf ("Test %d failed line(%d)\n"
                "Input: value = %lg\n"
                "Output: %d\n"
                "Output expected: %d\n",
                number, __LINE__, val, answer, correct_answer);
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

        case INFINITY_ROOTS:
            printf ("Infinity number of roots\n");

            break;

        default:
            printf ("%s %d\n", "Error, unknown value of num_roots: ", num_roots);

            break;

    }
}

bool CompareDouble (double val1, double val2)
{
    return (val1 - val2) < PRECISION;
}

void TestAll ()
{
    printf ("Testing function SolveQuadraticEquation\n\n");

    TestSolveQuadraticEquation (0, 0, 0, INFINITY_ROOTS, 0, 0, 1);
    TestSolveQuadraticEquation (0, 0, 1, 0, 0, 0, 2);
    TestSolveQuadraticEquation (0, 1, 0, 1, 0, 0, 3);
    TestSolveQuadraticEquation (0, 1, 4, 1, -4, 0, 4);
    TestSolveQuadraticEquation (1, 2, 2, 0, 0, 0, 5);
    TestSolveQuadraticEquation (1, 2, 1, 1, -1, 0, 6);
    TestSolveQuadraticEquation (1, -4, 3, 2, 3, 1, 7);

    printf ("\nTesting function SolveLinearEquation\n\n");

    TestSolveLinearEquation (0, 0, INFINITY_ROOTS, 0, 1);
    TestSolveLinearEquation (0, 1, 0, 0, 2);
    TestSolveLinearEquation (1, 3, 1, -3, 3);

    printf ("\nTesting function TestIsCloseTo0\n\n");

    TestIsCloseTo0 (0.001, 0, 1);
    TestIsCloseTo0 (0.0009, 1, 2);
    TestIsCloseTo0 (1.68, 0, 3  );
}

