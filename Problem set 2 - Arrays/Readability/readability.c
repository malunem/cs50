#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int main(void)
{
    //Ask input from user
    string text = get_string("Text: ");
    
    int chars = strlen(text);
    int letters = 0;
    int words = 0;
    int sentences = 0;
    
    //Count letters, words and sentences
    for (int n = 0; n <= chars; n++)
    {
        if ((text[n] >= 'a' && text[n] <= 'z') || (text[n] >= 'A' && text[n] <= 'Z'))
        {
            letters++;
        }
    	
        else if (text[n] == ' ' || text[n] == '\0')
        {
            words++;
        }
    	
        else if (text[n] == '.' || text[n] == '?' || text[n] == '!')
        {
            sentences++;
        }
    }
    
    // Calculate the average number of letters per 100 word
    float L = (float) letters / (float) words * 100;

    // Calculate the average number of sentences per 100 words
    float S = (float) sentences / (float) words * 100;
    
    //Apply Coleman-Liau index formula
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    
    //Print result
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    
    else if (index >= 1 && index < 16)
    {
        printf("Grade %i\n", index);
    }
    
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
}