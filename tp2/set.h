#ifndef ORGANIZACION_DE_COMPUTADORAS_SET_H
#define ORGANIZACION_DE_COMPUTADORAS_SET_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct set;
typedef struct set set_t;

set_t* crear_set(int indice_set);
int is_dirty_set(set_t *set, int via);
int read_byte_set(set_t *set, int way, int offset, int contador_usos);
void write_byte_set(set_t* set, char byte, int way, int offset, int contador_usos);
int find_lru_set(set_t* set, int contador_usos);
int esta_en_set(set_t* set, int tag);
void set_tag_set(set_t* set, int via, int tag);
int get_tag_set(set_t* set, int via);
void destruir_set(set_t* set);

#endif //ORGANIZACION_DE_COMPUTADORAS_SET_H
