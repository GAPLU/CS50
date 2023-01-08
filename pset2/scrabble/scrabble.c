#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Print the result
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    int score = 0;
    // A loop for computing the score
    for (int i = 0; i < strlen(word); i++)
    {
        // Makes every letter lowercase
        if (isupper(word[i]))
        {
            word[i] = word[i] + 32;
        }
        // Checks if its a letter
        if (word[i] >= 97 && word[i] <= 122)
        {
            // Assigns respective number for a letter
            int n = word[i] - 97;
            // Adds number to the overall score
            score = score + POINTS[n];
        }

    }
    return score;
}