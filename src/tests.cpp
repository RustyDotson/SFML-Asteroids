#include <iostream>
#define IS_TRUE(x) { if (!(x)) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl; }


bool function1(int a) {
    return a > 5;   
}


void test_function1()
{
    IS_TRUE(!function1(0));
    IS_TRUE(!function1(5));
    IS_TRUE(function1(10));
}


int main() {
    test_function1();
    return 0;
}