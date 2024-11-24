### **C++ Notes on Value Types and `const`**

---

### **1. Value Types in C++**

C++ categorizes values into different types based on their characteristics and behavior. Here’s a summary:

#### **Lvalues (Locator Values)**
- Refers to objects with a specific memory location.
- Can appear on the **left-hand side** of an assignment.
- Examples:
  ```cpp
  int x = 10;   // 'x' is an lvalue.
  x = 20;       // Valid: lvalues can be modified.
  ```

#### **Rvalues (Right-Hand Side Values)**
- Temporary objects without a persistent memory location.
- Cannot appear on the left-hand side of an assignment.
- Examples:
  ```cpp
  int y = 5 + 10; // '5 + 10' is an rvalue (temporary result of addition).
  ```

#### **Prvalues (Pure Rvalues)**
- Subset of rvalues representing temporary values (e.g., literals or the result of expressions).
- Example:
  ```cpp
  int z = 10;      // '10' is a prvalue.
  int sum = x + y; // 'x + y' is a prvalue.
  
  ```

#### **Xvalues (Expiring Values)**
- Subset of rvalues representing objects about to expire (used in move semantics).
- Example:
  ```cpp
  int &&ref = std::move(x); // `std::move(x)` is an xvalue.
  ```

#### **Glvalues (Generalized Lvalues)**
- Includes both lvalues and xvalues (i.e., anything with a memory address).

#### **Rvalues Summary**
- **Rvalues = Prvalues + Xvalues**.
- Rvalues are typically temporary and cannot be assigned to directly.

---

### **2. `const` in C++**

`const` is a keyword used to indicate immutability. It can be applied to variables, pointers, references, and member functions.

#### **2.1. `const` with Variables**
- A `const` variable cannot be modified after initialization.
- Example:
  ```cpp
  const int a = 10; // 'a' cannot be changed.
  a = 20;           // Error: 'a' is read-only.
  ```

---

#### **2.2. `const` with Pointers**
- **Pointer to a `const` value**: You can’t modify the value being pointed to.
  ```cpp
  const int *ptr = &a; // The value at 'a' cannot be modified via 'ptr'.
  *ptr = 20;           // Error!
  ```

- **`const` pointer**: You can’t change the pointer itself.
  ```cpp
  int *const ptr = &a; // The pointer cannot point to another location.
  ptr = &b;            // Error!
  ```

- **`const` pointer to a `const` value**:
  ```cpp
  const int *const ptr = &a; // Neither the value nor the pointer can change.
  ```

---

#### **2.3. `const` with References**
- A reference to a `const` value can bind to rvalues or lvalues but cannot modify the referred value.
- Example:
  ```cpp
  const int &ref = 10; // 'ref' is a reference to a rvalue.
  ref = 20;           // Error: Cannot modify the value.
  ```

---

#### **2.4. `const` with Function Parameters**
- Use `const` to ensure function parameters are not modified:
  ```cpp
  void print(const std::string &str) {
      std::cout << str << std::endl;
  }
  ```

---

#### **2.5. `const` Member Functions**
- Member functions marked `const` cannot modify the object they are called on.
- Example:
  ```cpp
  class Box {
      int value;
  public:
      int getValue() const { return value; } // 'const' ensures 'value' is read-only.
  };
  ```

---

### **3. Combining Value Types and `const`**

#### Rvalues and `const`
- Rvalues can bind to `const` references.
- Example:
  ```cpp
  const int &ref = 10;  // OK: Rvalue binds to 'const int &'.
  ```

#### Lvalues and `const`
- Lvalues can bind to `const` references or `const` pointers.
- Example:
  ```cpp
  int x = 5;
  const int &ref = x;  // OK: Lvalue 'x' binds to 'const int &'.
  ```

---

### **4. Summary Table**

| **Value Type**       | **Can Bind to `T &`** | **Can Bind to `const T &`** | **Can Bind to `T &&`** |
|-----------------------|-----------------------|-----------------------------|-------------------------|
| **Lvalue**            | Yes                  | Yes                         | No                      |
| **Rvalue**            | No                   | Yes                         | Yes                     |
| **Prvalue**           | No                   | Yes                         | Yes                     |
| **Xvalue**            | No                   | Yes                         | Yes                     |

---

### **Key Notes**
1. Use `const T &` to allow both lvalues and rvalues in function parameters.
2. Use `T &&` for move semantics (binding to rvalues).
3. Rvalues are temporary values, while lvalues have a specific memory location.

---

