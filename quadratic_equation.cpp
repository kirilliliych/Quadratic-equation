#include <stdio.h>
#include <math.h>
void ReadCoeffs(double *first_coef, double *second_coef, double *third_coef);
int EquationSolution(double *first_coef, double *second_coef, double* third_coef, double *ptr_first_root, double *ptr_second_root, bool *ptr_linear);
void GetAnswer(double first_root, double second_root, bool linear, int result);
int main()
{
  double a = 0;
  double b = 0;
  double c = 0;
  double *ptr_a = &a;
  double *ptr_b = &b;
  double *ptr_c = &c;
  ReadCoeffs(ptr_a, ptr_b, ptr_c);
  double first_root = 0;
  double second_root = 0;
  double *ptr_first_root = &first_root;
  double *ptr_second_root = &second_root;
  bool linear = false;
  bool *ptr_linear = &linear;
  int result = EquationSolution(ptr_a, ptr_b, ptr_c, ptr_first_root, ptr_second_root, ptr_linear);
  GetAnswer(first_root, second_root, linear, result);
  return 0;
}
void ReadCoeffs(double *first_coef, double *second_coef, double *third_coef)
{
  double a = 0;
  double b = 0;
  double c = 0;
  printf("%s", "Enter coefficient A in Ax^2+Bx+C formula: ");
  scanf("%lf", &a);
  printf("%s", "Enter coefficient B in Ax^2+Bx+C formula: ");
  scanf("%lf", &b);
  printf("%s", "Enter coefficient C in Ax^2+Bx+C formula: ");
  scanf("%lf", &c);
  *first_coef = a;
  *second_coef = b;
  *third_coef = c;
}
int EquationSolution(double *first_coef, double *second_coef, double* third_coef, double *ptr_first_root, double *ptr_second_root, bool *ptr_linear)
{
  double a = *first_coef;
  double b = *second_coef;
  double c = *third_coef;
  if (!a)
  {
    *ptr_linear = true;
     if (!b)
     {
       if (!c)
       {
         return 1;
       }
       else
       {
         return -1;
       }
     }
     else
     {
       *ptr_first_root = -c / b;
    }
  }
  else
  {
    double discriminant = b * b - 4 * a * c;
    if (discriminant > 0)
    {
      *ptr_first_root = (-b - sqrt(discriminant)) / 2 / a;
      *ptr_second_root = (-b + sqrt(discriminant)) / 2 / a;
    }
    else if (!discriminant)
    {
      *ptr_first_root = *ptr_second_root = -b / 2 / a;
    }
    else
    {
      return -1;
    }
  }
  return 0;
}
void GetAnswer(double first_root, double second_root, bool linear, int result)
{
  if (result == -1)
  {
    printf("%s", "No solutions");
  }
  else if (result == 1)
  {
    printf("%s", "Infinite quantity of roots");
  }
  else if (!(linear))
  {
    printf("%s%lf\n%s%lf", "First root: ", first_root, "Second root: ", second_root);
  }
  else
  {
    printf ("%s%lf", "The only root: ", first_root);
  }
}
