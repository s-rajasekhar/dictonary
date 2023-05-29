
#include <stdio.h>

#define FILE_PATH "./words.txt"

int main()
{
    FILE *fp = fopen(FILE_PATH, "r");
    unsigned char *data = NULL;
    if (fp)
    {
        unsigned long fsize = 0;

        printf("Open Dictonary Success!\n");
        /* move to the end of the file */
        fseek(fp, 0, SEEK_END);
        /* Get posisiton of the file ptr, which is in turn file size */
        fsize = ftell(fp);
        /* if there is data */
        if (fsize)
        {
            /* move to start of the file */
            fseek(fp, 0, SEEK_SET);
            /* alloc memory to store the file data */
            data = (unsigned char *)malloc(fsize);
            if (fread(data, sizeof(unsigned char), fsize, fp) != fsize)
            {
                printf("failed reading whole data.\n");
                fclose(fp);
                return 0;
            }
        }
        else
            printf("Empty Dictionary.\n");
    }
    else
        return 1;

    return 0;
}