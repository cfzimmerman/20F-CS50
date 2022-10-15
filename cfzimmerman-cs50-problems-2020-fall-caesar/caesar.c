#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    //If the user inputs more or less command line arguments than two, an error message is displayed
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
        //Error key 1 means the user input the wrong number of command line arguments
    }

    string numbers = argv[1];
    int numlen = strlen(numbers);
    int i;
    int nothing = 0;

    //If the user's input includes anything other than numbers, an error message is displayed
    for (i = 0; i <= numlen; i++)
    {
        if (((numbers[i] >= 48) && (numbers[i] <= 57)) || (numbers[i] == 0))
        {
            //I am extremely self aware that I created a variable for it to do absolutely nothing, but I couldn't think of any other way to make the logic work for this task.
            nothing ++;
        }
        else
        {
            printf("Usage: ./caesar key\n");
            return 2;
            //Error key 2 means the user input non-characters into the command line
        }

    }
    
    //Lines 39 to 50 establish the number of letters shifted and keep the shift count from exceeding 25
    int shift = atoi(numbers);

    if (shift < 0)
    {
        printf("Usage: ./caesar key\n");
        return 3;
    }

    while (shift >= 26)
    {
        shift = shift - 26;
    }

    //Prompt user for text
    string plaintext = get_string("plaintext: ");
    
    //Count length of text for use in "for loop"
    int textlength = strlen(plaintext);
    int y;

    for (y = 0; y <= textlength; y++)
    {
        //If the input is an ASCII coded uppercase letter, shift it so that the output includes only uppercase letters. This means cycling values that otherwise exceed 90 back down to 65.
        if (plaintext[y] >= 65 && plaintext[y] <= 90)
        {
            if ((plaintext[y] + shift) > 90)
            {
                (plaintext[y] = plaintext[y] - (26 - shift));
            }
            else
            {
                (plaintext[y] = plaintext[y] + shift);
            }
        }
        //Lowercase version of the description on line 61
        else if (plaintext[y] >= 97 && plaintext[y] <= 122)
        {
            if ((plaintext[y] + shift) > 122)
            {
                (plaintext[y] = plaintext[y] - (26 - shift));
            }
            else
            {
                (plaintext[y] = plaintext[y] + shift);
            }
        }
    }
    
    printf("ciphertext: %s\n", plaintext);

    return 0;

}
