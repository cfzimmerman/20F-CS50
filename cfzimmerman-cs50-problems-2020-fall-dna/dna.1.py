import csv
import sys

def main():
    if (len(sys.argv) != 3):
        print("Usage: python dna.py data.csv sequence.txt")
    csvfile = open(sys.argv[1])
    csvdict = csv.DictReader(csvfile)
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
    
    for i in range(len(txt)):
        
        a = 4
        b = 5
        c = 8
        temp = 0
        
        if (txt[i:(i + a)] == "AATG"):
            temp += 1
            while (txt[(i + a):(i + a + 4)] == "AATG"):
                temp += 1
                a = a + 4
            if (temp > results["AATG"]):
                results["AATG"] = temp
                
    print(f"{results}")

    
if __name__ == "__main__":
    main()