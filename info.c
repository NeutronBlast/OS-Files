#include "info.h"
#include "utilities.h"

void infoFather(char*path, int indent, int op, char * output,FI numbers){
    I info;

    if (stat(path, &statbuf) == 1) {
    fprintf(stderr, " No se pudo aplicar stat sobre el archivo %s: %s \n", path, strerror(errno));
    exit(1);
    }

    realpath(path, info.abpath);
    info.bits = statbuf.st_mode;
    if ((info.bits & S_IRUSR) == 0){
        info.perms = (char*)malloc(sizeof(char)*47);
        strcpy(info.perms,"Usuario no tiene permiso de leer este archivo");
    }

    info.bytes = statbuf.st_size;

    info.perms = (char*)malloc(sizeof(char)*11);
    info.perms[0]= (S_ISDIR(statbuf.st_mode)) ? 'd' : '-';
    info.perms[1]=(statbuf.st_mode & S_IRUSR) ? 'r' : '-';
    info.perms[2]=(statbuf.st_mode & S_IWUSR) ? 'w' : '-';
    info.perms[3]=(statbuf.st_mode & S_IXUSR) ? 'x' : '-';
    info.perms[4]=(statbuf.st_mode & S_IRGRP) ? 'r' : '-';
    info.perms[5]=(statbuf.st_mode & S_IWGRP) ? 'w' : '-';
    info.perms[6]=(statbuf.st_mode & S_IXGRP) ? 'x' : '-';
    info.perms[7]=(statbuf.st_mode & S_IROTH) ? 'r' : '-';
    info.perms[8]=(statbuf.st_mode & S_IWOTH) ? 'w' : '-';
    info.perms[9]=(statbuf.st_mode & S_IXOTH) ? 'x' : '-';
    info.perms[10]=' ';
    info.perms[11]='\0';


    info.userid = statbuf.st_uid;
    struct passwd *pw = getpwuid(statbuf.st_uid);

    //printf("username is %s\n",username);

    int n = strlen(info.abpath);
    info.luser = (char*)malloc(sizeof(char)*n);
    strcpy(info.luser, pw->pw_name);


    info.groupid = statbuf.st_gid;

    struct group *g = getgrgid(statbuf.st_gid);

    info.group = (char*)malloc(sizeof(char)*n);
    strcpy(info.group, g->gr_name);

    //printf("group is %s\n",info.group);

    info.lastmod = statbuf.st_ctime;
    info.la = statbuf.st_atime;

    if (op == 1){
    FILE *fp;
    char name[PATH_MAX+1];
    strcpy(name,output);
    fp = fopen(name, "w");

    fprintf(fp, "%s %c", info.abpath, ' ');
    fprintf(fp, "%s %c", info.perms, ' ');
    fprintf(fp, "%s", info.luser);
    fprintf(fp, "%s %d %s", "(",info.userid,") ");
    fprintf(fp, "%s", info.group);
    fprintf(fp, "%s %d %s","(", info.groupid, ") ");
    fprintf(fp, "%s %c", ctime(&info.lastmod), ' ');
    fprintf(fp, "%s", ctime(&info.la));
    fprintf(fp, "%d %c", numbers.numF, ' ');
    fprintf(fp, "%d %c", numbers.bytes, ' ');
    fprintf(fp, "%s", "\n");
    free(info.luser);   

    fclose(fp);
    }

    else if (op == 0){
        printf("%s ", info.abpath);
        printf("%s ", info.perms);
        printf("%s", info.luser);
        printf("(%d) ",info.userid);
        printf("%s", info.group);
        printf("(%d) ", info.groupid);
        printf("%s ", ctime(&info.lastmod));
        printf("%s", ctime(&info.la));
        printf("%d ", numbers.numF);
        printf("%d ", numbers.bytes);
        printf("%s", "\n");
    }
}

void infoFile(char*path, int indent, int op, char * output,pid_t child,int numF,int bytes){

    if (stat(path, &statbuf) == 1) {
    fprintf(stderr, " No se pudo aplicar stat sobre el archivo %s: %s \n", path, strerror(errno));
    exit(1);
    }

    FILE *fp;
    char name[PATH_MAX+1];

    sprintf(name, "%d", child);
    strcat(name,".txt");
    //printf("name of file %s\n",name);
    fp = fopen(name, "a");
    fprintf(fp, "%d %c", numF, ' ');
    fprintf(fp, "%d %c", bytes, ' ');
    fprintf(fp, "%s", "\n");

    fclose(fp);
}

