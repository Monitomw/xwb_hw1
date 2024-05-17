/*
 * @Author: WB 1197587021@qq.com
 * @Date: 2024-05-12 20:37:17
 * @LastEditors: WB 1197587021@qq.com
 * @LastEditTime: 2024-05-17 16:25:46
 * @FilePath: \xwb_hw1\src\algebra.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
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
    if ( a.rows != b.rows || a.cols != b.cols)
    {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
    else
    {
        int i, j;
        Matrix m=create_matrix(a.rows, a.rows);
        for ( i = 0; i < a.rows; i++)
        {
            for ( j = 0; j < a.rows; j++)
            {
                m.data[i][j] = a.data[i][j] + b.data[i][j];
            }
        }
        return m;
    }
    return create_matrix(0, 0);
}

Matrix sub_matrix(Matrix a, Matrix b)
{
    if ( a.rows != b.rows || a.cols != b.cols)
    {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
    else
    {
        int i, j;
        Matrix m=create_matrix(a.rows, a.rows);
        for (i = 0; i < a.rows; i++)
        {
            for (j = 0; j < a.rows; j++)
            {
                m.data[i][j] = a.data[i][j] - b.data[i][j];
            }
        }
        return m;
    }
    return create_matrix(0, 0);
}

Matrix mul_matrix(Matrix a, Matrix b)
{
    if (a.cols != b.rows)
    {
        printf("Error: The number of cols of matrix a must be equal to the number of rows of matrix b.\n");
        return create_matrix(0, 0);
    }
    else 
    {
        int i, j, k;
        Matrix m=create_matrix(a.rows, b.cols);
        for (i = 0; i < a.rows; i++)
        {
            for (j = 0; j < b.cols; j++){
                double sum = 0.0;
                for (k = 0; k < a.cols; k++)
                {
                    sum += a.data[i][k] * b.data[k][j];
                }
                m.data[i][j] = sum;
            }
        }
        return m;
    }
}

Matrix scale_matrix(Matrix a, double k)
{
    Matrix m=create_matrix(a.rows, a.cols);
    int i, j;
    for (i = 0; i < a.rows; i++)
    {
        for (j = 0; j < a.cols; j++)
        {
            m.data[i][j] = a.data[i][j] * k;
        }
    }
    return m;
}

Matrix transpose_matrix(Matrix a)
{
    Matrix m=create_matrix(a.cols, a.rows);
    int i, j;
    for (i = 0; i < a.rows; i++)
    {
        for (j = 0; j < a.cols; j++)
        {
            m.data[j][i] = a.data[i][j];
        }
    }
    return m;
}

double det_matrix(Matrix a)
{
     if (a.rows != a.cols)
    {
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }
    else
    {
        if (a.rows == 1)
        {
            return a.data[0][0];
        }
        else
        {
            int i, j, k;
            double sum = 0.0;
            for (i = 0; i < a.cols; i++)
            {
                Matrix b = create_matrix(a.rows-1, a.cols-1);
                for (j = 1; j < a.rows; j++){
                    int flag = 0;
                    for (k = 0; k < a.cols; k++)
                    {
                        if (k == i)
                        {
                            flag = 1;
                            continue;
                        }
                        else 
                        {
                            b.data[j - 1][k - flag] = a.data[j][k];
                        }
                    }
                }
                sum += ((i % 2) ? -1 : 1) * a.data[0][i] * det_matrix(b);
            }
            return sum;
        }
    }
    return 0;
}

Matrix inv_matrix(Matrix a)
{
    if (a.rows != a.cols)
    {
        printf("Error: The matrix must be a square matrix.\n");
        return create_matrix(0, 0);
    }
    else
    {
        if (det_matrix(a) == 0)
        {
            printf("Error: The matrix is singular.\n");
            return create_matrix(0, 0);
        }
        else 
        {
            Matrix b = create_matrix(a.rows, a.cols);
            int i, j, k, m;
            for (i = 0; i < a.rows; i++)
            {
                for (j = 0; j < a.cols; j++)
                {
                    Matrix c = create_matrix(a.rows - 1, a.cols - 1);
                    int flag_r = 0;
                    for (k = 0; k < a.rows; k++)
                    {
                        if (k == j)
                        {
                            flag_r = 1;
                            continue;
                        }

                        int flag_c = 0;

                        for (m = 0; m < a.cols; m++)
                        {
                            if (m == i)
                            {
                                flag_c = 1;
                                continue;
                            }
                            c.data[k - flag_r][m - flag_c] = a.data[k][m];
                        }
                    }
                    b.data[i][j] = ((i + j) % 2 ? -1.0 : 1.0) * det_matrix(c);
                }
            }
            b = scale_matrix(b, 1.0 / det_matrix(a));
            return b;
        }
    }
}

int rank_matrix(Matrix a)
{
    int r;
    if (a.cols >= a.rows)
    {
        r = a.rows;
    }
    else
    {
        r = a.cols;
        a = transpose_matrix(a);
    }
    int i, j, k;
    for (int i = 0; i < a.rows; i++)
    {
        if (a.data[i][i] != 0)
        {
            for (j = i + 1; j < a.rows; j++)
            {
                double t = a.data[j][i] / a.data[i][i];
                for (k = i; k < a.cols; k++)
                {
                    a.data[j][k] -= t * a.data[i][k];
                }
            }
        }
        else{
            int flag = 0;
            for (j = i + 1; j < a.rows; j++)
            {
                if (a.data[j][i] != 0)
                {
                    flag = 1;
                    for (k = i; k < a.cols; k++)
                    {
                        double temp;
                        temp = a.data[i][k]; 
                        a.data[i][k] = a.data[j][k];
                        a.data[j][k] = temp;
                    }
                    break;
                }
            }
            if (flag != 0)
            {
                for (j = i + 1; j < a.rows; j++)
                {
                    double t = a.data[j][i] / a.data[i][i];
                    for (k = i; k < a.cols; k++){
                        a.data[j][k] -= a.data[i][k];
                    }
                }
            }
            else
            {
                r-=1;
            }
        }
    }
    return r;
}

double trace_matrix(Matrix a)
{
    if (a.rows != a.cols)
    {
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }
    else 
    {
        int k;
        double tr=0.0;
        for (k = 0; k < a.rows; k++)
        {
            tr+=a.data[k][k];
        }
        return tr;
    }
    return 0;
}

void print_matrix(Matrix a)
{
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            // 按行打印，每个元素占8个字符的宽度，小数点后保留2位，左对齐
            printf("%-8.2f", a.data[i][j]);
        }
        printf("\n");
    }
}