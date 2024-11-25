### **Title: Template Specialization**

---

### **Introduction**

We can **specialize** a function or class template. A template being specialized is called the **primary template**, to distinguish it from the specialization, which is also a template. A specialization overrides the definition of the primary template. A specialization cannot be further specialized.

The primary template declares or defines a function or class along with its template parameters (number and types of parameters). A specialization must have the same name (of the function or class) and supply arguments for the specialized primary template.

A specialized template is still a template, but for partially or fully specified arguments. A specialization can be recognized by slightly different syntax, though it still uses the `template` keyword.

Specialization can be **partial** (partial specialization) or **complete** (complete specialization). Function templates can only be fully specialized. Class templates can be either partially or fully specialized.

---

### **Specialization of Function Templates**

A function template can only be fully specialized, meaning all arguments of the primary template must be specified: the specialized template no longer has parameters, so its parameter list is empty. Hence, declarations and definitions of function template specializations start with the `template` keyword and an empty parameter list:

```cpp
template <>
```

Then follows the definition of the function template, which looks like a regular function definition since we no longer use (in the function parameter list or the function body) the names of the primary template parameters, but rather their specified values (e.g., `int`, `1`, or `std::list`). However, there is one difference.

The difference lies in the function name. In a specialization, we include the list of primary template arguments after the function name, which we do not do in a regular function definition.

Here’s an example:

```cpp
#include <iostream>

struct A {};

template <typename T>
void foo(const T &t)
{
    std::cout << __PRETTY_FUNCTION__ << ": " << t << std::endl;
}

template <>
void foo<A>(const A &)
{
    std::cout << __PRETTY_FUNCTION__ << ": " << "A" << std::endl;
}

int main()
{
    foo(1);
    foo(.2);
    foo("Hello!");
    foo(A());
}
```

We can also declare the primary template and the specialization. If we declare the primary template but do not define it, the primary template implementation will not exist. We will still be able to specialize the template and use it only for those specializations. This is demonstrated in the example below.

The list of primary template arguments can be omitted if the compiler can deduce those arguments from the function parameter list. In the example below, we omitted the list of arguments (`<A>`) of the primary template after the `foo` function name in the declaration and definition of the specialization.

```cpp
#include <iostream>

struct A {};

// Declaration of the primary template
template <typename T>
void foo(const T &t);

// Declaration of a complete specialization
template <>
void foo(const A &);

// Definition of a complete specialization
template <>
void foo(const A &)
{
    std::cout << __PRETTY_FUNCTION__ << ": " << "A" << std::endl;
}

int main()
{
    // foo(1);
    foo(A());
}
```

Function templates cannot be partially specialized. Partial specialization would involve introducing parameters for the specialization, which is not allowed, as shown in the example below:

```cpp
#include <iostream>

template <typename T>
struct C {};

// Declaration of the primary function template
template <typename T>
void foo(const T &t);

// Error: partial specialization of a function template is not allowed
// template <typename T>
// void foo<C<T>>(const C<T> &)
// {
//     std::cout << __PRETTY_FUNCTION__ << ": " << "C<T>" << std::endl;
// }

// This is another primary template, not a specialization
template <typename T>
void foo(const C<T> &)
{
    std::cout << __PRETTY_FUNCTION__ << ": " << "C<T>" << std::endl;
}

int main()
{
    // foo(1);
    foo(C<int>());
}
```

The example below illustrates a recursive function template, where recursion is stopped by a specialization. In the specialization, we must provide the argument `0` for parameter `N` since the compiler cannot deduce it. The `int` argument for parameter `T` can be deduced, so it is not specified.

```cpp
#include <iostream>

template <typename T>
void print(const T &t)
{
    std::cout << t << '\n';
}

template <unsigned N, typename T>
void print(const T &t)
{
    print(t);
    print<N - 1>(t);
}

// Complete specialization of a function template
template <>
void print<0>(const int &)
{
}

int main()
{
    print("Hello!");
    print<10>(1);
}
```

---

### **Overloading Functions vs. Templates**

Can we manage without templates? In the example below, the `foo` function is overloaded to provide a different implementation depending on the function call argument.

The problem is that we lack a template that could be applied to any type. For this reason, the overload for type `int` is called for the argument `.2` of type `double`.

```cpp
#include <iostream>

struct A {};

void foo(const int &i)
{
    std::cout << "Function foo: " << i << std::endl;
}

void foo(const A &)
{
    std::cout << "Function foo: A" << std::endl;
}

int main()
{
    foo(1);
    foo('1');
    foo(A());
}
```

We can add a primary template to this example, as shown below. We now have a template for any type and an overload for type `A`. When the function `foo` is called with the argument `A()`, will the template or the overload be used? More precisely, will the overload of the template function (i.e., the function obtained after concretizing the primary function template for `T = A`) or the regular function overload be used? **The regular function overload always takes precedence.**

```cpp
#include <iostream>

struct A {};

// Definition of the primary function template
template <typename T>
void foo(const T &t)
{
    std::cout << __PRETTY_FUNCTION__ << ": " << t << std::endl;
}

// A function overload
void foo(const A &)
{
    std::cout << __PRETTY_FUNCTION__ << ": A" << std::endl;
}

int main()
{
    foo(1);
    foo(.2);
    foo(A());
}
```

