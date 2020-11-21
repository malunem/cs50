#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Error. Usage: ./recover filename\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");

    if (card == NULL)
    {
        printf("Can't read this file.\n");
        return 1;
    }

    typedef uint8_t BYTE;
    unsigned char bytes[512];
    int pixels;
    int images = 0;
    FILE *img_w = NULL;
    
    //allocate memory for file name 000.jpg 
    char *filename = malloc(8 * (sizeof(char)));
    if (filename == NULL)
    {
        printf("Can't allocate memory\n");
        return 1;
    }
    
    //scan file until can't read 512 block (end of file reached)
    while ((pixels = fread(bytes, sizeof(BYTE), 512, card)) == 512)
    {

        //START OF A NEW JPEG
        if (bytes[0] == 0xff &&
            bytes[1] == 0xd8 &&
            bytes[2] == 0xff &&
            (bytes[3] & 0xf0) == 0xe0)
        
        {
            //close previous image if exists 
            if (images > 0)
            {
                fclose(img_w);
            }

            //create filename in progression 001,002...
            sprintf(filename, "%03i.jpg", images);
            images++;

            //open file in write mode
            img_w = fopen(filename, "w");
            
            if (img_w == NULL)
            {
                return 1;
            }
            
            //writes file with input info
            fwrite(bytes, sizeof(BYTE), 512, img_w);
        }
        
        //continue writing opened image
        else if (images > 0)
        {
            fwrite(bytes, sizeof(BYTE), 512, img_w);
        }
    }
    
    free(filename);
    return 0;
}
