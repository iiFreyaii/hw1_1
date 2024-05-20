#include "algebra.h"
#include <stdio.h>
#include <math.h>

Matrix create_matrix(int row, int col)
{
    Matrix m;
    m.rows = row;
    m.cols = col;
    return m;
}

Matrix add_matrix(Matrix a, Matrix b)
{
    // ToDo
    int i,j;
    Matrix c;
    if(a.rows==b.rows&&a.cols==b.cols){
        c.rows=a.rows;
        c.cols=a.cols;
        for(i=0;i<a.rows;i++){
            for(j=0;j<a.cols;j++){
                c.data[i][j]=a.data[i][j]+b.data[i][j];
            }
        }
        return c;
    }
    else{
        printf("Error: Matrix a and b must have the same rows and cols.\n");
    }
}

Matrix sub_matrix(Matrix a, Matrix b)
{
    // ToDo
     int i,j;
    Matrix c;
    if(a.rows==b.rows&&a.cols==b.cols){
        c.rows=a.rows;
        c.cols=a.cols;
        for(i=0;i<a.rows;i++){
            for(j=0;j<a.cols;j++){
                c.data[i][j]=a.data[i][j]-b.data[i][j];
            }
        }
        return c;
    }
     else{
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
}

Matrix mul_matrix(Matrix a, Matrix b)
{
    // ToDo
    int i,j,k;
    double h;
    Matrix c;
    if(a.rows==b.cols&&a.cols==b.rows){
        c.rows=a.rows;
        c.cols=b.cols;
       for(i=0;i<a.rows;i++){
        for(j=0;j<b.cols;j++){
            h=0;
            for(k=0;k<a.cols;k++){
                h+=a.data[i][k]*b.data[k][j];
            }
            c.data[i][j]=h;
        }
       }
       return c;
    }
    else{
        printf("Error: The number of cols of matrix a must be equal to the number of rows of matrix b.\n");
        return create_matrix(0, 0);
    }
}

Matrix scale_matrix(Matrix a, double k)
{
    // ToDo
    int i,j;
    Matrix c;
    c.rows=a.rows;
    c.cols=a.cols;
    for(i=0;i<a.rows;i++){
        for(j=0;j<a.cols;j++){
            c.data[i][j]=k*a.data[i][j];
        }
    }

    return c;
}

Matrix transpose_matrix(Matrix a)
{
    // ToDo
    Matrix c;
    c.rows=a.cols;
    c.cols=a.rows;
    int i,j;
    for(i=0;i<a.rows;i++){
        for(j=0;j<a.cols;j++){
            c.data[j][i]=a.data[i][j];
        }
    }
    return c;
}

double det_matrix(Matrix a)
{
    // ToDo
    if(a.rows!=a.cols){
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }
    else{
        int k;/*k用于记录第k+1次消元,第k+1次消元需要消去a.data[k][k]下面的那一列*/
        double qqq=1,f=1;/*qqq用于存放每次乘的倍数的累计值,f用于储存行列式前的符号*/
        for(k=0;k<a.rows-1;k++){/*总共需要n-1次消元*/

        /*找出首项最大的那一行*/
        int i,temp,f;/*temp用于储存最大数在第几行，f用于储存行列式前的符号*/
        k=0;
        for(i=k;i<a.rows;i++){
            if(a.data[i+1][k]>a.data[i][k])
            temp=i;
        }

        /*把两行的数据交换*/
        if(temp!=k)
        f=-f;
        double t;/*t用于存放临时数据*/
        for(i=0;i<k;i++){
            t=a.data[k][i];
            a.data[k][i]=a.data[temp][i];
            a.data[temp][i]=t;
        }

        /*排除除数等于零的情况*/
        if(a.data[k][k]==0)
        return 0;

        /*进行消元*/
        int j;
        double q;/*q用于存放每行需要乘的倍数*/
        for(i=k+1;i<a.rows;i++){
            q=a.data[k][k]/a.data[i][k];
            qqq*=q;
            for(j=k+1;j<a.rows;j++){
                a.data[i][j]=a.data[i][j]*q-a.data[k][j];
            }
        }
    }
    /*最后把对角线乘起来*/
    double dett=1;
     for(int i=0;i<k;i++)
     dett*=a.data[i][i];
     dett*=qqq*f;
     return dett;
    }
}

Matrix inv_matrix(Matrix a)
{
    // ToDo
    return create_matrix(0, 0);
}

int rank_matrix(Matrix a)
{
    // ToDo
    return 0;
}
double trace_matrix(Matrix a){
    return 0;
}

void print_matrix(Matrix a) {
    // 遍历矩阵的行
    for (int i = 0; i < a.rows; i++) {
        // 遍历矩阵的列
        for (int j = 0; j < a.cols; j++) {
            // 使用printf打印每个元素
            printf("%-8.2f", a.data[i][j]); // %-8.2f表示左对齐，占8个字符宽度，小数点后保留2位
        }
        // 打印完一行后换行
        printf("\n");
    }
}
