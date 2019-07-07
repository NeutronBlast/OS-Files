#include "info.h"
#include "reporte.h"

FI getTotalBN(char*texto){
    FI aux;
    char au[PATH_MAX+1];
    char bytes[PATH_MAX+1];
    strcpy(au,"");
    strcpy(bytes,"");
    int i = 0;
    //printf("texto de entrada es %s\n",texto);
        for (i = 0; texto[i]!=' '; i++){
            if (texto[i]!=2)
                au[i] = texto[i];
            //printf("au %c con i igual a %d\n",au[i],i);
        }
        au[i]='\0';
        aux.numF = atoi(au);

        //printf("esto fue lo que me quedo en el texto para numF %d\n",aux.numF);
        strcpy(au,"");

        i=i+1;
        int j=0;
        for (i=i; texto[i]!='\0';i++){
            bytes[j]=texto[i];
            j++;
        }
        bytes[j]='\0';
        aux.bytes=atoi(bytes);
        //printf("esto fue lo que me quedo para el numero de bytes en el archivo %d\n",aux.bytes);
        strcpy(bytes,"");

    return aux;
}


void concatChildFIle(int limit,char * output, int op, pid_t child){
    FILE * fp;
    FI fileNumber;
    char texto[1000];
    //printf("output %s",output);

    if (op == 1)
        fp = fopen(output, "a");


    char name[1000];    
    FILE *gc;
    sprintf(name, "%d", child);
    strcat(name,".txt");
    //printf("Nombre de archivo hijo es %s\n", name);
    gc = fopen(name, "r");


        if (gc == NULL) 
        /*Si hay errores en el archivo*/
        {
            perror("No fue posible abrir el archivo");
            exit(0);
        }

    fileNumber.numF = 0;
    fileNumber.bytes = 0;
    int sumaN = 0;
    int sumaB = 0;

    //Sacar numero total de archivos y bytes
    while (!feof(gc)){
        fgets(texto, 1000, gc);
            //Si es 0 o es un entero
                if (texto[0]>=48 && texto[0]<=57){
                    //printf("test %s\n",texto);
                    fileNumber=getTotalBN(texto);
                    sumaN+=fileNumber.numF;
                    sumaB+=fileNumber.bytes;
                }
        strcpy(texto,"");
    }

    rewind(gc);

    int cont = 0;

    //Copiar informacion del directorio hijo
    while (!feof(gc)){
        fgets(texto, 1000, gc);
            //Si es 0 o es un entero
                if (texto[0]>=48 && texto[0]<=57){
                    continue;
                }
        if (op == 1){
            if (texto[0]=='/' || texto[0]==' ')
                cont++;

            if (cont<=2)
                fprintf(fp,"%s",texto);
        }
        else if (op == 0){
            if (texto[0]=='/' || texto[0]==' ')
                cont++;

            if (cont<=2)
                printf("%s",texto);
        }
        strcpy(texto,"");
    }
    //printf("esto fue fin de archivo %d .txt\n\n\n\n\n",child);
    fclose(gc);

    //Aqui se copia el total calculado

    if (op == 1){
        fprintf(fp,"%d %c",sumaN,' ');
        fprintf(fp, "%d %c", sumaB, ' ');
        fprintf(fp, "%s", "\n");

        fclose(fp);
    }

    else if (op == 0){
        printf("%d %d\n",sumaN,sumaB);
    }
}