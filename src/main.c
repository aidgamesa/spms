#include <global.h>

struct cmd_struct{
    const char* name;
    int (*fn)(int, const char**);
};

int main(int argc, const char* argv[]){

    struct cmd_struct commands[]={
        {
            "install",
            install
        }
    };

    struct argparse argparse;
    struct argparse_option options[] = {
        OPT_HELP(),
        OPT_END()
    };
    argparse_init(&argparse, options, usages, ARGPARSE_STOP_AT_NON_OPTION);
    argc = argparse_parse(&argparse, argc, argv);
    if (argc < 1) {
        argparse_usage(&argparse);
        return -1;
    }
    struct cmd_struct *cmd;

    for (long unsigned int i = 0; i < sizeof(commands)/sizeof(struct cmd_struct); i++) {
        if (!strcmp(commands[i].name, argv[0])) {
            cmd = &commands[i];
        }
    }
    if(!cmd){
        argparse_usage(&argparse);
        return -1;
    }
    return cmd->fn(argc, argv);
}