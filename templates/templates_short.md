### **Note on Templates in C++**

#### **Conclusion**
- Templates are the foundation of **generic programming** in C++.
- They allow the creation of code that works with **multiple data types** or configurations without duplicating logic.
- **Three kinds of template parameters**:
    1. **Type Parameters**: Represent types (e.g., `int`, `float`, or user-defined types).
    2. **Value Parameters**: Represent constant values (e.g., integers, sizes).
    3. **Template Parameters**: Represent other templates (e.g., `std::vector`).
- Among templates, **function templates** are particularly powerful and complex due to their ability to deduce arguments and perform type transformations.

---

### **Quiz Answers**

#### **1. What is the type template parameter?**
A **type template parameter** is a placeholder for a data type in a template. It allows the template to operate generically with different types.

**Example**:
```cpp
template <typename T> // T is a type template parameter
T add(T a, T b) {
    return a + b;
}
```
Here, `T` can represent any data type (e.g., `int`, `double`, `std::string`).

---

#### **2. What can a template be of?**
A template can be of:
1. **Function**:
    - A generic function that operates on different types or configurations.
   ```cpp
   template <typename T>
   T multiply(T a, T b) {
       return a * b;
   }
   ```

2. **Class/Struct**:
    - A generic class or struct that supports different types or values.
   ```cpp
   template <typename T>
   class Container {
       T value;
   public:
       Container(T v) : value(v) {}
       T getValue() { return value; }
   };
   ```

3. **Alias**:
    - A shorthand for a complex type.
   ```cpp
   template <typename T>
   using Vec = std::vector<T>;
   ```

4. **Variable** (since C++14):
    - A constant variable template.
   ```cpp
   template <typename T>
   constexpr T pi = T(3.1415926535897932385);
   ```

---

#### **3. Template Argument vs Parameter**

1. **Template Parameter**:
    - A placeholder defined in the template declaration.
    - It specifies what kind of arguments the template expects.
   ```cpp
   template <typename T, int N> // T and N are parameters
   void func();
   ```

2. **Template Argument**:
    - The actual value or type provided when instantiating the template.
   ```cpp
   func<int, 10>(); // int and 10 are arguments
   ```

---

### **Summary Table**

| **Concept**            | **Definition**                                                | **Example**                            |
|-------------------------|--------------------------------------------------------------|----------------------------------------|
| Type Template Parameter | Placeholder for a type in a template                         | `template<typename T>`                 |
| Value Template Parameter| Placeholder for a constant value in a template               | `template<int N>`                      |
| Template Template Parameter| Placeholder for a template in a template                 | `template<template<typename> class C>`|
| Parameter vs Argument   | Parameters are placeholders; arguments are actual values/types| `T` is a parameter, `int` is an argument|

