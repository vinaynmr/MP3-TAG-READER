#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "main.h"


void for_help_mode_tag(char **tag_name,char **short_tag)
{
    printf("COMMAND LINE ARGUMENTS: './a.out' 'mode' 'short tag' 'mp3_filename'\n");
    printf("Modes for edit -> '-e' or for view -> '-v'\n");
    printf("    Tag name -> short tag\n");
    for(int i = 0;i < 8; i++)
        printf("        %s -> %s\n",tag_name[i],short_tag[i]);
    printf("Please understand the explaination give proper 'COMMAND LINE ARGUMENTS'\n");
    printf("EXAMPLE:\nEDIT: ./a.out -e -t Fear.mp3\nVIEW : ./a.out -v Fear.mp3\n");
}

status view_mode(Tag_Reader *tag_reader)
{
    char stag[4],ver[4];//to read tag from file
    int count = 0;
    fseek(tag_reader -> fp,10,SEEK_SET);
    while(tag_reader -> fp != NULL)
    {
        fread(stag,4,1,tag_reader -> fp);
        stag[4] = '\0';
        if(stag[0] == '\0')
        {
            printf("PROCCESS COMPLETED\n");
            return success;
        }
        
        fread(&tag_reader -> size,4,1,tag_reader -> fp);
        
        swap_size(tag_reader);
        tag_reader -> size--;
        
        fseek(tag_reader -> fp,3,SEEK_CUR);
        tag_reader -> data = calloc(tag_reader -> size,sizeof(char));
        int i;
        for(i = 0; i < TAGS; i++)
        {
            if(!strcmp(stag,tag_reader -> in_tags[i])){
                fread(tag_reader -> data,tag_reader -> size,1,tag_reader -> fp);
                tag_reader -> data[tag_reader -> size] = '\0';
                printf("%s :  %s\n",tag_reader -> in_tags[i],tag_reader -> data);
                count++;
                break;
            }
        }
        if(i == TAGS)
            fseek(tag_reader -> fp,tag_reader -> size,SEEK_CUR);
        if(count == TAGS)
            break;
        free(tag_reader -> data);
    }
    return success;
}

void swap_size(Tag_Reader *tag_reader)
{
    char *ptr = (char *)&tag_reader -> size;
    for(int i = 0; i < sizeof(tag_reader -> size)/2; i++)
    {
        char temp = *(ptr + i);
        *(ptr + i) = *(ptr + sizeof(tag_reader -> size) - i - 1);
        *(ptr + sizeof(tag_reader -> size) - i - 1) = temp;
    }
}
