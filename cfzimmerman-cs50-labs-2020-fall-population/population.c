#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    //Prompt user for start size greater than 9
    int popstart;
    do
    {
        popstart = get_int("Start size: ");
    }
    while (popstart < 9);

    //Prompt user for end size greater than or equal to popstart
    int popend;
    do
    {
        popend = get_int("End size: ");
    }
    while (popend < popstart);

    //Determine years elapsed in the scenario

    int years;
    years = 0;

    while (popend > popstart)
    {
        (popstart = (popstart + (popstart/3) - (popstart/4)));
        years ++;
    }

    printf("Years: %i\n", years);


}