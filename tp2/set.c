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
        set->bloques[i] = crear_bloque();
    }

    return set;
}

void destruir_set(set_t* set){
    for (int i = 0; i < CANT_BLOQUES_SET; i++) destruir_bloque(set->bloques[i]);
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
            if (!es_valido(set->bloques[i])) return -1;
            return (int)(read(set->bloques[i], offset, contador_usos));
        }
    }
    return -1;
}

void write_byte_set(set_t* set, char byte, int tag, int offset, int contador_usos){
    for (int i = 0; i < CANT_BLOQUES_SET; i++){
        if(get_tag(set->bloques[i]) == tag){
            write(set->bloques[i], offset, byte, contador_usos);
        }
    }
}

int find_lru_set(set_t* set, int contador_usos){
    int tiempo_minimo = contador_usos, tiempo_actual;
    int way;
    for(int i = 1; i < CANT_BLOQUES_SET; i++){
        tiempo_actual = get_ultimo_uso(set->bloques[i]);
        if(tiempo_actual < tiempo_minimo){
            tiempo_minimo = tiempo_actual;
            way = i;
        }
    }

    return way;
}

int is_dirty_set(set_t *set, int via){
    return is_dirty_bloque(set->bloques[via]);
}

void set_tag_set(set_t* set, int via, int tag){
    set_tag(set->bloques[via], tag);
}

int get_tag_set(set_t* set, int via){
    return get_tag(set->bloques[via]);
}