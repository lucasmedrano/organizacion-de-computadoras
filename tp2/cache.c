#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "cache.h"
#include "set.h"
#include "bloque.h"

#define CANT_SETS_EN_CACHE 16
#define TAM_MEM_PPAL 65536
#define TAM_BLOQUE_CACHE 64

struct cache{
    set_t** sets;
    int misses;
    int accesos_a_mem;
    int contador_usos;
};

struct mem_principal{
	char* datos;
};

cache_t* cache;
mem_principal_t* mem_principal;

void init(){
	mem_principal = malloc(sizeof(mem_principal_t));
	mem_principal->datos = malloc(TAM_MEM_PPAL);

	cache = malloc(sizeof(cache_t));
	cache->misses = 0;
	cache->accesos_a_mem = 0;
	cache->contador_usos = 0;
	cache->sets = malloc(CANT_SETS_EN_CACHE * sizeof(set_t *));
	for (int i = 0; i < CANT_SETS_EN_CACHE; i++){
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

void read_block(int blocknum){
	int index = blocknum % CANT_SETS_EN_CACHE;
	int way = find_lru(index);
	int tag = get_tag_set(cache->sets[index], way);
	if (is_dirty(way, index)){
		write_block(way, index);
	}
	for (int i = 0; i < TAM_BLOQUE_CACHE; i++){
		write_byte_set(cache->sets[index],read_byte_memoria(mem_principal, address + i), tag, i, cache->contador_usos);
	}
}

void write_block(int way, int setnum){
	for (int i = 0; i < TAM_BLOQUE_CACHE; i++){
		write_byte_memoria(mem_principal, setnum + get_tag_set(cache->sets[setnum], way) , read_byte_set(cache->sets[setnum], way, i, cache->contador_usos));
	}
}

int read_byte(int address){
	int tag = address & 0xff00;
	int index = address & 0x00f0;
	int offset = address & 0x000f;
	cache->contador_usos++;
	cache->accesos_a_mem++;
	if (!esta_en_set(cache->sets[index], tag)){
		cache->misses++;
		read_block((tag + index)/ TAM_BLOQUE_CACHE);
	}
	return(read_byte_set(cache ->sets[index], tag, offset, cache->contador_usos));
}

int write_byte(int address, char value){
	if (address > TAM_MEM_PPAL) return 1;
	int tag = address & 0xff00;
	int index = address & 0x00f0;
	int offset = address & 0x000f;
	cache->contador_usos++;
	cache->accesos_a_mem++;
	if (!esta_en_set(cache->sets[index], tag)){
		cache->misses++;
		read_block((tag + index)/ TAM_BLOQUE_CACHE);
	}
	write_byte_set(cache->sets[index], value, tag, offset, cache->contador_usos);
	return 0;
}

int get_miss_rate(){
	return (cache->misses/cache->accesos_a_mem)*100;
}

char read_byte_memoria(mem_principal_t* memoria, int address){
	if (address > TAM_MEM_PPAL) return 1;
	return memoria[address];
}

int write_byte_memoria(mem_principal_t* memoria, int address, char byte){
	if (address > TAM_MEM_PPAL) return 1;
	memoria[address] = byte;
	return 0;
}

int main(){



	return 0;
}