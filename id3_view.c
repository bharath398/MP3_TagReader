

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>
#include "id3_view.h"
#include "error_handling.h"

Taginfo ti;

void read_id3_tags(const char *filename) {
    // Implementation for reading ID3 tags
    ti.fp=fopen(filename,"r");
    if(ti.fp==NULL)
    {
        printf("couldn't open file\n");
       exit(0);
    }
    
    fseek(ti.fp,10,SEEK_SET);
    int ret=get_data(ti.fp,ti.tag_id,"TIT2",ti.title_size);
    if(ret==-1)
    printf("INFO:Cannot read title from file\n");

    ret=get_data(ti.fp,ti.tag_id,"TPE1",ti.artist_size);
    if(ret==-1)
    printf("INFO:Cannot read Artist from file\n");

    ret=get_data(ti.fp,ti.tag_id,"TALB",ti.album_size);
    if(ret==-1)
    printf("INFO:Cannot read Album from file\n");
  
    ret=get_data(ti.fp,ti.tag_id,"TYER",ti.year_size);
    if(ret==-1)
    printf("INFO:Cannot read year from file\n");


    ret=get_data(ti.fp,ti.tag_id,"TCON",ti.genre_size);
    if(ret==-1)
    printf("INFO:Cannot read Genre from file\n");

    ret=get_data(ti.fp,ti.tag_id,"COMM",ti.comment_size);
    if(ret==-1)
    printf("INFO:Cannot read Comments from file\n");
    
}

void view_tags(const char *filename) 
{
 read_id3_tags(filename);   
 printf("---------------------------------------------------------------------------------\n");
 printf("                           MP3 Tag Reader and Editor                             \n");
 printf("---------------------------------------------------------------------------------\n");
 printf("%-20.20s : %-50.50s\n","TITLE",ti.title);
 printf("%-20.20s : %-50.50s\n","ARTIST",ti.artist);
 printf("%-20.20s : %-50.50s\n","ALBUM",ti.album);
 printf("%-20.20s : %-50.50s\n","YEAR",ti.year);
 printf("%-20.20s : %-50.50s\n","GENRE",ti.genre);
 printf("%-20.20s : %-50.50s\n","COMMENT",ti.comment);
 printf("---------------------------------------------------------------------------------\n");
}



void store_data(FILE *fp,uint d,const char *id)
{
    fseek(fp,3,SEEK_CUR);

    int i;
    char fname[d];
    i=fread(fname,1,d-1,fp);
    fname[d-1]='\0';
    if(strcmp(id,"TIT2")==0)
    {
        ti.title=malloc(d*sizeof(char));
        strcpy(ti.title,fname);
        

    }
    if(strcmp(id,"TPE1")==0)
    {
        ti.artist=malloc(d*sizeof(char));
        strcpy(ti.artist,fname);
       
    }
    if(strcmp(id,"TALB")==0)
    {
        ti.album=malloc(d*sizeof(char));
        strcpy(ti.album,fname);
       
    }
    if(strcmp(id,"TYER")==0)
    {
        ti.year=malloc(d*sizeof(char));
        strcpy(ti.year,fname);
    }
    if(strcmp(id,"TCON")==0)
    {
        ti.genre=malloc(d*sizeof(char));
        strcpy(ti.genre,fname);
    }
    if(strcmp(id,"COMM")==0)
    {
        ti.comment=malloc(d*sizeof(char));
        strcpy(ti.comment,fname);
    }
}


int get_data(FILE *fp,char *tagid,const char *src_id,int size)
{
    fread(tagid,4,1,fp);
    if(strcmp(tagid,src_id)==0)
    {
          size=0;
       fread(&size,4,1,fp);
      size=size>>24;

 
   store_data(fp,size,src_id);
   return 0;
}
return -1;
}

