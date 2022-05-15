#include<iostream>
#include<cstdlib>
#include <sstream>
#include <memory>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>

using namespace std;
const int max_n =1024;
int M = max_n - (max_n % 64);
int N = max_n % 64;
float** src_ij;
float** dst_ij;
float** dst_ji;
float** ji_ij;

void mult()
{
    __m256 a0, a1, a2, a3, a4, a5, a6, a7;
    __m256 b0, b1, b2, b3, b4, b5, b6, b7;
    __m256 c0, c1, c2, c3, c4, c5, c6, c7;
    __m256 d0 = _mm256_setzero_ps();
    __m256 d1 = _mm256_setzero_ps();
    __m256 d2 = _mm256_setzero_ps();
    __m256 d3 = _mm256_setzero_ps();
    __m256 d4 = _mm256_setzero_ps();
    __m256 d5 = _mm256_setzero_ps();
    __m256 d6 = _mm256_setzero_ps();
    __m256 d7 = _mm256_setzero_ps();
    __m256 d8 = _mm256_setzero_ps();

    int i, j, k, r;
    float cc;
    float* pi;
    for (i = 0; i < max_n; i++)
    {
        for (j = 0; j < max_n; j++)
        {
            for (k = 0; k < M; k += 64)
            {
                float* dz1 = &src_ij[i][k];
                a0 = _mm256_loadu_ps(dz1);
                a1 = _mm256_loadu_ps(dz1 + 8);
                a2 = _mm256_loadu_ps(dz1 + 16);
                a3 = _mm256_loadu_ps(dz1 + 24);
                a4 = _mm256_loadu_ps(dz1 + 32);
                a5 = _mm256_loadu_ps(dz1 + 40);
                a6 = _mm256_loadu_ps(dz1 + 48);
                a7 = _mm256_loadu_ps(dz1 + 56);
                dz1 = &dst_ji[j][k];
                b0 = _mm256_loadu_ps(dz1);
                b1 = _mm256_loadu_ps(dz1 + 8);
                b2 = _mm256_loadu_ps(dz1 + 16);
                b3 = _mm256_loadu_ps(dz1 + 24);
                b4 = _mm256_loadu_ps(dz1 + 32);
                b5 = _mm256_loadu_ps(dz1 + 40);
                b6 = _mm256_loadu_ps(dz1 + 48);
                b7 = _mm256_loadu_ps(dz1 + 56);

                c0 = _mm256_mul_ps(a0, b0);
                c1 = _mm256_mul_ps(a1, b1);
                c2 = _mm256_mul_ps(a2, b2);
                c3 = _mm256_mul_ps(a3, b3);
                c4 = _mm256_mul_ps(a4, b4);
                c5 = _mm256_mul_ps(a5, b5);
                c6 = _mm256_mul_ps(a6, b6);
                c7 = _mm256_mul_ps(a7, b7);

                d0 = _mm256_add_ps(c0, d0);
                d1 = _mm256_add_ps(c1, d1);
                d2 = _mm256_add_ps(c2, d2);
                d3 = _mm256_add_ps(c3, d3);
                d4 = _mm256_add_ps(c4, d4);
                d5 = _mm256_add_ps(c5, d5);
                d6 = _mm256_add_ps(c6, d6);
                d7 = _mm256_add_ps(c7, d7);

            }
            d0 = _mm256_add_ps(d1, d0);
            d2 = _mm256_add_ps(d3, d2);
            d4 = _mm256_add_ps(d5, d4);
            d6 = _mm256_add_ps(d7, d6);
            d0 = _mm256_add_ps(d0, d2);
            d4 = _mm256_add_ps(d4, d6);
            d0 = _mm256_add_ps(d0, d4);

            d0 = _mm256_hadd_ps(d0, d8);
            d0 = _mm256_hadd_ps(d0, d8);

            pi = (float*)(&d0);
            cc = (*pi) + (*(pi + 4));
            d0 = _mm256_setzero_ps();
            d1 = _mm256_setzero_ps();
            d2 = _mm256_setzero_ps();
            d3 = _mm256_setzero_ps();
            d4 = _mm256_setzero_ps();
            d5 = _mm256_setzero_ps();
            d6 = _mm256_setzero_ps();
            d7 = _mm256_setzero_ps();

            r = M;
            while (r < max_n)
            {
                cc += src_ij[i][r] * dst_ji[j][r];
                r++;
            }
            ji_ij[i][j] = cc;
        }

    }
}
void mult0()
{
    __m256 a0;
    __m256 b0;
    __m256 c0;
    __m256 d0 = _mm256_setzero_ps();
    __m256 d8 = _mm256_setzero_ps();

    int i, j, k, r;
    float cc;
    float* pi;
    for (i = 0; i < max_n; i++)
    {
        for (j = 0; j < max_n; j++)
        {
            for (k = 0; k < M; k += 8)
            {
                
                a0 = _mm256_loadu_ps(&src_ij[i][k]);
                b0 = _mm256_loadu_ps(&dst_ji[j][k]);
               
                c0 = _mm256_mul_ps(a0, b0);
                d0 = _mm256_add_ps(c0, d0);
                
            }
            
            d0 = _mm256_hadd_ps(d0, d8);
            d0 = _mm256_hadd_ps(d0, d8);

            pi = (float*)(&d0);
            cc = (*pi) + (*(pi + 4));
            d0 = _mm256_setzero_ps();
           
            r = M;
            while (r < max_n)
            {
                cc += src_ij[i][r] * dst_ji[j][r];
                r++;
            }
            ji_ij[i][j] = cc;
        }

    }
}


