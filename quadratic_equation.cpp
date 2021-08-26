#include <stdio.h>
#include <math.h>
#include <assert.h>

const int INFINITY_ROOTS = -1;                                                                                                                 // signals about infinite number of roots
const double PRECISION = 0.001;                                                                                                                // a precision of comparison double to 0

void ReadCoeffs (double *first_coef, double *second_coef, double *third_coef);
int SolveQuadraticEquation (double first_coef, double second_coef, double third_coef, double *ptr_first_root, double *ptr_second_root);
int SolveLinearEquation (double second_coef, double third_coef, double *ptr_first_root);
bool CloseTo0 (double val);
void PrintAnswer (double first_root, double second_root, int num_roots);

int main()
{
    printf("%s \n","///// QuadraticEquationSolver /////");
    printf("\t %s \n \n","(c) kirilliliych, 2021");
    double a = 0;
    double b = 0;
    double c = 0;

    ReadCoeffs (&a, &b, &c);

    double first_root = 0;
    double second_root = 0;

    int num_roots = SolveQuadraticEquation (a, b, c, &first_root, &second_root);

    PrintAnswer (first_root, second_root, num_roots);

    return 0;
}

void ReadCoeffs(double *first_coef, double *second_coef, double *third_coef)
{
    printf("Enter coefficient A in Ax^2+Bx+C formula: ");
    scanf("%lg", first_coef);
    printf("Enter coefficient B in Ax^2+Bx+C formula: ");
    scanf("%lg", second_coef);
    printf("Enter coefficient C in Ax^2+Bx+C formula: ");
    scanf("%lg", third_coef);
}

int SolveQuadraticEquation (double first_coef, double second_coef, double third_coef, double *ptr_first_root, double *ptr_second_root)
{
    assert(isfinite(first_coef));
    assert(isfinite(second_coef));
    assert(isfinite(third_coef));

    if (CloseTo0(fabs(first_coef)))
    {
        int n_linear_roots = SolveLinearEquation (second_coef, third_coef, ptr_first_root);
        return (n_linear_roots < 0) ? INFINITY_ROOTS : (n_linear_roots > 0) ? 1 : 0;
    }

  else
  {
      double discriminant = second_coef * second_coef - 4 * first_coef * third_coef;

      if (discriminant > 0)
      {
          *ptr_first_root = (-second_coef - sqrt(discriminant)) / (2 * first_coef);
          *ptr_second_root = (-second_coef + sqrt(discriminant)) / (2 * first_coef);

          return 2;
      }

      if (CloseTo0(fabs(discriminant)))
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
    assert(isfinite(second_coef));
    assert(isfinite(third_coef));

    if (CloseTo0(second_coef))
    {
        if (CloseTo0(third_coef))
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

bool CloseTo0 (double val)
{

    return fabs(val) < PRECISION;
}

void PrintAnswer (double first_root, double second_root, int num_roots)
{
    assert(isfinite(first_root));
    assert(isfinite(second_root));

    switch (num_roots)
    {
        case 0:
        printf("No solutions");
        break;

        case 1:
        printf("%s %lg","The only root: ", first_root);
        break;

        case 2:
        printf("%s %lg %s %lg", "First root: ", first_root, "Second root: ", second_root);
        break;

        case INFINITY_ROOTS:
        printf("Infinity number of roots");
        break;

        default:
        printf("Error, unknown value of num_roots");
        break;
    }
}