void info(struct dirent *entrada, int indent, int op, char * output,pid_t child){
    I info;

    if (stat(entrada->d_name, &statbuf) == 1) {
    fprintf(stderr, " No se pudo aplicar stat sobre el archivo %s: %s \n", entrada->d_name, strerror(errno));
    exit(1);
    }

    realpath(entrada->d_name, info.abpath);
    info.bits = statbuf.st_mode;
    if ((info.bits & S_IRUSR) == 0){
        info.perms = (char*)malloc(sizeof(char)*47);
        strcpy(info.perms,"Usuario no tiene permiso de leer este archivo");
        return;
    }

    info.bytes = statbuf.st_size;

    info.perms = (char*)malloc(sizeof(char)*11);
    info.perms[0]= (S_ISDIR(statbuf.st_mode)) ? 'd' : '-';
    info.perms[1]=(statbuf.st_mode & S_IRUSR) ? 'r' : '-';
    info.perms[2]=(statbuf.st_mode & S_IWUSR) ? 'w' : '-';
    info.perms[3]=(statbuf.st_mode & S_IXUSR) ? 'x' : '-';
    info.perms[4]=(statbuf.st_mode & S_IRGRP) ? 'r' : '-';
    info.perms[5]=(statbuf.st_mode & S_IWGRP) ? 'w' : '-';
    info.perms[6]=(statbuf.st_mode & S_IXGRP) ? 'x' : '-';
    info.perms[7]=(statbuf.st_mode & S_IROTH) ? 'r' : '-';
    info.perms[8]=(statbuf.st_mode & S_IWOTH) ? 'w' : '-';
    info.perms[9]=(statbuf.st_mode & S_IXOTH) ? 'x' : '-';
    info.perms[10]=' ';
    info.perms[11]='\0';


    info.userid = statbuf.st_uid;

    info.userid = statbuf.st_uid;
    struct passwd *pw = getpwuid(statbuf.st_uid);

    //printf("username is %s\n",username);

    int n = strlen(info.abpath);
    info.luser = (char*)malloc(sizeof(char)*n);
    strcpy(info.luser, pw->pw_name);

    info.groupid = statbuf.st_gid;

    struct group *g = getgrgid(statbuf.st_gid);

    info.group = (char*)malloc(sizeof(char)*n);
    strcpy(info.group, g->gr_name);

    info.lastmod = statbuf.st_ctime;
    info.la = statbuf.st_atime;

    FILE *fp;
    char name[PATH_MAX+1];

    sprintf(name, "%d", child);
    strcat(name,".txt");
    //printf("name of file %s\n",name);
    fp = fopen(name, "a");

    fprintf(fp, "%s %c", info.abpath, ' ');
    fprintf(fp, "%s %c", info.perms, ' ');
    fprintf(fp, "%s", info.luser);
    fprintf(fp, "%s %d %s", "(",info.userid,") ");
    fprintf(fp, "%s", info.group);
    fprintf(fp, "%s %d %s","(", info.groupid, ") ");
    fprintf(fp, "%s %c", ctime(&info.lastmod), ' ');
    fprintf(fp, "%s", ctime(&info.la));
    free(info.luser);   

    fclose(fp);
}

void infoSub(char*path, int indent, int op, char * output,pid_t child){
    I info;

    if (stat(path, &statbuf) == 1) {
    fprintf(stderr, " No se pudo aplicar stat sobre el archivo %s: %s \n", path, strerror(errno));
    exit(1);
    }

    realpath(path, info.abpath);
    info.bits = statbuf.st_mode;
    if ((info.bits & S_IRUSR) == 0){
        info.perms = (char*)malloc(sizeof(char)*47);
        strcpy(info.perms,"Usuario no tiene permiso de leer este archivo");
    }

    info.bytes = statbuf.st_size;

    info.perms = (char*)malloc(sizeof(char)*11);
    info.perms[0]= (S_ISDIR(statbuf.st_mode)) ? 'd' : '-';
    info.perms[1]=(statbuf.st_mode & S_IRUSR) ? 'r' : '-';
    info.perms[2]=(statbuf.st_mode & S_IWUSR) ? 'w' : '-';
    info.perms[3]=(statbuf.st_mode & S_IXUSR) ? 'x' : '-';
    info.perms[4]=(statbuf.st_mode & S_IRGRP) ? 'r' : '-';
    info.perms[5]=(statbuf.st_mode & S_IWGRP) ? 'w' : '-';
    info.perms[6]=(statbuf.st_mode & S_IXGRP) ? 'x' : '-';
    info.perms[7]=(statbuf.st_mode & S_IROTH) ? 'r' : '-';
    info.perms[8]=(statbuf.st_mode & S_IWOTH) ? 'w' : '-';
    info.perms[9]=(statbuf.st_mode & S_IXOTH) ? 'x' : '-';
    info.perms[10]=' ';
    info.perms[11]='\0';


    info.userid = statbuf.st_uid;

    info.userid = statbuf.st_uid;
    struct passwd *pw = getpwuid(statbuf.st_uid);

    //printf("username is %s\n",username);

    int n = strlen(info.abpath);
    info.luser = (char*)malloc(sizeof(char)*n);
    strcpy(info.luser, pw->pw_name);


    info.groupid = statbuf.st_gid;

    struct group *g = getgrgid(statbuf.st_gid);

    info.group = (char*)malloc(sizeof(char)*n);
    strcpy(info.group, g->gr_name);

    info.lastmod = statbuf.st_ctime;
    info.la = statbuf.st_atime;

    FILE *fp;
    char name[PATH_MAX+1];

    sprintf(name, "%d", child);
    strcat(name,".txt");
    //printf("name of file %s\n",name);
    fp = fopen(name, "a");

    fprintf(fp, "%s %c", info.abpath, ' ');
    fprintf(fp, "%s %c", info.perms, ' ');
    fprintf(fp, "%s", info.luser);
    fprintf(fp, "%s %d %s", "(",info.userid,") ");
    fprintf(fp, "%s", info.group);
    fprintf(fp, "%s %d %s","(", info.groupid, ") ");
    fprintf(fp, "%s %c", ctime(&info.lastmod), ' ');
    fprintf(fp, "%s", ctime(&info.la));
    free(info.luser);   

    fclose(fp);

    //Para el numero de archivos se necesitara otra funcion donde se cuenten cuantos archivos hay y se sumen los bytes para cada uno
}

