#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    // user must provide exactly one argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // cipher key must be exactly 26 characters
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    for (int i = 0; i < 26; i++)
    {
        // test for characters that are not alphabetic
        if (!isalpha(argv[1][i]))
        {
            printf("Key must contain only letters.\n");
            return 1;
        }

        // test for repeated characters
        for (int j = i + 1; j < 26; j++)
        {
            if (argv[1][i] == argv[1][j])
            {
                printf("Key must contain each letter only once.\n");
                return 1;
            }
        }
    }

    // if conditions met, proceed
    string plain = get_string("plaintext: ");
    string alpha = "abcdefghijklmnopqrstuvwxyz";
    string ciphr = argv[1];

    // prep list to hold changes to each letter
    int map[26];

    // find values for map
    for (int i = 0; i < 26; i++)
    {
        ciphr[i] = tolower(ciphr[i]);
        map[i] = (int)(ciphr[i] - alpha[i]);
    }

    // replace plain text with cipher text
    for (int i = 0, n = strlen(plain); i < n; i++)
    {
        if (plain[i] >= 65 && plain[i] <= 90)
        {
            plain[i] = plain[i] + map[plain[i] - 65];
        }
        else if (plain[i] >= 97 && plain[i] <= 122)
        {
            plain[i] = plain[i] + map[plain[i] - 97];
        }
    }

    // give user the output, passed through the cipher
    printf("ciphertext: %s\n", plain);

    // success!
    return 0;
}