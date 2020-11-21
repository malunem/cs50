#include <stdio.h>
#include <cs50.h>

int fact(int n);
int reps = 0;

int main(void)
{
    int n = get_int("number: ");
    
    fact(n);
    
    printf("%i\n", reps);
}

int fact(int number)
{
    if (number == 1)
    {
        return 1;
    }
    else if (number%2 == 0)
    {
        reps++;
        return fact(number / 2);
    }
    else
    {
        reps++;
        return fact(3 * number + 1);
    }
}