#include <cs50.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
    /*Asks user for credit card number*/
    long card = get_long("Number: ");

    /*Set count as zero and anticipate n existence*/
    int count = 0;
    long n;

    /*Make a for loop that sets n as card number, works until n exists
    and delete the last digit of n at every iteration.*/
    for (n = card; n > 0; n /= 10)
    {
    	/*At every iteration, change count by 1.
    	Count will equal the number of digits*/
    	(count++);
    }

    /*Check if card has a legit number of digits*/
    if (count != 13 && count != 15 && count != 16)
    {
    	printf("INVALID1\n");
    	return 0;
    }

    /*Save the first two digits of card number*/
    long first2 = card;
    printf("first2: %li\n", first2);

    do
    {
        first2 /= 10;
        printf("first2: %li\n", first2);
        sleep(1);
    }
    while (first2 >= 100);
    
    printf("first2: %li\n", first2);

    /*Save the first digit of card number*/
    long first1 = first2 / 10;

    if (count == 13 || count == 15 || count == 16)
    {
    	/*Abort if card couldn't be an American Express, Visa or MasterCard*/
    	if ((count == 15 && (first2 != 34 && first2 != 37)))
    	{
    		printf("INVALID2\n");
    		return 0;
    	}
    	else
    	{
    	    printf("ok");
    	}
  }
}