
---

### **Passing Functions**

#### **1. Ways to Pass Functions**
A function can be passed to another function using:
- **Reference**: Using a reference to the function.
- **Pointer**: Using a pointer to the function.
- **Not by value**: Functions themselves cannot be copied as values.

---

#### **2. Passing Functions by Reference**
- **Declaration**: Use a reference parameter of type `F&`, where `F` is a template parameter.
- **Behavior**: The compiler deduces that the parameter is a reference to the passed function.

**Example**:
```cpp
void hello() {
    std::cout << "Hello World!\n";
}

template <typename F>
void foo(F& f) { // f is a reference to the function
    f();         // Call the referenced function
}

int main() {
    foo(hello);  // Pass function by reference
}
```

**Key Points**:
- The function itself is not copied; only its reference is used.
- A non-const reference cannot bind to an rvalue. You’d need `const F&` if you want to handle such cases.

---

#### **3. Passing Functions by Pointer**
- **Declaration**: Use a pointer parameter of type `F*`, where `F` is a template parameter.
- **Behavior**: The compiler deduces the function type, and the pointer is passed.

**Example**:
```cpp
void hello() {
    std::cout << "Hello World!\n";
}

template <typename F>
void foo(F* f) { // f is a pointer to the function
    f();         // Call the function via the pointer
}

int main() {
    foo(&hello);  // Pass function pointer
}
```

**Key Points**:
- The function address is passed, and the pointer is used to call the function.
- You can also pass the function name directly (without `&`) because the function name **decays** into a pointer.

---

#### **4. Decay of a Function into a Pointer**
- **Decay**: When you pass a function by name, it automatically converts to a pointer to the function.

**Example**:
```cpp
foo(hello);  // Equivalent to foo(&hello);
```

---

### **Passing C-Style Arrays**

#### **1. Ways to Pass Arrays**
A C-style array can be passed:
- **By Reference**: The parameter type is `A&`, where `A` is a template parameter.
- **By Pointer**: The parameter type is `A*`, where `A` is a template parameter.
- **Not by Value**: Arrays cannot be passed as values (only their addresses can be passed).

---

#### **2. Passing Arrays by Reference**
- **Declaration**: Use a reference parameter of type `A&`, where `A` is a template parameter.
- **Behavior**: The compiler deduces the array type, including its size.

**Example**:
```cpp
template <typename A>
void foo(A& a) {  // Reference to the entire array
    std::cout << "Array passed by reference\n";
}

int main() {
    int arr[] = {1, 2, 3};
    foo(arr);  // Pass the whole array by reference
}
```

**Key Points**:
- The size of the array is preserved during deduction.
- Modifying `a` directly affects the original array.

---

#### **3. Passing Arrays by Pointer**
- **Declaration**: Use a pointer parameter of type `A*`, where `A` is a template parameter.
- **Behavior**: The compiler deduces the array's element type, but the size is not preserved.

**Example**:
```cpp
template <typename A>
void foo(A* a) {  // Pointer to the first element of the array
    std::cout << "Array passed by pointer\n";
}

int main() {
    int arr[] = {1, 2, 3};
    foo(arr);  // Pass the array as a pointer to its first element
}
```

**Key Points**:
- The array decays into a pointer to its first element.
- You lose the size information of the array.

---

#### **4. Decay of an Array into a Pointer**
- **Decay**: When you pass an array name, it automatically converts to a pointer to its first element.

**Example**:
```cpp
int arr[] = {1, 2, 3};
foo(arr);  // Equivalent to foo(&arr[0]);
```

---

### **Value Argument Deduction**

#### **1. What is Value Argument Deduction?**
- **Definition**: The compiler deduces the value of a template parameter directly from the function argument.
- **Applicable to**:
    - C-style arrays.
    - Template types (e.g., `std::array`).

#### **2. Passing C-Style Arrays**
- The size of the array can be deduced as part of the type.

**Example**:
```cpp
template <typename T, std::size_t N>
void foo(const T (&arr)[N]) {  // Array size N is deduced
    std::cout << "Array size: " << N << "\n";
}

int main() {
    int arr[] = {1, 2, 3};
    foo(arr);  // N is deduced as 3
}
```

#### **3. Passing Template Types**
- Template types like `std::array` can also be used for value argument deduction.

**Example**:
```cpp
#include <array>

template <typename T, std::size_t N>
void foo(const std::array<T, N>& arr) {  // N is deduced
    std::cout << "Array size: " << N << "\n";
}

int main() {
    foo(std::array<int, 3>{1, 2, 3});  // N is deduced as 3
}
```

---

### **Multiple Template Function Parameters**

#### **1. How Deductions Work**
- When a function has multiple template parameters, deduction is performed independently for each parameter.

**Key Rule**: If a parameter is deduced more than once, all deductions must agree. Otherwise, deduction fails.

#### **2. Example**
```cpp
template <typename T>
T max(const T& a, const T& b) {
    return a > b ? a : b;
}

int main() {
    max(1, 2);    // Works: Both arguments are `int`.
    max(1.0, 2);  // Fails: Arguments are of different types.
}
```

---

### **Key Takeaways**
1. Functions can be passed by reference or pointer, but not by value.
2. Arrays can be passed by reference or pointer, with or without decay into a pointer.
3. Template deduction works by analyzing types and values, respecting strict rules about qualifiers and conversions.
4. For multiple parameters, consistency in deductions is critical for success.