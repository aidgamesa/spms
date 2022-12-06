#pragma once


//C INCLUDES
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

//DEPENDS
#include <argparse.h>
#include <archive.h>
#include <archive_entry.h>
//#include <ini.h>
int ini_parse(const char* filename,
              int (*handler)(void* user, const char* section,
                             const char* name, const char* value),
              void* user);

//SPMS INCLUDES
#include <install.h>
#include <mkmeta.h>
#include <spms_error.h>

static const char *const usages[] = {
    "install <filename>",
    "mkmeta <meta.ini file>",
    NULL
};