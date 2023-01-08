import csv
import sys
from cs50 import get_int


def main():
    # Get a card number
    num = get_int("Number: ")
    # Count products sum
    sum_p = sum_prod(num)
    # Count sum of the rest
    sum_r = sum_rest(num)
    # Count total sum
    sum = sum_p + sum_r
    # Check if yhe last element is 0
    if int(sum % 10) == 0:
        # Remain only first 2 digits
        num = str(num)
        # Estimate a length
        length = len(num)
        num = int(num[:2])
        # Chek if it's AMEX
        if (num == 34 or num == 37) and length == 15:
            print("AMEX")
        # Check if it's MASTERCARD
        elif num > 50 and num < 56 and length == 16:
            print("MASTERCARD")
        # Check if it's VISA
        elif int(num / 10) == 4 and (length == 13 or length == 16):
            print("VISA")
        # Else it's invalid
        else:
            print("INVALID")
    else:
        print("INVALID")


# Count sum of the products
def sum_prod(num):
    sum = 0
    while num >= 10:
        digit = int(int((int(num % 100) / 10)) * 2)
        if digit > 9:
            digit = int((digit / 10)) + int((digit % 10))
        sum = sum + digit
        num = int(num / 100)
    return sum


# Counts sum of the rest
def sum_rest(num):
    sum = 0
    while num > 0:
        digit = int(num % 10)
        sum = sum + digit
        num = int(num / 100)
    return sum


if __name__ == "__main__":
    main()
