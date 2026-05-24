#include "beging.h"

static Datas* bootstrap_sample(Datas* ds)//возвращает рандомные примеры для обучения
{
    Datas* sample=create_datas(ds->kol_prim,ds->kol_priz);
    for(int i=0;i<ds->kol_prim;i++)
    {
        int ind=rand()%ds->kol_prim;
        for(int g=0;g<ds->kol_priz;g++)
        {
            sample->data[i][g]=ds->data[ind][g];
        }
        sample->prav[i]=ds->prav[ind];
    }
    return sample;

}
BegModel* create_beg_model(int kol_tree,int max_glub,int min_split,int kol_priz_sub)//создание бег модели
{
    BegModel* mod=malloc(sizeof(BegModel));

    mod->kol_tree=kol_tree;
    mod->max_glub=max_glub;
    mod->min_split=min_split;
    mod->kol_priz_sub=kol_priz_sub;
    mod->kol_class=0;
    mod->kol_priz=0;
    mod->trees= calloc(kol_tree,sizeof(Tree*));
    return mod;
}
void freeModel (BegModel* mod)//удаление модели
{
    for(int i =0;i<mod->kol_tree;i++)
        if(mod->trees[i])del_tree(mod->trees[i]);
    free(mod->trees);
    free(mod);
}

void fit_beg(BegModel * mod,Datas* ds)//обучает каждое дерево с bootstrap и сохраняет 
{
    srand(time(NULL));
    int max_prav=0;
    for(int i =0;i<ds->kol_prim;i++)
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
            fprintf(stderr,"Bootstrap не смог разбить дерево %d\n",i+1);
            continue;
        }
        Tree* dub=create_tree(mod->max_glub,mod->min_split,mod ->kol_priz_sub);
        fit_tree(dub,sluch);
        mod->trees[i]=dub;
        del_data(sluch);
        printf("Дерево %d/%d обучено🌲\n",i+1,mod->kol_tree);
    }
}

int pred_beg(BegModel *mod ,float *sample)//предсказание
{
    int* schet_pred_tree=calloc(mod->kol_class,sizeof(int));

    for(int i =0;i<mod->kol_tree;i++)
    {
        if(mod->trees[i])
        {
            int pred=predict_tree(mod->trees[i],sample);
            if(pred>=0 && pred< mod->kol_class)schet_pred_tree[pred]++;

        }
    }
    int res=max_pred(schet_pred_tree,mod->kol_class);
    return res;
}