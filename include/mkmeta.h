#pragma once

struct metainfo {
    char name[1024];
    int version;
};

int mkmeta(int argc, const char** argv);