#include <stdio.h>
#include <math.h>

const int infinity_roots = -1;

void ReadCoeffs(double *first_coef, double *second_coef, double *third_coef);
int EquationSolver(double first_coef, double second_coef, double third_coef, double *first_root, double *second_root);
void GetAnswer(double first_root, double second_root, int num_roots);

int main()
{
    double a = 0;
    double b = 0;
    double c = 0;

    ReadCoeffs(&a, &b, &c);

    double first_root = 0;
    double second_root = 0;

    int num_roots = EquationSolver(a, b, c, &first_root, &second_root);

    GetAnswer(first_root, second_root, num_roots);

    return 0;
}

void ReadCoeffs(double *first_coef, double *second_coef, double *third_coef)
{
    double a = 0;
    double b = 0;
    double c = 0;

    printf("Enter coefficient A in Ax^2+Bx+C formula: ");
    scanf("%lf", &a);
    printf("Enter coefficient B in Ax^2+Bx+C formula: ");
    scanf("%lf", &b);
    printf("Enter coefficient C in Ax^2+Bx+C formula: ");
    scanf("%lf", &c);

    *first_coef = a;
    *second_coef = b;
    *third_coef = c;
}

int EquationSolver(double first_coef, double second_coef, double third_coef, double *ptr_first_root, double *ptr_second_root)
{
    if (first_coef == 0)
    {
         if (second_coef == 0)
         {
             if (third_coef == 0)
             {
                 return infinity_roots;
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

  else
  {
    double discriminant = second_coef * second_coef - 4 * first_coef * third_coef;

    if (discriminant > 0)
    {
      *ptr_first_root = (-second_coef - sqrt(discriminant)) / 2 / first_coef;
      *ptr_second_root = (-second_coef + sqrt(discriminant)) / 2 / first_coef;

      return 2;
    }

    if (discriminant == 0)
    {
        *ptr_first_root = -second_coef / 2 / first_coef;

        return 1;
    }
    else
    {
      return 0;
    }
  }
}
void GetAnswer(double first_root, double second_root, int num_roots)
{
    switch (num_roots)
    {
        case 0:
        printf("No solutions");
        break;

        case 1:
        printf("%s %lf","The only root: ", first_root);
        break;

        case 2:
        printf("%s %lf %s %lf", "First root: ", first_root, "Second root: ", second_root);
        break;

        default:
        printf("Infinity number of roots");
        break;
    }
}
