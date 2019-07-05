#include "reporte.h"

void concatChildFIle(int limit,char * output, pid_t children[]){
    FILE * fp;
    char texto[1000];
    printf("output %s",output);
    strcat(output,".txt");
    fp = fopen(output, "w");
    for(int inicio=0; inicio<=limit; inicio++){
    char name[1000];    
    FILE *gc;
    sprintf(name, "%d", children[inicio]);
    strcat(name,".txt");
    printf("Nombre de archivo hijo es %s\n", name);
    gc = fopen(name, "r");


        if (gc == NULL) 
        /*Si hay errores en el archivo*/
        {
            perror("No fue posible abrir el archivo nieto\n");
            exit(0);
        }
        

    while (!feof(gc)){
        fgets(texto, 1000, gc);
        fprintf(fp, "%s", texto);
    }
    fclose(gc);



	}
    fclose(fp);
}