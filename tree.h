#ifndef Tree_H
#define Tree_H

#include <stdio.h>
#include <stdlib.h>

typedef struct datas{
    int kol_prim; //количество примеров в датасте
    int kol_priz; //количество признаков
    float **data; // признаки
    int *prav; // правильный вариант
}Datas
