
### **Title: Template Argument Deduction**

---

### **Introduction**

Template arguments are inferred for our convenience, so they do not have to be explicitly provided, avoiding mistakes in the process. The compiler infers template arguments in the following cases:

- Calling a non-member function template (the most common and simplest case),
- Calling a member function template (including constructors),
- Initializing a variable of type `auto` (including function parameters and return values).

---

### **Basics of Deduction**

We will discuss deduction using a non-member function template as an example. For a **function template call**, the compiler must concretize the **function template**, i.e., generate the function code from the function template based on its arguments.

The compiler infers the arguments for the template (function) based on:

- **Types** of the function parameters,
- **Types and categories** of the arguments in the function call.

---

### **Simplest Case**

In the simplest case, we call a function with one parameter:

```cpp
template <parameter list>
void foo(ParameterType t)
{
  // Body of a function template.
}

int main()
{
  foo(expr);
}
```

The compiler must infer the arguments for the parameters (those in `parameter list`) of the function template `foo` based on the expression `expr` and the type `ParameterType` of the parameter `t` in the function `foo`.

For deduction to occur, the type `ParameterType` must depend on (use in its definition) at least one template parameter. There are many ways to define `ParameterType` in terms of template parameters, and we will discuss the most important ones.

---

### **Basic Rule with Restriction**

**Rule**: The deduced template argument must allow the parameter to be initialized by the argument.

Initialization always occurs based on the argument (explicit or default) of the function.

**Restriction**: Initialization must occur without type conversion.

This refers to the conversion of the type of the function argument into the type of the function parameter. For non-template functions, this restriction does not apply (conversions are allowed there).

Initialization of the parameter `t` in the simplest case above looks like this:

```cpp
ParameterType t = expr;
```

The compiler must infer the arguments for the template parameters used in the definition of `ParameterType` so that the initialization is possible without a type conversion. This may prove impossible, preventing the concretization of the template.

For example, if `ParameterType` is a reference type to a constant object of type `T`, where `T` is a template parameter, and the function argument is `1`, the initialization looks like this:

```cpp
const T &t = 1;
```

The deduced argument will be `T = int`, because this initialization is possible without a type conversion. However, if `ParameterType` is a reference type to a non-constant object of type `T`, the initialization looks like this:

```cpp
T &t = 1;
```

The deduced argument will still be `T = int`, because r-values of built-in types (like the literal `1`) are of non-constant type (as per the standard). Therefore, the concretization will fail, because a non-const l-value reference `t` cannot be initialized by an r-value.

---


### **Highest-Level**

Type qualifiers and declarators can be at the highest level.

#### **Declarators**

The `*` declarator for pointer types and the `&` declarator for reference types can appear in different positions in the type definition. The **highest-level declarator** is the first one from the right-hand side. For example, in the type `int* const&`, the highest-level declarator is `&`.

#### **Qualifiers**

**Highest-level type qualifiers** (`const` and `volatile`) can appear in any type except for reference types.

---

### **Regular Types**

The defined regular type (non-pointer and non-reference) can have the highest-level qualifiers placed either before or after the name of the used type, e.g., `const int` or `int const` (and these are the same types). These qualifiers are significant only at compile time (not during runtime): the compiler cannot allow modification of a `const` type, and access to a `volatile` type cannot be optimized.

**Flexibility:** A variable can be initialized with an initializing expression even if their types (regular) differ only in the highest-level qualifiers because it's simply a matter of copying the value. Example:

```cpp
#include <concepts>

int main()
{
  static_assert(std::same_as<const int, int const>);

  int a1 = 1;
  const int a2 = 2;
  volatile int a3 = 3;
  const volatile int a4 = 4;

  int b1 = a4;
  const int b2 = a3;
  volatile int b3 = a2;
  const volatile int b4 = a1;
}
```

This flexibility also applies to the initialization of a function parameter using a function argument, which leads to a restriction.

**Restriction:** Functions cannot be overloaded based on the qualifiers of a regular type (function parameter) because the initialization of a regular parameter (where flexibility places no restrictions on the qualifiers) cannot influence the choice of overload.

