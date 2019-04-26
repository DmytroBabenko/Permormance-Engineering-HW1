//
// Created by Dmytro Babenko on 2019-04-25.
//

#include <xmmintrin.h>
#include <iostream>
#include <chrono>
#include <random>



#include "Task2.h"


float dot_product(const float* a, const float* b, unsigned size)
{
    __m128 rA,rB, rC;
    __m128 r0 = _mm_setzero_ps();

    for (unsigned i = 0; i < size; i+=4){
        rA = _mm_load_ps(&a[i]);
        rB = _mm_load_ps(&b[i]);

        rC = _mm_mul_ps(rA, rB);
        r0 = _mm_add_ps(r0, rC);
    }

    float* buffer = (float*)&r0;

    float sum = 0;
    for (unsigned i = 0; i < 4 && i < size; ++i)
    {
        sum += *(buffer + i);
    }


    return sum;
}


void transpose_square_matrix(float* A, unsigned int size)
{
    for (unsigned int i = 0; i < size; ++i)
    {
        for (unsigned int j = i; j < size; ++j)
        {
            if (i != j)
            {
                std::swap(*((A + i*size) + j), *((A + j*size) + i));
            }

        }
    }
}


void mul_square_matrices(float* A, float* B, float* C, unsigned int size )
{
    transpose_square_matrix(B, size);

    for (unsigned i = 0; i < size; ++i)
    {
        for (unsigned j = 0; j < size; ++j)
        {
            float val = dot_product(A + i * size, B + j*size, size);
            *(C + i*size +j) = val;
        }
    }

    transpose_square_matrix(B, size);
}

//This function was found here: https://pdfs.semanticscholar.org/852c/0115d6011b6cd2746d18f56d64a53e65af5d.pdf%5C
void mul_square_matrices_copied(const float* A, const float* B, float* C, unsigned size)
{
    for (size_t i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; j+= 4)
        {
            __m128 m0 = _mm_setzero_ps();
            for (size_t k = 0; k < size; ++k)
            {
//                __m128 m1 = _mm_broadcast_ss(A + i*size +k);
                __m128 m1 = _mm_set1_ps(*(A + i*size +k));
                __m128 m2 = _mm_load_ps(B + k*size + j);
                __m128 m3 = _mm_mul_ps(m1, m2);
                m0 = _mm_add_ps(m0, m3);
            }
            _mm_store_ps(C + i*size + j, m0);
        }
    }
}


void task2()
{

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(-1000.0f, 1000.0f);


    float A[100][100], B[100][100];

    for (unsigned i = 0; i < 100; ++i)
    {
        for (unsigned j = 0; j < 100; ++j)
        {
            A[i][j] = dist(mt);
            B[i][j] = dist(mt);
        }
    }

    float C[100][100];

    auto start = std::chrono::steady_clock::now();
    mul_square_matrices((float*)A, (float*)B, (float*)C, 100);
    auto end = std::chrono::steady_clock::now();
    auto time_micros_sec = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout<<"Task2: my mul_square_matrices function time: "<<time_micros_sec<<" µs"<<std::endl;

    start = std::chrono::steady_clock::now();
    mul_square_matrices_copied((float*)A, (float*)B, (float*)C, 100);
    end = std::chrono::steady_clock::now();
    time_micros_sec = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout<<"Task2: copied mul_square_matrices function time: "<<time_micros_sec<<" µs"<<std::endl;
}
