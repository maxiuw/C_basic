#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    if (argc !=2)
    {
        return 1;

    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        return 1;
    }

    int pic_n = 0;
    int i = 0;
    unsigned char bytes[513];  
    do{
         
         // numbers 0-255

        // how many bytes we wanna read from the file, how many times from which file and where to
        fread(bytes, 513, 1, file);
        // check if bytes are 0xff 0xd8 0xff
        printf("%x,%x,%x,%x\n",bytes[i],bytes[i+1],bytes[i+2],bytes[i+3]);
        if (bytes[i]==0xff && bytes[i+1] == 0xd8 && bytes[i+2] ==0xff)// && (bytes[i+3] & 0x0f)==0xe0)
            {
            printf("for i = %i, it's jpgggggggggggggggggggggggggggggggg",i);
            }
        else
        {
            i+=512;    
        }
    //         {

    //             unsigned char* name;
    //             unsigned char pic[512];

    //             for (int j = 0; j<512; j++,i++) // int *pic = malloc(512*BYTE);

    //                 {
    //                     pic[j] = bytes[i];
    //                 }

    //             sprintf(name, "%03i.jpg",pic_n);
    //             FILE *img = fopen(name,"w");
    //             fwrite(pic,512,1,img);
    //             pic_n++;
    //         }
    //     i+=512;
    // }while(i<20000);
    }while(strlen((char*)bytes)>512);

}
