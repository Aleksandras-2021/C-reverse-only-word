#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define buffer_size 255

void openFile(FILE **fp,char *fileName,char mode[]);
char *createDynamicArray();
void reverseSymbols(char *buffer);

void openFile(FILE **fp,char *fileName,char *mode)
{
    *fp = fopen(fileName, mode);

    if (*fp == NULL && mode == "r")
    {
        while(*fp==NULL)
        {
            printf("Failed to open INPUT file, please enter new file name:");
            fclose(*fp);
            scanf("%s",fileName);
            *fp = fopen(fileName, mode);
        }
        return;
    }
    else
    {
        printf("file named: %s opened/created successfully \n",fileName);
    }

}

char *createDynamicArray()
{
    char *p = malloc(buffer_size*sizeof(char));

    if (p == NULL)
    {
        printf("Unable to allocate memory\n");
        return NULL;
    }
    return p;
}

void reverseSymbols(char *buffer)
{
    int len = strlen(buffer);
    int i = 0, j = 0;
    char *temp = malloc(buffer_size*sizeof(char));

    for(i = 0; i< len; i++)
    {
        for(j = 0; i<len; j++, i++)
        {
            if(buffer[i]==' ' || buffer[i] =='\n')
                break;
            temp[j] = buffer[i];
        }
        while(j>0)
        {
            j--;
            buffer[i-j-1] = temp[j];

        }
    }

    free(temp);
}

//3 namu darbai, variantas 2
//Aleksandras Bukelis 1 kursas, 2 grupe, 1 pogrupis

int main(int argc, char *argv[])
{
    printf("This program reverses symbol order in word, but not the order of words \n");

    FILE* fp; //Input file
    FILE* fw; //Output file
    char *buffer = createDynamicArray();
    int bufferLength;

//*****FILE OPENING/CREATING PART******//

    openFile(&fp,argv[1],"r");  //ARGV[1] INPUT FILE
    openFile(&fw,argv[2],"w");  //ARGV[2] OUTPUT FILE
    fseek(fp, 0, SEEK_SET);

//************************************//

    if(argv[2]!= NULL && fw != NULL)
    {
        while(fgets(buffer, buffer_size, fp)!= NULL)
        {
            bufferLength = strlen(buffer);
            reverseSymbols(buffer);
            fwrite(buffer,bufferLength,1,fw);
            free(buffer);
            buffer = createDynamicArray();
        }
        fclose(fw);
    }
    else //If output file is not given, print results to console
    {
        while(fgets(buffer, buffer_size, fp)!= NULL)
        {
            bufferLength = strlen(buffer);
            reverseSymbols(buffer);
            fwrite(buffer,bufferLength,1,stdout);
            free(buffer);
            buffer = createDynamicArray();
        }
    }

    fclose(fp);

    printf("\n Task accomplished \n");
    return 0;
}
