#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "cache.h"
#include "set.h"
#include "bloque.h"

#define cant_sets_en_cache 16

struct cache{
    set_t** sets;
    int misses;
    int accesos_a_mem;
    int contador_usos;
};

cache_t* cache;

void init(){
	cache = malloc(sizeof(cache_t));
	cache->misses = 0;
	cache->accesos_a_mem = 0;
	cache->contador_usos = 0;
	cache->sets = malloc(cant_sets_en_cache * sizeof(set_t *));
	for (int i = 0; i < cant_sets_en_cache; i++){
		cache -> sets[i] = crear_set(i);
	}
}

int find_lru(int setnum){
	return (find_lru_set((cache->sets[setnum])));
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
	cache->contador_usos++;
	cache->accesos_a_mem++;

	return(read_byte_set(cache ->sets[index], tag, offset, cache->contador_usos));
}

int write_byte(int address, char value){
	int tag = address & 0xff00;
	int index = address & 0x00f0;
	int offset = address & 0x000f;
	cache->contador_usos++;
	cache->accesos_a_mem++;

	write_byte_set(cache->sets[index], value, tag, offset, cache->contador_usos);
}
int get_miss_rate(){
	return (cache->misses/cache->accesos_a_mem)*100;
}

int main(){
	return 0;
}