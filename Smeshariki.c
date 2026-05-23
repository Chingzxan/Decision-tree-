#include "beging.h"

int main(int argc,char*argv[])
{
    if(argc>=2 && argc<=5)
    {
        printf("Васаб.Введи пожалуйста только:имя датасета,количество деревьев,\n");
        printf("максимальную глубину,минимальное разбиение и количество признаков. Удачи🐉\n");

        return 1;
    }
    
    char *datafile =argv[1];
    int kol_tree =atoi(argv[2]);
    int max_glub=atoi(argv[3]);
    int min_split=atoi(argv[4]);
    int kol_priz_sub=atoi(argv[5]);

    Datas *ds =load_data(datafile);
    
    printf("Датасет загружен на 5+ : %d примеров,%d признаков\n",ds->kol_prim,ds->kol_priz);
 
    BegModel* mod=create_beg_model(kol_tree,max_glub,min_split,kol_priz_sub);
    if(!mod)
    {
        fprintf(stderr,"Модель не создалась :( )\n");
        del_data(ds);
        return 1;
    } 

    fit_beg(mod,ds);
    printf("Оуу да ,модель загрузилась успешно\n");

    printf("\n=== Предсказание команды ===\n");
    printf("Введите 3 числа(стороны слева  ,справо и центр) через пробел,или напишите 'q',чтобы выйти\n ");
    
    char input[15];

    while(1)
    {
        printf(">");
        if(!fgets(input,sizeof(input),stdin))
            break;
        input[strcspn(input,"\n")]=0;// убираем \n
        if(strcmp(input,"q")==0)break;

        float sample[3];

        int n=sscanf(input,"%f %f %f",&sample[0],&sample[1],&sample[2]);
        
        if(n!=3)
        {
            printf("Ну тебе сказали 3 числа!!!Давай ещё раз\n");
            continue;
        }
        int pred = pred_beg(mod,sample);
        
        if(pred==0)printf("Предсказанное действие:Остановитесь\n");
        else if(pred==1)printf("Предсказанное действие:Продолжайте движение вперёд\n");
        else if(pred==2) printf("Предсказанное действие:Поверните на право\n");
        else if (pred==3)printf("Предсказанное действие:Поверните на лево\n");
        else printf("Ошибка\n");
    }
    printf("\n=== Выход ===\n");
    
    freeModel(mod);
    del_data(ds);
    
    printf("\nДо скорой встречи\n");
    printf("До скорой встречи\n");
    printf("Моя программа к тебе на вечно\n");
    
    return 0;
}