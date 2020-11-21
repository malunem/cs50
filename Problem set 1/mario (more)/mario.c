#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    /*aks user for pyramid height between 1 and 8*/
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    if (height >= 1 && height <= 8)
    {
        /*make as rows as height*/
        for (int x = 1; x <= height; x++)
        {
            /*print as blank spaces as height minus number of hashes and decreases by 1 at every row*/
            for (int y = height - x; y > 0; y--)
            {
                printf(" ");
            }
            /*print 1 hash in the first row and increase by 1 until hashes quantity equals to height*/
            for (int z = 0; z < x; z++)
            {
                printf("#");
            }
            /*print 2 blank spaces*/
            printf("  ");
            /*print 1 hash in the first row and increase by 1 until hashes quantity equals to height*/
            for (int w = 0; w < x; w++)
            {
                printf("#");
            }
            printf("\n");
        }
    }
}