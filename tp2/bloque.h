#ifndef ORGANIZACION_DE_COMPUTADORAS_BLOQUE_H
#define ORGANIZACION_DE_COMPUTADORAS_BLOQUE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct bloque;
typedef struct bloque bloque_t;

bloque_t* crear_bloque();
void destruir_bloque(bloque_t* bloque);
int is_dirty_bloque(bloque_t* bloque);
bool es_valido(bloque_t* bloque);
int get_ultimo_uso(bloque_t* bloque);
unsigned char read(bloque_t* bloque, int offset, int uso);
void write(bloque_t* bloque, int offset, char byte, int uso);
int get_tag(bloque_t* bloque);
void set_tag(bloque_t* bloque, int tag);



#endif //ORGANIZACION_DE_COMPUTADORAS_BLOQUE_H
