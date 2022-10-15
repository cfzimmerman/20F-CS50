#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

//Initialize function
int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);
    
    //Determine the winner by way of comparing greater and lesser scores
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
    
    //Return the value 0 to show that the program completed successfully
    return 0;

    // TODO: Print the winner
}

int compute_score(string word)
{
    //Initialize the variables needed for the function
    int i = 0;
    int score = 0;
    int n = strlen(word);
    
    for (i = 0; i < n; i++)
    {
        //If the character does not fit within the ASCII confines of upper or lower case letters, set the non-letter value to zero
        if ((word[i] >= 65 && word[i] <= 90) || (word[i] >= 97 && word[i] <= 122))
        {
            //Subtract 97 so that the value of an ASCII lowercase letter will correspond with the POINTS array at the top. For example, setting "a" equal to position zero giving it one point.
            if (islower(word[i]))
            {  
                (word[i] = word[i] - 97);
            }
            //Subtract 65 so that the value of an ASCII uppercase letter will correspond with the POINTS array at the top. For example, setting "A" equal to position zero giving it one point. 
            else
            {
                (word[i] = word[i] - 65);
            }
        
            //Create an integer value that can be used to compare the position of a letter on the POINTS array with its actual point value
            int p = word[i];
            
            //Add up the score of each letter of the word
            score = score + POINTS[p];
        }
        
        //This sets the value of all non-letter inputs to zero
        else (word[i] = 0);
    }
    
    return score;
}