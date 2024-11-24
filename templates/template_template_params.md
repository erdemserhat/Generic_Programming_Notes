### **Notes on Template Template Parameters**

```cpp
#include <array>
#include <iostream>

using namespace std;

template <template <typename, long unsigned> typename C, typename T>
void
foo(T t)
{
  cout << __PRETTY_FUNCTION__ << endl;
  C<T, 1> c1 = {t};
  C<T, 2> c2 = {t, t};
}

int
main()
{
  foo<array>(1);

  // This is cool: pointer to an instantiated function template.  We
  // instantiate the function right here, because we point to it.
  void (*fp)(double) = foo<array, double>;
  fp(.1);
}
```

---

### **1. What Are Template Template Parameters?**
Template template parameters allow a template (like `foo` in the code) to accept another template as an argument. In this code:
```cpp
template <template <typename, long unsigned> typename C, typename T>
void foo(T t);
```
- **`C`**: A template template parameter. It represents a template (e.g., `std::array`) that takes two parameters:
    1. A type (e.g., `int`, `double`).
    2. A non-type parameter (e.g., the size of the array).
- **`T`**: A type parameter that represents the element type of `C`.

---

### **2. Code Behavior**

#### **Template Function: `foo`**
```cpp
template <template <typename, long unsigned> typename C, typename T>
void foo(T t) {
    cout << __PRETTY_FUNCTION__ << endl; // Prints the function's signature
    C<T, 1> c1 = {t};                   // Creates a container C with 1 element
    C<T, 2> c2 = {t, t};                // Creates a container C with 2 elements
}
```

1. **`C<T, 1>`**:
    - Creates an instance of the template `C` with element type `T` and size `1`.
2. **`C<T, 2>`**:
    - Creates an instance of the template `C` with element type `T` and size `2`.
3. **`__PRETTY_FUNCTION__`**:
    - Outputs the complete signature of the instantiated function for debugging purposes.

#### **Function Call: `foo<array>(1)`**
```cpp
foo<array>(1);
```
1. `C` is explicitly set to `std::array`.
2. `T` is deduced from the argument `1` as `int`.
3. The compiler instantiates the function:
   ```cpp
   void foo<std::array, int>(int t);
   ```
4. **Result**:
    - Creates:
        - `std::array<int, 1> c1 = {1};`
        - `std::array<int, 2> c2 = {1, 1};`
    - Prints the function signature via `__PRETTY_FUNCTION__`.

---

#### **Function Pointer: `fp`**
```cpp
void (*fp)(double) = foo<array, double>;
fp(.1);
```

1. **What Happens**:
    - `foo<array, double>` is instantiated explicitly:
      ```cpp
      void foo<std::array, double>(double t);
      ```
    - A function pointer `fp` is created to point to this specific instantiation.
    - Calling `fp(.1)` dynamically calls the instantiated function.

2. **Why This Works**:
    - `fp` matches the function signature:
        - Return type: `void`.
        - Argument: `double`.
    - This is possible because the template `foo` is explicitly instantiated for `<array, double>`.

3. **Output**:
   ```
   void foo<std::array, double>(T) [with C = std::array; T = double]
   ```

---

### **3. Key Concepts Demonstrated**

#### **Template Template Parameters**
- `template <template <typename, long unsigned> typename C>`:
    - Allows `foo` to accept a template like `std::array` that takes two parameters:
        1. The type of the elements (`T`).
        2. The size of the container (`long unsigned`).

#### **Template Argument Deduction**
- `foo<array>(1)`:
    - Explicitly specifies `C = std::array`.
    - Deduces `T = int` from the argument `1`.

#### **Explicit Instantiation**
- `void (*fp)(double) = foo<array, double>;`:
    - Instantiates `foo` with `C = std::array` and `T = double`.
    - Assigns the instantiated function to a function pointer.

---

### **4. Advantages of This Approach**

1. **Generic Code**:
    - `foo` can work with any container template like `std::array` or custom templates with similar signatures.

2. **Runtime Flexibility**:
    - Using function pointers (`fp`) enables dynamic function calls to specific template instantiations.

3. **Compile-Time Safety**:
    - Ensures correctness of template instantiations and avoids runtime errors.

---

### **5. Output Example**
For the provided code:
```cpp
foo<array>(1);
fp(.1);
```

**Output:**
```
void foo<std::array, int>(T) [with C = std::array; T = int]
void foo<std::array, double>(T) [with C = std::array; T = double]
```

---

### **6. Key Takeaways**
- **Template template parameters** allow passing templates (e.g., `std::array`) to functions.
- Template argument deduction simplifies usage by automatically determining types from arguments.
- You can explicitly instantiate a template function and assign it to a function pointer for dynamic calls.