#include <iostream>
#include "code/helper/helper.h"

int main() 
{
    Helper* helper = new Helper();
    helper -> readLines();

    std::cout << "hello c++" << std::endl;
}
