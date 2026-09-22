/**
 * @file id3_writer.c
 * @brief Implementation of functions for writing and editing ID3 tags in MP3 files.
 */

#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include "id3_edit.h"
#include "id3_view.h"
Tagdata td;



int write_id3_tags(char *argv[], const char *tag,const char *value) {
    // Implementation for writing ID3 tags
   
    if(strcmp(tag,"-t")==0)
    strcpy(td.id,"TIT2");
    else if(strcmp(tag,"-a")==0)
    strcpy(td.id,"TALB");
    else if(strcmp(tag,"-A")==0)
    strcpy(td.id,"TPE1");
    else if(strcmp(tag,"-y")==0)
    strcpy(td.id,"TYER");
    else if(strcmp(tag,"-g")==0)
    strcpy(td.id,"TCON");
    else if(strcmp(tag,"-c")==0)
    strcpy(td.id,"COMM");
     

    strcpy(td.f_data,argv[3]);

    td.fp=fopen(argv[4],"r+");
    if (td.fp==NULL)
    {
        printf("ERROR:unable to open file\n");
        return -1;
            
    }
    td.dup_fp=fopen("dup.mp3","w+");
    fseek(td.fp,0,SEEK_SET);
    fseek(td.dup_fp,0,SEEK_SET);
    char a[10];
    fread(a,10,1,td.fp);
    fwrite(a,10,1,td.dup_fp);
    char *tagids[6]={"TIT2","TPE1","TALB","TYER","TCON","COMM"};
    
   
    
    for(int i=0;i<6;i++)
    {
        
            fread(a,4,1,td.fp);
            fwrite(a,4,1,td.dup_fp);
            if(strcmp(tagids[i],td.id)==0)
            {
               int ret= copydata(1);
               if(ret==1)
               {
                printf("ERROR: Unable to copy the updated Data from Source to Destination '.mp3' file\n");
                return -1;
               }
               break;
            }
            else
            {
               int ret= copydata(0);
               if(ret==1)
               {
                printf("ERROR: Unable to copy remaining Data from Source to Destination '.mp3' file\n");
                return -1;
               }
            }

       
    }
  
    fseek(td.fp,0,SEEK_SET);
    fseek(td.dup_fp,0,SEEK_SET);


    char c;
		while(fread(&c, 1, 1, td.dup_fp)>0 )
		{
				fwrite(&c, 1, 1, td.fp);
		}
    
    return 1;
}


int edit_tag(char *argv[], const char *tag, const char *value) 
{
    if(!(write_id3_tags(argv,tag,value)))
    {
        printf("Error:Couldn't edit %s tag",tag);
        return -1;
        
    }

    return 0;
}

void store_size(FILE * fptr, int size)
{		int i;
		char *value =(char*)&size;
		for (i = 3; i >= 0; i--)
		{
				fwrite((value+i),1,1,fptr);
		}
}
int  copydata(int flag)
{
    if(flag==1)
    {
        int size,new_size;
        fread(&size,1,4,td.fp);
        size=size>>24;
        new_size=strlen(td.f_data)+1;
        store_size(td.dup_fp,new_size);
        char f[3];
        fread(f,1,3,td.fp);
        fwrite(f,1,3,td.dup_fp);
        fwrite(td.f_data,1,new_size-1,td.dup_fp);
        fseek(td.fp,size-1,SEEK_CUR);

        char c;
		while(fread(&c, 1, 1, td.fp)>0 )
		{
				fwrite(&c, 1, 1, td.dup_fp);
		}
        return 0;
    }
    else
    {
        int size;
        fread(&size,1,4,td.fp);
        fwrite(&size,1,4,td.dup_fp);
        size=size>>24;
        char f[3];
        fread(f,1,3,td.fp);
        fwrite(f,1,3,td.dup_fp);
        char str[size];
        fread(str,1,size-1,td.fp);
        str[size-1]='\0';
        fwrite(str,1,size-1,td.dup_fp);
        
        return 0;

    }
return 1;
}