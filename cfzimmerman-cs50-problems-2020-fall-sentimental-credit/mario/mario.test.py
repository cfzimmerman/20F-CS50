def main():
    height = int(input("Height: "))
    while ((height < 1) or (height > 8)):
        height = int(input("Height: "))
    h = "#"
    s = " "
    for i in range(1, (height + 1)):
        if ((height-i) == 0):
            print((h*i), (""), (h*i))
        else:
            print((s*(height-i-1)), (h*i), (""), (h*i))

if __name__ == "__main__":
    main()