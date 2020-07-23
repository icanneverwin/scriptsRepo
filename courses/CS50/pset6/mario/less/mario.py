#lines = int(input("Height: "))
#for i in range(1, lines + 1):
#    for j in range(lines - 1, 0, -1):
#        print(" " * j, end="")
#    print("#")

from cs50 import get_int

while True:
    lines = get_int("Height: ")
    if lines > 0 and lines < 9:
        break
j = 1

for i in range(lines - 1, -1, -1):
    print(" " * i, end ="")
    print("#" * j)
    j += 1
