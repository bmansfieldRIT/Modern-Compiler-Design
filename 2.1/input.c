#include <stdio.h>
#include <stdlib.h>

char* get_input(void){
    FILE *fp;


    /* opening file for reading */
    fp = fopen("program.txt" , "r");
    if (fp == NULL) {
        perror("Error opening file");
        return NULL;
    }

    fseek(fp, 0, SEEK_END); // seek to end of file
    int size = ftell(fp); // get current file pointer
    fseek(fp, 0, SEEK_SET); // seek back to beginning of file

    char *str = malloc(size);

    if (fgets (str, size, fp) != NULL ) {
        fclose(fp);
        return str;
    }

    return NULL;
}
