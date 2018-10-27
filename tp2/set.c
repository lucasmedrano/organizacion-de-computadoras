#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "set.h"
#include "bloque.h"

#define CANT_BLOQUES_SET 4

struct set{
	int indice;
    bloque_t** bloques;
};

set_t* crear_set(int indice_set){
    set_t* set = malloc(sizeof(set_t));
    if (!set) return NULL;

    set->bloques = malloc(CANT_BLOQUES_SET * sizeof(bloque_t*));
    if (!(set->bloques)){
    	free(set);
    	return NULL;
    }
    set->indice = indice_set;

    for (int i = 0; i < CANT_BLOQUES_SET; i++){
        set->bloques[i] = crear_bloque(set->indice);
    }

    return set;
}

void destruir_set(set_t* set){
    free(set->bloques);
    free(set);
}

bool esta_en_set(set_t* set, int tag){
    for (int i = 0; i < CANT_BLOQUES_SET; i++){
        if(get_tag(set->bloques[i]) == tag){
            return true;
        }
    }
    return false;
}

int read_byte_set(set_t *set, int tag, int offset, int contador_usos){
    for (int i = 0; i < CANT_BLOQUES_SET; i++){
        if(get_tag(set->bloques[i]) == tag){
            if (!es_valido(set->bloques[i])) return //no se que devolver aca
            return (int)(read(set->bloques[i], offset, contador_usos));
        }
    }
}

void write_byte_set(set_t* set, char byte, int tag, int offset, int contador_usos){
    for (int i = 0; i < CANT_BLOQUES_SET; i++){
        if(get_tag(set->bloques[i]) == tag){
            return write(set->bloques[i], offset, byte, contador_usos));
        }
    }
}

int find_lru_set(set_t* set){
    int tiempo_minimo = 0;
    int way;
    for(int i = 1; i < CANT_BLOQUES_SET; i++){
        if(get_ultimo_uso(set->bloques[i]) < tiempo_minimo){
            way = i;
        }
    }

    return way;
}

int is_dirty_set(set_t *set, int via){
    return is_dirty_bloque(set->bloques[via]);
}

int get_tag_set(set_t* set, int via){
    return get_tag(set->bloques[via]);
}