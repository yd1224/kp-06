#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
double getInput(const char *prompt);
bool isScientificNotation(const char *input);
void Show(float **aValues, const float *bValues, int rows, int columns);
int main()
{
    float **a;
    float *b;
    int n;

    // Get the number of strings
    n = getInput("Enter the number of equations: ");

    // Allocate memory for b
    b = (float *)malloc(n * sizeof(float));

    // Allocate memory for a
    a = (float **)calloc(n, sizeof(float *));
    if (a == NULL || b == NULL)
    {
        printf("Memory allocation failed\n");
        return 1; // Exiting with an error code
    }

    // Get values for a and b
    for (int i = 0; i < n; i++)
    {
        // Allocate memory for a[i]
        a[i] = (float *)malloc(n * sizeof(float));
        if (a[i] == NULL)
        {
            printf("Memory allocation failed\n");
            return 1; // Exiting with an error code
        }

        // Get values for a[i]
        for (int j = 0; j < n; j++)
        {
            printf("Enter value for the a%d%d: ", i + 1, j + 1);
            a[i][j] = getInput("");
        }

        // Get value for b[i]
        printf("Enter value for the b%d: ", i + 1);
        b[i] = getInput("");
    }

    // Show the values
    Show(a, b, n, n);

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
            {
                printf(" + ");
            }
        }
        printf(" = %f", bValues[i]);
        printf("\n");
    }
}