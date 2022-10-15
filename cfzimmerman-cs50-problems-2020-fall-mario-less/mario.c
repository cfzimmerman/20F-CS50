#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Prompt user for number between one and eight, inclusive
   int height;
   do
   {
       height = get_int("Height: ");
   }
   while ((height > 8) || (height < 1));

   //Make a pyramid that follows the height condition
   
   //Begin by initializing variables that represent the number of hashes and spaces as well as counters that regulate how often the cycle needs to repeat
   
   int topfloorhash = ((height + 1) - height);
   int topfloorhashcounter = topfloorhash + 1;
   int heightcounter = ((height + 1) - height);
   int topfloorhashcountercounter = topfloorhashcounter;
   int heightspace = (height - 1);
   int heightspacecounter = heightspace;

    do
    {

        while (heightspacecounter > 0)
        {
            printf(" ");
            heightspacecounter --;
        }
        
        //This loop is for placing hashes
        while (topfloorhashcounter <= (heightcounter + 1))
        {
            printf("#");
            topfloorhashcounter ++;
            topfloorhashcountercounter ++;
        }

        //These conditions set the total structure of the loop by changing hash and space counts and going to new lines
        
        topfloorhash ++;
        heightspace --;
        heightcounter = topfloorhashcountercounter ++;
        heightspacecounter = heightspace;
        printf("\n");
    }
    while (topfloorhash <= height);


}