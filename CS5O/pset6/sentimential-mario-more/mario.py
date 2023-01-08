import csv
import sys
from cs50 import get_int


def main():
    # Check if the prompt is correct
    while True:
        n = get_int('Height: ')
        if n > 0 and n < 9:
            break
    # Build a pyramid
    pyramid(n, 0)


# Draw a pyramid
def pyramid(height, edge):
    if height == 0:
        return
    pyramid(height - 1, edge + 1)
    print(' ' * edge + '#' * height + '  ' + '#' * height, end="")
    print()


if __name__ == "__main__":
    main()