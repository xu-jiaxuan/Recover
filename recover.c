#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    int counter = 0;
    unsigned char bytes[512];
    FILE *img;

    while (fread(bytes, 512, 1, file) == 1)
    {
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)
        {
            if (counter != 0)
            {
                fclose(img);
            }
            char filename[8];
            sprintf(filename, "%03i.jpg", counter);
            counter++;
            img = fopen(filename, "w");
            fwrite(bytes, 512, 1, img);
        }
        else
        {
            fwrite(bytes, 512, 1, img);
        }
    }
    fclose(img);
    
    fclose(file);
}