#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
double getInput(const char *prompt);
bool isScientificNotation(const char *input);
void Show(float **aValues, const float *bValues, int rows, int columns);
int checkConvergence(float **aValues, int rows, int columns);
int main()
{
    float **a;
    float *b;
    float accuracy;
    float *x0;
    float *x;
    int n;
    float max;

    while (1)
    {
        n = getInput("Enter the number of equations: ");
        b = (float *)malloc(n * sizeof(float));
        a = (float **)calloc(n, sizeof(float *));
        if (a == NULL || b == NULL)
        {
            printf("Memory allocation failed\n");
            return 1;
        }

        // Get values for a and b
        for (int i = 0; i < n; i++)
        {
            a[i] = (float *)malloc(n * sizeof(float));
            if (a[i] == NULL)
            {
                printf("Memory allocation failed\n");
                return 1;
            }

            for (int j = 0; j < n; j++)
            {
                printf("Enter value for the a%d%d: ", i + 1, j + 1);
                a[i][j] = getInput("");
            }

            printf("Enter value for the b%d: ", i + 1);
            b[i] = getInput("");
        }
        // Check convergence
        if (checkConvergence(a, n, n))
        {
            break;
        }
        else
        {
            printf("Could not converge. Please enter different values.\n");
        }
    }
    Show(a, b, n, n);
    // Getting accuracy
    while (1)
    {
        accuracy = getInput("Please, enter the accuracy (0-1): ");
        if (accuracy <= 0 || accuracy > 1)
        {
            printf("Error. Please, try again\n");
        }
        else
        {
            break;
        }
    }
    x0 = (float *)malloc(n * sizeof(float));
    x = (float *)malloc(n * sizeof(float));
    for (int i = 0; i < n; i++)
        x0[i] = b[i] / a[i][i];
    do
    {
        float max = 2 * accuracy;
        for (int i = 0; i < n; i++)
        {
            float sum = 0.0;
            for (int j = 0; j < n; j++)
            {
                if (j != i)
                {
                    sum += a[i][j] * x0[j];
                }
            }

            x[i] = b[i] + sum;
        }

        for (int i = 0; i < n; i++)
        {
            if (fabs(x[i] - x0[i]) > max)
            {
                max = fabs(x[i] - x0[i]);
            }
        }

        for (int i = 0; i < n; i++)
        {
            x0[i] = x[i];
        }
    } while (max > accuracy);
    for (int i = 0; i < n; i++)
        printf("%f", x0[i]);
    // Free memory
    for (int i = 0; i < n; i++)
    {
        free(a[i]);
    }
    free(a);
    free(b);

    return 0;
}

double getInput(const char *prompt)
{
    const int SIZE = 100;
    char input[SIZE];
    double number;

    do
    {
        printf("%s", prompt);
        scanf("%s", input);

        int invalidInput = 0;
        for (int i = 0; input[i]; i++)
        {
            if (isdigit(input[i]) == 0 && input[i] != '.' && input[i] != '-' && !isScientificNotation(input))
            {
                printf("\nYour input is invalid\n");
                invalidInput = 1;
                break;
            }
        }

        if (!invalidInput)
        {
            number = atof(input);
            break;
        }
    } while (1);

    return number;
}

bool isScientificNotation(const char *input)
{
    int len = strlen(input);
    int eCount = 0;
    int digitsBeforeE = 0;
    int digitsAfterE = 0;

    for (int i = 0; i < len; i++)
    {
        char c = input[i];
        if (c == 'e' || c == 'E')
        {
            eCount++;
        }
        else if (isdigit(c) && eCount == 0)
        {
            digitsBeforeE++;
        }
        else if (isdigit(c) && eCount == 1)
        {
            digitsAfterE++;
        }
    }

    return (eCount == 1) && (digitsBeforeE > 0) && (digitsAfterE > 0);
}
void Show(float **aValues, const float *bValues, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            printf("%fx", aValues[i][j]);
            if (j < columns - 1)
                printf(" + ");
        }
        printf(" = %f", bValues[i]);
        printf("\n");
    }
}
int checkConvergence(float **aValues, int rows, int columns)
{
    int convergenceFlag = 1;

    for (int row = 0; row < rows; row++)
    {
        float rowSum = 0.0;

        // Calculate the sum of elements in the current row excluding the diagonal element
        for (int col = 0; col < columns; col++)
        {
            if (col != row)
                rowSum += aValues[row][col];
        }

        // Check if the diagonal element is less than or equal to the sum of other elements in the row
        if (aValues[row][row] <= rowSum)
        {
            convergenceFlag = 0;
            break;
        }
    }
    return convergenceFlag;
}
