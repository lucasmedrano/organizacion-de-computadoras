#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bloque.h"

#define TAMAÑO_BLOQUE 64

struct bloque{
    int tag;
    int dirty;
    bool valido;
    int tiempo_ultimo_uso;
    char* datos;
};

bloque_t* crear_bloque(int tag){
    bloque_t* bloque = malloc(sizeof(bloque_t));
    if (!bloque) return NULL;
    bloque->tag = tag;
    bloque->dirty = 0;
    bloque->valido = false;
    bloque->tiempo_ultimo_uso = 0;
    bloque->datos = malloc(TAMAÑO_BLOQUE);
    if (!(bloque->datos)) return NULL;
    return bloque;
}

void destruir_bloque(bloque_t* bloque){
    free(bloque->datos);
    free(bloque);
}

int is_dirty_bloque(bloque_t* bloque){
    return bloque->dirty;
}

bool es_valido(bloque_t* bloque){
    return bloque->valido;
}

int get_ultimo_uso(bloque_t* bloque){
    return bloque->tiempo_ultimo_uso;
}

char read(bloque_t* bloque, int offset, int uso){
    bloque->tiempo_ultimo_uso = uso;
    return (bloque->datos)[offset];
}

void write(bloque_t* bloque, int offset, char byte, int uso){
    bloque->valido = true;
    bloque->tiempo_ultimo_uso = uso;
    (bloque->datos)[offset] = byte;
    bloque->dirty = 1;
}

int get_tag(bloque_t* bloque){
    return bloque->tag;
}

