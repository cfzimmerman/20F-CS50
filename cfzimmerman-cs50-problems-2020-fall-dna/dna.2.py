import csv
import sys

def main():
    if (len(sys.argv) != 3):
        print("Usage: python dna.py data.csv sequence.txt")
    csvfile = open(sys.argv[1])
    csvstr = csvfile.read()
    txtfile = open(sys.argv[2])
    txt = txtfile.read()
    
    table = {}
    
            
    
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
                
    print(f"{results}")
    print(f"{type(csvdict)}")
    
if __name__ == "__main__":
    main()