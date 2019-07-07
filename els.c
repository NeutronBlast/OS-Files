#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>
#include <time.h>
#include <sys/stat.h>
#include "info.h"
#include "utilities.h"
#include "reporte.h"

pid_t children[1000];
int status = 0;
pid_t wpid;
int Nchildren = 0;

void recorrido(const char *actual, int indent, int op, char * output)
{
    /*Funcion que recorre todo el directorio actual y subdirectorios y ve los archivos*/
    DIR *dir;
    struct dirent *entrada;


    char path[PATH_MAX+1];

    if (!(dir = opendir(actual))){
    /*Error en archivo actual*/
        exit(1);
    }


    while ((entrada = readdir(dir)) != NULL)
    /* Mientras consiga archivos*/
    {

        if (entrada->d_type == DT_DIR) //Es un directorio
        {
            if ((strcmp(entrada->d_name, ".") != 0) && (strcmp(entrada->d_name, "..") != 0)) //Que no tome en cuenta el "." ni ".."
            {
                int cont = 0;
                                
                strcpy(path, actual); //Se concatena el nombre para buscar si hay subdirectorios
                strcat(path, "/");
                strcat(path, entrada->d_name);
                //printf("path %s\n", path);
                cont = frequency(path);


                if (cont==1){
                    if ((children[Nchildren] = fork()) == 0){
                        children[Nchildren] = getpid();
                        //Informacion del directorio
                        infoSub(path,indent,op,output,children[Nchildren]);
                        //Buscar archivos en ese directorio
                        lookFile(path, indent, op, output, children[Nchildren],0,0);
                        //Buscar por subdirectorios
                        lookSub(path, indent, op, output,children[Nchildren],0,0);
                        exit(0);
                        }
                    Nchildren++;
                }

                //Directorio en entrada

                recorrido(path, indent + 2,op,output);
            }
        }
    }


    closedir(dir);

}

int main(int argc, char *argv[]) {
    int op = 0;
    char * output = NULL;

    if (argv[1]){
    /*Nombre archivo de salida*/
    size_t len = strlen(argv[1]);
    output = malloc(len+2);
    strcpy(output, argv[1]);
    op = 1;
    }

    recorrido(".", 0,op,output);

    FI numberFile;
    numberFile.numF = Nchildren;
    numberFile.bytes = 0;

    numberFile = lookFile(".",0,op,output,0,numberFile.numF,numberFile.bytes);
    //printf("files %d %d",numberFile.numF,numberFile.bytes);
    
    //Esperar a que todos los hijos terminen para generar reporte final
    while ((wpid = wait(&status)) > 0);

    Nchildren = Nchildren-1;

    if (op == 0)
        printf("\t\tREPORTE FINAL\n\n");

    infoFather(".", 0, op, output, numberFile);
        for (int inicio =0; inicio<=Nchildren; inicio++){
            concatChildFIle(Nchildren, output, op, children[inicio]);
        }

    if (op == 1)
        printf("El reporte final ha sido generado en el archivo %s.txt\n",output);

    return 0; 
}