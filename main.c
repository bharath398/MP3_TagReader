/**
 * @file main.c
 * @brief Main entry point for the MP3 Tag Reader application.
 */

#include <stdio.h>
#include <string.h>
#include "main.h"
#include "id3_view.h"
#include "id3_edit.h"
#include "error_handling.h"

/**
 * @brief Displays the help message for the MP3 Tag Reader application.
 */
void display_help() {
    printf("ERROR: ./a.out : INVALID ARGUMENTS\n");
    printf("USAGE :\n");
    printf("To get help please pass like   :   ./a.out -h\n");
    printf("To view please pass like       :   ./a.out -v mp3filename\n");
    printf("To edit please pass like       :   ./a.out -e -g/-t/-a/-A/-y/-c mp3filename\n");
    
}

/**
 * @brief Main function to handle command-line arguments and execute appropriate actions.
 * 
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return 0 on success, non-zero on failure.
 */
int main(int argc, char *argv[]) {

 
    if (argc < 2)
    {
        display_help();
        return 1;
    }

    if ((strcmp(argv[1], "-h") == 0 )|| strcmp(argv[1],"--help")==0) 
    {
        display_help();
        return 0;
    }
    else if (strcmp(argv[1], "-v") == 0 && argc == 3)
    {
        if(strstr(argv[2],".mp3")!=NULL)
        view_tags(argv[2]);
        else 
        {
        printf("Error:Please pass mp3 file\n");
        return 1;
        }

    } else if (strcmp(argv[1], "-e") == 0 && argc == 5) {
        if(strstr(argv[4],".mp3")==NULL)
        {
            display_help();
            return -1;
        }
        if((strcmp("-t",argv[2])!=0)&&(strcmp("-a",argv[2])!=0)&&(strcmp("-A",argv[2])!=0)&&(strcmp("-y",argv[2])!=0)&&(strcmp("-c",argv[2])!=0)&&(strcmp("-g",argv[2])!=0))
       {
        display_help();
            return -1;
       }

        
        if (edit_tag(argv, argv[2], argv[3]) != 0) {
            printf("Failed to edit tag.");
            return 1;
        }
        printf("Tag edited successfully.\n");
    } else {
        display_help();
        return 1;
    }

    return 0;
}
