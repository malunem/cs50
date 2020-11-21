#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    /*Asks user how much is owed*/
    float dollars;
    do
    {
        dollars = get_float("Change owed: ");

    }
    while (dollars <= 0);
	
    /*Transform dollars in cents and round it*/
    int cents = round(dollars * 100);
    /*Divide cents by quarters, dimes, nickels and pennies and save partial results*/
    int quarters = (cents / 25);
    cents = (cents - (quarters * 25));
    int dimes = (cents / 10);
    cents = (cents - (dimes * 10));
    int nickels = (cents / 5);
    cents = (cents - (nickels * 5));
    int pennies = (cents / 1);
	
    /*Sum partial results to get total number of coins and print*/
    int coins = (quarters + dimes + nickels + pennies);
    printf("%i\n", coins);

}