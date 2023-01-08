from cs50 import get_string
import curses.ascii


def main():
    # Get a text
    text = get_string("Text: ")
    # Count letters
    letters = count_letters(text)
    # Count words
    words = count_words(text)
    # Count sentences
    sentences = count_sentences(text)
    # Count 1st index
    L = (letters / words) * 100
    # Count 2nd index
    S = (sentences / words) * 100
    # Count main index
    index = round(0.0588 * L - 0.296 * S - 15.8)
    # Estimate a grade
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print("Grade ", + int(index))


# Count letters
def count_letters(text):
    letters = 0
    for i in range(len(text)):
        if curses.ascii.isalpha(text[i]):
            letters = letters + 1
    return letters


# Count words
def count_words(text):
    words = 0
    for i in range(len(text)):
        if text[i - 1] != '\000' and not text[i - 1] == ' ' and text[i] == ' ':
            words = words + 1
    if (text[len(text) - 1] == ' '):
        return words
    return words + 1


# Count sentences
def count_sentences(text):
    sentences = 0
    for i in range(len(text)):
        if text[i] == '.' or text[i] == '!' or text[i] == '?':
            sentences = sentences + 1
    return sentences


if __name__ == "__main__":
    main()