#include "beging.h"

int main(int argc,char*argv[])
{
    if(argc>=2 && argc<=5)
    {
        printf("Васаб.Введи пожалуйста только:имя датасета,количество деревьев,
            максимальную глубину,минимальное разбиение и количество признаков. Удачи🐉\n");

        return 1;
    }
    
    char *datafile =argv[1];
    int kol_tree =atoi(argv[2]);
    int max_glub=atoi(argv[3]);
    int min_split=atoi(argv[4]);
    int kol_priz_sub=atoi(argv[5]);

    Datas *ds =load_datas(datafile);
    
    printf("Датасет загружен на 5+ : %d примеров,%d признаков\n",ds->kol_prim,ds->kol_priz);
 
    BegModel* mod=create_beg_model(kol_tree,max_glub,min_split,kol_priz_sub);
    if(!mod)
    {
        fprintf(stderr,"Модель не создалась :( )\n")
        free_datas(ds);
        return 1;
    } 

    fit_beg(mod,ds);
    printf("Оуу да ,модель загрузилась успешно\n");

    printf("\n=== Предсказание в прямом эфире ===\n");
    printf("Введите 3 цифры(слева справо центр) через пробел,или напишите 'q',чтобы выйти ");
    
    


}