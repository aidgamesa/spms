#include <global.h>

int exit_error(const char* message){
    perror(message);
    exit(EXIT_FAILURE);
}