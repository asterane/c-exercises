#include <stdio.h>
#include <stdlib.h>

#define LEN 45

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s dict\n", argv[0]);
        return 1;
    }

    char *inname = argv[1];
    FILE *infile = fopen(inname, "r");
    if (infile == NULL) {
        printf("Could not open in.\n");
        return 1;
    }

    char *outname = "hash.txt";
    FILE *outfile = fopen(outname, "w");
    if (outfile == NULL) {
        printf("Could not open out.\n");
        return 1;
    }

    char word[LEN + 1];
    char c;
    
    int hash;
    int values[65536] = { 0 };
    int distrib[128] = { 0 };
    
    while (fgets(word, LEN + 2, infile)) {
        c = word[0];
        hash = 1;
        for (int i = 0; c != '\0'; i++, c = word[i]) {
            hash = hash + c;
            hash = hash + (hash << 5);
        }

        hash = hash & 65535;
        values[hash]++;
        fprintf(outfile, "%i\n", hash);
    }

    for (int i = 0; i < 65536; i++) {
        distrib[values[i]]++;
        //fprintf(outfile, "%i\n", values[i]);
    }

    float avg = 0.0;
    
    for (int i = 0; i < 16; i++) {
        avg += (i * distrib[i]);
        //printf("%i hits: %i\n", i, distrib[i]);
    }

    avg /= (65536 - distrib[0]);
    printf("Avg hits: %.4f\n", avg);
    printf("Utilized: %.4f\n", 1.0 - (float) distrib[0] / 65536);

    fclose(infile);
    fclose(outfile);
}
