#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define salida_error_parametros 1
#define salida_error_archivo_inexistente 2
#define mensaje_error_cantidad_parametros "qsort: La cantidad de parametros no es la correcta.\nIntente 'qsort -h' para más información"
#define mensaje_error_parametros "qsort: La combinación de parametros no es válida.\nIntente 'qsort -h' para más información"
#define mensaje_error_archivo_inexistente "El archivo que quiere ordenar no existe"
#define MENSAJE_AYUDA "Usage:\n\tqsort -h\n\tqsort -V\n\tqsort [options] archivo\nOptions:\n\t-h, --help \tImprime ayuda.\n\t-V, --version \tVersión del programa.\n\t-o, --output \tArchivo de salida.\n\t-n, --numeric \tOrdenar los datos numéricamente en vez de alfabéticamente.\nExamples:\n\tqsort -n numeros.txt"
#define VERSION "v1.0"

void mostrar_error_y_salir(char *mensaje_error, int numero_salida){
    fprintf(stderr, "%s\n", mensaje_error);
    exit(numero_salida);
}

void mostrar_version(){printf("%s\n", VERSION);}

void mostrar_ayuda(){printf("%s\n", MENSAJE_AYUDA);}

int obtener_longitud_maxima(FILE* archivo){
    //Obtiene longitud contando el \n o \0 del final
    // ejemplo: para "hola", maximo = 5
    int maximo = 0;
    int actual = 0;
    int caracter;
    while ((caracter = fgetc(archivo)) != EOF){
        actual++;
        if (caracter == '\n'){
            if (actual > maximo) maximo = actual;
            actual = 0;
        }
    }
    return maximo;
}

int obtener_cantidad_palabras(FILE *archivo, int len){
    int cantidad = 0;
    char palabra[len];
    while(fscanf(archivo,"%s",palabra) != EOF) cantidad ++;
    return cantidad;
}

void obtener_palabras(FILE* archivo_a_ordenar, char **lista_palabras, int len){
    int indice = 0;
    char palabra[len];

    while(fscanf(archivo_a_ordenar,"%s",palabra) != EOF){
        *(palabra + strlen(palabra)) = '\0';
        lista_palabras[indice] = malloc(strlen(palabra) + 1);
        strcpy(lista_palabras[indice], palabra);
        indice ++;
    }
}

void orgaqsort(char** izq, char** der){
    if (izq <= der) {
        char *aux;
        char **inicio = izq;
        char **fin = der;
        while (inicio < fin){
            while ((strcmp(*inicio, *izq) <= 0) && (inicio < der))inicio++; //falta hacer que compare enteros, que seria
            while ((strcmp(*fin, *izq) > 0) && (fin > izq)) fin--;       //atoi(*inicio) <=/> atoi(*izq), y tambien hacer qsort general
            if (inicio < fin){
                aux = *inicio;
                *inicio = *fin;
                *fin = aux;
            }
        }
        aux = *izq;
        *izq = *fin;
        *fin = aux;
        orgaqsort(izq, fin-1);
        orgaqsort(fin+1, der);
    }

}

int main(int argc, char *argv[]){

    int longitud, cantidad_palabras, nro_archivo_entrada, nro_archivo_salida, criterio_ordenamiento;
    char** lista_palabras;
    FILE* archivo;
    FILE* output = stdout;

    if ((argc < 2) || argc > 5) {
        mostrar_error_y_salir(mensaje_error_cantidad_parametros, salida_error_parametros);
    }
    else if ((strcmp(argv[1], "-h") == 0) || (strcmp(argv[1], "--help") == 0)){
        if(argc != 2) mostrar_error_y_salir(mensaje_error_cantidad_parametros, salida_error_parametros);
        mostrar_ayuda();
        return 0;
    }
    else if ((strcmp(argv[1], "-V") == 0) || (strcmp(argv[1], "--version") == 0)){
        if(argc != 2) mostrar_error_y_salir(mensaje_error_cantidad_parametros, salida_error_parametros);
        mostrar_version();
        return 0;
    }

    else if ((strcmp(argv[1], "-o") == 0) || (strcmp(argv[1], "--output") == 0)){
        if (argc != 4) mostrar_error_y_salir(mensaje_error_cantidad_parametros, salida_error_parametros);
        nro_archivo_entrada = 3;
        nro_archivo_salida = 2;
        criterio_ordenamiento = 0;
    }

    else if (((strcmp(argv[2], "-o") == 0) || (strcmp(argv[2], "--output") == 0)) && ((strcmp(argv[1], "-n") == 0) || (strcmp(argv[1], "--numeric") == 0))) {
        if (argc != 5) mostrar_error_y_salir(mensaje_error_cantidad_parametros, salida_error_parametros);
        nro_archivo_entrada = 4;
        nro_archivo_salida = 3;
        criterio_ordenamiento = 1;
    }

    else mostrar_error_y_salir(mensaje_error_parametros, salida_error_parametros);

    archivo = fopen(argv[nro_archivo_entrada],"r");
    if (!archivo) mostrar_error_y_salir(mensaje_error_archivo_inexistente, salida_error_archivo_inexistente);
    if (strcmp(argv[nro_archivo_salida], "-")){
        output = fopen(argv[nro_archivo_salida], "w");
        if (!output) mostrar_error_y_salir(mensaje_error_archivo_inexistente, salida_error_archivo_inexistente);
    }

    longitud = obtener_longitud_maxima(archivo);
    rewind(archivo);
    cantidad_palabras = obtener_cantidad_palabras(archivo, longitud);
    rewind(archivo);
    lista_palabras = malloc(cantidad_palabras * sizeof(char*));
    obtener_palabras(archivo, lista_palabras, longitud);
    orgaqsort(lista_palabras, lista_palabras + cantidad_palabras -1);
    for (int i = 0; i < cantidad_palabras; i++){
        fprintf(output, "%s\n",lista_palabras[i]);
        free(lista_palabras[i]);
    }
    printf("%i\n", criterio_ordenamiento);
    fclose(archivo);
    fclose(output);
    free(lista_palabras);
    return 0;
}
