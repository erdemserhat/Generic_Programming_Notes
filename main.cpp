#include <algorithm>
#include <iostream>
#include <ratio>
#include <vector>
#include <algorithm>
#include <iostream>
#include <list>
#include <thread>
#include <vector>

using namespace std;

void exampleVoidFunction() {
    std::cout <<"Hello from function hello" <<std::endl;
}

double exampleDoubleFunction() {
    return 1.0;
}

std::string exampleStringFunction() {
    return "ahmet";
}

char exampleCharFunction() {
    return 'a';
}


int sum (int a, int b) {
    return a + b;
}

template <typename T>
T sumTemplate (T a, T b) {
    return a + b;
}

template <typename T>
void printTemplate(T t, const int N) {
    for (int i=0; i<N; i++) {
        std::cout<<t<<std::endl;
    }
}

template<typename T>
void print (T a) {
    std::cout<<a<<std::endl;
}

template <char N, typename T>
void printSpecial(char a, T b) {
    std::cout<<a << b <<std::endl;
}


template <typename T>
class Example {
    public:
    T a;

    void print() {
        std::cout<<a<<std::endl;
    }
};

volatile bool running = true;

void stop() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Wait for 500 ms
    running = false;
}

void loop() {
    while (running) {
        print("Hello from loop");
    }
}


int counter = 0;  // Shared resource

void increment() {
    for (int i = 0; i < 1000; ++i) {
        ++counter;  // Non-atomic operation
    }
}
template <typename T>
void foo(const T &t)
{
    std::cout << "Function foo: ";
    std::cout << t;
    std::cout << std::endl;
}


struct A
{
};

std::ostream &
operator << (std::ostream &os, const A &)
{
    os << "A";
    return os;
}

// B doesn't have to derive from a base class.
struct B
{
};

std::ostream &
operator << (std::ostream &os, const B &)
{
    os << "B";
    return os;
}






int main() {

    //int a =10;
   // int b = 20;

    //std::cout << sum(a,b)<<std::endl;

    //std::cout << sumTemplate(1.2,1.2)<<std::endl;
   // printTemplate("Serhat",5);
   // std::vector<int> numbers = {1, 2, 3, 4, 5};


    //  for (int i=0; i<numbers.size(); i++) {
    //     std::cout<<numbers[i]<<std::endl;
    //}

    //std::string s = "hello";

   // int a = 10;

   // print(a);

    //Example<double> a;

   // a.a = 1.0;
   // a.print();

   // std::vector v{1.0, 1.1, 1.2};
  //  sort(v.begin(), v.end());

   // for(const auto &e: v)
    //    cout << e << endl;

    //int a = 1000000;
  //  int b = a;

   // print(a);
    //print(b);

   // int a = 10;
   //int* ptr =&a;
    //cout << *ptr;  // Prints the memory address of `a`

    //char aStr[] = "A";
    //char bStr[] = "B";

   // int* a;
    //int b = 20;
    //cout<<"Beginning of operation"<<endl;


    //pointer logic
    // pointer refers address of variable
    // to refer the values's itself use *a
    // to rerefer a another variable use *a = 34;



    /* pointers.md


    a = new int;
    *a =10;
    cout<<"A"<<*a<<endl;
    std::cout<<"B"<<b<<endl;

    cout<<"Operation 1"<<endl;

    *a=b; // -----> you are referring the value of pointer
    //
    a = &b;// ----> // you are defaulty refer of addres of value

    cout<<"A"<<*a<<endl;
    std::cout<<"B"<<b<<endl;

    *a=34;

    cout<<"Operation 2"<<endl;

    cout<<"A"<<*a<<endl;
    std::cout<<"B"<<b<<endl;

    */

    /*


    // you can change the value of const value with pointer
    const int* v = new int;
    int x = 10;
    int y = 20;


    v = &x;
    print(*v);

    v =&y;
    print(*v);
    */

    //std:vector list {1,2,3,4};

   // int* dsa = nullptr;
    //print(*dsa);


    //The value being pointed to by ptr is constant (cannot be changed through ptr).
    //The pointer ptr itself can point to a different address.
    //const int* ptr;  // Or: int const* ptr;

   // int a = 10, b = 20;
    //const int* ptr = &a;  // Pointer to a constant int
    //*ptr = 30;            // Error: cannot modify value through ptr
    //ptr = &b;             // Allowed: ptr can point to a different address

    //int* const ptr;
    //The pointer ptr is constant (cannot point to a different address).
    //The value being pointed to can be modified.


    //////////////////////////////////////////////////////////////////////


    /*

    std::tuple<int, double, std::string> t{1, 2.5, "example"};

    // Access elements using std::get
    std::cout << std::get<0>(t) << " ";  // Outputs: 1
    std::cout << std::get<1>(t) << " ";  // Outputs: 2.5
    std::cout << std::get<2>(t) << "\n"; // Outputs: example

    volatile int a = 10; //The volatile keyword is used to tell the compiler not to optimize accesses to a variable, because the variable might be changed by an external factor (e.g., hardware, multi-threading).

    unsigned int d = -1; //The keyword unsigned is a modifier in C++ that applies to integer types (e.g., int, char, etc.) to ensure they can only hold non-negative values.
    //For a 32-bit unsigned int: range = 0 to 4,294,967,295.
    std::cout<<d<<std::endl; // return 4,294,967,295 insyead of -1, because it reversed.

    auto start = std::chrono::high_resolution_clock::now(); //-> important expression



    std::thread stopper(stop); // Start a new thread
    std::thread looper(loop);
    stopper.join();
    looper.join();

    auto end = std::chrono::high_resolution_clock::now();


    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Elapsed time: " << duration.count() << " ms" << std::endl;
    */






    foo(1);  // Works because int supports <<
    foo(A());  // Works because operator<<(std::ostream&, const A&) is defined
    foo(B());  // Works because operator<<(std::ostream&, const B&) is defined



































    return 0;
}

