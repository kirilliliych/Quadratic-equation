#include <assert.h>
#include <math.h>
#include <stdio.h>

#define TEST_OK(number) printf ("Test %d passed\n", number);
#define TEST_FAILED(number, line, inp, outp, outp_expected) printf ("Test %d failed (line %d)\nInput: %d\nOutput: %d\nOutput expected: %d\n\n", number, __LINE__, inp, outp, outp_expected);

const int INFINITY_ROOTS = -1;                                                                                                                 // signals about infinite number of roots
const double PRECISION = 0.001;                                                                                                                // a precision of comparison double to 0

void ReadCoeffs             (double *first_coef, double *second_coef, double *third_coef);
void CorrectInput           (double *coefficient);
int  SolveQuadraticEquation (double first_coef, double second_coef, double third_coef, double *ptr_first_root, double *ptr_second_root);
int  SolveLinearEquation    (double second_coef, double third_coef, double *ptr_first_root);
void TestIsCloseTo0         ();
bool IsCloseTo0             (double val);
void PrintAnswer            (double first_root, double second_root, int num_roots);


int main()
{
    printf ("\t\t\t///// QuadraticEquationSolver /////\n");
    printf ("\t\t\t\t(c) kirilliliych, 2021\n\n");

    double a = 0;
    double b = 0;
    double c = 0;

    TestIsCloseTo0();

    ReadCoeffs (&a, &b, &c);

    double first_root = 0;
    double second_root = 0;

    int num_roots = SolveQuadraticEquation (a, b, c, &first_root, &second_root);

    PrintAnswer (first_root, second_root, num_roots);

    return 0;
}

void ReadCoeffs (double *first_coef, double *second_coef, double *third_coef)
{
    assert (first_coef  != nullptr);
    assert (second_coef != nullptr);
    assert (third_coef  != nullptr);

    printf ("Enter coefficient A in Ax^2+Bx+C formula: ");

    CorrectInput (first_coef);

    printf ("Enter coefficient B in Ax^2+Bx+C formula: ");

    CorrectInput (second_coef);

    printf ("Enter coefficient C in Ax^2+Bx+C formula: ");

    CorrectInput (third_coef);

}

void CorrectInput (double *coefficient)
{
    assert (coefficient != nullptr);

    while (scanf ("%lg", coefficient) == 0)
    {
        printf ("Invalid input. Please, enter a number!\n");

        while (getchar () != '\n');
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

int SolveLinearEquation (double second_coef, double third_coef, double *ptr_first_root)
{
    assert (isfinite (second_coef));
    assert (isfinite (third_coef));
    assert (ptr_first_root != nullptr);

    if (IsCloseTo0 (second_coef))
    {
        if (IsCloseTo0 (third_coef))
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
    double test_1 = 0.000999;
    double test_2 = 0.001;

    if (IsCloseTo0 (test_1) == true)
    {
        TEST_OK(number);
    }

    else
    {
        TEST_FAILED(number, __LINE__, test_1, IsCloseTo0 (test_1), true);
    }

    number++;

    if (IsCloseTo0 (test_2) == false)
    {
       TEST_OK(number);
    }

    else
    {
        TEST_FAILED(number, __LINE__, test_2, IsCloseTo0 (test_2), false);
    }
}

bool IsCloseTo0 (double val)
{
    assert (isfinite (val));

    return fabs (val) < PRECISION;
}

void PrintAnswer (double first_root, double second_root, int num_roots)
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
            printf ("%s %lg %s %lg %s", "First root: ", first_root, "Second root: ", second_root, "\n");
            break;

        case INFINITY_ROOTS:
            printf ("Infinity number of roots\n");
            break;

        default:
            printf ("%s %d", "Error, unknown value of num_roots: ", num_roots);
            break;
    }
}
