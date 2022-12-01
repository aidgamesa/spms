#include <global.h>

int install(int argc, const char** argv){
    printf("%d\n", argc);
    for(int i = 0; i < argc; i++){
        printf("%s\n", argv[i]);
    }
    return 0;
}
int install_backend(const char* filename){
    return 0;
}