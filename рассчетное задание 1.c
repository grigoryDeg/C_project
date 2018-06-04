#include <stdio.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Rus");
    int a[3], b[3], c[3];                                //задаем массивы для координат трех векторов
    printf("Введите координаты вектора а\n");
    for (int i = 0; i<3; i++) {
            scanf("%d", &a[i]);
  }                                                      //вводим координаты вектора а
    printf("Введите координаты вектора b\n");
    for (int i = 0; i<3; i++) {
            scanf("%d", &b[i]);
  }                                                 //вводим координаты вектора б
    printf("Введите координаты вектора c\n");
    for (int i = 0; i<3; i++) {
            scanf("%d", &c[i]);
  }                                                     //вводим координаты вектора с

    int m1, m2, m3, m4, m5, m6, m7, m8, m9;
    int matrix[3][3];

    m1=matrix[0][0]=a[0];
    m2=matrix[0][1]=a[1];
    m3=matrix[0][2]=a[2];

    m4=matrix[1][0]=b[0];
    m5=matrix[1][1]=b[1];
    m6=matrix[1][2]=b[2];

    m7=matrix[2][0]=c[0];
    m8=matrix[2][1]=c[1];
    m9=matrix[2][2]=c[2];

    int det = (m1*m5*m9)+(m4*m8*m3)+(m2*m6*m7)-(m7*m5*m3)-(m8*m6*m1)-(m2*m4*m9);

    printf("Получившаяся матрица: \n");
    printf("|%d %d %d|\n", matrix[0][0], matrix[0][1], matrix[0][2]);
    printf("|%d %d %d|=%d\n", matrix[1][0], matrix[1][1], matrix[1][2], det);
    printf("|%d %d %d|\n", matrix[2][0], matrix[2][1], matrix[2][2]);

    printf("Определитель матрицы:");
    printf("%d\n", det);
    if(det !=0) printf("Векторы не комплонарны.");
    else printf("Векторы компланарны.");


    return 0;
}
