#include "tree.h"

static float gini(int *prav,int num_prav)//Критерий gini
{
    if (num_prav ==0)return 0.0;
    int max_class=0;
    float g=1.0;//сам gini;
    for(int i=0;i<num_prav;i++)
    {
        if(prav[i]>max_class)max_class=prav[i];
    }
    int *count =calloc(max_class+1,sizeof(int));
    for(int i=0;i<num_prav;i++)count[prav[i]]++;//сколько каждого значения
    
    for(int i=0;i<=max_class;i++)
    {
        float a = (float)count[i]/num_prav;//количество одного признака делим на всех 
        g -= a*a; //возводим в квадрат
    }
    free(count);
    return g;
}

Tree* create_tree(int max_glub,int min_split,int kol_priz)// создание дерева
{
    Tree* dub=(Tree*)malloc(sizeof(Tree));

    dub->koren=NULL;
    dub->max_glub=max_glub;
    dub->min_split=min_split;
    dub->kol_priz=kol_priz;

    return dub;
}

void free_Node(Node* node)//удаление узла 
{
    if(!node)return;
    if(node->uzel==0)
    {
        free_Node(node->left);
        free_Node(node->right);
    }
    free(node);
}

void del_tree(Tree* dub)//удаление Дерева
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
    int *count=calloc(max_prav+1,sizeof(int));
    for(int i=0;i<num_prav;i++)count[prav[i]]++;
    int popul=0;
    for(int i = 0;i<=max_prav;i++)
    {
        if(count[i]>popul)popul=i;
    }
    free(count);
    return popul;
}

Datas* create_datas(int kol_prim,int kol_priz)//Создание датасета с данными для обучения
{
    Datas* ds =malloc(sizeof(Datas));
    ds->kol_prim=kol_prim;
    ds->kol_priz=kol_priz;
    ds->data=malloc(kol_prim*sizeof(float*));
    for(int i=0;i<kol_prim;i++)
    {
        ds->data[i]=malloc(kol_priz*sizeof(float));
    }
    ds->prav=calloc(kol_prim,sizeof(int));

    return ds;
}
void del_data(Datas* ds)//Удаление датасета 
{
    for(int i = 0;i<ds->kol_prim;i++)
    {
        free(ds->data[i]);
    }
    free(ds->data);
    free(ds->prav);
    free(ds);
}


void random_priz(int *index,int n)//рандомное распределение признаков 
{
    for(int i=n-1;i>0;i--)
    {
        int j=rand()%(i+1);
        int temp=index[i];
        index[i]=index[j];
        index[j]=temp;
    }
}

Datas* load_data(char* file)//загрузка датасета 
{
    FILE *f= fopen(file,"r");
    
    int stolb=0,strok=0;
    char line[1000];
    while(fgets(line,sizeof(line),f))
    {
        if(stolb==0)
        {
            char *token=strtok(line,",");
            while(token)
            {
                strok++;
                token=strtok(NULL,",");
            }
            strok--;//значение,а не признак
        }
        stolb++;
    }
    
    rewind(f);

    Datas* ds = create_datas(stolb,strok);
    int prim_ind=0;
    while(fgets(line,sizeof(line),f)&& prim_ind<stolb)
    {
        int priz_ind=0;
        char *token=strtok(line,",");
        while(token && priz_ind<strok)
        {
            ds->data[prim_ind][priz_ind++]=atof(token);
            token=strtok(NULL,",");

        }
        ds->prav[prim_ind++]=(token) ? atoi(token):0;
    }
    fclose(f);
    return ds;
}


static void best_split(Datas *ds,int *index,int kol_index, //Лучшее разбиение дерева,для наибольшего gini
    int* feature_sub,int kol_sub,int* best_feature,float* best_znach,float* best_gain){

    *best_gain = -1.0;
    int*curr_prav=malloc(kol_index * sizeof(int));

    for(int i =0;i<kol_index;i++)curr_prav[i]=ds->prav[index[i]];

    float parent_gini=gini(curr_prav,kol_index);
    free(curr_prav);
    
    for(int i = 0;i<kol_sub;i++)
    {
        int feat=feature_sub[i];
        float *values=malloc(kol_index*sizeof(float));
        for(int g =0;g<kol_index;g++)values[g]=ds->data[index[g]][feat];

        int *order=malloc(kol_index*sizeof(int));
        for(int g=0;g<kol_index;g++)order[g]=g;
        for(int g=0;g<kol_index-1;g++)
        {
            for(int j=g+1;j<kol_index;j++)
            {
                if(values[order[g]]>values[order[j]])
                {
                    int t=order[g];
                    order[g]=order[j];
                    order[j]=t;
                }
            }
        }
        for(int g=0;g<kol_index-1;g++)
        {
            float znach =(values[order[g]]+values[order[g+1]])/2.0;
            int left=0,right=0;
            for(int j =0;j<kol_index;j++)
            {
                if(values[j]<=znach)left++;
                else right++;
            }
            if(left==0 ||right==0)continue;
            int *left_prav=malloc(left*sizeof(int));
            int *right_prav=malloc(right*sizeof(int));

            int l=0,r=0;
            for(int j=0;j<kol_index;j++)
            {
                if(values[j]<=znach)
                    left_prav[l++]=ds->prav[index[j]];
                else right_prav[r++]=ds->prav[index[j]];
            }
        
            float gini_left=gini(left_prav,left);
            float gini_right=gini(right_prav,right);
            float gain=parent_gini-((float)left/kol_index)*gini_left-((float)right/kol_index)*gini_right;
        
            if(gain>*best_gain)
            {
                *best_gain=gain;
                *best_feature=feat;
                *best_znach=znach;
            }
            free(left_prav);
            free(right_prav);
        }
    free(values);
    free(order);
    }
}

