/*
    Assumes:
    1. Each item/element in dictonary is delimited by a new line \n
    2. Compiled using GCC, as this uses fnmatch
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <fnmatch.h>

#define FILE_PATH "./words.txt" /* Input File, Can be read from Console, if time permit will add. Not that important. */
#define ASCII_CHARS 128         /* Considers only first 128 ASCII characters */

/* Structre to store each item from dictonary */
typedef struct
{
    char *ptr; /* String pointer */
    void *nxt; /* Next Node */
} word_list;

word_list *head[ASCII_CHARS];    /* Head Pointer */
word_list *current[ASCII_CHARS]; /* Current Pointer */
int total_words[ASCII_CHARS];    /* List count */

/*
    This function takes dictonary item as input
*/
void push(word_list *ptr)
{
    /* Find to which linked list this item need to be added */
    /* Assumption, 128 ASCII characters only, hence on conversion of first char to int we will get the array item where we have to store this item */
    unsigned int ascii = ptr->ptr[0];
    /* If value is greater than valid ascii value ignore item */
    if (ascii > ASCII_CHARS)
        return;

    /* If first item in the list, point to head */
    if (!total_words[ascii])
    {
        head[ascii] = ptr;
    }
    else
    {
        /* Update previous nxt ptr */
        current[ascii]->nxt = ptr;
    }
    current[ascii] = ptr;

    /* Increment total items in the list */
    total_words[ascii]++;
}

/* Return 1 on positive exit, else 0*/
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
                    word_list *word = (word_list *)malloc(sizeof(word_list));
                    word->ptr = token;
                    word->nxt = NULL;
                    /* Push new dictonary item */
                    push(word);
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