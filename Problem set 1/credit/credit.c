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
        printf("INVALID\n");
        return 0;
    }
    
    /*Save the first two digits of card number*/
    long first2 = card;
    	
    do
    {
        first2 /= 10;
    }
    while (first2 >= 100);
    	
    /*Save the first digit of card number*/
    long first1 = first2 / 10;
    
    if (count == 13 || count == 15 || count == 16)
    {
        /*Abort if card couldn't be an American Express, Visa or MasterCard*/
        if ((count == 15 && (first2 != 34 && first2 != 37)) ||
            (count == 13 && first1 != 4) || (count == 16 && ((first1 != 4) &&
                                             (first2 != 51 && first2 != 52 && first2 != 53 && first2 != 54 && first2 != 55))))
        {
            printf("INVALID\n");
            return 0;
            
        }
    }
    
    int sum1 = 0;
    long dig2 = card;
    int add;
    int adddig = 0;
    
    /*Make a for loop that sets dig2 as card number, work until dig2 exists
    and delete the last digit of dig2 at every iteration.*/
    for (dig2 = card; dig2 > 0; dig2 /= 10)
    {
        /*Remove another last digit so to consider every other digit*/
        dig2 /= 10;
        /*Divide dig2 by 10, consider the remainder, multiply it by 2 and add it to sum1*/
        add = ((dig2 % 10) * 2);
        if (add > 9)
        {
            adddig = add % 10;
            add /= 10;
            adddig = adddig + add;
            add = 0;
        }
    	
        sum1 = (sum1 + add + adddig);
        adddig = 0;
    }
    
    long dig1 = card;
    
    /*Make a for loop that sets dig1 as card number, work until dig1 exists
    and delete the last digit of dig1 at every iteration.*/
    for (dig1 = card; dig1 > 0; dig1 /= 10)
    {
        /*Divide dig2 by 10, consider the remainder and add it to sum1*/
        sum1 = (sum1 + (dig1 % 10));
        /*Remove another last digit so to consider every other digit*/
        dig1 /= 10;
    }
    
    /*abort if sum check isn't right*/
    if ((sum1 % 10) != 0)
    {
        printf("INVALID\n");
    }
    
    if ((sum1 % 10) == 0)
    {
        if (count == 15)
        {
            printf("AMEX\n");
        }
        if (count == 13)
        {
            printf("VISA\n");
        }
        if (count == 16 && first1 == 4)
        {
            printf("VISA\n");
        }
        else if (count == 16 && (first2 == 51 || first2 == 52 || first2 == 53 || first2 == 54 || first2 == 55))
        {
            printf("MASTERCARD\n");
        }
    }
}