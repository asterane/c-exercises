#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // check for proper argument count
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s infile\n", argv[0]);
        return 1;
    }

    // pull file name
    char *infile = argv[1];

    // open the provided file if possible
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    // buffer, sized to fit one block
    u_int8_t buffer[512];

    // variables for creating new .jpg files
    int outn = 0;
    char outfile[8];
    FILE *outptr;

    int read = 0;
    int n;

    // check for end of raw file before proceeding
    while (feof(inptr) == 0)
    {
        // read a block of memory into the buffer
        n = fread(&buffer, 1, 512, inptr);

        if (n == 0)
        {
            break;
        }

        // zero fill rest of buffer when end of file reached
        while (n < 512)
        {
            buffer[n] = 0;
            n++;
        }

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            buffer[3] >= 224 && buffer[3] < 240)
        {
            if (read == 1)
            {
                // close the previous file only if it is actually open
                fclose(outptr);
            }

            read = 1;

            // create a new file to start writing buffers into and write the first one
            sprintf(outfile, "%03i.jpg", outn);
            outptr = fopen(outfile, "w");
            fwrite(&buffer, 1, 512, outptr);

            // increment file counter
            outn++;
        }
        else if (read == 1)
        {
            // write the buffer into the current file
            fwrite(&buffer, 1, 512, outptr);
        }
    }

    // close all open files
    fclose(outptr);
    fclose(inptr);
}
