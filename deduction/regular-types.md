This section is about **regular types** (non-pointer, non-reference types) and how qualifiers like `const` and `volatile` affect their behavior. 

---

### **What Are Regular Types?**

A **regular type** is a type that does not involve pointers (`*`) or references (`&`). For example:
- `int`, `float`, `char` are regular types.
- They can have qualifiers like `const` or `volatile`.

#### **Qualifiers for Regular Types**
Qualifiers:
- **`const`**: Means the value cannot be modified after initialization.
- **`volatile`**: Indicates that the value can be changed outside the program's control (e.g., hardware interaction), so the compiler should not optimize access to it.

Both qualifiers are **compile-time features**:
- **`const`** prevents modification of the variable.
- **`volatile`** prevents the compiler from optimizing access.

---

### **Position of Qualifiers**
Qualifiers can appear before or after the type name, but they mean the same thing:
- `const int` and `int const` are equivalent.

Example:
```cpp
const int x = 10; // Same as int const x = 10;
```

---

### **Flexibility in Initialization**

The compiler allows initializing a variable or parameter with an expression, even if their types differ **only** by qualifiers. This is because qualifiers like `const` and `volatile` affect the variable itself, not the value being copied.

Example:
```cpp
int a1 = 1;
const int a2 = 2;
volatile int a3 = 3;
const volatile int a4 = 4;

int b1 = a4;            // Qualifiers are stripped during initialization.
const int b2 = a3;      // `a3`'s volatile qualifier is ignored here.
volatile int b3 = a2;   // `a2`'s const qualifier is ignored here.
const volatile int b4 = a1; // `a1` has no qualifiers, but can be assigned to b4.
```

The **compiler allows this flexibility** because it treats the values being assigned, not the qualifiers of the source variables.

---

### **How This Applies to Function Parameters**

This flexibility also applies to **function parameters**. When you pass arguments to a function, their qualifiers are ignored, and the function parameter is initialized with the value.

---

### **Restriction: No Overloading Based on Qualifiers**
Functions **cannot** be overloaded based solely on qualifiers for **regular types**. The reason is that qualifiers are ignored during parameter initialization, so two functions with parameters that differ only by qualifiers will have the **same signature**.

#### Example:

```cpp
void foo(int) {}         // Function with a regular int parameter.

// The following is NOT allowed because it has the same signature as the above:
// void foo(const int) {}
```

Since qualifiers are ignored during linkage, the two functions would conflict.

---

### **Why Are Qualifiers Removed?**

Qualifiers are **irrelevant to the function caller**. They only matter inside the function implementation, so the compiler removes them from the function's **signature** to enable proper linkage.

#### Checking with `nm`
Using the `nm` command, you can inspect the binary's symbol table. Functions differing only by qualifiers will have the **same symbol**.

---

### **Pointers to Functions**

You can assign a function pointer to functions with or without qualifiers in their parameters. Since the qualifiers are ignored, the pointer can refer to either version.

#### Example:

```cpp
void foo(int) {}         // Function with regular int parameter.

// Function pointer can point to foo with or without qualifiers:
void (*fp1)(int) = foo;
void (*fp2)(const int) = foo;
```

---

### **Key Takeaways**
1. Qualifiers like `const` and `volatile` affect how variables are handled **inside a function**, but they are ignored when passing arguments or linking functions.
2. Regular types allow initialization with expressions even if their qualifiers differ.
3. Functions cannot be overloaded based on qualifiers for regular types because qualifiers are stripped from the function signature during compilation.