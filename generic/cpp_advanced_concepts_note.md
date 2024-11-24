
# C++ Concepts: Virtual Functions, `const` in Overriding, `struct` vs `class`, and Named vs Unnamed Parameters

---

## **1. Virtual Functions**

A **virtual function** in C++ allows derived classes to override functions in the base class, enabling **runtime polymorphism** (dynamic dispatch).

### **Key Characteristics of Virtual Functions**
- Declared with the `virtual` keyword in the base class.
- The derived class can override the function by providing its own implementation.
- The correct function is determined at **runtime**, based on the actual object type.

### **How Virtual Functions Work**
- The compiler generates a **vtable** (virtual table), which is a table of pointers to virtual functions.
- Each object of a class with virtual functions has a pointer to the vtable.

### **Example**
```cpp
#include <iostream>
using namespace std;

class Base {
public:
    virtual void display() {  // Virtual function
        cout << "Base display" << endl;
    }
};

class Derived : public Base {
public:
    void display() override {  // Overriding the virtual function
        cout << "Derived display" << endl;
    }
};

int main() {
    Base* obj = new Derived();  // Base pointer to Derived object
    obj->display();  // Outputs: "Derived display" (runtime resolution)

    delete obj;
    return 0;
}
```

### **Key Benefits**
- Enables **runtime polymorphism**.
- Allows for flexible and extensible code design.

---

## **2. `const` Keyword When Overriding Functions**

### **Purpose of `const` for Member Functions**
- Marks a function as read-only, meaning it **cannot modify the object** it is called on.
- Used for functions that only inspect the object, like getters or display methods.

### **Why Use `const` When Overriding**
1. **Match the Base Class Signature:**
   - If the base class declares a function as `const`, the derived class must also declare it as `const` to properly override it.

2. **Avoiding Errors:**
   - Without `const`, the compiler treats the derived function as a separate function, not an override.

3. **Access with `const` Objects:**
   - Only `const` member functions can be called on `const` objects or references.

### **Example**
```cpp
#include <iostream>
using namespace std;

class Base {
public:
    virtual void display() const {  // Virtual function marked as const
        cout << "Base display" << endl;
    }
};

class Derived : public Base {
public:
    void display() const override {  // Must also be const to override
        cout << "Derived display" << endl;
    }
};

int main() {
    const Base* obj = new Derived();  // Pointer to const object
    obj->display();  // Outputs: "Derived display"

    delete obj;
    return 0;
}
```

### **What Happens Without `const`?**
If `const` is omitted in the derived class, the function does not override the base class function:
```cpp
class Derived : public Base {
public:
    void display() {  // Missing const
        cout << "Derived display" << endl;
    }
};
```
- The `Derived` function is treated as a **new function** and not an override.

---

## **3. `struct` vs `class`**

Both `struct` and `class` are used to define user-defined types in C++. The primary difference lies in **default access levels**.

### **Key Differences**
| **Feature**             | **`struct`**                      | **`class`**                       |
|--------------------------|------------------------------------|------------------------------------|
| **Default Access Level** | Members are `public` by default.  | Members are `private` by default. |
| **Purpose/Use Case**     | Simple data structures or POD types. | Encapsulation and behavior-rich types. |
| **Inheritance**          | Public by default.                | Private by default.                |

### **When to Use `struct`**
- For **plain data structures** or lightweight types.
- When members are intended to be public.

### **When to Use `class`**
- For encapsulating **private data** with public behavior.
- For **object-oriented programming** with inheritance or polymorphism.

### **Examples**
```cpp
// struct Example
struct Point {
    int x;
    int y;

    void print() const {
        std::cout << "Point(" << x << ", " << y << ")" << std::endl;
    }
};

// class Example
class Account {
private:
    double balance;

public:
    Account(double initialBalance) : balance(initialBalance) {}

    void deposit(double amount) {
        balance += amount;
    }

    double getBalance() const {
        return balance;
    }
};
```

---

## **4. Named vs Unnamed Parameters**

In function definitions, parameters can be **named** or **unnamed**.

### **Named Parameters**
- A parameter is named when you need to use it inside the function body.

**Example:**
```cpp
void foo(const int &i) {
    std::cout << i << std::endl;  // Using the named parameter i
}
```

### **Unnamed Parameters**
- A parameter can remain unnamed if it is not used in the function body.
- Commonly used when overloading functions for type-based behavior.

**Example:**
```cpp
void foo(const A &) {  // Unnamed parameter
    std::cout << "Function foo: A" << std::endl;
}
```

### **Why Use Unnamed Parameters?**
- Signals that the parameter is intentionally unused.
- Avoids compiler warnings about unused variables.
- Keeps the code concise.

### **When to Use Named vs Unnamed Parameters**
| **Use Named**              | **Use Unnamed**                   |
|-----------------------------|-----------------------------------|
| When the parameter is used. | When the parameter is unused.    |
| To improve code readability. | To signal intent and avoid warnings. |

---

## **Conclusion**
- **Virtual Functions:** Enable runtime polymorphism but require `virtual` in the base class.
- **`const` in Overriding:** Ensures consistency with the base class signature and allows usage with `const` objects.
- **`struct` vs `class`:** Use `struct` for simple, public data structures; use `class` for encapsulation and object-oriented design.
- **Named vs Unnamed Parameters:** Name parameters when they are used; leave them unnamed when they are not required.


