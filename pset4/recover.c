#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define BLOCK_SIZE 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: recover infile\n");
        return 1;
    }
	// remember filenames
	char *infile = argv[1];

	// open memory card
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
    	fprintf(stderr, "Could not open %s.\n", infile);
    	return 2;
    }

    BYTE buffer[512];
    int imageCount = 0;

    char filename[8];
    FILE *outptr = NULL;

    // repeat until end of card
    // read a blog of the memory card image
    while (true)
    {
    	size_t bytesRead = fread(buffer, sizeof(BYTE), BLOCK_SIZE, inptr);

    	// break out of the loop when we reach the end of the image
    	if (bytesRead == 0 && feof(inptr))
    	{
    		break;
    	}

    	// check if we found a JPEG
        bool containsJPEGheader = buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0;

    	// if we found a yet another JPEG, we must close the previous file
    	if (containsJPEGheader && outptr != NULL)
    	{
    		fclose(outptr);
    		imageCount++;
    	}

    	// if we found a JPEG, we nned to open the file for writing
    	if (containsJPEGheader)
    	{
    		sprintf(filename, "%03i.jpg", imageCount);
    		outptr = fopen(filename, "w");
    	}

    	// write anytime we have an open file
    	if (outptr != NULL)
    	{
    		fwrite(buffer, sizeof(BYTE), bytesRead, outptr);
    	}
    }

    // close last JPEG file
    fclose(outptr);

    // close infile
    fclose(inptr);

    // success
    return 0;
}
