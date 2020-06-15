#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(void)
{
    int i = 1;
    int size = 512*sizeof(BYTE);
    FILE* image= calloc(i,size); // MEMO of size i elements of 512 bytes size 
    char *name = "asia.jpg";
    image = fopen("asia","w");

}
