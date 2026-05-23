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