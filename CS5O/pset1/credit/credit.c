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

    //counts a sum of the products
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

    //counts a sum of all other digits in the card number
    while (card_number_copy > 0)
    {
        int digit = card_number_copy % 10;
        sum_other = sum_other + digit;
        card_number_copy = card_number_copy / 100;
    }
    //a final sum
    int sum = sum_products + sum_other;
    //checks whether the card is valid
    if (sum % 10 == 0)
    {
        //cuts of all the digits except first 2 and counts amount of digits overall
        while (card > 99)
        {
            card = card / 10;
            length++;
        }
        //checks whether its AMEX
        if (card == 34 || card == 37 & length == 15)
        {
            printf("AMEX\n");
        }
        //checks whether its MASTERCARD
        else if (card > 50 & card < 56 & length == 16)
        {
            printf("MASTERCARD\n");
        }
        //checks whether its VISA
        else if ((card / 10 == 4) & (length == 13 || length == 16))
        {
            printf("VISA\n");
        }
        //in all other cases says that its invalid
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