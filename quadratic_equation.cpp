void ReadCoeffs (double *first_coef, double *second_coef, double *third_coef)
    {
    assert (first_coef  != nullptr);
    assert (second_coef != nullptr);
    assert (third_coef  != nullptr);
    assert (isfinite (*first_coef));
    assert (isfinite (*second_coef));
    assert (isfinite (*third_coef));

    printf ("Enter coefficient A in Ax^2+Bx+C formula: ");

    EquationCoefGetRightInput (first_coef);

    printf ("Enter coefficient B in Ax^2+Bx+C formula: ");

    EquationCoefGetRightInput (second_coef);

    printf ("Enter coefficient C in Ax^2+Bx+C formula: ");

    EquationCoefGetRightInput (third_coef);
    }

void EquationCoefGetRightInput (double *coefficient)
    {
    assert (coefficient != nullptr);

    while (scanf ("%lg", coefficient) != 1)
        {
        printf ("Invalid input. Please, enter a number!\n");

        while (getchar () != '\n');
        }
    }

int SolveQuadraticEquation (double first_coef, double second_coef, double third_coef,
                            double *ptr_first_root, double *ptr_second_root)
    {
    assert (isfinite (first_coef));
    assert (isfinite (second_coef));
    assert (isfinite (third_coef));
    assert (ptr_first_root  != nullptr);
    assert (ptr_second_root != nullptr);
    assert (ptr_first_root  != ptr_second_root);

    if (IsEqualTo0 (first_coef))
        {
        return SolveLinearEquation (second_coef, third_coef, ptr_first_root);
        }

    double discriminant = second_coef * second_coef - 4 * first_coef * third_coef;

    if (IsEqualTo0 (discriminant))
        {
        *ptr_first_root = -second_coef / (2 * first_coef);

        return 1;
        }

    if (discriminant > PRECISION)
        {
        double discriminant_square_root = sqrt (discriminant);

        *ptr_first_root  = (-second_coef - discriminant_square_root) / (2 * first_coef);
        *ptr_second_root = (-second_coef + discriminant_square_root) / (2 * first_coef);

        return 2;
        }

    return 0;
    }

int SolveLinearEquation (double linear_coef, double constant_of_free_term, double *ptr_root)
    {
    assert (isfinite (linear_coef));
    assert (isfinite (constant_of_free_term));
    assert (ptr_root != nullptr);

    if (IsEqualTo0 (linear_coef))
        {
        if (IsEqualTo0 (constant_of_free_term))
            {
            return INFINITE_ROOTS_NUM;
            }
        else
            {
            return 0;
            }
        }
    else
        {
        *ptr_root = -constant_of_free_term / linear_coef;

        return 1;
        }
    }

bool IsEqualTo0 (double value)
    {
    assert (isfinite (value));

    return fabs (value) < PRECISION;
    }

void PrintAnswer (int number_of_roots, double first_root, double second_root)
    {
    assert (isfinite (first_root));
    assert (isfinite (second_root));

    switch (number_of_roots)
        {
        case 0:
            printf ("No solutions\n");
            break;

        case 1:
            printf ("%s %lg %s", "The only root: ", first_root, "\n");
            break;

        case 2:
            printf ("%s %lg %s %lg\n", "First root: ", first_root, "\tSecond root: ", second_root);
            break;

        case INFINITE_ROOTS_NUM:
            printf ("Infinite number of roots\n");
            break;

        default:
            printf ("%s %d\n", "Error, unknown value of number_of_roots: ", number_of_roots);
            break;

        }
    }

bool IsEqual (double value_1, double value_2)
    {
    assert (isfinite (value_1));
    assert (isfinite (value_2));

    return fabs (value_1 - value_2) <= PRECISION;
    }

void Swap (double *value_1, double *value_2)
    {
    assert (value_1 != nullptr);
    assert (value_2 != nullptr);

    double temp = *value_1;

    *value_1 = *value_2;
    *value_2 = temp;
    }