void zhuanzhi()
{
    int i, j;
    for (i = 0; i < max_n; i++)
    {
        for (j = 0; j < max_n; j++)
        {
            dst_ji[j][i] = dst_ij[i][j];
        }
    }
}

void zhuan4(const __m128 s1, const __m128 s2, const __m128 s3, const __m128 s4, 
    float* d1, float* d2,float* d3, float* d4)
{
    __m128 t1, t2, t3, t4, t5, t6, t7, t8;
    t1 = _mm_permute_ps(s1, 0b01001110);//将第一行数据进行交换得到a2,a3,a0,a1
    t2 = _mm_permute_ps(s2, 0b01001110);//将第二行数据进行交换得到b2,b3,b0,b1
    t3 = _mm_permute_ps(s3, 0b01001110);//将第三行数据进行交换得到c2,c3,c0,c1
    t4 = _mm_permute_ps(s4, 0b01001110);//将第四行数据进行交换得到d2,d3,d0,d1
    t5 = _mm_blend_ps(s1, t3, 0b1100);//合并原序列第一行和重排序列第三行得到a0,a1,c0,c1
    t6 = _mm_blend_ps(s2, t4, 0b1100);//b0,b1,d0,d1
    t7 = _mm_blend_ps(t1, s3, 0b1100);//a2,a3,c2,c3
    t8 = _mm_blend_ps(t2, s4, 0b1100);//b2,b3,d2,d3
    t5 = _mm_permute_ps(t5, 0b11011000);
    t6 = _mm_permute_ps(t6, 0b11011000);
    t7 = _mm_permute_ps(t7, 0b11011000);
    t8 = _mm_permute_ps(t8, 0b11011000);
   _mm_stream_ps (d1, _mm_unpacklo_ps(t5, t6));//生成转置子块，并写入对应位置a0,b0,c0,d0
   _mm_stream_ps (d2, _mm_unpackhi_ps  (t5, t6));//a1,b1,c1,d1
   _mm_stream_ps (d3, _mm_unpacklo_ps(t7, t8));//a2,b2,c2,d2
   _mm_stream_ps (d4, _mm_unpackhi_ps  (t7, t8));//a3,b3,c3,d3
    
}

void zhuan8( float* s1,  float* s2,  float* s3,  float* s4,
     float* s5,  float* s6,  float* s7,  float* s8,
    float* d1, float* d2, float* d3, float* d4,
    float* d5, float* d6, float* d7, float* d8)
{
    __m128 t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16;
    t1 = _mm_loadu_ps(s1);
    t5 = _mm_loadu_ps(s1 + 4);
    t2 = _mm_loadu_ps(s2);
    t6 = _mm_loadu_ps(s2 + 4);
    t3 = _mm_loadu_ps(s3);
    t7 = _mm_loadu_ps(s3 + 4);
    t4 = _mm_loadu_ps(s4);
    t8 = _mm_loadu_ps(s4 + 4);
    t9 = _mm_loadu_ps(s5);
    t13 = _mm_loadu_ps(s5 + 4);
    t10 = _mm_loadu_ps(s6);
    t14 = _mm_loadu_ps(s6 + 4);
    t11 = _mm_loadu_ps(s7);
    t15 = _mm_loadu_ps(s7 + 4);
    t12 = _mm_loadu_ps(s8);
    t16 = _mm_loadu_ps(s8 + 4);
    zhuan4(t1, t2, t3, t4, d1, d2, d3, d4);
    zhuan4(t9, t10, t11, t12, d1 + 4, d2 + 4, d3 + 4, d4 + 4);
    zhuan4(t5, t6, t7, t8, d5, d6, d7, d8);
    zhuan4(t13, t14, t15, t16, d5 + 4, d6 + 4, d7 + 4, d8 + 4);
}

