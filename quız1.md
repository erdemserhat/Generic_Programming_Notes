### **Quiz Answers**

#### **1. Does generic programming in C++ suffer performance loss?**
- **No**, generic programming in C++ does not suffer from performance loss.
    - Templates in C++ are resolved at **compile-time**, which means the compiler generates optimized, type-specific code for each instance of a template.
    - This approach avoids any runtime overhead, making it as fast as hand-written, type-specific code.

---

#### **2. What’s the difference between static and dynamic polymorphism?**

| **Feature**               | **Static Polymorphism**                  | **Dynamic Polymorphism**                |
|----------------------------|------------------------------------------|-----------------------------------------|
| **Timing**                | Happens at **compile-time**.             | Happens at **runtime**.                 |
| **Mechanism**             | Achieved via **templates** or **overloading**. | Achieved via **virtual functions** and **vtable**. |
| **Flexibility**           | Works with **any type** (class and non-class types). | Works only with **class types**.        |
| **Performance**           | **No runtime overhead**.                 | **Slower** due to runtime function lookup. |

---

#### **3. What data types can we use in generic programming?**
- Generic programming in C++ can work with **any data type**, including:
    - **Primitive types:** `int`, `float`, `char`, etc.
    - **User-defined types:** Classes, structs, etc.
    - **Pointers and references.**
    - **Standard library types:** `std::vector`, `std::string`, etc.
- The only requirement is that the type must support the operations used in the template (e.g., `operator+`, `operator<<`, etc.).

---

