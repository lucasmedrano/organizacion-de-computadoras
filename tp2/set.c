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

int ready_byte_set(set_t *set, int tag, int offset){
    for (int i = 0; i < cant_bloques_en_set; i++){
        if(obtener_tag(set->bloques[i]) == tag){
            return int(read(set->bloques[i]), offset);
        }
    }
    //Ver que hacer si no está esa address en cache.
}

int is_dirty_set(set_t *set, int via){
    return is_dirty_bloque(set->bloques[via]);
}