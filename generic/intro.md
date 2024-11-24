
---

## **C++ Concepts Demonstrated in the Code**

### **1. Basic Functions**
- Functions returning different types:
  ```cpp
  void exampleVoidFunction();       // Returns nothing
  double exampleDoubleFunction();  // Returns a double
  std::string exampleStringFunction();  // Returns a string
  char exampleCharFunction();      // Returns a char
  ```

- Example:
  ```cpp
  double exampleDoubleFunction() {
      return 1.0;  // Returns a double value
  }
  ```

### **2. Regular Function**
- Summation function with fixed types:
  ```cpp
  int sum(int a, int b) {
      return a + b;  // Adds two integers
  }
  ```

---

### **3. Function Templates**
- A generic function that works with multiple data types.
  ```cpp
  template <typename T>
  T sumTemplate(T a, T b) {
      return a + b;
  }
  ```

- Example:
  ```cpp
  std::cout << sumTemplate(1.2, 1.2) << std::endl;  // Output: 2.4
  ```

---

### **4. Template Functions for Iteration**
- A template function to print an element `N` times:
  ```cpp
  template <typename T>
  void printTemplate(T t, const int N) {
      for (int i = 0; i < N; i++) {
          std::cout << t << std::endl;
      }
  }
  ```

- Example:
  ```cpp
  printTemplate("Hello", 3);  // Prints "Hello" three times
  ```

---

### **5. Printing with Templates**
- Generic print function:
  ```cpp
  template<typename T>
  void print(T a) {
      std::cout << a << std::endl;
  }
  ```

---

### **6. Special Templates with Non-Type Parameters**
- Template with a `char` parameter:
  ```cpp
  template <char N, typename T>
  void printSpecial(char a, T b) {
      std::cout << a << b << std::endl;
  }
  ```

---

### **7. Template Classes**
- Example of a generic class:
  ```cpp
  template <typename T>
  class Example {
  public:
      T a;

      void print() {
          std::cout << a << std::endl;
      }
  };
  ```

- Example Usage:
  ```cpp
  Example<double> obj;
  obj.a = 1.0;
  obj.print();  // Outputs: 1.0
  ```

---

### **8. STL Example with `std::vector`**
- Sorting and iterating through a vector:
  ```cpp
  std::vector<double> v {1.0, 1.1, 1.2};
  sort(v.begin(), v.end());  // Sorts the vector

  for(const auto &e: v)
      std::cout << e << std::endl;
  ```

---

### **9. Pointer Basics**
- **Definition:** A pointer stores the memory address of another variable.
  ```cpp
  int a = 10;
  int* ptr = &a;  // `ptr` points to `a`
  std::cout << *ptr;  // Outputs the value of `a`
  ```

- **Modifying Values via Pointers:**
  ```cpp
  *ptr = 20;  // Changes the value of `a` to 20
  ```

---

### **10. Pointers with `const`**
#### Case 1: Pointer to a `const` Value
- The value being pointed to cannot be changed:
  ```cpp
  const int* ptr = &a;  // Pointer to a constant int
  *ptr = 30;  // Error: cannot modify the value
  ptr = &b;   // Allowed: can point to another address
  ```

#### Case 2: Constant Pointer
- The pointer itself cannot point to another address:
  ```cpp
  int* const ptr = &a;  // Constant pointer to an int
  *ptr = 30;  // Allowed: can modify the value
  ptr = &b;   // Error: cannot change the address
  ```

#### Case 3: Constant Pointer to a Constant Value
- Neither the value nor the pointer can change:
  ```cpp
  const int* const ptr = &a;
  *ptr = 30;  // Error: cannot modify the value
  ptr = &b;   // Error: cannot change the address
  ```

---

### **11. Dynamically Allocating Memory**
- Allocating and modifying memory with pointers:
  ```cpp
  int* a = new int;
  *a = 10;
  std::cout << *a << std::endl;  // Outputs: 10
  delete a;  // Free the allocated memory
  ```

---

### **12. Null Pointers**
- A pointer that points to "nothing":
  ```cpp
  int* ptr = nullptr;
  ```

---

### **13. Miscellaneous Notes**
- **STL Iteration:**
  Use range-based for loops for simplicity:
  ```cpp
  std::vector<int> list {1, 2, 3, 4};
  for(const auto &e : list)
      std::cout << e << std::endl;
  ```

- **Understanding References:**
  References act as aliases for variables, enabling direct modification of the original data:
  ```cpp
  int a = 10;
  int& ref = a;
  ref = 20;  // Modifies `a` directly
  ```

---
