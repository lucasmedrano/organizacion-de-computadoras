#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bloque.h"


struct bloque{
    int tag;
    int index;
    int dirty;
    bool valido;
    int tiempo_ultimo_uso;
    char* datos;
};

bloque_t* crear_bloque(int index){
    bloque_t* bloque = malloc(sizeof(bloque_t));
    if (!bloque) return NULL;
    bloque->index = index;
    bloque->dirty = 0;
    bloque->valido = false;
    bloque->tiempo_ultimo_uso = 0;
    bloque->datos = malloc(64);
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

int get_index(bloque_t* bloque){
    return bloque->index;
}

int get_ultimo_uso(bloque_t* bloque){
    return bloque->tiempo_ultimo_uso;
}

char read(bloque_t* bloque, int offset, int uso){
    bloque->tiempo_ultimo_uso = uso;
    return (bloque->datos)[offset];
}

void write(bloque_t* bloque, int offset, char byte, int uso){
    bloque->tiempo_ultimo_uso = uso;
    (bloque->datos)[offset] = byte;
}

int get_tag(bloque_t* bloque){
    return bloque->tag;
}

