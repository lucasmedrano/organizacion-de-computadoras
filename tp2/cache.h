#ifndef ORGANIZACION_DE_COMPUTADORAS_CACHE_H
#define ORGANIZACION_DE_COMPUTADORAS_CACHE_H


struct cache;
typedef struct cache cache_t;


void init();
int find_set(int address);
int is_dirty(int way, int setnum);
#endif //ORGANIZACION_DE_COMPUTADORAS_CACHE_H