#ifndef ORGANIZACION_DE_COMPUTADORAS_SET_H
#define ORGANIZACION_DE_COMPUTADORAS_SET_H

struct set;
typedef struct set set_t;

set_t* crear_set(int indice_set);
int is_dirty_set(set_t *set, int via);

#endif //ORGANIZACION_DE_COMPUTADORAS_SET_H
