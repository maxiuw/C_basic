#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc!=2)
    {
        return 1;
    }
    FILE *file = fopen(argv[1],"r");
    if (file == NULL)
    {
        return 1;

    }
    int i = 1;
    BYTE bytes[512]; //0-255
    int pic_n = 0;
    char name[9];
    FILE* image = NULL;

    do
    {
        // bytes = calloc(512*BYTE);
        fread(bytes,512,1,file);


        if (bytes[0]==0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0)==0xe0)

        {
            if (pic_n ==0)
            {
                pic_n++;
                printf("found jpg");
                sprintf(name, "%03i.jpg",pic_n);
                image = fopen(name,"w");
                fwrite(bytes,512,1,image);
            }

            else if (pic_n>0)
            {
                fclose(image);
                pic_n++;
                printf("found jpg");
                sprintf(name, "%03i.jpg",pic_n);
                image = fopen(name,"w");
                fwrite(bytes,512,1,image);
            }

        }

        else if (pic_n>0)
        {
            // FILE *app = fopen(name,"a");
            // image = fopen(name,"a");
            fwrite(bytes,512,1,image);
        }



    }while(feof(file)==0);
    fclose(image);
    fclose(file);

    return 0;
}
