

### **1. Using Function Pointer as a Template Parameter**
You can declare a template parameter as a pointer to a function with a specific signature.

#### Syntax:
```cpp
template <ReturnType (*FunctionPointer)(ParameterTypes...)>
```

#### Example:
```cpp
#include <iostream>

void myFunction(int x) {
    std::cout << "Called with " << x << '\n';
}

template <void (*F)(int)>
void callFunction(int value) {
    F(value); // Calls the function passed as the template argument
}

int main() {
    callFunction<myFunction>(42); // Pass myFunction as the template argument
    return 0;
}
```

**Output:**
```
Called with 42
```

---

### **2. Using Function Reference as a Template Parameter**
You can also pass the function as a **reference**. This ensures the function cannot be null, which adds safety.

#### Syntax:
```cpp
template <ReturnType (&FunctionReference)(ParameterTypes...)>
```

#### Example:
```cpp
#include <iostream>

void myFunction(int x) {
    std::cout << "Called with " << x << '\n';
}

template <void (&F)(int)>
void callFunction(int value) {
    F(value); // Calls the function passed as the template argument
}

int main() {
    callFunction<myFunction>(42); // Pass myFunction as the template argument
    return 0;
}
```

**Output:**
```
Called with 42
```

---
