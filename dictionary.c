
#include <stdio.h>

#define FILE_PATH "./words.txt" /* Input File, Can be read from Console, if time permit will add. Not that important. */

/* Return 1 on positive exit, else 0*/
/*
    Assumes, each item/element in dictonary is delimited by a new line \n
*/
int main()
{
    unsigned char *data = NULL; /*Dictonary Data will be read into this pointer*/
    FILE *fp = fopen(FILE_PATH, "r");

    if (fp)
    {
        /* If file open success */
        unsigned long fsize = 0; /* Data size in the file */
        char *token;             /* Pointer for tokenization */

        printf("Open Dictonary Success!\n");
        /* Move file handle to the end of the file */
        fseek(fp, 0, SEEK_END);
        /* Get posisiton of the file handle, which is in turn file size */
        fsize = ftell(fp);

        if (fsize) /* If there is data */
        {
            /* Move back file handle to the start of file */
            fseek(fp, 0, SEEK_SET);
            /* Alloc data pointer to read size */
            data = (unsigned char *)malloc(fsize);

            /* Read data, assuming whole data will be read properlly in single call */
            if (fread(data, sizeof(unsigned char), fsize, fp) != fsize)
            {
                printf("failed reading whole data.\n");
                fclose(fp);
                return 0;
            }

            /* Tokenize input data with delimiter \n */
            token = strtok((char *)data, "\n");
            /* loop till token is not null */
            while (token != NULL)
            {
                if (strlen(token) > 0) /* Minimum of single character */
                {
                    printf("%s\n", token);
                }
                token = strtok(NULL, "\n");
            }
            /* */
            printf("Processed all data.\n");
        }
        else
            printf("Empty Dictionary.\n");
    }
    else
        return 0;

    return 1;
}