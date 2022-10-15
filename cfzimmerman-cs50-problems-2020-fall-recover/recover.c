#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Define BYTES as a data type
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    // Return error if the user doesn't input the right number of command line arguments (./recover card.raw)
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    
    // Return error if the file input isn't valid
    FILE *file = fopen(argv[1], "r");
    {
        if (file == NULL)
        {
            printf("Usage: ./recover card.raw\n");
            return 2;
        }
    }
    
    // jpgnum is the counter for how many jpgs have been processed
    int jpgnum = -1;
    
    // dynname (dynamic name) is the character array that holds the name of each jpg
    char dynname[8];
    
    // The buffer array of bytes is used to scan through the file and to copy to each image
    BYTE buffer[512];
    
    // sprintf is used throughout the program to update the name of the next file to be opened
    sprintf(dynname, "%03i.jpg", jpgnum);
    
    // Open the -01.jpg file, which holds all the extaneous data before the first jpg begins. This file is deleted at the end of the end of main.
    FILE *img = fopen(dynname, "w");
    
    // This loop continues to run the functions below until the last buffer array is left unfilled with bytes
    while (fread(buffer, 1, 512, file) == 512)
    {
        // This function fills up the very first jpg with its first sequence of data. It is not used after that.
        if (((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0)) && (img == NULL))
        {
            fwrite(buffer, 1, 512, img);
        }
        // When the conditions match for a new jpeg, this function closes the old jpg, increases the jpg count, updates the jpg image name, opens a new jpg file with that name, and begins writing into it
        else if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {
            fclose(img);
            jpgnum ++;
            sprintf(dynname, "%03i.jpg", jpgnum);
            img = fopen(dynname, "w");
            fwrite(buffer, 1, 512, img);
        }
        // This fills a file with data until the next jpg header is reached
        else if (img != NULL)
        {
            fwrite(buffer, 1, 512, img);
        }
    }
    
    remove("-01.jpg");
    return 0;
}