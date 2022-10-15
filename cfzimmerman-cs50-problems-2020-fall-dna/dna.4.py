import csv
import sys
import re
import functools

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
            people[name].append(int(item))
    
    hitlist = []
    for name in people:
        if (name[0].islower() == True):
            hitlist.append(name)
        
        if (name.isupper() == True):
            hitlist.append(name)
    for target in hitlist:
        garbage = people.pop(target)
    
    txtfile = open(sys.argv[2])
    txt = txtfile.read()
    
    data = csv.DictReader(f)
    data.fieldnames
    data.fieldnames = [name, StR]
    
    results = {
    "AGATC" : 0,
    "TTTTTTCT" : 0,
    "AATG" : 0,
    "TCTAG" : 0,
    "GATA" : 0,
    "TATC" : 0,
    "GAAA" : 0,
    "TCTG" : 0,
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
            
    result_list =list(results.values())

    print(f"{results}\n\n")
    print(f"{people}")

    
if __name__ == "__main__":
    main()
    
    