#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //prompt for name of user
    string name = get_string("What's your name?\n");
    
    //print name of user
    printf("hello, %s\n", name);
}