FI lookFile(char *actual, int indent, int op, char * output,pid_t child,int numF, int bytes)
{
    FI aux;
    /*Buscar todos los subdirectorios*/
    DIR *dir;
    struct dirent *entrada;
    //printf("child pid %d   parent pid %d\n",getpid(),getppid());fflush(stdout);
    //printf("path actual %s\n", actual);

    char path2[PATH_MAX+1];

    if (!(dir = opendir(actual))){
    return aux;
    }


    while ((entrada = readdir(dir)) != NULL)
    /* Mientras consiga archivos*/
    {

        if (entrada->d_type != DT_DIR){ //No es un directorio

            if (strcmp(actual, "") == 0){
                strcpy(path2, "./"); //Se concatena para tener ./ empezando
                strcat(path2, entrada->d_name);
                strcpy(actual, path2);
            }
            else
            {
                strcpy(path2, actual); //Se concatena para tener toda la ruta completa
                strcat(path2, "/");
                strcat(path2, entrada->d_name);
                //printf("File path is %s\n",path2);

                FILE* fp = fopen(path2,"r");
                fseek(fp,0,SEEK_END);
                int Fbytes = ftell(fp);
                bytes+=Fbytes;
                aux.bytes = bytes;
                numF++;
                aux.numF = numF;

                    if (Fbytes==-1){
                        perror("Archivo");
                        exit(1);
                    }

                fclose(fp);
                //printf("Bytes in total is %d ", bytes);
                //printf("Number of files is %d\n",numF);
            }
        }
        else if (entrada->d_type == DT_DIR){
            if ((strcmp(entrada->d_name, ".") != 0) && (strcmp(entrada->d_name, "..") != 0)) //Que no tome en cuenta el "." ni ".."
            { 
                numF++;
                aux.numF = numF;
            }
        }

    }
    //printf("por aqui %s %d %d\n\n\n\n",actual, numF,bytes);
    if (child != 0)
        infoFile(actual,indent,op,output,child,numF,bytes);
    closedir(dir);

    return aux;

}

void lookSub(char *actual, int indent, int op, char * output,pid_t child,int numF, int bytes)
{
    FI aux;
    aux.numF = numF;
    aux.bytes = bytes;
    /*Buscar todos los subdirectorios*/
    DIR *dir;
    struct dirent *entrada;
    //printf("child pid %d   parent pid %d\n",getpid(),getppid());fflush(stdout);
    //printf("path actual %s\n", actual);


    char path[PATH_MAX+1];

    if (!(dir = opendir(actual))){
    return;
    }


    while ((entrada = readdir(dir)) != NULL)
    /* Mientras consiga archivos*/
    {

        if (entrada->d_type == DT_DIR) //Es un directorio
        {
            if ((strcmp(entrada->d_name, ".") != 0) && (strcmp(entrada->d_name, "..") != 0)) //Que no tome en cuenta el "." ni ".."
            {  
                   
                strcpy(path, actual); //Se concatena el nombre para buscar si hay subdirectorios
                strcat(path, "/");
                strcat(path, entrada->d_name);

                infoSub(path,indent,op,output,child);

                //Por cada subdirectorio le busco los archivos
                aux = lookFile(path, indent, op, output, child,0,0);

                lookSub(path, indent + 2,op,output,child,numF++,bytes);
            }
        }

    }

    closedir(dir);
}