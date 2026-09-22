#ifndef ID3_READER_H
#define ID3_READER_H
#include <stdio.h>
#include <stdlib.h>
typedef unsigned int uint;
typedef struct {
    FILE *fp;
    char tag_id[4];
    char *title;
    uint title_size;
    int t_pos;

    char *album;
    uint album_size;
    int al_pos;

    char *artist;
    uint artist_size;
    int at_pos;

    char *year;
    uint year_size;
    int y_pos;

    char *genre;
    uint genre_size;
    int g_pos;

    char *comment;
    uint comment_size;
    int c_pos;



   
} Taginfo;


void read_id3_tags(const char *filename);

void display_metadata(Taginfo *ti);

void view_tags(const char *filename);


void store_data(FILE *fp,uint d,const char *id);
int get_data(FILE *fp,char *tagid,const char *src_id,int size);
void check_flag(Taginfo *data,FILE *fp);

#endif // ID3_READER_H
