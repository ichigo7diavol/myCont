#define DEBUG

#include <vector>
#include <iostream>
#include <exception>
#include <cont.h>
#include <thread>

int main () {

    std::vector<int> v{1,2,3,4,5};

    auto it = v.end();
    Cont<int>::iterator it2;

    ++it2;
    it2++;

    //it++ 1;

    std::cout << *(it - 3);

    //std::vector<int> v1 = {1,2,3,4,5};
    //auto it = v1.end();

    //Cont<int> c(5);

    //for (int i = 0; i < 5; ++i)
    //    c.push_back(i);

    //Cont<int> c2;
    //c2 = std::move(c);

    //for (int i = 0; i < 5; ++i)
    //    std::cout << c2[i] << c.capacity() << " " << c2.capacity() << std::endl;
//    std::this_thread::sleep_for(std::chrono::seconds(100));
    //int * p = new int [10000];
    //delete [] p;


    return 0;
}
