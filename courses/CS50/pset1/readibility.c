#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    string user_input;
    int i, len, alpha_count, words_count, sentence_count;
    float index, avg_letters, avg_sentences;
    alpha_count = 0;
    words_count = 1;
    sentence_count = 0;
    user_input = get_string("Text: ");
    //printf("\n");

    len = strlen(user_input);

    for (i = 0; i < len; i++)
    {
        if (isalpha(user_input[i]) != 0)
        {
            alpha_count += 1;
        }
        //if (user_input[i] == ' ' || i == len - 1)
        //if (isalpha(user_input[i]) != 0 && user_input[i-1] == ' ')
        if (user_input[i] != ' ' && user_input[i+1] == ' ')
        {
            words_count += 1;
        }
        if (user_input[i] == '.' || user_input[i] == '!' || user_input[i] == '?')
        {
            sentence_count += 1;
        }
    }

    avg_letters = (float) alpha_count / (float) words_count * 100;
    avg_sentences = (float) sentence_count / (float) words_count * 100;
    index = 0.0588 * avg_letters - 0.296 * avg_sentences - 15.8; // L - letters per 100 words, S - sentences per 100 words;

    printf("%i Letter(s)\n%i Word(s)\n%i sentence(s)\n", alpha_count, words_count, sentence_count);
    printf("avg_letters: %f, avg_sentences: %f, index: %f\n", avg_letters, avg_sentences, index);

    if ((int) round(index) < 1)
    {
        printf("Before Grade 1\n");
    }
    else if ((int) round(index) > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(index));
    }

    //382.14 7.14
    //22.469 2.11

}