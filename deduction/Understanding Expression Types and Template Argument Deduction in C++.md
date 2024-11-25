### **Understanding Expression Types and Template Argument Deduction in C++**

---

#### **Type of Expression**
- Every expression in C++ has a **non-reference type**.
- Even if the expression is the name of a reference, the type of the expression is non-referential.
- **Compiler Behavior**: The compiler removes the highest-level `&` declarator from the type of the expression before further processing, as per the C++ standard ([expr.type]).

---

#### **Types of Template Arguments**
Template arguments can be deduced by the compiler for various kinds of template parameters:
1. **Type Arguments**
2. **Value Arguments**
3. **Template Arguments**

---

#### **Type Argument Deduction**
- A **type argument** is deduced for typical template parameters.
- This process is more complex than value or template parameter deduction because it considers both:
    1. The **types of function parameters**.
    2. The **types of function call arguments**.

##### **Types of Function Parameters**
- **Regular types**: Non-pointer and non-reference types used for pass-by-value.
- **Pointer types**: Used for pass-by-pointer (essentially pass-by-value for the pointer itself).
- **Reference types**: Used for pass-by-reference.

##### **Types of Function Call Arguments**
- **Function types**: Represent callable objects or functions passed as arguments.
- **Array types**: Arrays passed to functions, which may decay to pointers.

---

#### **Rules for Deduction**
1. **General Rule**: The deduced type of a function parameter may differ from the type of the function call argument.
    - This difference is limited to **top-level qualifiers** (e.g., `const`, `volatile`) or **declarators** (e.g., `*`, `&`).
2. **Never Reference**: The deduced type for a template parameter is never a reference type because function arguments are always of non-reference types.

---

#### **Example**

```cpp
#include <iostream>

template <typename T>
void foo(T t) {
    std::cout << "Type deduced: " << __PRETTY_FUNCTION__ << std::endl;
}

int main() {
    int a = 10;
    const int b = 20;
    volatile int c = 30;

    foo(a); // T deduced as int
    foo(b); // T deduced as const int
    foo(c); // T deduced as volatile int
}
```

**Explanation**:
- When passing `a`, the deduced type is `int`.
- When passing `b`, the deduced type includes the `const` qualifier: `const int`.
- When passing `c`, the deduced type includes the `volatile` qualifier: `volatile int`.

---

