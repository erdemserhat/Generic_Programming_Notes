### What is a Pointer?
A pointer is a **variable that stores the memory address of another variable**. Instead of holding a value directly, a pointer points to the location in memory where a value is stored.

### Key Concepts
1. **Declaring a Pointer:**
   ```cpp
   int* ptr;  // Declares a pointer to an int
   ```
    - The `*` indicates that `ptr` is a pointer.
    - By itself, the pointer doesn't hold any valid address until it's assigned.

2. **Assigning a Pointer:**
   ```cpp
   int a = 10;
   int* ptr = &a;  // `&a` gives the address of `a`
   ```
    - The `&` operator retrieves the memory address of `a`.
    - Now, `ptr` points to `a`.

3. **Dereferencing a Pointer:**
   ```cpp
   cout << *ptr;  // Outputs the value at the memory address stored in `ptr` (10)
   ```
    - The `*` (dereference operator) accesses the value stored at the memory address.

---

### Pointer Operations
1. **Access Address of a Variable:**
   ```cpp
   int a = 10;
   cout << &a;  // Prints the memory address of `a`
   ```

2. **Access Value via Pointer:**
   ```cpp
   int a = 10;
   int* ptr = &a;
   cout << *ptr;  // Prints 10 (value of `a`)
   ```

3. **Modify Value via Pointer:**
   ```cpp
   int a = 10;
   int* ptr = &a;
   *ptr = 20;  // Changes the value of `a` to 20
   cout << a;  // Prints 20
   ```

---

### Example:
```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 5;
    int* p = &a;  // Pointer `p` stores the address of `a`

    cout << "Address of a: " << p << endl;  // Prints address of `a`
    cout << "Value of a using pointer: " << *p << endl;  // Prints 5

    *p = 10;  // Change the value of `a` using the pointer
    cout << "New value of a: " << a << endl;  // Prints 10

    return 0;
}
```

---

### Key Points:
1. **Pointer Declaration:**
    - `int* p;` declares `p` as a pointer to an integer.

2. **Assigning Address:**
    - `p = &a;` assigns the address of `a` to `p`.

3. **Dereferencing:**
    - `*p` gives the value stored at the memory address `p`.

4. **Null Pointer:**
   A pointer can be set to `nullptr` if it doesn’t point to any memory address.
   ```cpp
   int* p = nullptr;  // Safe to initialize when no address is assigned yet
   ```

---