We can also add a specialization for `T = A`, but the regular function overload will still be chosen. When selecting an overload, the compiler does not consider specializations, only regular function overloads and template function overloads. Thus, adding a specialization does not persuade the compiler to use it.

```cpp
#include <iostream>

struct A {};

// Definition of the primary function template
template <typename T>
void foo(const T &t)
{
    std::cout << __PRETTY_FUNCTION__ << ": " << t << std::endl;
}

// Definition of a complete specialization of a function template
template <>
void foo(const A &)
{
    std::cout << __PRETTY_FUNCTION__ << ": A" << std::endl;
}

// A function overload
// void foo(const A &)
// {
//     std::cout << __PRETTY_FUNCTION__ << ": A" << std::endl;
// }

int main()
{
    foo(1);
    foo(.2);
    foo(A());
}
```

---

### **When Do We Need Specializations?**

It might seem that template specialization is unnecessary because we achieved the same functionality by overloading regular functions. However, there are features of specializations that cannot be achieved through overloading.

Template specialization allows users to define functions for code that has already been included in a header file, e.g., a library template. The library declares the function template it requires, but the definition of its specialization—or even the primary template—can be left to the user. For instance, this is how the library header file `library.hpp` might look:

```cpp
// Declaration of a primary function template
template <typename T>
void foo(const T &t);

// This function template uses the above declaration
// Without the declaration, this template wouldn't compile
template <typename T>
void goo(const T &t)
{
    foo(t);
}
```

This is how the library might be used:

```cpp
#include "library.hpp"

#include <iostream>

// A regular function overload won't work here
void foo(const int &)
{
    std::cout << "overload\n";
}

// We need a specialization of the primary template
template <>
void foo(const int &)
{
    std::cout << "specialization\n";
}

int main()
{
    goo(1);
}
```

If the function overload is declared after including the library, the function `goo` will not recognize it and won't use it. However, the function knows it can use the `foo` function template because its primary template was declared.

We could move the definition of the function overload `foo` before the `#include` directive, so the function `goo` could use the overload. However, this approach creates unnecessary disorder.

---

### **Specialization of User-Defined Template Types**

We can declare or define user-defined template types, such as structures, classes, and unions. These primary templates can be fully or partially specialized. The primary template and its specializations share only the type name, while their interfaces (members accessible to the user), implementations, and memory sizes may differ entirely.

An example of type specialization in the standard library is `std::vector<bool>`, a container for the type `bool`. This specialization has a similar interface to the primary template `std::vector` but a completely different implementation.

---

### **Example of Complete Specialization**

Below, we define the primary template type `A` with one member function `foo`. The complete specialization for the argument `double` does not have the function `foo` but includes the function `goo` and inherits from `std::pair`. The syntax for a fully specialized type is identical to that of a fully specialized function.

```cpp
#include <iostream>
#include <utility>

// Definition of a primary template
template <typename T>
struct A
{
    void foo()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

// A complete specialization
template <>
struct A<double> : std::pair<double, double>
{
    void goo()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

int main()
{
    A<int> i;
    i.foo();
    A<float>().foo();

    // Error: "foo" is in the primary template, which we've overwritten
    // A<double>().foo();

    // But we can call "goo" instead
    A<double>().goo();

    // Comparing with the < operator inherited from std::pair
    std::cout << (A<double>() < A<double>()) << std::endl;
}
```

---

### **Partial Specialization and Example**

In the partial specialization of a template type, we introduce a parameter that is used in the definition of the primary template's argument. The specialization's parameter list is no longer empty, unlike in the case of full specialization.

In the example below, we declare the primary template type `A` with a typical parameter `T` and then define two specializations, both with their own parameter `T`. The `T` parameters of the three templates are unrelated, as they each have a local scope.

The first specialization defines the implementation of type `A` for cases where the primary template's argument is `std::vector`. We allow any type of vector elements by using the specialization's parameter `T`.

The second specialization defines the implementation of type `A` for cases where the primary template's argument is a template type that can be concretized with one argument, `int`.

In the `main` function, type `A` is used with different specializations. The most interesting case is the last one, which is commented out because it cannot compile: the compiler cannot decide which specialization to use.

```cpp
#include <iostream>
#include <list>
#include <vector>
#include <tuple>

// Definition of a primary template
template <typename T>
struct A;

// A partial specialization for a vector of elements of any type
template <typename T>
struct A<std::vector<T>>
{
    void foo()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

// A partial specialization for any template type of the integer argument
template <template <typename...> typename T>
struct A<T<int>>
{
    void goo()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

int main()
{
    A<std::vector<bool>>().foo();
    A<std::vector<double>>().foo();
    A<std::list<int>>().goo();
    A<std::tuple<int>>().goo();

    // Ambiguous instantiation: the first or the second specialization?
    // A<std::vector<int>> a;
}
```

---

### **Summary**

- Both function templates and type templates can be specialized.
- Specialization can be either **partial** or **complete**.
- Specialization allows for overriding the implementation of a primary template for selected combinations of its arguments.

---

### **Quiz**

1. Can a function template be partially specialized?
2. When resolving overloads, does the compiler prefer a function template or a regular function overload?
3. Does the specialization of a type template inherit from the primary type template?

---