These qualifiers (which are implementation details of the function body) are irrelevant to the function caller and are therefore removed by the compiler from the function's signature (they are not part of the function's interface) to enable linkage. Check (using the `nm` command) the function signatures in the symbol table of the program below.

```cpp
void foo(int)
{
}

// This function has the same signature as the one above, even though their
// parameters differ with the qualifiers.
// void foo(const int)
// {
// }

int main()
{
  const int i = 1;
  foo(i);

  // Can point to a function with a regular parameter that is either
  // non-const or const.
  void (*fp1)(int) = foo;
  void (*fp2)(const int) = foo;
}
```

---

### **Pointer Types**

The qualifiers of a pointer type appear to the right of the highest-level `*` declarator, i.e., at the end of the type definition (or at the beginning when reading from right to left). They apply to the pointer variable, not to the pointed-to data.

As with regular types, a pointer variable can be initialized based on a pointer value even if their types (pointer types) differ in the highest-level qualifiers because the pointer value is simply copied. This is also why functions cannot be overloaded for pointer types (function parameters) that differ only in their highest-level qualifiers. Example:

```cpp
void foo(int *)
{
}

// This function has the same signature as the one above.
// void foo(int * const)
// {
// }

int main()
{
  int i = 1;
  int * const p1 = &i;
  int * p2 = p1;

  foo(p1);
  foo(p2);
}
```

In a pointer type, directly to the left of the highest-level `*` declarator, you can also specify **highest-level qualifiers** for the type of the pointed-to data. These qualifiers can be called **lower-level** if we refer to the pointer type.

**Condition for Pointer Type:** The lower-level qualifiers of a pointer type must include the highest-level qualifiers of the pointed-to data type.

Here is an example:

```cpp
int main()
{
  int a1 = 1;
  const int a2 = 2;
  volatile int a3 = 3;
  const volatile int a4 = 4;

  // The commented lines below would bypass the qualifiers.

  int * p11 = &a1;
  // int * p12 = &a2;
  // int * p13 = &a3;
  // int * p14 = &a4;

  const int * p21 = &a1;
  const int * p22 = &a2;
  // const int * p23 = &a3;
  // const int * p24 = &a4;

  volatile int * p31 = &a1;
  // volatile int * p32 = &a2;
  volatile int * p33 = &a3;
  // volatile int * p34 = &a4;

  const volatile int * p41 = &a1;
  const volatile int * p42 = &a2;
  const volatile int * p43 = &a3;
  const volatile int * p44 = &a4;
}
```

This condition allows functions to be overloaded for pointer types (function parameters) that differ in qualifiers for the type of pointed-to data. It enables overloading based on the type of data the pointer refers to. Here’s an example:

```cpp
#include <iostream>
#include <utility>

void foo(int *)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void foo(const int *)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
  int i = 1;
  foo(&i);
  foo(&std::as_const(i));
}
```

---

### **Reference Types**

A reference either names a given data (e.g., an array element) or is an alias for another variable. A reference type does not have top-level qualifiers because a reference must faithfully represent the type of the data it refers to: a reference expression is replaced by an expression with the data the reference refers to. Moreover, a reference can only be initialized once and cannot later be changed to alias another data, making the `const` qualifier at the top level unnecessary. Thus, for example, the type `int & const` is invalid.

For this reason, functions cannot be overloaded for reference types (function parameters) that would differ only in their top-level qualifiers. Even declaring such a function is impossible if the reference type of its parameter were to have a qualifier.


---

### **Condition for Reference Type**

The **lower-level qualifiers** of the reference type must include the **highest-level qualifiers** of the type of the data it refers to.

Here is an example:

```cpp
int main()
{
  int a1 = 1;
  const int a2 = 2;
  volatile int a3 = 3;
  const volatile int a4 = 4;

  // The commented lines below would bypass the qualifiers.

  int &p11 = a1;
  // int &p12 = a2;
  // int &p13 = a3;
  // int &p14 = a4;

  const int &p21 = a1;
  const int &p22 = a2;
  // const int &p23 = a3;
  // const int &p24 = a4;

  volatile int &p31 = a1;
  // volatile int &p32 = a2;
  volatile int &p33 = a3;
  // volatile int &p34 = a4;

  const volatile int &p41 = a1;
  const volatile int &p42 = a2;
  const volatile int &p43 = a3;
  const volatile int &p44 = a4;
}
```

