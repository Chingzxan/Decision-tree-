#include "beging.h"

int main(int argc,char*argv[])
{
    if(argc>=2 && argc<=5)
    {
        printf("Васаб.Введи пожалуйста только:имя датасета,количество деревьев,
            максимальную глубину,минимальное разбиение и количество признаков. Удачи🐉");

        return 1;
    }
    
    char *datafile =argv[1];
    int kol_tree =atoi(argv[2]);
    int max_glub=atoi(argv[3]);
    int min_split=atoi(argv[4]);
    int num_priz_sub=atoi(argv[5]);

    Datas *ds =load_datas(datafile);
    
    printf("Датасет загружен на 5+ : %d примеров,%d признаков",ds->kol_prim,ds->kol_priz);
    
}