//
// Created by Dmytro Babenko on 2019-04-25.
//

#include <iostream>
#include <xmmintrin.h>
#include <immintrin.h>
#include <chrono>
#include <random>


void a_mul_b_plus_c_mul_d(const float* a, const float* b, const float* c, const float* d, float* res, size_t n){

    __m128 rA,rB,rC, rD, rResult;

    for (size_t i = 0; i < n; i+=4){
        rA = _mm_load_ps(&a[i]);
        rB = _mm_load_ps(&b[i]);
        rC = _mm_load_ps(&c[i]);
        rD = _mm_load_ps(&d[i]);

        rResult = _mm_add_ps(_mm_mul_ps(rA, rB), _mm_mul_ps(rC, rD));
        _mm_store_ps(&res[i],rResult);
    }
}



void task1()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(-1000.0f, 1000.0f);

    const size_t n = 1000;

    float a[n], b[n], c[n], d[n];
    float res[n] = {};

    for (size_t i = 0; i < n; ++i)
    {
        a[i] = dist(mt);
        b[i] = dist(mt);
        c[i] = dist(mt);
        d[i] = dist(mt);
    }

    auto start = std::chrono::steady_clock::now();

    a_mul_b_plus_c_mul_d(a, b, c, d, res, n);

    auto end = std::chrono::steady_clock::now();

    auto time_micros_sec = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout<<"Task1 time: "<<time_micros_sec<<" µs"<<std::endl;

}