This condition allows functions to be overloaded for reference types (function parameters) that differ in qualifiers for the type of data the reference refers to. Overloading is based on the type of data referred to. Here is an example:

```cpp
#include <iostream>
#include <utility>

void foo(int &)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void foo(const int &)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
  int i = 1;

  foo(i);
  foo(std::as_const(i));
}
```

---

### **Type of Expression**

Every expression in C++ is of a non-reference type. Therefore, the type of the function argument is non-referential, even if the expression is the name of a reference. According to the standard ([expr.type]), the compiler removes the highest-level `&` declarator from the type of the expression before further processing.

---

### **Types of Arguments**

For each **kind** of template parameter, the compiler can deduce an argument. Most commonly, we want the compiler to deduce type arguments, but it can also deduce value or template arguments.

---

### **Type Argument**

A type argument for a template is deduced for a typical template parameter. This deduction is the most complex (compared to value or template parameter deduction) because it distinguishes between:

- The **types of function parameters**, particularly:
    - **Regular** (non-pointer and non-reference) types for pass-by-value,
    - **Pointer** types for pass-by-pointer (which is pass-by-value for the pointer itself),
    - **Reference** types for pass-by-reference.

- The **types of function call arguments**, particularly:
    - **Function** types,
    - **Array** types.

Depending on the specific (most important) types of function parameters (regular, pointer, or reference), slightly different rules apply, but they all stem from the basic rule with restrictions. For these specific types, the deduced type may differ from the type of the function call argument only by top-level qualifiers or declarators. The deduced type will never be a reference type because the argument to a function is never of a reference type.

---

### **Regular Parameter Type**

**The deduced template argument is the type of the function argument without top-level qualifiers.**

This means that the initialization of function parameters (when passing arguments by value) copies the value of the function argument to the function parameter. Deduction does not need to account for type qualifiers because the function body operates on a copy. In the parameter definition, qualifiers can be provided to request the compiler to enforce constraints on this parameter.

Example:

```cpp
#include <iostream>

template <typename T>
void foo(T t)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

// We cannot overload templates with parameters of regular types that
// differ with qualifiers.

// template <typename T>
// void foo(const T t)
// {
// }

int main()
{
  int w = 1;
  const int x = 2;
  volatile int y = 3;
  const volatile int z = 4;

  foo(w);
  foo(x);
  foo(y);
  foo(z);
}
```

This type of template parameter can also accept arguments of pointer types:

```cpp
#include <iostream>

template <typename T>
void foo(const T t)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
  int i = 1;
  int const volatile *p1 = &i;
  int volatile *const p2 = &i;
  int const *volatile p3 = &i;
  int *const volatile p4 = &i;

  foo(p1);
  foo(p2);
  foo(p3);
  foo(p4);
}
```


### **Pointer Parameter Type**

**The deduced template argument is the type of the function argument without the highest-level `*` declarator and its qualifiers. The qualifiers of the pointed-to data are also omitted if they are specified in the parameter type definition.**

Explanation:

- The highest-level `*` declarator is omitted because it is already included in the parameter type definition.
- Top-level qualifiers are omitted because they do not affect the function that operates on a copy of the argument's value (just like with a regular parameter type).
- If qualifiers for the **pointed-to data** are specified in the parameter type definition, they will be omitted in the deduced type. If they are not specified, qualifiers from the argument type will propagate into the deduced type, allowing the parameter to be initialized.

Example:

```cpp
#include <iostream>

template <typename T>
void foo(T *t)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

// Can't overload for pointer types with different top-level qualifiers.
// template <typename T>
// void foo(T * const t)
// {
//   std::cout << __PRETTY_FUNCTION__ << std::endl;
// }

template <typename T>
void foo(T volatile *t)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
  int i = 1;
  int const volatile *p1 = &i;
  int volatile *const p2 = &i;
  int const *volatile p3 = &i;
  int *const volatile p4 = &i;

  foo(p1);
  foo(p2);
  foo(p3);
  foo(p4);
}
```

