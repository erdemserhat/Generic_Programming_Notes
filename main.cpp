#include <algorithm>
#include <iostream>
#include <ratio>
#include <vector>
#include <algorithm>
#include <iostream>
#include <list>
#include <thread>
#include <vector>
#include <array>
#include <iostream>

using namespace std;


struct A {

};



template<typename T>
void primaryFunction(const T& arg) {
    std::cout<<arg<<std::endl;
}

template<>
void primaryFunction<A>(const A& args) { // if you like you can ommit <A> because the compile is able to deduce it from  function params
    std::cout<<"A"<<std::endl;
}


void foo(const int &i)
{
    std::cout << "Function foo: " << i << std::endl;
}

void foo(const A &)
{
    std::cout << "Function foo: A" << std::endl;
}



int main() {
    primaryFunction(1);
    primaryFunction<A>(A());

    foo(1);
    foo('1');
    foo(A());


}

