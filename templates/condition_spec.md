### **Why `if (N)` Works in C++**

In C++, non-boolean values (like integers) are **implicitly converted to boolean** in conditional statements:

- **`0`** → `false`
- **Non-zero values** (positive or negative) → `true`

---

### **Examples**

#### Positive and Negative Integers:
```cpp

void print(const T &t)
{
    std::cout << t << '\n';
}

constexpr int square(int x) {
    return x * x;
}

template <int N, typename T>
void print(const T &t)
{
    if constexpr (N)
    {
        print(t);
        print<N - 1>(t);
    }
}

 //Example

int main() {

    int N = 5; // Positive
    if (N) { // True
        std::cout << "N is non-zero\n";
    }

    N = -5; // Negative
    if (N) { // True
        std::cout << "N is non-zero\n";
    }

    N = 0;
    if (N) { // False
        std::cout << "Won't print\n";
    }


    print("Hello!");
    print<10>(1);



    return 0;
}





```

#### Floats:
```cpp
float x = 3.14;
if (x) { // True
    std::cout << "Non-zero float\n";
}

x = 0.0;
if (x) { // False
    std::cout << "Won't print\n";
}
```

#### Pointers:
```cpp
int *ptr = nullptr;
if (ptr) { // False
    std::cout << "Won't print\n";
}

ptr = new int;
if (ptr) { // True
    std::cout << "Pointer is non-null\n";
}
```

---

### **Key Rule**
Any **non-zero value** in `if (N)` is `true`. Zero is `false`.