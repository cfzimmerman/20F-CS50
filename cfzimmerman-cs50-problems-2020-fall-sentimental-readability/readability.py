import cs50
import re


def main():
    # Get text input, initialize letters and index variables, count the number of words, and add up the number of punctuation marks in the input
    text = cs50.get_string("Text: ")
    letters = 0
    index = 0
    words = text.count(" ") + 1
    punctuation = text.count(".") + text.count("!") + text.count("?")
    
    # Count the number of letters a through z and A through Z in the input
    # The line of code directly below  came from this webpage: https://stackoverflow.com/questions/18455222/how-to-count-the-number-of-letters-in-a-string-without-the-spaces
    letters = len(re.findall('[a-zA-Z]', text))
    
    # Calculate the average number of letters and sentences per 100 words
    avgwords = ((100*letters)/words)
    avgsent = ((100*punctuation)/words)
    
    # Calculate and round the index
    index = ((0.0588*avgwords) - (0.296*avgsent) - 15.8)
    index = round(index)
    
    # Screen for values above and below the grade level threshhold and print the lexile index
    if (index > 15):
        print("Grade 16+")
    elif (index < 1):
        print("Before Grade 1")
    else:
        print(f"Grade {index}")
 

if __name__ == "__main__":
    main()