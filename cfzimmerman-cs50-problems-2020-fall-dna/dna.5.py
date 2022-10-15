import csv
import sys
import re
import functools

def main():
    if (len(sys.argv) != 3):
        print("Usage: python dna.py data.csv sequence.txt")
    csvfile = open(sys.argv[1])
    data = csv.DictReader(csvfile)
    
    txtfile = open(sys.argv[2])
    txt = txtfile.read()
    
    inplay = 0
    results = {}
    for value in data.fieldnames:
        results[value] = 0
        inplay += 1

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

# Scan through the "data" set of dictionaries to whose sequence matches with the "results" of scanning the genetic information
    names = []
    for value in data:
        for point in value:
            if (value[point].isnumeric() == True ):
                if (int(value[point]) == int(results[point])):
                    names.append(name)
            else:
                name = value[point]
    
    found = 0
    suspect = "No match"
    for i in range(len(names)):
        temp = names.count(names[i])
        if (temp > found):
            found = temp
            suspect = names[i]
    
    if (found >= inplay - 1):
        print(f"{suspect}")
    else:
        print("No match")
            
    
if __name__ == "__main__":
    main()