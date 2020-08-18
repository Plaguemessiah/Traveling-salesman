#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    int n;
    cout << "Введите число городов";
    cout << "\n";
    cin >> n;
    cout << "\n";
    int town[n][2]; 
    town[0][0] = 0;
    town[0][1] = 0;
    for (int i = 1; i < n; i++)
    {
        town[i][0] = rand()%(n*10);
        town[i][1] = rand()%(n*10);
    } // Заполняем таблицу координат - Done
    
    cout << "Коодинаты городов:";
    cout << "\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cout << town[i][j] << " ";
        }
    cout << "\n";
    } // Выводим таблицу координат - Done

    double map[n][n];
    cout << "Расстояния:";
    cout << "\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                map[i][j] = 0;
            }
            else
            {
                map[i][j] = round(sqrt((town[i][0] - town[j][0])*(town[i][0] - town[j][0]) + (town[i][1] - town[j][1])*(town[i][1] - town[j][1])));
            }
        }
    } //Заполняем таблицу расстояний - Done

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
        cout << map[i][j] << "    ";
        }
        cout << "\n";
    } //Выводим таблицу расстояний - Done

    double super[n][n][4];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            super[i][j][1] = 0;
            super[i][j][3] = 1;
        }
    }
    
    int ant[n];
    int antbest[n];
    double l = 0;
    double lbest = map[n-1][0]; //Добавляем нужные массивы и переменные - Done

    for (int i = 0; i < n; i++)
    {
        ant[i] = n+1;
    } //Заполняем пчелу - Done

    antbest[0] = 0;
    for (int i = 1; i < n; i++)
    {
        antbest[i] = i;
        lbest = lbest + map[i-1][i];
    }
    cout << "Прямой порядок:";
    cout << "\n";
    cout << lbest;
    cout << "\n";
    double lexp = lbest;

    for (int i = 0; i < n; i++)
    {
        cout << (antbest[i] + 1) << "  ";
    }
    cout << "\n";//Прямой изначальный порядок эталонного пути - Done
    
   for (int c = 0; c < n; c++)
    {
        ant[0] = c;
        int nextbest = 0;
        for (int b = 0; b < n-1; b++)
        {
            double jumpbest = 100000;
            for (int a = 0; a < n; a++)
            {
                if (map[ant[b]][a] < jumpbest)
                {
                    int allow = 1;
                    for (int i = 0; i <= b; i++)
                    {
                        if (ant[i] == a)
                        {
                            allow = 0;
                        }
                    }
                    if (allow == 1)
                    {
                    nextbest = a;
                    jumpbest = map[ant[b]][a];
                    }
                }
            }//Нашли ближайший для b-ого - Done
            ant[b+1] = nextbest;
            l = l + map[ant[b]][nextbest];
        }
        l = l + map[nextbest][c];
        
        if (l < lbest)
        {
            lbest = l;
            for (int i = 0; i < n; i++)
            {
               antbest[i] = ant[i];
            }
        }
    }//Находим кратчайший из жадных - Done
    
    cout << "Кратчайший из жадных:";
    cout << "\n";
    cout << lbest;
    cout << "\n"; 
    for (int i = 0; i < n; i++)
    {
        cout << (antbest[i] + 1)<< "  ";
    }
    cout << "\n";
    cout << "\n";//Ну и выводим всё нужное - Done
    
    int next;
     for (int i = 1; i < n; i++)
    {
        ant[i] = n+1;
    }
    ant[0] = 0;
    lbest = round((lexp + lbest)/2);
    //lbest = lexp;
    
    for (int final = 0; final < n*n*5000; final++)
    {
        l = 0;
        ant[0] = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if(super[i][j][3] < 0)
                {
                    super[i][j][3] = 1;
                    super[i][j][1] = super[i][j][1]*0.99;
                }
                
                if(super[i][j][3] > 100)
                {
                    super[i][j][3] = super[i][j][3] - 50;
                }
            }
        }
        
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                super[i][j][2] = 1;
            }
        }
        
         for (int i = 0; i < n; i++)
        {
            super[i][0][0] = 0;
            super[i][0][2] = 0;
        }//Обнуляем первую строку - Done
        
        int z = 0;
        double F = 0;
        for (int j = 0; j < n; j++)
        {
            if (super[0][j][2] == 1)
            {
                z =  z + 1;
                F = F + super[0][j][1];
            }
        }
                
        for (int j = 0; j < n; j++)
        {
            if (super[0][j][2] == 1)
            {
                super[0][j][0] = (1 + 0.5*super[0][j][1])/(z + 0.5*F);
            }
              
            else
            {
                super[0][j][0] = 0;
            }
        }//Распределяем вероятности для первого хода - Done
        
        double prob[n];//Делаем первый ход - получаем число next - Done
        prob[0] = 1000*super[0][0][0];
        double pr = rand()%1000;
        
        for (int i = 1; i < n; i++)
        {
            prob[i] = prob[i-1] + 1000*super[0][i][0];
        }
        
        for (int i = 1; i < n; i++)
        {
            if (pr >= prob[i-1])
            {
                if (pr <= prob[i])
                {
                    if (super[0][i][2] == 1)
                    {
                        next = i;
                    }
                }
            }
        }
        
        l = l + map[0][next];
        ant[1] = next;
        super[0][next][3] = super[0][next][3] + 2*n;
        
        for (int i = 0; i < n; i++)
        {
            super[i][next][0] = 0;
            super[i][next][2] = 0;
        }
        
        for (int j = 0; j < n; j++)
        {
            super[0][j][0] = 0;
            super[0][j][2] = 0;
        }//Обнуляем новую строку и ПРЕДЫДУЩИЙ столбец - Done
        
        for (int a = 1; a < n-1; a++)
        {
            int z = 0;
            double F = 0;
            for (int j = 0; j < n; j++)
            {
                if (super[ant[a]][j][2] == 1)
                {
                    z =  z + 1;
                    F = F + super[ant[a]][j][1];
                }
            }
            
            for (int j = 0; j < n; j++)
            {
                if (super[ant[a]][j][2] == 1)
                {
                    super[ant[a]][j][0] = (1 + 0.5*super[ant[a]][j][1])/(z + 0.5*F);
                }
                    
                else
                {
                    super[ant[a]][j][0] = 0;
                }
            }//Распределяем вероятности - Done
            
            double prob[n];//Делаем ход - получаем новую точку next - Done
            prob[0] = 1000*super[ant[a]][0][0];
            double pr = rand()%1000;
            
            for (int i = 1; i < n; i++)
            {
                prob[i] = prob[i-1] + 1000*super[ant[a]][i][0];
            }
            
            for (int i = 1; i < n; i++)
            {
                if (pr >= prob[i-1])
                {
                    if (pr <= prob[i])
                    {
                        if (super[ant[a]][i][2] == 1)
                        {
                            next = i;
                        }
                    }
                }
            }
            
            l = l + map[ant[a]][next];
            ant[a+1] = next;
            super[ant[a]][next][3] = super[ant[a]][next][3] + 2*n;
            
            for (int i = 0; i < n; i++)
            {
                super[i][next][0] = 0;
                super[i][next][2] = 0;
            }
            
            for (int j = 0; j < n; j++)
            {
                super[ant[a]][j][0] = 0;
                super[ant[a]][j][2] = 0;
            }//Обнуляем новую строку и ПРЕДЫДУЩИЙ столбец - Done
        }//Полный прогон пчелы - Done
        l = l + map[next][0];
        super[next][0][3] = super[next][0][3] + n-1;
        
        double lamda = l/lbest;//Распределяем феромоны - Done
        double mu;
        int count;
        
        if (lamda > 1)
        {
            double base = (n/15.0)*(n/15.0)*(pow((1/lamda), 10) - 0.15);
            if (base < 0)
            {
                base = 0;
            }
            if (base > 0)
            {
                super[ant[n-1]][ant[0]][1] = super[ant[n-1]][ant[0]][1] + ceil(base*100)/100;
            super[ant[0]][ant[n-1]][1] = super[ant[0]][ant[n-1]][1] + ceil(base*100)/100;
            for (int i = 0; i < n-1; i++)
            {
                super[ant[i]][ant[i+1]][1] = super[ant[i]][ant[i+1]][1] + ceil(base*100)/100;
                super[ant[i+1]][ant[i]][1] = super[ant[i+1]][ant[i]][1] + ceil(base*100)/100;
            }
            }
        }//Если новая длина больше старой - Done
        
        if (lamda < 1) 
        {   for (int i = 0; i < n; i++)
            {
                antbest[i] = ant[i];
            }
            lbest = l;
            double base = (n/15.0)*(n/15.0)*pow((1/lamda), 2);
               
            super[ant[n-1]][ant[0]][1] = super[ant[n-1]][ant[0]][1] + ceil(base*100)/100;
            super[ant[0]][ant[n-1]][1] = super[ant[0]][ant[n-1]][1] + ceil(base*100)/100;
            for (int i = 0; i < n-1; i++)
            {
                super[ant[i]][ant[i+1]][1] = super[ant[i]][ant[i+1]][1] + ceil(base*100)/100;
                super[ant[i+1]][ant[i]][1] = super[ant[i+1]][ant[i]][1] + ceil(base*100)/100;
            }
        }//Если новая длина меньше старой - Done
        
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i != j)
                {
                    super[i][j][3] = super[i][j][3] - 1;
                }
            }
        }
        
        for (int i = 0; i < n; i++)
        {
            int z = 0;
            double F = 0;
            for (int j = 0; j < n; j++)
            {
                z =  z + 1;
                F = F + super[i][j][1];
            }
            
            for (int j = 0; j < n; j++)
            {
                super[i][j][0] = (1 + 0.5*super[i][j][1])/(z + 0.5*F);
            }
        }
        
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if(super[i][j][0] > 0.9)
                {
                    super[i][j][1] = super[i][j][1]*0.9;
                }
                
                if(super[i][j][0] < 1.0/(5*n))
                {
                    if (super[i][j][1] != 0)
                    {
                        super[i][j][1] = super[i][j][1]*1.1;
                    }
                    
                    else
                    {
                        super[i][j][1] = super[i][j][1] + 0.001;
                    }
                }
            }
        }
    }//Конец - Done
    
    cout << "Результат муравьиного алгоритма:";
    cout << "\n"; 
    cout << lbest;
    cout << "\n"; 
    for (int i = 0; i < n; i++)
    {
        cout << (antbest[i] + 1)<< "  ";
    }
    cout << "\n";
    return 0;//Совсем конец - Done
}
