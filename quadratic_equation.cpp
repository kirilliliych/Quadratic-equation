#include <bits\stdc++.h>
using namespace std;
int main()
{
long double a,b,c;
cout << "Enter coefficient A in Ax^2+Bx+C formula: ";
cin >> a;
while(!a)
{
cout << "That's not a quadratic equation. Please, enter coefficient A in Ax^2+Bx+C formula again:";
cin >> a;
}
cout << "Enter coefficient B in Ax^2+Bx+C formula: ";
cin >> b;
cout << "Enter coefficient C in Ax^2+Bx+C formula: ";
cin >> c;
long double discriminant = b*b-4*a*c;
if(discriminant>0)
{
cout << "Root 1: " << ((-1)*b-sqrt(discriminant))/2/a << endl << "Root 2: " << ((-1)*b+sqrt(discriminant))/2/a;
}
else if (!discriminant)
{
cout << "The only root is: " << (-1)*b/2/a;
}
else cout << "There are no roots in real numbers";
return 0;
}
