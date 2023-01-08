#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Prompts user to insert the text
    string text = get_string("Text: ");
    // Counts letters
    float letters = count_letters(text);
    // Counts words
    float words = count_words(text);
    // Counts sentences
    float sentences = count_sentences(text);
    // Counts amount of letters per 100 words
    float L = (letters / words) * 100.0;
    // Counts amount of sentences per 100 words
    float S = (sentences / words) * 100.0;
    // Counts an index
    float index = round(0.0588 * L - 0.296 * S - 15.8);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) index);
    }
}

// Count letters in the text
int count_letters(string text)
{
    int letters = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }
    return letters;
}

// Counts amount of words in the text
int count_words(string text)
{
    int words = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i - 1] != '\000' && text[i - 1] != ' ' && text[i] == ' ')
        {
            words++;
        }
    }
    if (text[strlen(text) - 1] == ' ')
    {
        return words;
    }
    return words + 1;
}

// Counts amount of sentences in the text
int count_sentences(string text)
{
    int sentences = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}

