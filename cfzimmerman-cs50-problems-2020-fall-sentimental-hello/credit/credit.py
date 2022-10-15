def main():
    while True:
        num = input("Number: ")
        if (True == num.isdigit()):
            break
    # After checking whether the input is only numbers, the value-in-num loop checks the how many numbers were provided
    count = 0
    for value in num:
        count += 1
    
    # Filter for characteristic number of digits and first few numbers
    # If the card fails any of the conditions below, it is marked INVALID
    if ((count == 12) or (count == 14) or (count == 15)):
        # American Express, 15 digits
        if (num[0] == str(3)):
            if ((num[1] == str(4)) or (num[1] == str(7))):
                lista = []
                suma = 0
                sumb = 0
                # Add the values that need to be doubled to a list and double them while doing so
                for a in range(1, 15, 2):
                    lista.append(int(num[a])*2) 
                # Cast the integers to strings to check their length using the str() function
                for b in range(7):
                    lista[b] = str(lista[b])
                # If the doubled list item has more than one digit, break the two digits apart and add them to the suma count (pronounced "sum" "A")
                for c in range(7):
                    if (len(lista[c]) == 1):
                        suma = int(lista[c]) + suma
                    else:
                        suma = (int(lista[c][0]) + int(lista[c][1]) + suma)
                # Add the integers that don't need to be doubled together in the sumb count ("sum" "B")
                for d in range(0, 16, 2):
                    sumb = int(num[d]) + sumb
                # If suma plus sumb is divisable by ten, the card number is authenticated
                if (((suma + sumb) % 10) == 0):
                    print("AMEX\n")
                else:
                    print("INVALID")
            else:
                print("INVALID")
    # The American Express comments almost perfectly match the steps required for Visa and Mastercard except the range() values vary based on how many numbers are on the card
    elif (num[0] == str(5)):
        # Mastercard, 16 digits
        if ((num[1] == str(1)) or (num[1] == str(2)) or (num[1] == str(3)) or (num[1] == str(4)) or (num[1] == str(5))):
            lista = []
            suma = 0
            sumb = 0
            for a in range(0, 16, 2):
                lista.append(int(num[a])*2) 
            for b in range(8):
                lista[b] = str(lista[b])
            for c in range(8):
                if (len(lista[c]) == 1):
                    suma = int(lista[c]) + suma
                else:
                    suma = (int(lista[c][0]) + int(lista[c][1]) + suma)
            for d in range(1, 17, 2):
                sumb = int(num[d]) + sumb
            if (((suma + sumb) % 10) == 0):
                print("MASTERCARD\n")
            else:
                print("INVALID\n")
        else:
            print("INVALID")
     
    elif (num[0] == str(4)):
        # Visa, 13 or 16 digits
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
        elif (count == 16):
            lista = []
            suma = 0
            sumb = 0
            for a in range(0, 16, 2):
                lista.append(int(num[a])*2) 
            for b in range(8):
                lista[b] = str(lista[b])
            for c in range(8):
                if (len(lista[c]) == 1):
                    suma = int(lista[c]) + suma
                else:
                    suma = (int(lista[c][0]) + int(lista[c][1]) + suma)
            for d in range(1, 17, 2):
                sumb = int(num[d]) + sumb
            if (((suma + sumb) % 10) == 0):
                print("VISA\n")
            else:
                print("INVALID\n")
        else:
            print("INVALID\n")
    else:
        print("INVALID\n")
        
    
if __name__ == "__main__":
    main()