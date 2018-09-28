#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define salida_error_parametros 1

void mostrar_ayuda(){
    /*Sería mas lindo definir esta cadena en otro archivo y leerla de ahí Para que no quede hardcodeada*/
    char ayuda[] = "Usage:\n\tqsort -h\n\tqsort -V\n\tqsort [options] archivo\nOptions:\n\t-h, --help \tImprime ayuda.\n\t-V, --version \tVersión del programa.\n\t-o, --output \tArchivo de salida.\n\t-n, --numeric \tOrdenar los datos numéricamente en vez de alfabéticamente.\nExamples:\n\tqsort -n numeros.txt";
    printf("%s\n", ayuda);
}

void mostrar_version(){ printf("%s\n", "v1.0");}

void error_cantidad_parametros(){
    printf("%s\n", "qsort: La cantidad de parametros no es la correcta.\nIntente 'qsort -h' para más información");
    exit(salida_error_parametros);
}

void error_parametros(){
    printf("%s\n", "qsort: La combinación de parametros no es válida.\nIntente 'qsort -h' para más información");
    exit(salida_error_parametros);
}

int main(int argc, char *argv[]){
    if ((argc < 2) || argc > 4){error_cantidad_parametros();}
    else if ((strcmp(argv[1], "-h") == 0) || (strcmp(argv[1], "--help") == 0)){
        if(argc != 2) error_cantidad_parametros();
        mostrar_ayuda();
    }
    else if ((strcmp(argv[1], "-V") == 0) || (strcmp(argv[1], "--version") == 0)){
        if(argc != 2) error_cantidad_parametros();
        mostrar_version();
    }

    /*else if ((strcmp(argv[1], "-o") == 0) || (strcmp(argv[1], "--output") == 0)){
        /*Llamar a qsort con el archivo en argv[2] y ordenando por letra
    }

    else if ((strcmp(argv[2], "-o") == 0) || (strcmp(argv[2], "--output") == 0) || (strcmp(argv[1], "-n") == 0)){
        /*Llamar a qsort con el archivo en argv[3] y ordenando por numero
    }*/

    else {error_parametros();}

}
