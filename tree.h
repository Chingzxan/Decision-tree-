#ifndef Tree_H
#define Tree_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
}Tree;

Tree* create_tree(int max_glub,int min_split,int kol_priz);

void del_tree(Tree* dub);
void free_Node(Node *node);


Datas* create_datas(int num_priz,int num_features);
void del_data(Datas* ds);

void random_priz(int *index,int n);

Datas* load_data(char *file);

void fit_tree(Tree* dub, Datas* ds);
int predict_tree(Tree* dub,float* prim);

#endif