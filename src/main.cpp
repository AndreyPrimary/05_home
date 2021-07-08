#include "lib.h"

#include <iostream>

#include "matrix_map.h"

void test_common()
{
    Matrix_map<int, -1> matrix;

    Matrix_map<int, -1>::node<int> node = matrix[1];

    std::cout << "node: " 
        << " X: " << node.x 
        << " Y: " << node.y
        << " val: " << node.val
        << std::endl;
}

int main (int, char **)
{
    
    std::cout << "Design Version: " << version() << std::endl;

    test_common();

    return 0;
}

