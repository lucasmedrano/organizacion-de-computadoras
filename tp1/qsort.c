#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define salida_error_parametros 1
#define salida_error_archivo_inexistente 2
#define mensaje_error_cantidad_parametros "qsort: La cantidad de parametros no es la correcta.\nIntente 'qsort -h' para más información"
#define mensaje_error_parametros "qsort: La combinación de parametros no es válida.\nIntente 'qsort -h' para más información"
#define mensaje_error_archivo_inexistente "El archivo que quiere ordenar no existe"

void mostrar_ayuda(){
    /*Sería mas lindo definir esta cadena en otro archivo y leerla de ahí Para que no quede hardcodeada*/
    char ayuda[] = "Usage:\n\tqsort -h\n\tqsort -V\n\tqsort [options] archivo\nOptions:\n\t-h, --help \tImprime ayuda.\n\t-V, --version \tVersión del programa.\n\t-o, --output \tArchivo de salida.\n\t-n, --numeric \tOrdenar los datos numéricamente en vez de alfabéticamente.\nExamples:\n\tqsort -n numeros.txt";
    printf("%s\n", ayuda);
}

void mostrar_version(){ printf("%s\n", "v1.0");}

void mostrar_error_y_salir(char *mensaje_error, int numero_salida){
    fprintf(stderr, "%s\n", mensaje_error);
    exit(numero_salida);
}

void qsort(char** izq, char** der, int num){
    /* tomo *izq como el pivote */
    if (izq != der) {
        char *aux;
        char **inicio = izq;
        char **fin = der;
        while (inicio != fin) {
            while (strcmp(*inicio, *izq) <= 0) inicio++;  // falta hacer algo con num
            while (strcmp(*fin, *izq) > 0) fin--;         // en estas lineas
            if (inicio != fin){
                aux = *inicio;
                *inicio = *fin;
                *fin = aux;
            }
        }
        aux = *izq;
        *izq = *fin;
        *fin = aux;
        qsort(izq, fin--, num); // no se si esta bien esto, quiero el anterior a fin
        qsort(fin++, der, num); // idem pero con el siguiente
    }

}

void orgaqsort(char *nombre_archivo_a_ordenar, char *nombre_archivo_a_escribir, bool ordenar_por_numero){
    /*Si nombre_archivo_a_escribir == Null escribe por stdout.
    Si nombre_archivo_a_escribir es un archivo, escribe en el archivo
    Si ordenar_por_numero == False ordena por letra
    Si ordenar_por_numero == True ordena por numero*/

    /*FILE *archivo_a_escribir;*/
    FILE *archivo_a_ordenar;

    archivo_a_ordenar = fopen(nombre_archivo_a_ordenar,"r");
    /*archivo_a_escribir = fopen(nombre_archivo_a_escribir, "w")*/
    char* palabra;
    char** lista_de_strings;
    int indice = 0;

    if (archivo_a_ordenar == NULL){
        mostrar_error_y_salir(mensaje_error_archivo_inexistente, salida_error_archivo_inexistente);
    }
    else{
        /*Esto lo hice para probar, pero aca habria que ordenar el archivo, ya que existe*/
        printf("\nEl contenido del archivo de prueba es \n\n");
        while(palabra = fgets(archivo_a_ordenar)){
            int i = strlen(palabra);
            palabra[i-1] = '\0';
            lista_de_strings[indice] = palabra;
            indice++;
         //   printf("%c",caracter);
        }
    }
    fclose(archivo_a_ordenar);
}


int main(int argc, char *argv[]){
    if ((argc < 2) || argc > 5) mostrar_error_y_salir(mensaje_error_cantidad_parametros, salida_error_parametros);
    else if ((strcmp(argv[1], "-h") == 0) || (strcmp(argv[1], "--help") == 0)){
        if(argc != 2) mostrar_error_y_salir(mensaje_error_cantidad_parametros, salida_error_parametros);
        mostrar_ayuda();
    }
    else if ((strcmp(argv[1], "-V") == 0) || (strcmp(argv[1], "--version") == 0)){
        if(argc != 2) mostrar_error_y_salir(mensaje_error_cantidad_parametros, salida_error_parametros);
        mostrar_version();
    }

    else if ((strcmp(argv[1], "-o") == 0) || (strcmp(argv[1], "--output") == 0)){
        /*Llama a qsort con el archivo en argv[2] y ordenando por letra*/
        if (argc < 4) mostrar_error_y_salir(mensaje_error_cantidad_parametros, salida_error_parametros);
        orgaqsort(argv[3], argv[2], false);
    }

    else if ((strcmp(argv[2], "-o") == 0) || (strcmp(argv[2], "--output") == 0) || (strcmp(argv[1], "-n") == 0)){
        /*Llama a qsort con el archivo en argv[3] y ordenando por numero*/
        if (argc < 5) mostrar_error_y_salir(mensaje_error_cantidad_parametros, salida_error_parametros);
        orgaqsort(argv[4], argv[3], true);
    }

    else mostrar_error_y_salir(mensaje_error_parametros, salida_error_parametros);

}
