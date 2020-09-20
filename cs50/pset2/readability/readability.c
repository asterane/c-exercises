#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // get text for readability test; find length
    string text = get_string("Text: ");
    int length = strlen(text);

    // initialize variables for tracking statistics
    int letters = 0;
    int words = 1;
    int sentences = 0;

    // characterize contents of the text
    for (int i = 0; i < length; i++)
    {
        // locate all letters
        if ((text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122))
        {
            letters++;

            // if preceding character is a space or quotes, a word begins here
            if (text[i - 1] == 32 || text[i - 1] == 34)
            {
                words++;
            }
            // if following character is ( . ! ? ), a sentence ends here
            else if (text[i + 1] == 33 || text[i + 1] == 46 || text[i + 1] == 63)
            {
                sentences++;
            }
        }
    }

    //printf("%i letters; %i words; %i sentences\n", letters, words, sentences);

    // get characteristics for readability test
    float L = ((float) letters / words) * 100.0;
    float S = ((float) sentences / words) * 100.0;

    // find Coleman-Liau index
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // print grade level back to user
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
        printf("Grade %i\n", index);
    }
}