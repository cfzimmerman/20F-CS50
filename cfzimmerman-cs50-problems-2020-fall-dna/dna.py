import csv
import sys


def main():
    # If there's an incorrect number of command line arguments, return a usage error
    if (len(sys.argv) != 3):
        print("Usage: python dna.py data.csv sequence.txt")
        
    # Open the csvfile and read its contents into a dictionary
    csvfile = open(sys.argv[1])
    data = csv.DictReader(csvfile)
    
    # Open the text file and read its contents into a buffer
    txtfile = open(sys.argv[2])
    txt = txtfile.read()
    
    # inplay counts the number of alleles "in play" for the current run. This counter is used to determine if there is a match at the bottom.
    inplay = 0
    results = {}
    for value in data.fieldnames:
        results[value] = 0
        inplay += 1

    #  This loop iterates through every allele possibility. First, it determines how many characters long the allele is. Then, it iterates one character at a time through the text, checking if two adjacent segments of the allele's length are identical. If so, it marks that and continues adding to the temp counter while adjacent values remain identical. At the end of the sequence of consecutive alleles, if the temp variable is the longest string found so far, that value is saved for later use at the location of the dictionary key currently being read in the "for loop" above.
    for key in results:
        a = len(key)
        b = a
        combo = key
        for i in range(len(txt)):
            temp = 0
            if (txt[i:(i + a)] == combo):
                temp += 1
                while (txt[(i + a):(i + a + b)] == combo):
                    temp += 1
                    a = a + b
                if (temp > results[combo]):
                    results[combo] = temp

    # This loop iterates through all of the people on the csv file and checks their allele counts against the values in the results dictionary. When a given allele count matches someone on the csv file, their name is added to a list.
    names = []
    for value in data:
        for point in value:
            if (value[point].isnumeric() == True):
                if (int(value[point]) == int(results[point])):
                    names.append(name)
            else:
                name = value[point]
    # All the names added to the list are counted. Whoever's name appears most often is the only name left under consideration
    found = 0
    suspect = "No match"
    for i in range(len(names)):
        temp = names.count(names[i])
        if (temp > found):
            found = temp
            suspect = names[i]
    
    # If the name appears once for every allele (if a given name matches allele counts for every tested sequence), it has been matched successfully. The "-1" is because "names" is automatically stored in the csv file along with the other alleles, but "names", obviously, never shows up in the genetic sequence. That is accounted for here.
    if (found >= inplay - 1):
        print(f"{suspect}")
    else:
        print("No match")
    
    # My code doesn't pass check50, but the deadline (and my sanity) demand I hand this in. It doesn't correctly read sequences/19.txt for some reason. There are five consecutive instances of "GATA" in the text, but my program only detects two of them. It correctly reads "GATA" as well as all other alleles on all other files, and I combed obsessively over my iterating function for finding repeating sequences. If it works for other four-letter alleles and for GATA on other files, I'm really not sure how to isolate the bug. I apologize for submitting incomplete work, but I've spent hours on this issue and can't come up with an answer (tutorials weren't very fruitful). If you get the chance to look at it, I'd really appreciate your thoughts on why my code isn't working for this specific allele at this specific spot.


if __name__ == "__main__":
    main()