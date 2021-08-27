#include <assert.h>
#include <math.h>
#include <stdio.h>

#define TEST_OK(number) printf ("Test %d passed\n", number);

const int INFINITY_ROOTS = -1;                                                                                                                 // signals about infinite number of roots
const double PRECISION = 0.001;                                                                                                                // a precision of comparison double to 0 and double to double
const int ERROR = -2;                                                                                                                          // signals about an error in switch

void ReadCoeffs                      (double *first_coef, double *second_coef, double *third_coef);

int  CorrectInput                    (double *coefficient, bool if_testing);

void TestSolveQuadraticEquation      ();
int  SolveQuadraticEquation          (double first_coef, double second_coef, double third_coef, double *ptr_first_root, double *ptr_second_root);

void TestSolveLinearEquation         (double second_coef, double third_coef, double correct_root, int correct_number_roots, int number);
int  SolveLinearEquation             (double second_coef, double third_coef, double *ptr_first_root);

void TestIsCloseTo0                  ();
bool IsCloseTo0                      (double val);

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

void TestSolveLinearEquation (double second_coef, double third_coef, double correct_root, int correct_number_roots, int number)
{
  assert (isfinite (second_coef));
  assert (isfinite (third_coef));
  assert (isfinite (correct_root));

  double root = 0;

  int number_roots = SolveLinearEquation (second_coef, third_coef, &root);

  if ((correct_number_roots != number_roots) || (correct_root != root))
  {
      printf ("Test % failed line(%d)\n"
              "Input: B = %lg, C = %lg\n"
              "Output: number of roots = %d, root = %lg\n"
              "Output expected: number of roots = %d, root = %lg\n", number, __LINE__, second_coef, third_coef, number_roots, root, correct_number_roots, correct_root);
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

void TestIsCloseTo0 ()
{
    printf ("Testing function IsCloseTo0:\n\n");

    int number = 1;
    double test = 0.000999;


    number++;

    test = 0.001;


    printf ("\n");
}

bool IsCloseTo0 (double val)
{
    assert (isfinite (val));

    return fabs (val) < PRECISION;
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

