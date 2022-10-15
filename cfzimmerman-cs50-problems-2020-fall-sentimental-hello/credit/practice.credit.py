def main():
    while True:
        num = input("Number: ")
        if (True == num.isdigit()):
            break
    count = 0
    for value in num:
        count += 1
    listcount = 0

    if (num[0] == str(4)):
        # Visa, 13 or 16
        if (count == 13):
            lista = []
            suma = 0
            sumb = 0
            for a in range(1, 13, 2):
                lista.append(int(num[a])*2) 
            for b in range(6):
                lista[b] = str(lista[b])
            for c in range(6):
                if (len(lista[c]) == 1):
                    suma = int(lista[c]) + suma
                else:
                    suma = (int(lista[c][0]) + int(lista[c][1]) + suma)
            for d in range(0, 14, 2):
                sumb = int(num[d]) + sumb
            if (((suma + sumb) % 10) == 0):
                print("VISA\n")
            else:
                print("INVALID\n")
        else:
            print("INVALID")

if __name__ == "__main__":
    main()
    
    #for c in range(0, 16, 2):
        #listb.append(num[c])
    #for d in range(8):
        #numbersb.join(listb[d])
        #summation = summation + sum(numbersb)
    #if (summation % 10 == 0):
        #print("AMEX\n")