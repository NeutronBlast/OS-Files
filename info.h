#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <grp.h>
#include <string.h>
#include <pwd.h>
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
    char * group;
    time_t lastmod;
    time_t la;
}I;

typedef struct {
    int numF;
    int bytes;
}FI;

void infoFather(char*path, int indent, int op, char * output,FI numbers);

void fileInfo(char *actual, int indent, int *totalbytes, int *numF);

void infoSub(char*path, int indent, int op, char * output,pid_t child);

FI lookFile(char *actual, int indent, int op, char * output,pid_t child,int numF, int bytes);

void lookSub(char *actual, int indent, int op, char * output,pid_t child,int numF, int bytes);

#endif // INFO_H