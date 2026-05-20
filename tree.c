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
    free(ds);
}


void random_priznak(int *index,int n)//рандомное количество признаков 
{
    for(int i=n-1;i>0;i--)
    {
        int j=rand()%(i+1);
        int temp=index[i];
        index[i]=index[j];
        index[j]=temp;
    }
}

Datas* load_data(char* file)
{
    FILE *f= fopen(file,"r");
    
    int stolb=0,strok=0;
    char line[1000]
    while(fgets(line,sizeof(line),f))
    {
        if(stolb==0)
        {
            char *token=strtok(line,',');
            while(token)
            {
                strok++;
                token=strtok(NULL,',');
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
        char *token=strtok(line,',');
        while(token && priz_ind<strok)
        {
            ds->data[prim_ind][priz_ind++]=atof(token);
            token=strtok(NULL,',');

        }
        ds->data[prim_ind++][priz_ind]=(token) ? atoi(token):0;
    }
    fclose(f);
    return ds;
}


static void best_split(Datas *ds,int *index,int kol_index, 
    int* feature_sub,int kol_sub,int* best_feature,float* best_znach,float* best_gain){

    *best_gain = -1.0;
    int*curr_prav=malloc(kol_index * sizeof(int));

    for(int i =0;i<kol_index;i++)curr_prav[i]=ds->prav[index[i]];

    float parent_gini=gini(curr_prav,kol_index);
    free(curr_prav);
    
    for(int i = 0;i<kol_sub;i++)
    {
        int feat=feature_sub[i];
        float *values=malloc(kol_index*sizeof(ind));
        for(int g =0;g<kol_index;g++)values[g]=ds->data[index[i]][feat];

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
            int left=0,int right=0;
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
            float gini=parent_gini-((float)left/kol_index)*gini_left-((float)right/kol_index)*gini_right;
        
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