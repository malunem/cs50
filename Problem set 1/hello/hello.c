#include <cs50.h>
#include <stdio.h>

int main(void)
{
    /*Asks user's name and then say hello, name*/
    string name = get_string("What's your name?\n");
    printf("Hello, %s\n", name);
}