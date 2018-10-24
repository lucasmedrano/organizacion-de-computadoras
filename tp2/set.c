#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "set.h"
#include "bloque.h"

#define cant_bloques_en_set 4

struct set{
	int indice;
    bloque_t** bloques;
};

set_t* crear_set(int indice_set){
    set_t* set = malloc(sizeof(set_t));
    if (!set) return NULL;

    set->bloques = malloc(cant_bloques_en_set * sizeof(bloque_t*));
    if (!(set->bloques)){
    	free(set);
    	return NULL;
    }
    set->indice = indice_set;

    for (int i = 0; i < cant_bloques_en_set; i++){
        set->bloques[i] = crear_bloque(set->indice);
    }

    return set;
}

int read_byte_set(set_t *set, int tag, int offset, int contador_usos){
    for (int i = 0; i < cant_bloques_en_set; i++){
        if(get_tag(set->bloques[i]) == tag){
            return (int)(read(set->bloques[i], offset, contador_usos));
        }
    }
    //Ver que hacer si no está esa address en cache. Habria que buscarla, pero no hicimos esa funcion todavía
}

void write_byte_set(set_t* set, char byte, int tag, int offset, int contador_usos){
    for (int i = 0; i < cant_bloques_en_set; i++){
        if(get_tag(set->bloques[i]) == tag){
            return write(set->bloques[i], offset, byte, contador_usos));
        }
    }
}

int find_lru_set(set_t* set){
    bloque_t *bloque_mas_viejo;
    int tiempo_minimo = 0;
    for(int i = 1; i < cant_bloques_en_set; i++){
        if(get_ultimo_uso(set->bloques[i]) < tiempo_minimo){
            bloque_mas_viejo = set->bloques[i];
        }
    }

    int tag = get_tag(bloque_mas_viejo);
    
    // | = OR
    // 0x0 es el offset de la direccion inicial del bloque. Creo que es asi.
    return (tag | set->indice | 0x0);

}

int is_dirty_set(set_t *set, int via){
    return is_dirty_bloque(set->bloques[via]);
}