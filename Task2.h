//
// Created by Dmytro Babenko on 2019-04-25.
//

#ifndef HW_1_TASK2_H
#define HW_1_TASK2_H


float dot_product(const float* a, const float* b, unsigned int size);
void transpose_square_matrix(float* A, unsigned int size);
void mul_square_matrices(float* A, float* B, float* C, unsigned int size );

//This function was found here: https://pdfs.semanticscholar.org/852c/0115d6011b6cd2746d18f56d64a53e65af5d.pdf%5C
void mul_square_matrices_copied(const float* A, const float* B, float* C, unsigned size);
void task2();
#endif //HW_1_TASK2_H
