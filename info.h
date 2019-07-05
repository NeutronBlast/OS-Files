#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>
#include <time.h>
#include <sys/stat.h>
#ifndef INFO_H
#define INFO_H

struct stat statbuf;

typedef struct{
    char abpath[PATH_MAX+1];
    mode_t bits;
    size_t bytes;
    char * perms;
    uid_t userid;
    char * luser;
    gid_t groupid;
    time_t lastmod;
    time_t la;
    int cont;
    int totalbytes;
}I;

void fileInfo(char *actual, int indent, int *totalbytes, int *numF);
void info(struct dirent *entrada, int indent, int op, char * output, pid_t child);

#endif // INFO_H