#include <iostream>
#include <chrono>
#include <thread>

#include "include/bar.hpp"

int main()
{
    Bar bar(13, 77, 30);
    bar.clear();

    for (int i = 0; i < 100; ++i)
    {
        bar.update(i);
        bar.draw();

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    std::cout << std::endl;
    return 0;
}
