#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "cache.h"
#include "set.h"
#include "bloque.h"

#define cant_sets_en_cache 16

struct cache{
    set_t** sets;
    int tasa_de_misses;
};

cache_t* cache;

void init(){
	cache = malloc(sizeof(cache_t));
	cache -> tasa_de_misses = 0;
	cache -> sets = malloc(cant_sets_en_cache * sizeof(set_t *));
	for (int i = 0; i < cant_sets_en_cache; i++){
		cache -> sets[i] = crear_set(i);
	}
}

int find_set(int address){
	return (address & 0x00f0);
}

int is_dirty(int way, int setnum){
	return (is_dirty_set(cache -> sets[setnum], way));
}

int read_byte(int address){
	int tag = address & 0xff00;
	int index = address & 0x00f0;
	int offset = address & 0x000f;

	ready_byte_set(cache ->sets[index], tag, offset);
}

int main(){
	return 0;
}