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