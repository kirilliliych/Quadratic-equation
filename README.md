# Quadratic-equation

### Features
Solves Ax^2 + Bx + C = 0 
***
### What it does 
This programme accepts three variables:  
A, B and C from Ax^2 + Bx + C = 0.
**Arguments' type is double! Do not try to initialize them with symbol, string, etc. It will not work!**
Then it solves the equation, telling whether it has no soultions, one, two or infinity of them and shows the roots if there are any.
***
### Functions
1. _void ReadCoeffs (double *first_coef, double *second_coef, double *third_coef)_ - accepts A, B and C.
2. _void RepeatInput (double *coefficient)_ - repeats input if there is a mistake.
3. _int SolveQuadraticEquation (double first_coef, double second_coef, double third_coef, double *ptr_first_root, double *ptr_second_root)_ - solves the quadratic equation __(calls SolveLinearEquation if needs)__, returns number of roots.
4. _int SolveLinearEquation (double second_coef, double third_coef, double *ptr_first_root)_ - solves the linear equation, returns number of roots. 
5. _bool IsCloseTo0 (double val)_ - decides whether double variable is equal to 0 with 0.001 precision.
6. _void PrintAnswer (double first_root, double second_root, int num_roots)_ - shows an answer.     
