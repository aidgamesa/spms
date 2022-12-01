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

//SPMS INCLUDES
#include <install.h>
#include <spms_error.h>

static const char *const usages[] = {
    "install <filename>",
    NULL
};