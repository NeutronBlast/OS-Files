#include "info.h"
#include "utilities.h"

/* void fileInfo(char *actual, int indent, int *totalbytes, int *numF){
    DIR *dir;
    struct dirent *entrada;

    char path[PATH_MAX+1];
    char path2[PATH_MAX+1];


    if (!(dir = opendir(actual))){
        return;
    }

    while ((entrada = readdir(dir)) != NULL)
    {
    if (entrada->d_type != DT_DIR){ //No es un directorio

        if (strcmp(actual, "") == 0)
            {
                strcpy(path2, "./"); //Se concatena para tener ./ empezando
                strcat(path2, entrada->d_name);
                strcpy(actual, path2);
                printf("File path is %s\n",path2);
            }
            else
            {

                strcpy(path2, actual); //Se concatena para tener toda la ruta completa
                strcat(path2, "/");
                strcat(path2, entrada->d_name);

                FILE* fp = fopen(path2,"r");
                fseek(fp,0,SEEK_END);
                int Fbytes = ftell(fp);

                    if (Fbytes==-1){
                        perror("Archivo");
                        exit(1);
                    }

                fclose(fp);
                printf("Bytes of file is %d ", Fbytes);
                printf("File path is %s\n", path2);
                //fileInfo(path, indent, totalbytes+=Fbytes, numF++);
                //totalbytes = totalbytes + bytes;
            }

       }

        else{
            if ((strcmp(entrada->d_name, ".") != 0) && (strcmp(entrada->d_name, "..") != 0)) //Que no tome en cuenta el "." ni ".."
            {                                
                strcpy(path, actual); //Se concatena el nombre para buscar si hay subdirectorios
                strcat(path, "/");

                //Directorio en entrada
                strcat(path, entrada->d_name);

                fileInfo(path, indent, totalbytes, numF++);
            }
        } //Es un directorio


    }

    closedir(dir);
    fileInfo(path, indent+2, totalbytes, numF++);

}*/

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

    int n = strlen(info.abpath);
    info.luser = (char*)malloc(sizeof(char)*n);
    usr(info.abpath, info.luser);


    info.groupid = statbuf.st_gid;
    info.lastmod = statbuf.st_ctime;
    info.la = statbuf.st_atime;

    info.cont = 0;
    info.totalbytes = 0; 
    //fileInfo(info.abpath,indent,&info.totalbytes,&info.cont);

    if (op == 0){
        printf("\tINFORMACION DEL ARCHIVO\n\n");
        printf("Mi path absoluto es %s\n",info.abpath);    
        printf("Tamaño en bytes: %ld bytes\n",info.bytes);
        printf("Permisos %s \n",info.perms);
        printf("User ID: %d\n", info.userid);
        printf("User en letras %s\n",info.luser);
        printf("Grupo %d\n", info.groupid);
        printf("Ultimo acceso %s",ctime(&info.lastmod));
        printf("Ultima modificacion %s",ctime(&info.la));
        printf("Number of files %d\n",info.cont);
        printf("Total of bytes %d\n\n\n",info.totalbytes);
    }

    FILE *fp;
    char name[PATH_MAX+1];

    sprintf(name, "%d", child);
    strcat(name,".txt");
    printf("name of file %s\n",name);
    fp = fopen(name, "a");

    fprintf(fp, "%s %c", info.abpath, ' ');
    fprintf(fp, "%s %c", info.perms, ' ');
    fprintf(fp, "%s", info.luser);
    fprintf(fp, "%s %d %s", "(",info.userid,") ");
    fprintf(fp, "%d %c", info.groupid, ' ');
    fprintf(fp, "%s %c", ctime(&info.lastmod), ' ');
    fprintf(fp, "%d %c", info.cont, ' ');
    fprintf(fp, "%d %c", info.totalbytes, ' ');
    fprintf(fp, "%s", "\n");
    free(info.luser);   

    fclose(fp);

    //Para el numero de archivos se necesitara otra funcion donde se cuenten cuantos archivos hay y se sumen los bytes para cada uno
}

void lookSub(const char *actual, int indent, int op, char * output,pid_t child)
{
    /*Buscar todos los subdirectorios*/
    DIR *dir;
    struct dirent *entrada;
    printf("child pid %d   parent pid %d\n",getpid(),getppid());fflush(stdout);


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

                info(entrada,indent,op,output,child);

                lookSub(path, indent + 2,op,output,child);
            }
        }
    }


    closedir(dir);

}