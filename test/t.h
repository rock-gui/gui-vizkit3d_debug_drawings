#include <iostream>

namespace bla {

class Test
{
public:
    Test() 
    {
        std::cout << "TEST\n" << std::endl;
    }
};
Test t = Test();

}
