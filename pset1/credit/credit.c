// Verifies that the card number is legitimate and, if yes, indicates the card type (Visa, MASTERCARD, AMEX)
#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    long card_number = get_long("Number: ");
    long card_number_copy = card_number;
    long card = card_number;
    int sum_products = 0;
    int sum_other = 0;
    int length = 2;

    // Count a sum of the products
    while (card_number > 9)
    {
        int digit = ((card_number % 100) / 10) * 2;
        if (digit >= 10)
        {
            digit = (digit / 10) + (digit % 10);
        }
        sum_products = sum_products + digit;
        card_number = card_number / 100;
    }

    // Count a sum of all other digits in the card number
    while (card_number_copy > 0)
    {
        int digit = card_number_copy % 10;
        sum_other = sum_other + digit;
        card_number_copy = card_number_copy / 100;
    }
    // Final sum
    int sum = sum_products + sum_other;
    // Check whether the card is valid
    if (sum % 10 == 0)
    {
        // Cut of all the digits except first 2 and counts amount of digits overall
        while (card > 99)
        {
            card = card / 10;
            length++;
        }
        // Check whether its AMEX
        if (card == 34 || card == 37 & length == 15)
        {
            printf("AMEX\n");
        }
        // Check whether its MASTERCARD
        else if (card > 50 & card < 56 & length == 16)
        {
            printf("MASTERCARD\n");
        }
        // Check whether its VISA
        else if ((card / 10 == 4) & (length == 13 || length == 16))
        {
            printf("VISA\n");
        }
        // Define all other cases
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}