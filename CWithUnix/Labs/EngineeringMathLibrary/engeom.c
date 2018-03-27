#include <stdio.h>

#define PI 3.14159265358979323846

void eng_sphere(float radius, float *surface, float *volume)
{
    *surface = 4.0 * PI * radius * radius;
    *volume = (4.0 / 3.0) * PI * radius * radius * radius;
    return;
}

float eng_volCylinder(float radius, float height)
{
    float volume = PI * radius * radius * height;
    return volume;
}

float eng_sumFloats(float x[], int numFloats)
{
    int min;
    float tmp;
    for (int i = 0; i < numFloats - 1; i++)
    {
        min = i;
        for (int j = i + 1; j < numFloats; j++)
        {
            if (x[j] < x[min])
            {
                min = j;
            }
        }
        if (min != i)
        {
            tmp = x[i];
            x[i] = x[min];
            x[min] = tmp;
        }
    }

    float sum = 0.0;
    for (int i = 0; i < numFloats; i++)
    {
        sum += x[i];
    }

    return sum;
}

int factorial(int n);
double powr(double base, int exponent);

double eng_sin(float angle)
{
    double EPSILON = 0.0000001;
    int i = 1, sign = 1;
    double result, rad;
    rad = angle / 180.0 * PI;
    while((powr(rad, i) / factorial(i)) > EPSILON)
    {
        result += sign * (powr(rad, i) / factorial(i));
        i += 2;
        sign *= -1;
    }

    return result;
}

int factorial(int n)
{
    int fact = 1;
    for (int i = n; i > 1; i--)
    {
        fact *= i;
    }

    return fact;
}

double powr(double base, int exponent)
{
    double total = 1;

    for (int i = 0; i < exponent; i++)
    {
        total *= base;
    }

    return total;
}

