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
        const char* name = archive_entry_pathname_utf8(entry);
        switch(archive_entry_filetype(entry)){
            case S_IFDIR:
                {
                    printf("DIR: %s\n", name);
                    break;
                }
            case S_IFREG:
                {
                    printf("FILE: %s\n", name);
                    break;
                }
            case S_IFLNK:
                {
                    printf("SYMLINK: %s -> %s\n", name, archive_entry_symlink(entry));
                    break;
                }
        }
    }
    return 0;
}