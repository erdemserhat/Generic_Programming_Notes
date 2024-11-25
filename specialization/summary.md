
---

***Specialization of Templates***

---

### **Introduction**

Templates can be **specialized** for both functions and classes. The template being specialized is called the **primary template**, to distinguish it from the specialization, which is also a template. Specialization overrides the definition of the primary template. A specialization cannot be further specialized.

A primary template declares or defines a function or class along with the template parameters (their number and types). A specialization must have the same name (of the function or class) and provide arguments for the specialized primary template.

A specialized template is also a template, but it applies to partially or fully specified arguments. Specialization syntax is slightly different from the primary template's syntax, but it still uses the `template` keyword.

Specialization can be either **partial** (applies to some arguments) or **complete** (applies to all arguments). Function templates can only be completely specialized, whereas class templates can be either partially or completely specialized.

---

### **Specialization of Function Templates**

Function templates can only be completely specialized, meaning all arguments of the primary template must be explicitly defined: the specialization no longer has parameters, so its parameter list is empty. The declaration and definition of a specialized function template start with the `template` keyword and an empty parameter list:

```cpp
template <>
```

After that, the definition of the function template follows, resembling the definition of a regular function. However, it uses fixed values (e.g., `int`, `1`, `std::list`) instead of template parameter names from the primary template.

The difference lies in the function name. In the specialization, the argument list of the primary template is provided after the function name, which is not done for regular functions.

Here’s an example:

```cpp
#include <iostream>

struct A {};

// Definition of the primary function template.
template <typename T>
void foo(const T &t)
{
  std::cout << __PRETTY_FUNCTION__ << ": ";
  std::cout << t << std::endl;
}

// A complete specialization of the function template.
template <>
void foo<A>(const A &)
{
  std::cout << __PRETTY_FUNCTION__ << ": ";
  std::cout << "A" << std::endl;
}

int main()
{
  foo(1);
  foo(.2);
  foo("Hello!");
  foo(A());
}
```

The primary template and its specialization can also be declared. If the primary template is declared but not defined, there will be no default implementation. You can only use the template through its specializations.

---

### **Partial Specialization**

Partial specialization introduces new parameters that are used in defining the primary template's arguments. The parameter list for partial specialization is not empty, unlike complete specialization.

Here’s an example:

```cpp
#include <iostream>
#include <vector>
#include <list>
#include <tuple>

// Definition of the primary template.
template <typename T>
struct A;

// A partial specialization for vectors with elements of any type.
template <typename T>
struct A<std::vector<T>>
{
  void foo()
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }  
};

// A partial specialization for any template with integer arguments.
template <template<typename...> typename T>
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
}
```

---

### **Overloading Functions and Templates**

Templates allow creating generalized implementations. If overloading regular functions for specific types, you may encounter issues with ambiguous calls. Using templates, you can generalize for types while specializing as needed for specific cases. The following demonstrates how a template can extend functionality to handle cases the overloaded functions would miss.

---

### **When to Use Specialization**

Template specialization is useful when a library declares a template but allows users to define specialized behavior. This pattern ensures that users can customize the behavior of specific combinations of template arguments while relying on default behavior for others.

---

### **Quiz**

1. Can function templates be partially specialized?
2. When resolving overloads, which takes precedence: a function template or a regular function overload?
3. Does specialization inherit from the primary class template?

---

