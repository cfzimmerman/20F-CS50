#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float changeowed;
    
    do
    {
        changeowed = get_float("Change owed: ");
    }
    while (changeowed < 0);
    
    //Line below from CS50 guide
    int cents = round(changeowed * 100);
    
    int cashcounter = 0;
    
    //Count quarters
    while (cents >= 25)
    {
        cents = (cents - 25);
        cashcounter ++;
    }
    
    //Count dimes
    while (cents >= 10)
    {
        cents = (cents - 10);
        cashcounter ++;
    }
    
    //Count nickels
    while (cents >= 5)
    {
        cents = (cents - 5);
        cashcounter ++;
    }
    
    //Count pennies
    while (cents >= 1)
    {
        cents --;
        cashcounter ++;
    }
    
    printf("%i\n", cashcounter);
    
    
}