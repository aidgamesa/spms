#include <global.h>


int handler(void* user, const char* section, const char* name, const char* value);

int mkmeta(int argc, const char** argv){
    struct argparse_option options[] = {
        OPT_HELP(),
        OPT_END()
    };
    struct argparse argparse;
    argparse_init(&argparse, options, usages, 0);
    argc = argparse_parse(&argparse, argc, argv);
    if (argc<1){
        argparse_usage(&argparse);
        return -1;
    }
    
    struct metainfo meta;

    const char* meta_file=argv[0];
    
    memcpy((&meta)->name, malloc(sizeof(meta.name)), sizeof(meta.name));

    ini_parse(meta_file, handler, &meta);

    int fd;
    if (access("meta", F_OK)!=0){
        fd=open("meta", O_WRONLY | O_CREAT);
    } else {
        fd=open("meta", O_WRONLY);
    }
    write(fd, (void*)&meta, sizeof(meta));

    return 0;
}

int handler(void* user, const char* section, const char* name, const char* value){
    struct metainfo* meta = (struct metainfo*)user;
    #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
    if (MATCH("meta", "name")){
        size_t lenght=sizeof(value);
        if (lenght<sizeof(meta->name)){
            memcpy(meta->name, value, lenght);
        }
        //meta->name=(char[1024])value;
    }
    if (MATCH("meta", "version")){
        meta->version=atoi(value);
    }
    return 1;
}