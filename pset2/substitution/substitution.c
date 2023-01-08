#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Checks if its only 1 string
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // Checks if its 26 letters
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    // Saves key into its own variable
    string key = argv[1];
    // Checks if this 26 letters make a cipher
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        // Checks if its only letters
        if (!isalpha(key[i]))
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
        // Checks if every letter is unique
        for (int j = 0; j < strlen(argv[1]); j++)
        {
            if (tolower(key[i]) == tolower(key[j]) && i != j)
            {
                printf("Usage: ./substitution key\n");
                return 1;
            }
        }
    }
    // Prompts user to type text
    string plaintext = get_string("plaintext: ");
    // Prints encrypted text
    printf("ciphertext: ");
    // Enctypts every letter
    for (int i = 0; i < strlen(plaintext); i++)
    {
        // Checks if its uppercase
        if (isupper(plaintext[i]))
        {
            printf("%c", toupper(key[plaintext[i] - 65]));
        }
        // Checks if its lowercase
        else if (islower(plaintext[i]))
        {
            int m = plaintext[i] - 97;
            char k = key[plaintext[i] - 97];
            printf("%c", tolower(key[plaintext[i] - 97]));
        }
        // Prints all non-letter characters without changes
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    return 0;
}