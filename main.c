#include "main.h"
#include "types.h"

int main(int argc, char *argv[])
{
    Tag_Reader tag_reader;
    char *tag_name[8] = {"TIT2","TPE1","TALB","TYER","TCON","COMM","TPUB","TCOM"};
    char *short_tag[8] = {"-t","-p","-a","-y","-e","-o","-u","-m"};
    for(int i = 0; i < TAGS; i++)
    {
        tag_reader.in_tags[i] = calloc(strlen(tag_name[i]) + 1,sizeof(char));
        strcpy(tag_reader.in_tags[i],tag_name[i]);
    }
    if(argc < 2)
        return failure;
    status ret = validation(argv,&tag_reader,tag_name,short_tag);
    if(ret == failure){
label:
        printf("Please give proper arguments!\n");
        return 0;
    }
    OperationType res = check_operation_type(argv);
    if(res == view)
    {
        printf("\t\t\t\t::::::VIEW PROCESS STARTED::::::\n");
        ret = view_mode(&tag_reader);
        if(ret == success)
            printf("\t\t\t\t::::::VIEW PROCESS COMPLETED::::::\n");
        else
            printf("\t\t\t\t::::::VIEW PROCESS FAILED::::::\n");
    }else if(res == edit)
    {
        printf("\t\t\t\t::::::EDIT PROCESS STARTED::::::\n");
        ret = edit_mode(&tag_reader);
        if(ret == success)
            printf("\t\t\t\t::::::EDIT PROCESS COMPLETED::::::\n");
        else
            printf("\t\t\t\t::::::EDIT PROCESS FAILED::::::\n");
    }else if(res == help)
        for_help_mode_tag(tag_name,short_tag);
    else
        goto label;
}

status validation(char *argv[],Tag_Reader *tag_reader,char **tag_name,char **short_tag)
{
   if(!strcmp(argv[1],"--help"))
   {
        strcpy(tag_reader -> mode,argv[1]);
        if(argv[2] != NULL)
            return failure;
        else
            return success;
   }else if(!strcmp(argv[1],"-e"))
   {
       strcpy(tag_reader -> mode,argv[1]);
       for(int i = 0; i < 8; i++)
       {
           if(!strcmp(argv[2],short_tag[i]))
           {
                strcpy(tag_reader -> tag,tag_name[i]);
                printf("tag name: %s\n",tag_reader -> tag);
                if(strstr(argv[3],".mp3"))
                {
                    tag_reader -> fp = fopen(argv[3],"r");
                    tag_reader -> fp_out = fopen("output.mp3","w");
                    return success;
                }else
                    return failure;
           }
       }
       return failure;
   }else if(!strcmp(argv[1],"-v"))
   {
       strcpy(tag_reader -> mode,argv[1]);
       if(strstr(argv[2],".mp3"))
       {
            tag_reader -> fp = fopen(argv[2],"r");
            return success;
       }else
            return failure;
   }else
       return failure;
}

OperationType check_operation_type(char *argv[])
{
    if(!strcmp(argv[1],"-v"))
        return view;
    else if(!strcmp(argv[1],"-e"))
        return edit;
    else if(!strcmp(argv[1],"--help"))
        return help;
    else
        return unsupported;
}
