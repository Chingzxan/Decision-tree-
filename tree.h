#ifndef Tree_H
#define Tree_H

#include <stdio.h>
#include <stdlib.h>

typedef struct datas{
    int kol_prim; //количество примеров в датасте
    int kol_priz; //количество признаков
    float **data; // признаки
    int *prav; // правильный вариант
}Datas;

typedef struct Node //куда что будет относиться
{
    int uzel;
    int predict_class;
    int index_priznak;
    float znach;// условия для разбиения
    struct Node *left;
    struct Node *right;
}Node;

typedef struct Tree{
    Node *koren;
    int max_glub;//глубина
    int min_split;//количество признаков или данных для разбиения
    int kol_priz;// рандомное количество признаков 
}
