#include <stdio.h>
#include <cs50.h>

// asks for user name; replies with a greeting
int main(void)
{
    string name = get_string("What's your name? ");
    printf("Hello, %s!\n", name);
}