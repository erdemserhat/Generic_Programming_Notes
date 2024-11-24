*POSITION OF CONST*
---

### 1. **`const` Before the `*`: The Data is Constant**
```cpp
const int* ptr;  // Or: int const* ptr;
```
- **What it means:**
    - The value being pointed to by `ptr` is constant (cannot be changed through `ptr`).
    - The pointer `ptr` itself can point to a different address.

- **Example:**
  ```cpp
  int a = 10, b = 20;
  const int* ptr = &a;  // Pointer to a constant int
  *ptr = 30;            // Error: cannot modify value through ptr
  ptr = &b;             // Allowed: ptr can point to a different address
  ```

---

### 2. **`const` After the `*`: The Pointer is Constant**
```cpp
int* const ptr;
```
- **What it means:**
    - The pointer `ptr` is constant (cannot point to a different address).
    - The value being pointed to can be modified.

- **Example:**
  ```cpp
  int a = 10, b = 20;
  int* const ptr = &a;  // Constant pointer to an int
  *ptr = 30;            // Allowed: can modify the value at `a` through ptr
  ptr = &b;             // Error: cannot change the address stored in ptr
  ```

---

### 3. **`const` Before and After the `*`: Both are Constant**
```cpp
const int* const ptr;  // Or: int const* const ptr;
```
- **What it means:**
    - The value being pointed to is constant (cannot be modified).
    - The pointer itself is constant (cannot point to another address).

- **Example:**
  ```cpp
  int a = 10, b = 20;
  const int* const ptr = &a;  // Constant pointer to a constant int
  *ptr = 30;                 // Error: cannot modify value
  ptr = &b;                  // Error: cannot change the address
  ```

---

### Quick Summary Table:
| **Expression**             | **What is Constant?**                  | **What Can Change?**            |
|----------------------------|----------------------------------------|----------------------------------|
| `const int* ptr`           | The value being pointed to is constant | The pointer can change addresses |
| `int* const ptr`           | The pointer itself is constant         | The value being pointed to       |
| `const int* const ptr`     | Both the value and the pointer are constant | Neither can change               |

---

By knowing this distinction, you can control immutability for both the pointer and the data it points to. Let me know if you'd like further clarification or examples!