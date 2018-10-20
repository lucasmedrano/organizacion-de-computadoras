#include "bloque.h"
#include <stdlib.h>

struct bloque{
    int index;
    bool dirty;
    bool valido;
    int tiempo_ultimo_uso;
    char* datos;
};

bloque_t* crear_bloque(int index){
    bloque_t* bloque = malloc(sizeof(bloque_t));
    if (!bloque) return NULL;
    bloque->index = index;
    bloque->dirty = false;
    bloque->valido = false;
    bloque->tiempo_ultimo_uso = 0;
    bloque->datos = malloc(64);
    if (!(bloque->datos)) return NULL;
    return bloque;
}

void* destruir_bloque(bloque_t* bloque){
    free(bloque->datos);
    free(bloque);
}

bool is_dirty(bloque_t* bloque){
    return bloque->dirty;
}

bool es_valido(bloque_t* bloque){
    return bloque->valido;
}

int get_index(bloque_t* bloque){
    return bloque->index;
}

int get_ultimo_uso(bloque_t* bloque){
    return bloque->tiempo_ultimo_uso;
}

char read(bloque_t* bloque, int offset){
    return bloque->datos[offset];
}

void write(bloque_t* bloque, int offset, char byte){
    bloque->datos[offset] = byte;
}

