#include "beging.h"

static Datas* bootstrap_sample(Datas* ds)
{
    Datas* sample=create_datas(ds->kol_prim,ds->kol_priz);
    for(int i=0;i<ds->kol_prim;i++)
    {
        int ind=rand()%ds->kol_prim;
        for(int g=0;g<ds->kol_priz;g++)
        {
            sample->data[i][g]=ds->data[ind][f];
        }
        sample->prav[i]=ds->prav[ind];
    }
    return sample;

}
BegModel* create_beg_model(int kol_tree,int max_glub,int min_split,int kol_priz_sub)
{
    BegModel* mod=malloc(sizeof(BegModel));

    mod->kol_tree=kol_tree;
    mod->max_glub=max_glub;
    mod->min_split=min_split;
    mod->kol_priz_sub=kol_priz_sub;
    mod->kol_class=0;
    mod->kol_priz=0;
    mod->trees= calloc(kol_tree,sizeof(Tree*));
    return model;
}
void freeModel (BegModel* mod)
{
    for(int i =0;i<mod->kol_tree;i++)
        if(mod->trees[i])free_tree(mod->trees[i]);
    free(mod->trees);
    free(mod);
}

void fit_beg(BegModel * mod,Datas* ds)
{
    srand(time(NULL));
    int max_prav=0;
    for(int =0;i<ds->prim;i++)
    {
        if(ds->prav[i]>max_prav)max_prav=ds->prav[i];
    }
    mod->kol_class=max_prav+1;
    mod->kol_priz=ds->kol_priz;

    for(int i=0;i<mod->kol_tree;i++)
    {
        Datas* sluch=bootstrap_sample(ds);
        if(!sluch)
        {
            fprintf(stderr,"Bootstrap ne razbil tree %d",i+1);
            continue;
        }
        Tree* dub=create_tree
    }
}