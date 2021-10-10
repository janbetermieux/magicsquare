//
// Created by jan.betermieux on 12/19/20.
//
#include <array>
using namespace std;

#ifndef GLTEST_MATRIXCOLORS_H
#define GLTEST_MATRIXCOLORS_H

struct color{
    float r,g,b;
};

array<color, 4> getMatrixColors(){
    color matrix0{};
    matrix0.r = 13 / 255.f, matrix0.g = 2 / 255.f, matrix0.b = 8 / 255.f;
    color matrix1{};
    matrix1.r = 54 / 255.f, matrix1.g = 186 / 255.f, matrix1.b = 1 / 255.f;
    color matrix2{};
    matrix2.r = 0.f, matrix2.g = 154 / 255.f, matrix2.b = 34 / 255.f;
    color matrix3{};
    matrix3.r = 0.f, matrix3.g = 1.f, matrix3.b = 43 / 255.f;
    array<color, 4> retval = {matrix0, matrix1, matrix2, matrix3};
    return retval;
}

#endif //GLTEST_MATRIXCOLORS_H