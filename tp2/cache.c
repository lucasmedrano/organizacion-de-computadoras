#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "cache.h"
#include "set.h"
#include "bloque.h"

#define CANT_SETS_EN_CACHE 16
#define TAM_MEM_PPAL 65536
#define TAM_BLOQUE_CACHE 64

#define MSJ_ERROR_PARAMETROS "La cantidad de parametros no es la correcta"
#define MSJ_ARCHIVO_INEXISTENTE "No se encontro el archivo"
#define SALIDA_PARAMETROS 1
#define SALIDA_ARCHIVO 2
#define MSJ_ERROR_ADDRESS "La direccion %d no es valida\n"
#define MSJ_ERROR_VALUE "El valor %d no es valido\n"
#define MSJ_WRITE_OK "El valor %d se escribio correctamente\n"
#define MSJ_ERROR_WRITE "El valor no pudo escribirse correctamente\n"

struct cache{
    set_t** sets;
    float misses;
    float accesos_a_mem;
    int contador_usos;
};

struct mem_principal{
	char* datos;
};

cache_t* cache;
mem_principal_t* mem_principal;

void init(){
	mem_principal = malloc(sizeof(mem_principal_t));
	mem_principal->datos = calloc(TAM_MEM_PPAL, 1);

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
	return (find_lru_set((cache->sets[setnum]), cache->contador_usos));
}

int find_set(int address){
    unsigned int index = address << 22;
	return index >> 28;
}

int find_offset(int address){
    unsigned int offset = address & 0x000000ff;
    offset <<= 26;
    return offset >> 26;
}

int find_tag(int address){
    unsigned int tag = address & 0x0000ffff;;
    return tag >> 10;
}

int is_dirty(int way, int setnum){
	return (is_dirty_set(cache -> sets[setnum], way));
}

void read_block(int blocknum){
    int index = blocknum % CANT_SETS_EN_CACHE;
	int way = find_lru(index);
    int address = blocknum * TAM_BLOQUE_CACHE;
    int tag = find_tag(address);
    if (is_dirty(way, index)){
        write_block(way, index);
	}
    set_tag_set(cache->sets[index], way, tag);
    cache->contador_usos++;
	unsigned char dato;
	for (int i = 0; i < TAM_BLOQUE_CACHE; i++){
	    dato = read_byte_memoria(mem_principal, address + i);
		write_byte_set(cache->sets[index], dato, way, i, cache->contador_usos);
	}
}

void write_block(int way, int setnum){
	int tag = get_tag_set(cache->sets[setnum], way);
	char dato;
	int address = ((tag << 10)|(setnum << 6));
	for (int i = 0; i < TAM_BLOQUE_CACHE; i++){
	    dato = read_byte_set(cache->sets[setnum], way, i, cache->contador_usos);
		write_byte_memoria(mem_principal, address + i, dato);
	}
}

int read_byte(int address){
	int tag = find_tag(address);
	int index = find_set(address);
	int offset = find_offset(address);
	int way = find_way(cache->sets[index], tag);
    cache->contador_usos++;
	cache->accesos_a_mem++;
	if (way == -1){
        cache->misses++;
		read_block((address - offset)/ TAM_BLOQUE_CACHE);
        way = find_way(cache->sets[index], tag);
	}
    return(read_byte_set(cache ->sets[index], way, offset, cache->contador_usos));
}

int write_byte(int address, char value){
	int tag = find_tag(address);
	int index = find_set(address);
	int offset = find_offset(address);
	int way = find_way(cache->sets[index], tag);
    cache->contador_usos++;
	cache->accesos_a_mem++;
	if (way == -1){
        cache->misses++;
        read_block((address - offset)/ TAM_BLOQUE_CACHE);
        way = find_way(cache->sets[index], tag);
	}
	write_byte_set(cache->sets[index], value, way, offset, cache->contador_usos);
	return 0;
}

int get_miss_rate(){
    float mr = ((cache->misses)/(cache->accesos_a_mem))*100;
	return mr;
}

unsigned char read_byte_memoria(mem_principal_t* memoria, int address){
	return memoria->datos[address];
}

int write_byte_memoria(mem_principal_t* memoria, int address, char byte){
	memoria->datos[address] = byte;
	return 0;
}

void destruir_cache(){
	for (int i = 0; i < CANT_SETS_EN_CACHE; i++) destruir_set(cache->sets[i]);
	free(mem_principal->datos);
	free(cache->sets);
	free(mem_principal);
	free(cache);
}

void mostrar_error_y_salir(char *mensaje_error, int numero_salida){
	fprintf(stderr, "%s\n", mensaje_error);
	exit(numero_salida);
}

int main(int argc, char* argv[]){
	if (argc != 2) mostrar_error_y_salir(MSJ_ERROR_PARAMETROS, SALIDA_PARAMETROS);
	FILE* archivo = fopen(argv[1], "r");
	if (!archivo) mostrar_error_y_salir(MSJ_ARCHIVO_INEXISTENTE, SALIDA_ARCHIVO);

	char linea[100];
	char* comando;
	char comando1[3];
	const char* separador = " ";
    int address;

	init();
	while (fgets(linea, 100, archivo)){
	    linea[strlen(linea) - 1] = '\0';
		comando = strtok(linea, separador);
		strcpy(comando1, comando);
		if (strcmp(comando1, "MR") == 0) printf("Miss rate: %d%\n", get_miss_rate());
		if (strcmp(comando1, "R") == 0 || strcmp(comando1, "W") == 0){
            comando = strtok(NULL, separador);
            address = atoi(comando);
            if (address > TAM_MEM_PPAL || address < 0){
				printf(MSJ_ERROR_ADDRESS, address);
				continue;
			}
			if (strcmp(comando1, "W") == 0){
			    comando = strtok(NULL, separador);
			    int value = atoi(comando);
				if (value > 255 || value < 0){
					printf(MSJ_ERROR_VALUE, value);
					continue;
				}
				if (!(write_byte(address, (unsigned char) value))) printf(MSJ_WRITE_OK, value);
				else printf(MSJ_ERROR_WRITE);
				continue;
			}
			printf("Read %d\n", read_byte(address));
		}
	}
	fclose(archivo);
	destruir_cache();
	return 0;
}