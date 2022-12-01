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
    printf("%s\n", filename);
    return 0;
}