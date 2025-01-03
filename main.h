#ifndef MP3_H
#define MP3_H

#include "types.h"

#define MODE 7
#define TAG_LEN 5
#define DATA_LEN 200
#define TAGS 8
#define FLAG_SIZE 4

typedef struct _Tagreader{
    char mode[MODE];
    char tag[TAG_LEN];
    char *in_tags[TAGS];
    char flag_bytes[FLAG_SIZE];
    int size;
    char *data;
    FILE *fp;
    FILE *fp_out;
}Tag_Reader;


//to check the operation type of the agrguments
OperationType check_operation_type(char *argv[]);

//validation for the arguments
status validation(char *argv[],Tag_Reader *tag_reader,char **tag_name,char **short_tag);

//if the mode is help mode then we give assistance for user
void for_help_mode_tag(char **tag_name,char **short_tag);

//work on tag for edit mode
status edit_mode(Tag_Reader *tag_reader);

//work on tag for view mode
status view_mode(Tag_Reader *tag_reader);

//work on swapping of size
void swap_size(Tag_Reader *tag_reader);

//if tag is matching read and write using file pointer
status tag_read_write(Tag_Reader *tag_reader,char *stag);

//other tags read and write except editing tag
void except_data_read_and_write(Tag_Reader *tag_reader);

//read and write remaining data
status read_and_write_remaining_data(Tag_Reader *tag_reader);

#endif