static Node* build_tree(Datas* ds,int* index,int kol_ind,int depth,int max_depth,int min_split,int kol_priz_sub,int max_priz)//Построение дерева
{
    Node *dub = malloc(sizeof(Node));

    int all_same=1;
    for(int i = 1; i<kol_ind;i++)
    {
        if(ds->prav[index[i]]!= ds->prav[index[0]])
        {
            all_same=0;
            break;
        }
    }
    if(all_same|| depth>=max_depth||kol_ind<min_split)
    {
        dub->uzel=1;
        int* prav_sub=malloc(kol_ind*sizeof(int));
        for(int i=0;i<kol_ind;i++)
            prav_sub[i]=ds->prav[index[i]];
            
        dub->predict_class =popul_class(prav_sub,kol_ind);
        free(prav_sub);

        dub->left=NULL;
        dub->right=NULL;
        return dub;


    }
    int* priz_pool=malloc(max_priz * sizeof(int));

    for(int i=0;i<max_priz;i++)priz_pool[i]=i;
    random_priz(priz_pool,max_priz);
    //kol_priz_sub- сколько признаков берём
    int* priz_subset =malloc(kol_priz_sub*sizeof(int));
    for(int i=0;i<kol_priz_sub;i++)
    {
        priz_subset[i]=priz_pool[i];
    }
    free(priz_pool);

    int best_priz=-1;

    float best_razb=0.0;
    float best_gain=-1.0;

    best_split(ds,index,kol_ind,priz_subset,kol_priz_sub,&best_priz,&best_razb,&best_gain);

    free(priz_subset);

    if(best_priz ==-1 || best_gain <= 1e-6)
    {
        dub->uzel =1;
        int *prav_sub = malloc(kol_ind*sizeof(int));
        for(int i=0; i<kol_ind;i++)prav_sub[i]=ds->prav[index[i]];
        dub->predict_class= popul_class(prav_sub,kol_ind);
        free(prav_sub);
        dub->left = dub->right = NULL;
        return dub;
    }
    dub->uzel=0;
    dub->index_priznak= best_priz;
    dub->znach=best_razb;

    int* left_ind=malloc(kol_ind*sizeof(int));
    int* right_ind=malloc(kol_ind*sizeof(int));

    int l_count =0, r_count = 0;
    for(int i=0;i<kol_ind;i++)
    {
        if(ds->data[index[i]][best_priz]<=best_razb)
         left_ind[l_count++]=index[i];
        else
         right_ind[r_count++]=index[i];

    }
    dub->left = build_tree(ds,left_ind,l_count,depth+1,max_depth,min_split,kol_priz_sub,max_priz);
    dub->right = build_tree(ds,right_ind,r_count,depth+1,max_depth,min_split,kol_priz_sub,max_priz);
    free(left_ind);
    free(right_ind);

    if(!dub->left||!dub->right)
    {
        free_Node(dub->left);
        free_Node(dub->right);
        dub->uzel=1;

        int* prav_sub=malloc(kol_ind*sizeof(int));
        for(int i=0;i<kol_ind;i++)
        {
            prav_sub[i]=ds->prav[index[i]];
        }
        dub->predict_class=popul_class(prav_sub,kol_ind);

        free(prav_sub);
        dub->left=dub->right=NULL;
    }
    return dub;
}


void fit_tree(Tree* dub,Datas* ds)//обучение
{
    int* index=malloc(ds->kol_prim*sizeof(int));
    for(int i =0;i<ds->kol_prim;i++)index[i]=i;

    dub->koren=build_tree(ds,index,ds->kol_prim,0,dub->max_glub,dub->min_split,dub->kol_priz,ds->kol_priz);
    free(index);

}
static int predict_node(Node* node ,float *prim)//предсказание одного значения
{
    if(node->uzel)return node->predict_class;
    if(prim[node->index_priznak]<=node->znach)return predict_node(node->left,prim);
    else return predict_node(node->right,prim);
}
int predict_tree(Tree* dub,float* sample)//предсказание дерева
{
    return predict_node(dub->koren,sample);
}

int max_pred(int* schet_pred_tree,int kol_class)//какое предсказание встречается больше всего
{
    int KISH =0;
    for(int XOOOY=1;XOOOY<kol_class;XOOOY++)
    {
        if(schet_pred_tree[XOOOY]>schet_pred_tree[KISH])KISH=XOOOY;
    }
    return KISH;
}