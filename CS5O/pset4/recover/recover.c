#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <cs50.h>

#define BLOCK_SIZE 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check if the prompt is valid
    if (argc != 2 || strcmp(argv[1], "card.raw") != 0)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    // Damaged file
    FILE *raw_file = fopen(argv[1], "r");
    // File for saving jpgs
    FILE *img;
    BYTE *buffer = malloc(sizeof(BYTE) * 512);
    char *filename = malloc(sizeof(BYTE) * 20);
    int file_count = 0;
    // Read data until the end of the damaged file
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        // Check if it's a start of jpg
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {
            // Case when it's the first jpg
            if (file_count == 0)
            {
                sprintf(filename, "%03i.jpg", file_count);
                img = fopen(filename, "w");
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
                file_count++;
            }
            // Case when it's not the first jpg
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", file_count);
                img = fopen(filename, "w");
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
                file_count++;
            }
        }
        // Case when it's not a start of jpg
        else if (file_count != 0)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
        }
    }
    fclose(raw_file);
    fclose(img);
    free(buffer);
    free(filename);
}