#ifndef ID3_WRITER_H
#define ID3_WRITER_H
#include<stdlib.h>
typedef struct 
{
    FILE *fp;
    FILE *dup_fp;

    char id[5];
     int d_size;
     char f_data[100];

}Tagdata;



int write_id3_tags( char *argv[], const char *tag,const char *value);

/**
TODO: Add documention as sample given above
 */
int edit_tag(char *argv[], const char *tag, const char *value);
void store_size(FILE * fptr, int size);
int copydata(int flag);

#endif // ID3_WRITER_H
