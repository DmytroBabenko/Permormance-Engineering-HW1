//
// Created by Dmytro Babenko on 2019-04-30.
//

#include <nmmintrin.h>
#include <string>
#include <chrono>
#include <iostream>

#include "Task3.h"


unsigned long find_sub_str16_max_pos(const char* str, unsigned len_str, const char* sub_str, unsigned len_sub_str)
{
    if (len_sub_str > len_str)
        return std::string::npos;

//restriction for sub_str
    if (len_sub_str >=16)
        return std::string::npos;


    for (unsigned i = 0; i < len_str - len_sub_str; ++i)
    {

        const __m128i A = _mm_loadu_si128((__m128i*)(str + i));
        const __m128i B = _mm_loadu_si128((__m128i*)sub_str);

        __m128i res = _mm_cmpestrm(A, len_str, B, len_sub_str, _SIDD_CMP_EQUAL_EACH);

        unsigned max_len_str_size = len_str < 16 ? len_str : 16;

        res = res & ((1 << (max_len_str_size)) - 1);

        int mask = _mm_cvtsi128_si32(res);

        int num_of_ones = _popcnt32(mask);

        if (num_of_ones == len_sub_str)
            return i;
    }

    return std::string::npos;
}


void task3()
{
    std::string str = "sajdhfbjashdfkjashfdhasihfgjsdhfbjsadbfjhdsbfjbdsjhfdbhgdjshfbghjdbfjghbdsjfhgdshjbbfhjvdbfjhvbdsjfhbvjdshbfjvsdfjvdsklfgjkdjsfngkjsndfkjgnkdsjfngkjdznfgkjdbnfgkjvbdnzkfjgkjdfbngzjkfbgjkdfgdkjfngkjdsfn";
    std::string sub_str = "jdshbfjvsdfjv";


    auto start = std::chrono::steady_clock::now();
    auto pos = find_sub_str16_max_pos(str.c_str(), str.size(), sub_str.c_str(), sub_str.size());
    auto end = std::chrono::steady_clock::now();
    auto time_micros_sec = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout<<"Task3: find_sub_str16_max_pos result: "<<pos<<std::endl;
    std::cout<<"Task3: find_sub_str16_max_pos function time: "<<time_micros_sec<<" µs"<<std::endl;


    start = std::chrono::steady_clock::now();
    auto correct_pos = str.find(sub_str);
    end = std::chrono::steady_clock::now();
    time_micros_sec = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout<<"Task3: std::string::find result: "<<correct_pos<<std::endl;
    std::cout<<"Task3: std::string::find function time: "<<time_micros_sec<<" µs"<<std::endl;

}