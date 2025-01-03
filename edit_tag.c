#include "main.h"
#include "types.h"

status edit_mode(Tag_Reader *tag_reader)
{
    char stag[5], flag_bytes[3], ver[10];
    fread(ver, 10, 1, tag_reader->fp);
    fwrite(ver, 10, 1, tag_reader->fp_out);

    while (fread(stag, 4, 1, tag_reader->fp) == 1) {

        fwrite(stag, 4, 1, tag_reader->fp_out);
        stag[5] = '\0';


        if (!strcmp(tag_reader->tag, stag)) 
        {
            status ret = tag_read_write(tag_reader, stag);
            if (ret == failure)
                return failure;
            status res = read_and_write_remaining_data(tag_reader);
            if(res == success)
                return success; // Return success after the loop finishes
            else
                return failure;
        }else 
            except_data_read_and_write(tag_reader);
    }
}

status tag_read_write(Tag_Reader *tag_reader, char *stag)
{
    char edit_string[100];
    fread(&tag_reader->size, 4, 1, tag_reader->fp);
    fread(tag_reader->flag_bytes, 3, 1, tag_reader->fp);
    swap_size(tag_reader);
    tag_reader -> size--;

    fseek(tag_reader->fp, tag_reader->size, SEEK_CUR);

    printf("Enter the data you wanna replace!\n");
    scanf("%[^\n]", edit_string);
    getchar(); // Consume newline left by scanf
    tag_reader->size = strlen(edit_string) + 1;

    swap_size(tag_reader);
    
    printf("%s: %s\n", stag, edit_string);

    fwrite(&tag_reader->size, 4, 1, tag_reader->fp_out);
    fwrite(tag_reader->flag_bytes, 3, 1, tag_reader->fp_out);
    fwrite(edit_string,strlen(edit_string), 1, tag_reader->fp_out);

    return success;
}

void except_data_read_and_write(Tag_Reader *tag_reader)
{
    fread(&tag_reader->size, 4, 1, tag_reader->fp);
    fwrite(&tag_reader->size, 4, 1, tag_reader->fp_out);

    fread(tag_reader->flag_bytes, 3, 1, tag_reader->fp);
    fwrite(tag_reader->flag_bytes, 3, 1, tag_reader->fp_out);

    swap_size(tag_reader);
    tag_reader -> size--;

    tag_reader->data = malloc(tag_reader->size * sizeof(char));

    fread(tag_reader->data, tag_reader->size, 1, tag_reader->fp);
    fwrite(tag_reader->data, tag_reader->size, 1, tag_reader->fp_out);

    free(tag_reader->data);
}

status read_and_write_remaining_data(Tag_Reader *tag_reader)
{
    char ch;
    while(fread(&ch,1,1,tag_reader->fp) != 0) 
    {
        fwrite(&ch, 1, 1, tag_reader->fp_out);
    }
    return success;
}
