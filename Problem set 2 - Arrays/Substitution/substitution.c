#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    //Check if there is only one key
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    
    string key = argv[1];
    int klen = strlen(argv[1]);
    
    //Check if key lenght is correct
    if (klen != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    
    for (int i = 0; i < klen; i++)
    {
        char c = key[i];
        
        //Check if every key character is a letter
        if (isupper(c) == 0 && islower(c) == 0)
        {
            printf("Invalid key\n");
            return 1;
        }
        
        //Check if key char is equal to a previous one
        for (int j = 0; j < i; j++)
        {
            if (c == key[j])
            {
                printf("Invalid key\n");
                return 1;
            }
        }
        //Check if key char is equal to a following
        for (int n = c + 1; n <= klen; n++)
        {
            if (c == key[n])
            {
                printf("Invalid key\n");
                return 1;
            }
        }
    }
    
    //Ask user for text to cipher and save its lenght
    string text = get_string("plaintext: ");
    
    int tlen = strlen(text);
    
    printf("ciphertext: ");
    
    //For every character, find the corresponding from the key using ascii numbers
    for (int m = 0; m < tlen; m++)
    {

        char c = text[m];
        int kn = (int) c;
        
        if (isupper(c))
        {
            c = toupper(key[kn - 65]);
        }
        else if (islower(c))
        {
            c = tolower(key[kn - 97]);
        }
        
        printf("%c", c);
    }
    
    printf("\n");
}