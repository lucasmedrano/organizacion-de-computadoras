#ifndef ORGANIZACION_DE_COMPUTADORAS_CACHE_H
#define ORGANIZACION_DE_COMPUTADORAS_CACHE_H


struct cache;
typedef struct cache cache_t;

struct mem_principal;
typedef mem_principal mem_principal_t;


void init();
int find_set(int address);
int is_dirty(int way, int setnum);
int find_lru(int setnum);
void read_block(int blocknum);
void write_block(int way, int, setnum);
int read_byte(int address);
int write_byte(int address, char value);
int get_miss_rate();

char read_byte_memoria(mem_principal_t* memoria, int address);
int write_byte_memoria(mem_principal_t* memoria, int address, char byte);

#endif //ORGANIZACION_DE_COMPUTADORAS_CACHE_H