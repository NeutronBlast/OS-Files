#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
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

/*El recorrido estara en otra liberia*/

struct archivos //Lista para todos los archivos
{

    char nombre[PATH_MAX+1];
    struct archivos *sig;
};

pid_t children[1000];
int status = 0;
pid_t wpid;
int Nchildren = 0;

void recorrido(const char *actual, int indent, struct archivos **a, int op, char * output)
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
                //printf("Hola, soy el path %s\n",path);
                int cont = 0;
                
                //strcpy(abpath,"");
                
                strcpy(path, actual); //Se concatena el nombre para buscar si hay subdirectorios
                strcat(path, "/");
                cont = frequency(path);

                if (cont==1){
                    printf("\n\nFORKED\n");
                    printf("cont %d\n",Nchildren);
                        if ((children[Nchildren] = fork()) == 0){
                        /*Get info*/
                        children[Nchildren] = getpid();
                        info(entrada,indent,op,output,children[Nchildren]);
                        }
                    Nchildren++;
                }

                //Directorio en entrada
                strcat(path, entrada->d_name);

                recorrido(path, indent + 2, a,op,output);
            }
        }
    }


    closedir(dir);

}

int main(int argc, char *argv[]) {
    int op = 0;
    char * output = NULL;

    if (!argv[1]){
        printf("Los resultados se imprimiran por pantalla\n");
    }

    else{
    /*Nombre archivo de salida*/
    size_t len = strlen(argv[1]);
    output = malloc(len+2);
    strcpy(output, argv[1]);
    op = 1;
    }
    
    struct archivos *a;
    a = malloc(sizeof(struct archivos));
    a->sig = NULL;
    recorrido(".", 0, &a,op,output);
    
    while ((wpid = wait(&status)) > 0);
    if (op == 1){
        Nchildren = Nchildren-1;
        concatChildFIle(Nchildren, output,children);
    }


    return 0; 
}