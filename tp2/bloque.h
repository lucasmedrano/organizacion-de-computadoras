#ifndef ORGANIZACION_DE_COMPUTADORAS_BLOQUE_H
#define ORGANIZACION_DE_COMPUTADORAS_BLOQUE_H


struct bloque;
typedef struct bloque bloque_t;

bloque_t* crear_bloque(int index);
void destruir_bloque(bloque_t* bloque);
int is_dirty_bloque(bloque_t* bloque);
bool es_valido(bloque_t* bloque);
int get_index(bloque_t* bloque);
int get_ultimo_uso(bloque_t* bloque);
char read(bloque_t* bloque, int offset);
void write(bloque_t* bloque, int offset, char byte);
int get_tag(bloque_t* bloque);



#endif //ORGANIZACION_DE_COMPUTADORAS_BLOQUE_H
