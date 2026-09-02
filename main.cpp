#include <iostream>

#include "ThreadPool.h"


int main()
{
    ThreadPool pool(4);

    for (int i = 1; i <= 5; ++i)
    {
        bool submitted = pool.submit(
            i,
            "Task " + std::to_string(i),
            [i]()
            {
                std::cout
                    << "Executing Task "
                    << i
                    << "\n";
            }
        );

        if (submitted)
        {
            std::cout
                << "Task "
                << i
                << " submitted\n";
        }
        else
        {
            std::cout
                << "Task "
                << i
                << " rejected\n";
        }
    }


    pool.shutdown();


    bool submitted = pool.submit(
        6,
        "Task 6",
        []()
        {
            std::cout << "This should not execute\n";
        }
    );


    if (!submitted)
    {
        std::cout
            << "Task 6 rejected because "
               "ThreadPool is stopped\n";
    }


    return 0;
}