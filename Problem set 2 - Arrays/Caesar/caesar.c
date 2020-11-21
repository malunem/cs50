#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    //Required arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    //Require all digits
    for (int i = 0, l = strlen(argv[1]); i < l; i++)
    {   
        if (isdigit(argv[1][i]) == 0)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    
    //Transform the array in an integer
    int k = atoi(argv[1]);
        
    //Ask user text to encrypt
    string text = get_string("plaintext: ");
    
    printf("ciphertext: ");
    
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        //Save current character
        char c = text[i];

        //Check if it's a letter, otherwise print as it is
        if (isupper(text[i]) || islower(text[i]))
        {
            for (int j = 0; j < k; j++)
            {
                c++;

                //Mantain char uppercase or lowercase
                if (isupper(text[i]) && c > 'Z')
                {
                    c = 'A';
                }
                
                if (islower(text[i]) && c > 'z')
                {
                    c = 'a';
                }
            }
        }
        
        printf("%c", c);
    }
    
    printf("\n");
    return 0;
}