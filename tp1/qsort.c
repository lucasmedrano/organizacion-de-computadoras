#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define salida_error_parametros 1
#define salida_error_archivo_inexistente 2
#define mensaje_error_cantidad_parametros "qsort: La cantidad de parametros no es la correcta.\nIntente 'qsort -h' para más información"
#define mensaje_error_parametros "qsort: La combinación de parametros no es válida.\nIntente 'qsort -h' para más información"
#define mensaje_error_archivo_inexistente "El archivo que quiere ordenar no existe"

void mostrar_error_y_salir(char *mensaje_error, int numero_salida){
    fprintf(stderr, "%s\n", mensaje_error);
    exit(numero_salida);
}

void mostrar_version(){ printf("%s\n", "v1.0");}

void mostrar_ayuda(){
    /*Sería mas lindo definir esta cadena en otro archivo y leerla de ahí Para que no quede hardcodeada*/
    char ayuda[] = "Usage:\n\tqsort -h\n\tqsort -V\n\tqsort [options] archivo\nOptions:\n\t-h, --help \tImprime ayuda.\n\t-V, --version \tVersión del programa.\n\t-o, --output \tArchivo de salida.\n\t-n, --numeric \tOrdenar los datos numéricamente en vez de alfabéticamente.\nExamples:\n\tqsort -n numeros.txt";
    printf("%s\n", ayuda);
}

int obtener_cantidad_palabras(char *nombre_archivo){
    FILE *archivo;
    archivo = fopen(nombre_archivo,"r");
    int cantidad = 0;
    char palabra[30];
    while(fgets(palabra, 30, archivo)) cantidad ++;
    return cantidad;
}

void obtener_palabras(char *nombre_archivo, char **lista_palabras){
    FILE *archivo_a_ordenar;
    archivo_a_ordenar = fopen(nombre_archivo,"r");

    char palabra[100];
    if (archivo_a_ordenar == NULL) mostrar_error_y_salir(mensaje_error_archivo_inexistente, salida_error_archivo_inexistente);

    int indice = 0;

    while(fgets(palabra, 100, archivo_a_ordenar) != NULL){
        *(palabra + strlen(palabra) - 1) = '\0';
        lista_palabras[indice] = malloc(strlen(palabra));
        strcpy(lista_palabras[indice], palabra);
        indice ++;
    }
    fclose(archivo_a_ordenar);
}

/*void orgaqsort(char** izq, char** der){
     tomo *izq como el pivote
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
        orgaqsort(izq, fin--); // no se si esta bien esto, quiero el anterior a fin
        orgaqsort(fin++, der); // idem pero con el siguiente
    }

}*/

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

    if ((strcmp(argv[1], "-o") == 0) || (strcmp(argv[1], "--output") == 0)){
        if (argc < 4)mostrar_error_y_salir(mensaje_error_cantidad_parametros, salida_error_parametros);

        int cantidad_palabras = obtener_cantidad_palabras(argv[3]);
        char **lista_palabras = malloc(cantidad_palabras * sizeof(char*));
        obtener_palabras(argv[3], lista_palabras);

    }

    else if ((strcmp(argv[2], "-o") == 0) || (strcmp(argv[2], "--output") == 0) || (strcmp(argv[1], "-n") == 0)){
        if (argc < 5) mostrar_error_y_salir(mensaje_error_cantidad_parametros, salida_error_parametros);

        int cantidad_palabras = obtener_cantidad_palabras(argv[4]);
        char **lista_palabras = malloc(cantidad_palabras * sizeof(char*));
        obtener_palabras(argv[4], lista_palabras);
    }

    else mostrar_error_y_salir(mensaje_error_parametros, salida_error_parametros);

}
