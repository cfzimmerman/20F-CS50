def main():
    height = int(input("Height: "))
    while ((height < 1) or (height > 8)):
        height = int(input("Height: "))
    h = "#"
    s = " "
    for i in range(height):
        print((s * (height - i - 1)), (h * (i + 1)))

if __name__ == "__main__":
    main()