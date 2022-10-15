#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

//Define functions used in main function

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    //Get the text and count its letters, numbers, and sentences. Float values use more bits, but the distinction is necessary to meet the requirement "handles single sentence with multiple words."
    
    string text = get_string("Text: ");
    float numletters = count_letters(text);
    float numwords = count_words(text);
    float numsentences = count_sentences(text);
    
    //Calculate average letters per 100 words and average sentences per 100 words. Apply Coleman-Liau index for value and round for grade level (allowing integer to truncate leads to incorrect rounding).
    
    float L = ((numletters * 100) / numwords);
    float S = ((numsentences * 100) / numwords);
    float index = ((0.0588 * L) - (0.296 * S) - 15.8);
    int gradelevel = roundf(index);
    
    //Print correct statements for "Before Grade 1", at grade level between 1 and 15, and grade 16+.
    
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if ((gradelevel >= 1) && (gradelevel <= 15))
    {
        printf("Grade %i\n", gradelevel);
    }
    else if (gradelevel >= 16)
    {
        printf("Grade 16+\n");
    }
    

}

//This function counts the number of upper and lower case letters in a string.

int count_letters(string textinput)
{
    int n = strlen(textinput);
    int lettercount = 0;
    int i = 0;

    for (i = 0; i <= n; i++)
    {
        //This loop ensures that only upper and lower case letters are included by excluding all characters with decimal ASCII values outside those of A-Z and a-z.
        if ((textinput[i] >= 65 && textinput[i] <= 90) || (textinput[i] >= 97 && textinput[i] <= 122))
        {
            lettercount++;
        }
    }
    return lettercount;
}

//This function counts the number of words in a string.

int count_words(string textinput)
{
    int n = strlen(textinput);
    int wordcount = 1;
    int i = 0;
    
    for (i = 0; i <= n; i++)
    {
        //This loop counts the number of spaces in a string. Given that there will be one word with no space in the beginning, the loop starts counting from one.
        if (textinput[i] == 32)
        {
            wordcount ++;
        }
    }
    
    return wordcount;
}

//This function counts the number of sentences in a string.
int count_sentences(string textinput)
{
    int n = strlen(textinput);
    int sentencecount = 0;
    int i = 0;
    
    for (i = 0; i <= n; i++)
    {
        //The criteria below adds one count for only the ASCII values of periods, question marks, and exclamation marks, which mark the end of every sentence.
        if ((textinput[i] == 46) || (textinput[i] == 33) || (textinput[i] == 63))
        {
            sentencecount ++;
        }
    }
    
    return sentencecount;
}
