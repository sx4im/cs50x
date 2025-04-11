#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *raw_file = fopen(argv[1], "r");
    if (raw_file == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    // Create a buffer for a block of data
    uint8_t buffer[512];
    int found_jpg = 0;
    int counter = 0;
    char filename[8];
    FILE *img = NULL;

    while (fread(buffer, 1, 512, raw_file) == 512)
    {
        // Check if the block is the start of a new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // If an image file is already open, close it
            if (img != NULL)
            {
                fclose(img);
            }
            // Create new filename and open a new image file
            sprintf(filename, "%03i.jpg", counter);
            counter++;
            img = fopen(filename, "w");
        }

        // If an image file is open, write the block to it
        if (img != NULL)
        {
            fwrite(buffer, 1, 512, img);
        }
    }
}
