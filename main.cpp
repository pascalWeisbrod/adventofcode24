#include <iostream>
#include "code/helper/helper.h"

int main() 
{
    Helper* helper = new Helper();
    std::string text = helper -> readInputFile(1);

    std::cout << text; 
}