---

### **Reference Parameter Type**

**The deduced template argument is the type of the function argument, excluding the qualifiers specified in the parameter type definition for the data referred to by the reference.**

The goal is to ensure that the reference parameter can indeed be initialized: if the type of the function argument is constant (or volatile), the reference must refer to constant (or volatile) data. Keep in mind that the type of the argument is never a reference type.

Example:

```cpp
#include <iostream>

template <typename T>
void foo(T &t)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

// Can't overload for reference types with different top-level qualifiers
// because no such thing exists!
// template <typename T>
// void foo(T & const t)
// {
//   std::cout << __PRETTY_FUNCTION__ << std::endl;
// }

template <typename T>
void foo(T volatile &t)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
  int w = 1;
  const int x = 2;
  volatile int y = 3;
  const volatile int z = 4;

  foo(w);
  foo(x);
  foo(y);
  foo(z);
}
```

---

### **Passing Functions**

A function can be passed by:

- Reference,
- Pointer,
- But not by value.

**Passing by Reference**  
A function can be passed by *reference* using a reference parameter type, specifically of type `F&`, where `F` is a template parameter. The deduced template argument will be the reference type of the passed function. Example:

```cpp
#include <iostream>

void hello()
{
  std::cout << "Hello World!\n";
}

template <typename F>
void foo(F &f)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  f();
}

void goo(void (&f)())
{
  f();
}

int main()
{
  foo(hello);
  goo(hello);

  // An expression of a pointer type is an rvalue, and so &hello is an
  // rvalue. Since the hello function is of a non-const type (there
  // is no such thing as a const non-member function), the constness
  // cannot be deduced, and therefore the non-const reference
  // parameter "F &" cannot be initialized with an rvalue. It would
  // compile if the foo parameter was a const reference.

  // foo(*hello);
}
```

**Passing by Pointer**  
A function can be passed by *pointer* using a pointer parameter type, specifically of type `F*`, where `F` is a template parameter. The deduced template argument will be the type of the passed function. Example:

```cpp
#include <iostream>

void hello()
{
  std::cout << "Hello World!\n";
}

template <typename F>
void foo(F *f)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  f();
}

void goo(void (*f)())
{
  f();
}

int main()
{
  foo(&hello);
  goo(&hello);
  // The following has the same effect as the above, because the
  // function name decays (is converted) to the function pointer.
  foo(hello);
  goo(hello);
}
```

**Decay of a Function into a Pointer**  
The conversion of a function name into a pointer to it is called **decay of a function into a pointer**, which originates from C. We used decay above by passing the function name as an argument to the template function call.

A function can also be passed by *pointer* using a regular (non-reference and non-pointer) parameter type, specifically of type `F`, where `F` is a template parameter. In this case, the deduced template argument will be a pointer type to the function. Example:

```cpp
#include <iostream>

void hello()
{
  std::cout << "Hello World!\n";
}

template <typename F>
void foo(F f)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  f();
}

void goo(void (*f)())
{
  f();
}

int main()
{
  foo(&hello);
  goo(&hello);
  // The following has the same effect as the above, because the
  // function name decays (is converted) to the function pointer.
  foo(hello);
  goo(hello);
}
```

---

### **Passing C-Style Arrays**

A C-style array can be passed to a template function by:

- Reference,
- Pointer,
- But not by value.

**Passing by Reference**  
An array can be passed by *reference* using a reference parameter type, specifically of type `A&`, where `A` is a template parameter. The deduced template argument will be the array type. Example:

```cpp
#include <iostream>

template <typename A>
void foo(A &a)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void goo(int (&a)[3])
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
  int a[] = {1, 2, 3};
  foo(a);
  goo(a);
}
```
---

**Passing by Pointer**  
An array can be passed by *pointer* using a pointer parameter type, specifically of type `A*`, where `A` is a template parameter. The deduced template argument will be the type of the array. Example:

