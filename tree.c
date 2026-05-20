#include "tree.h"

static float gini(int *prav,int num_prav)
{
    if (num_prav ==0)return 0.0;
    int max_class=0;
    int g=1.0;//сам gini;
    for(int i=0;i<num_prav;i++)
    {
        if(prav[i]>max_class)max_class=prav[i];
    }
    int *count =calloc(max_class+1,sizeof(int));
    for(int i=0;i<num_prav;i++)count[prav[i]]++;//сколько каждого значения
    
    for(int i=0;i<max_class;i++)
    {
        float a = (float)count[i]/num_prav;//количество одного признака делим на всех 
        g -= a*a; //возводим в квадрат
    }
    free(count);
    return g;
}

Tree* create_tree(int max_glub,int min_split,int kol_priz)
{
    Tree* dub=(Tree*)malloc(sizeof(Tree*));

    dub->koren=NULL;
    dub->max_gulb=max_glub;
    dub->min_split=min_split;
    dub->kol_priz=kol_priz;

    return dub;
}

void free_Node(Node* node)
{
    if(node->uzel!=0)
    {
        free(node->left);
        free(node->right);
    }
    free(node);
}

void del_tree(Tree* dub)
{
    free_Node(dub->koren);
    free(dub);
}

static int popul_class(int * prav,int num_prav)// какой класс больше всего встречается
{
    if(num_prav == 0)return 0;
    int max_prav=0;
    for(int i=0;i<num_prav;i++)
    {
        if(prav[i]>max_prav)max_prav=prav[i];
    }
    int *count=calloc(max_prav+1,sizeoff(int));
    for(int i=0;i<num_prav;i++)count[prav[i]]++;
    int popul=0;
    for(int i = 0;i<=max_prav;i++)
    {
        if(count[i]>popul)popul=i;
    }
    free(count);
    return popul;
}

Datas* create_datas(int num_prim,int num_features)
{
    Datas* ds =malloc(sizeof(Dataset));
    ds->num_prim=num_prim;
    ds->num_features=num_features;
    ds->data=malloc(num_prim*sizeof(float*));
    for(int i=0;i<num_prim;i++)
    {
        ds->data[i]=malloc(num_features*sizeof(float));
    }
    ds->prav=calloc(num_prim,sizeof(int));

    return ds;
}
void free_datas(Datas* ds)
{
    for(int i = 0,i<ds->num_prim;i++)
    {
        free(ds->data[i]);
    }
    free(ds->data);
    free(ds->prav);
}