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
    if(a.cols==b.rows){
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
    if(a.rows==a.cols){
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
    else{
    printf("Error: The matrix must be a square matrix.\n");
    return create_matrix(0, 0);
    }

}

double det_matrix(Matrix a)
{
    // ToDo
    if(a.rows!=a.cols){ 
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }
    else{
        int k;/*k用于记录第k+1次消元,此时a.data[k][k]是主元，第k+1次消元需要消去a.data[k+1][k]及其下面的那一列数*/
        double mul=1;
        int f=1;/*mul用于存放每次乘的倍数的累计值,f用于储存行列式前的符号*/
        for(k=0;k<a.rows-1;k++){/*如果行列式的值不为零则总共需要n-1次消元*/

        /*找出首项最大的那一行,遍历*/

        int i,temp=k;/*temp用于储存首位最大数在第几行(a.data[temp][])*/
        for(i=k;i<a.rows;i++){
            if(a.data[i][k]>a.data[temp][k])
            temp=i;
        }

        /*把两行([k][temp])的数据交换*/

        if(temp!=k){
        f=-f;/*换行时需要变号*/
        double t;/*t用于存放交换时的临时数据*/
        for(i=0;i<a.rows;i++){
            t=a.data[k][i];
            a.data[k][i]=a.data[temp][i];
            a.data[temp][i]=t;
        }
        }
        /*排除除数等于零的情况*/
        if(a.data[k][k]==0)
        return 0;

        /*进行消元消去a.data[k+1][]*/
        int j;
        double q;/*q用于存放每次消元中a.data[k][]这行需要乘的倍数*/
        for(i=k+1;i<a.rows;i++){
            q=a.data[i][k]/a.data[k][k];
           // mul*=q;
            for(j=0;j<a.cols;j++){               /*j用于遍历列所以写成a.cols*/
                a.data[i][j]=a.data[i][j]-a.data[k][j]*q;
            }
        }
    }
    /*最后把对角线乘起来*/
    double det=1;/*用来存放行列式的值，这次不乱用变量名了*/ 
     for(int i=0;i<a.rows;i++)
     det*=a.data[i][i];
     det*=/*mul**/f;
     return det;
    }
}
    
Matrix delete_matrix(Matrix a,int i,int j){
    /*用来算伴随矩阵的每一个元素的*/
    int k,t;
    Matrix d= create_matrix(a.rows-1,a.cols-1);
    if(j!=0&&i!=0){
    for(k=0;k<i;k++){         /*左上角那块*/
        for(t=0;t<j;t++){
            d.data[k][t]=a.data[k][t];
        }
    }
    }
    if(j!=0){
    for(k=i;k<a.rows;k++){    /*左下角那块*/
        for(t=0;t<j;t++){
            d.data[k][t]=a.data[k+1][t];
        }
    }
    }
    if(i!=0){
    for(k=0;k<i;k++){          /*右上角那块*/
        for(t=j;t<a.cols;t++){
            d.data[k][t]=a.data[k][t+1];
        }
    }
    }
    
    for(k=i;k<a.rows;k++){     /*右下角那块*/
        for(t=j;t<a.cols;t++){
            d.data[k][t]=a.data[k+1][t+1];
        }
    }
return d;
}

Matrix inv_matrix(Matrix a)
{
    // ToDo
if(a.rows!=a.cols){
    printf("Error: The matrix must be a square matrix.\n");
    return create_matrix(0, 0);
}
else if(det_matrix(a)==0){
    printf("Error: The matrix is singular.\n");
    return create_matrix(0, 0);
}
else{

    /*下面求伴随矩阵*/
    Matrix com = create_matrix(a.rows,a.cols);/*初始化伴随矩阵*/
    int i,j;
    for(i=0;i<a.rows;i++){
        for(j=0;j<a.cols;j++){
        com.data[i][j]==det_matrix(delete_matrix(a,i,j));
        if((i+j)%2!=0)
        com.data[i][j]=-com.data[i][j];
        }
    }
    Matrix inv =create_matrix(a.rows,a.cols);             /*inv用于存放逆矩阵*/
    double q=1.0/det_matrix(a);                   /*系数*/
    for(i=0;i<a.rows;i++){
        for(j=0;j<a.cols;j++){
            inv.data[i][j]=q*com.data[i][j];
        }
    }
return inv;
}
}

int rank_matrix(Matrix a)
{
    // ToDo
    return 0;
}
double trace_matrix(Matrix a){
    if(a.rows==a.cols){
    int i;
    double trace=0.0;
    for(i=0;i<a.rows;i++){
    trace+=a.data[i][i];
    }
    return trace;
    }
    else{
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
        }
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
    return;
}