```cpp
#include <iostream>

template <typename A>
void foo(A *a)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void goo(int (*a)[3])
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
  int a[] = {1, 2, 3};
  // foo(a);
  // goo(a);
  foo(&a);
  goo(&a);
}
```

If the parameter type of the template function is a regular type (non-reference and non-pointer), and the function call argument is the name of an array, then a pointer to the first element of the array (not a pointer to the array) will be passed to the function, because:

1. The array decays (is converted) into a pointer to the first element of the array.
2. The deduced argument will be the pointer type to the array's element.

Here is an example demonstrating decay:

```cpp
#include <iostream>

template <typename A>
void foo(A a[])
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void goo(int a[])
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
  int a[] = {1, 2, 3};
  foo(a);
  goo(a);
  // foo(&a);
  // goo(&a);
}
```

---

### **Value Argument**

A value argument for a template is deduced only from the type of the function call argument, from which the required value can be deduced. The type of the function call argument must include a specific value that becomes the deduced value argument.

The only types of function call arguments from which value arguments can be deduced are:

- C-style array type,
- Any template type.

---

#### **C-Style Array Type**

Here is an example:

```cpp
#include <iostream>

template <typename T, std::size_t N>
void foo(const T (&array)[N])
{
  std::cout << "The array has " << N << " elements.\n";
}

int main()
{
  int array[] = {1, 2, 3};
  foo(array);
}
```

---

#### **Any Template Type**

The value parameters of both templates must match. These two templates are:

1. The function template: the value parameter of this template has a deduced argument,
2. The type template: the function call argument belongs to this template type.

For example, the value parameter `I` must be of type `std::size_t` because the value parameter of the template type `std::array` is also of type `std::size_t`:

```cpp
#include <array>
#include <iostream>

using namespace std;

template <typename T, std::size_t I>
void foo(const array<T, I> &)
{
  cout << __PRETTY_FUNCTION__ << endl;
  cout << "The array has " << I << " elements.\n";
}

int main()
{
  foo(array{"Hello ", "World!"});
  foo(array{1, 2, 3, 4, 5});
}
```

---

### **Multiple Template Function Parameters**

In the previous examples, we used only one parameter for the template function, so the template parameters could be used in at most one definition of the template function's parameter type. However, a template function can have any number of parameters, and a template parameter can be used in any number of parameter type definitions for the template function. How are the template arguments deduced in such cases?

In such cases, template argument deduction is carried out independently for each pair of function parameter and function call argument. For each pair, the arguments for the template parameters used in the type definition of that parameter are deduced. If any argument is deduced more than once (i.e., for different pairs), it must be the same; otherwise, deduction fails.

During deduction, type conversion is not allowed. In the example below, different arguments are deduced because type conversion is not allowed between different function call argument types. Hence, deduction fails:

```cpp
template <typename T>
T max_ref(const T &a, const T &b)
{
  return b < a ? a : b;
}

template <typename T>
T max_val(T a, T b)
{
  return b < a ? a : b;
}

double MAX(const double &a, const double &b)
{
  return b < a ? a : b;
}

int main()
{
  // 1 is converted to .1 (which is a temporary, an rvalue), so that a
  // const reference to double (the first parameter) can bind to it.
  MAX(1, .1);

  // The following call to a template function fails, because:
  //
  // * no conversion is allowed, so 1 cannot be converted to .1.
  // 
  // * T is first deduced int, then double, so deduction fails.

  // max_ref(1, .1);
  // max_val(1, .1);
  
  // No deduction takes place.
  max_ref<int>(1, '1');
  max_ref<double>(1, .1);
  max_val<int>(1, '1');
  max_val<double>(1, .1);
}
```

---

### **Summary**

- A template argument can be deduced or provided (explicitly or implicitly).
- Template argument deduction depends on the type of the function parameter and the type of the function call argument.
- Deduced arguments can be pointer types, reference types, constant types, or even array types.

---

### **Quiz**

1. What is template argument deduction based on?
2. Does deduction consider the return type of the function?
3. What is the decay of an array?

---



