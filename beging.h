#ifndef BEGING_H
#define BEGING_H

#include "tree.h"

typedef struct(
    Tree **trees;
    int kol_tree;
    int max_glub;
    int min_split;
    int kol_priz_sub;
    int kol_class;
    int kol_priz;
)BegModel;

BegModel* create_beg_model(int kol_tree, int max_glub,int min_split,int kol_priz_sub);
void freeModel(BegModel* mod);

void fit_beg(BegModel* mod,Datas* ds);
int pred_beg(BegModel *mod,float* sample);
#endif