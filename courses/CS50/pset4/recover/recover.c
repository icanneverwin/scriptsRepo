#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Wrong number of arguments. Usage: basename <filename>");
        return 1;
    }

    //open file
    FILE *file = fopen(argv[1], "r");
    FILE *newfile = NULL;
    if (!file)
    {
        printf("Incorrect file");
        return 1;
    }

    unsigned char *bytes = malloc(512);
    int i = 0;
    char *filename = malloc(10);

    //read until the end of file
    while (1)
    {
        // check if end of the file
        if (fread(bytes, 512, 1, file) < 1)
        {
            break;
        }

        // check if first 4 bytes are JPEG
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && ((bytes[3] & 0xf0) == 0xe0))
        {
            //check if first file
            if (i == 0)
            {
                sprintf(filename, "%03i.jpg", i); //new filename is created
                newfile = fopen(filename, "w");
                fwrite(bytes, 512, 1, newfile);
            }
            else
            {
                fclose(newfile);
                sprintf(filename, "%03i.jpg", i);
                newfile = fopen(filename, "w");
                fwrite(bytes, 512, 1, newfile);
            }

            i++;
        }
        else // if not JPEG
        {
            //check if already found JPEG
            if (newfile != NULL)
            {
                fwrite(bytes, 512, 1, newfile);
            }
        }
    }

    fclose(newfile);
    fclose(file);
    free(bytes);
    free(filename);
}
