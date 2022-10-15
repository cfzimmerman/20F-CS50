import csv
import sys
import re

def main():
    if (len(sys.argv) != 3):
        print("Usage: python dna.py data.csv sequence.txt")
    csvfile = open(sys.argv[1])
    csvdata = csvfile.read()
    # The line of code below comes from this webpage: https://www.geeksforgeeks.org/python-extract-words-from-given-string/
    csvdata = re.findall(r'\w+', csvdata) 
    
    people = {}
    peoplecount = 0
    
    for item in csvdata:
        if ((item.isalpha()) == True):
            name = item
            people[name] = []
            peoplecount += 1
        else:
            people[name].append(item)
    
    # In hindsight, I realize how ominous it sounds to "delete people." No dystopian intentions here.
    if peoplecount == 7:
        del people["name"]
        del people["AGATC"]
        del people["AATG"]
        del people["TATC"]
        
    if peoplecount == 32:
        del people["name"]
        del people["AGATC"]
        del people["TTTTTTCT"]
        del people["AATG"]
        del people["TCTAG"]
        del people["GATA"]
        del people["TATC"]
        del people["GAAA"]
        del people["TCTG"]
        
    print(f"{people}")
    
    txtfile = open(sys.argv[2])
    txt = txtfile.read()
    
    results = {
    "AATG" : 0,
    "TATC" : 0,
    "TCTG" : 0,
    "GAAA" : 0,
    "GATA" : 0,
    "AGATC" : 0,
    "TCTAG" : 0,
    "TTTTTTCT" : 0,
    }
    
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
                    
    
if __name__ == "__main__":
    main()