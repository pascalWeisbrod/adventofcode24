#include <iostream>
#include <chrono>
#include "code/helper/helper.h"
#include "code/day1/day1.h"

int main() 
{
    Helper* helper = new Helper();
    std::string text = helper -> readInputFile(7);

    auto timeBefore = std::chrono::system_clock::now();

    work(text);

    auto timeAfter = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(timeBefore.time_since_epoch());
    auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(timeAfter.time_since_epoch());

    std::cout << "Seconds: " << (duration2.count() - duration.count()) / 1000.0 << std::endl;
}
