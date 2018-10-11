#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mips/regdef.h>

#define salida_error_parametros 1
#define salida_error_archivo_inexistente 2
#define mensaje_error_cantidad_parametros "qsort: La cantidad de parametros no es la correcta.\nIntente 'qsort -h' para más información"
#define mensaje_error_parametros "qsort: La combinación de parametros no es válida.\nIntente 'qsort -h' para más información"
#define mensaje_error_archivo_inexistente "El archivo que quiere ordenar no existe"
#define MENSAJE_AYUDA "Usage:\n\tqsort -h\n\tqsort -V\n\tqsort [options] archivo\nOptions:\n\t-h, --help \tImprime ayuda.\n\t-V, --version \tVersión del programa.\n\t-o, --output \tArchivo de salida.\n\t-n, --numeric \tOrdenar los datos numéricamente en vez de alfabéticamente.\nExamples:\n\tqsort -n numeros.txt"
#define VERSION "v1.0"

extern void orgaqsortassembly(char** izq, char** der, int num);

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
    char c = ' ';
    while (c != EOF){
        c = fgetc(archivo);
        if (c == '\n') cantidad ++;
    }
    return cantidad;
}

void obtener_palabras(FILE* archivo, char **lista_palabras, int len, int cantidad_palabras){
    int indice = 0;
    char palabra[len + 1];

    int i;
    for (i = 0; i < cantidad_palabras; i++){
        int j;
        fgets(palabra, len + 1, archivo);
        for(j = 0; j < (strlen(palabra) + 1); j++){
            if (palabra[j] == '\n' || palabra[j] == EOF) palabra[j] = '\0';
        }
        lista_palabras[indice] = malloc(strlen(palabra) + 1);
        strcpy(lista_palabras[indice], palabra);
        indice ++;
    }
}

int comparar_como_numero(const char *numero1,const char *numero2){
    int n1 = atoi(numero1);
    int n2 = atoi(numero2);
    return(n1-n2);
}

//----------------------------------------------------------------------------------------------

void orgaqsortgeneral(char** izq, char** der, int (*fcmp)(const char *,const char *)){
    if (izq <= der) {
        char *aux;
        char **inicio = izq;
        char **fin = der;
        while (inicio < fin){
            while ((fcmp(*inicio, *izq) <= 0) && (inicio < der))inicio++;
            while ((fcmp(*fin, *izq) > 0) && (fin > izq)) fin--;
            if (inicio < fin){
                aux = *inicio;
                *inicio = *fin;
                *fin = aux;
            }
        }
        aux = *izq;
        *izq = *fin;
        *fin = aux;
        orgaqsortgeneral(izq, fin-1, fcmp);
        orgaqsortgeneral(fin+1, der, fcmp);
    }
}

void orgaqsort(char **izq, char **der, int num){
    //si num = 0 ordena alfabeticamente
    //Si num != 0 ordena como numeros
    if (num) orgaqsortgeneral(izq, der, comparar_como_numero);
    else orgaqsortgeneral(izq, der, strcmp);
}

int main(int argc, char *argv[]){

    int longitud, cantidad_palabras, nro_archivo_entrada, nro_archivo_salida, criterio_ordenamiento, i;
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
    // Verificación para ingreso de ordenamientos y archivos
    else if ((strcmp(argv[1], "-o") == 0) || (strcmp(argv[1], "--output") == 0)){
        if (argc != 4) mostrar_error_y_salir(mensaje_error_cantidad_parametros, salida_error_parametros);
        nro_archivo_entrada = 3;
        nro_archivo_salida = 2;
        criterio_ordenamiento = 0;
    }

    else if ((argc > 2) && ((strcmp(argv[2], "-o") == 0) || (strcmp(argv[2], "--output") == 0)) && ((strcmp(argv[1], "-n") == 0) || (strcmp(argv[1], "--numeric") == 0))) {
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
    obtener_palabras(archivo, lista_palabras, longitud, cantidad_palabras);
    orgaqsort(lista_palabras, lista_palabras + cantidad_palabras -1, criterio_ordenamiento);
    for (i = 0; i < cantidad_palabras; i++){
        fprintf(output, "%s\n",lista_palabras[i]);
        free(lista_palabras[i]);
    }
    fclose(archivo);
    fclose(output);
    free(lista_palabras);
    return 0;
}