void zhuanzhi_simd()
{
   float* x = dst_ij[0];
   float* y = dst_ji[0];
    float* s1 = x, * s2 = x + max_n, * s3 = x + 2 * max_n, * s4 = x + 3 * max_n,
        * s5 = x + 4 * max_n, * s6 = x + 5 * max_n, * s7 = x + 6 * max_n, * s8 = x + 7 * max_n,
        * d1 = y, * d2 = y + max_n, * d3 = y + 2 * max_n, * d4 = y + 3 * max_n,
        * d5 = y + 4 * max_n, * d6 = y + 5 * max_n, * d7 = y + 6 * max_n, * d8 = y + 7 * max_n;
        
    
    for (int i = 0; i < max_n; i += 8)
    {

        d1 = y + i, d2 = d1 + max_n, d3 = d1 + 2 * max_n, d4 = d1 + 3 * max_n,
            d5 = d1 + 4 * max_n, d6 = d1 + 5 * max_n, d7 = d1 + 6 * max_n, d8 = d1 + 7 * max_n;
        int j = max_n;
        while (j >= 8)
        {
            zhuan8(s1, s2, s3, s4, s5, s6, s7, s8, d1, d2, d3, d4, d5, d6, d7, d8);
            s1 += 8; s2 += 8; s3 += 8; s4 += 8;
            s5 += 8; s6 += 8; s7 += 8; s8 += 8;
            d1 += 8 * max_n; d2 += 8 * max_n; d3 += 8 * max_n; d4 += 8 * max_n;
            d5 += 8 * max_n; d6 += 8 * max_n; d7 += 8 * max_n; d8 += 8 * max_n;
            j -= 8;
        }
        s1 += 7 * max_n; s2 += 7 * max_n; s3 += 7 * max_n; s4 += 7 * max_n;
        s5 += 7 * max_n; s6 += 7 * max_n; s7 += 7 * max_n; s8 += 7 * max_n;
    }
   
}
void trans(float* x, float* y, size_t n)
{
    float* s = x, * d = y;
    for (int i = 0; i < n; i++)
    {
        d = y + i;
        for (int j = 0; j < n; j++)
        {
            *d = *(s++);
            d += n;
        }
    }
}

int main()
{
 
    src_ij = (float**)malloc(sizeof(int*) * max_n);
    dst_ij = (float**)malloc(sizeof(int*) * max_n);
    dst_ji = (float**)malloc(sizeof(int*) * max_n);
    ji_ij = (float**)malloc(sizeof(int*) * max_n);
   
    src_ij[0] = (float*)malloc(sizeof(float) * max_n * max_n);
    dst_ij[0] = (float*)malloc(sizeof(float) * max_n * max_n);
    dst_ji[0] = (float*)malloc(sizeof(float) * max_n * max_n);
    ji_ij[0] = (float*)malloc(sizeof(float) * max_n * max_n);
    
    for (int i = 1; i < max_n; i++)
    {
        src_ij[i] = src_ij[i - 1] + max_n;
        dst_ij[i] = dst_ij[i - 1] + max_n;
        dst_ji[i] = dst_ji[i - 1] + max_n;
        ji_ij[i] = ji_ij[i - 1] + max_n;
    }
    
    for (int i = 0; i < max_n; i++)
    {
        for (int j = 0; j < max_n; j++)
        {
            src_ij[i][j] = rand() % 3; //i+j ;
            dst_ij[i][j] = rand() % 3; //2 * i+j ;
            dst_ji[i][j] = 0;
            ji_ij[i][j] = 0;;
        }
    }
    long beginTime = clock();
    zhuanzhi();
    for (int i = 0; i < max_n; i++)
    {
        for (int j = 0; j < max_n; j++)
        {
            for (int k = 0; k < max_n; k++)
            {
                ji_ij[i][j] += src_ij[i][k] * dst_ji[j][k];
            }
        }
    }
    long endTime = clock();
    std::cout << "endTime-beginTime:" << ((double)(endTime - beginTime)) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
    
    cout << "ji_ij:" << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << ji_ij[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
    //******************************************************************
    for (int i = 0; i < max_n; i++)
    {
        for (int j = 0; j < max_n; j++)
        {
            dst_ji[i][j] = 0;
            ji_ij[i][j] = 0;;
        }
    }
    long beginTime1 = clock();
    //zhuanzhi();
    trans(dst_ij[0], dst_ji[0], max_n);
    mult();
    long endTime1 = clock();
    std::cout << "endTime-beginTime:" << ((double)(endTime1 - beginTime1)) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
    
    cout << "ji_ij:" << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << ji_ij[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
    //*********************************************************************
    for (int i = 0; i < max_n; i++)
    {
        for (int j = 0; j < max_n; j++)
        {
            dst_ji[i][j] = 0;
            ji_ij[i][j] = 0;;
        }
    }
    long beginTime2 = clock();
    zhuanzhi_simd();
    mult();
    long endTime2 = clock();
    std::cout << "endTime-beginTime:" << ((double)(endTime2 - beginTime2)) / CLOCKS_PER_SEC * 1000 << "ms" << endl;

    cout << "ji_ij:" << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << ji_ij[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;

    for (int i = 0; i < max_n; i++)
    {
        for (int j = 0; j < max_n; j++)
        {
            dst_ji[i][j] = 0;
            ji_ij[i][j] = 0;;
        }
    }
    long beginTime4 = clock();
    zhuanzhi_simd();
    mult0();
    long endTime4= clock();
    std::cout << "endTime-beginTime:" << ((double)(endTime4 - beginTime4)) / CLOCKS_PER_SEC * 1000 << "ms" << endl;

    cout << "ji_ij:" << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << ji_ij[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
    free(src_ij);
    free(dst_ij);
    free(dst_ji);
    free(ji_ij);
    return 0;
}