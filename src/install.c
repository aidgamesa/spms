#include <global.h>

int install_real(const char* filename);

int install(int argc, const char** argv){
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
    for (int i = 0; i<argc; i++){
        printf("installing %s...\n", argv[i]);
        install_real(argv[i]);
    }
    return 0;
}
int install_real(const char* filename){
    if (access(filename, F_OK)!=0){
        exit_error(filename);
    }
    struct archive* a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);
    struct stat st;
    stat(filename, &st);
    if (st.st_size < 1 || archive_read_open_filename(a, filename, 0)  != ARCHIVE_OK){
        printf("Error loading file %s\n", filename);
        return EXIT_FAILURE;
    }
    struct archive_entry* entry;
    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        int name_len=sizeof(archive_entry_pathname_utf8(entry))+1;
        char* name = malloc(name_len);
        // = strcat((char*)"/", (char*)archive_entry_pathname_utf8(entry));
        strcpy(name, "/");
        strcat(name, (char*)archive_entry_pathname_utf8(entry));
        switch(archive_entry_filetype(entry)){
            case S_IFDIR:
                {
                    int r = mkdir(name, archive_entry_mode(entry));
                    if (r!=0 && errno != EEXIST){
                        exit_error("mkdir");
                    }
                    break;
                }
            case S_IFREG:
                {
                    if (strstr(name, "/meta")){
                        struct metainfo meta;
                        int fd = memfd_create("meta", O_RDWR);
                        
                        ftruncate(fd, sizeof(meta));
                        archive_read_data_into_fd(a, fd);
                        lseek(fd, 0, SEEK_SET);
                        read(fd, (void*)&meta, sizeof(meta));
                        printf("meta:\n\tname: %s\n\tversion: %d\n", meta.name, meta.version);
                        break;
                    }
                    int fd;
                    if (access(name, F_OK)!=0){
                        fd=open(name, O_WRONLY | O_CREAT, archive_entry_mode(entry));
                    } else {
                        fd=open(name, O_WRONLY);
                        chmod(name, archive_entry_mode(entry));
                    }
                    if (fd<1){
                        exit_error("open");
                    }
                    archive_read_data_into_fd(a, fd);
                    close(fd);
                    break;
                }
            case S_IFLNK:
                {
                    if (symlink(archive_entry_symlink(entry),name)!=0 && errno != EEXIST){
                        exit_error("symlink");
                    }
                    break;
                }
        }
    }
    return 0;
}