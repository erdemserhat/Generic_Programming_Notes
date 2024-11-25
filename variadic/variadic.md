### **Title: Variadic Templates**

---

### **Introduction**

C++11 introduced **variadic templates**, which can accept any number of template arguments, including none. A variadic template is a statically typed compile-time mechanism that is instantiated at the point of use.

A variadic template is identified by the ellipsis (`...`) in the template parameter list:

```cpp
#include <iostream>

using namespace std;

template <typename ...P>
void foo()
{
  cout << __PRETTY_FUNCTION__ << endl;
  cout << sizeof...(P) << endl;
}

int main()
{
  foo<>();
  foo<int>();
  foo<bool, double>();
}
```

---

### **Parameter Pack**

The ellipsis is part of the definition of a **parameter pack**, which is followed (without a separating space) by the name of the pack. A parameter pack can belong to a template or a function. Parameter packs are used exclusively in **expansions**.

---

#### **Template Parameter Pack**

The parameters in a template parameter pack are of the same kind: in the example above, they are types, while in the example below, they are values:

```cpp
#include <iostream>

using namespace std;

template <unsigned ...N>
void foo()
{
  cout << __PRETTY_FUNCTION__ << endl;
  cout << sizeof...(N) << endl;
}

int main()
{
  foo<>();
  foo<1>();
  foo<1, 2>();
  // foo<1, -1>();
}
```

---

### **Pack Expansion**

The name of a pack followed by ellipsis is called a **pack expansion**. A template parameter pack is expanded into a comma-separated list of template arguments:

```cpp
#include <iostream>
#include <string>

struct A {};

template <typename ...P>
struct B: P...
{
  B()
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
};

int main()
{
  // Expands to a structure type that does not have a base class.
  B<>();
  // Expands to a structure type that has the base class A.
  B<A>();
  // Expands to a structure type derived from A and string.
  B<A, std::string>();
}
```

In the examples above, the template arguments must be explicitly specified because the functions and constructor do not have parameters or arguments from which the template arguments could be deduced. Arguments for template parameters in the pack are deduced based on the **function parameter pack** definition and the function call arguments.

---

#### **Function Parameter Pack**

A function parameter pack is defined in the function parameter list using ellipsis: first, the name of the template parameter pack is provided, followed by the ellipsis and the name of the function parameter pack. Interestingly, defining a function parameter pack also implicitly expands the template parameter pack.

```cpp
#include <iostream>

using namespace std;

template <typename ...P>
void foo(P ...p)
{
  cout << __PRETTY_FUNCTION__ << endl;
}

int main()
{
  foo();
  foo(1);
  foo(1, 2.0);
}
```

In the example above, the function accepts arguments by value. It could also accept arguments by constant reference if the pack is defined as `const Args &...args`.

---

### **Pack Expansion**

Expanding a function parameter pack involves writing the pack's name followed by ellipsis.

```cpp
#include <iostream>
#include <string>
#include <vector>

template <typename T, typename ...P>
auto factory(P ...p)
{
  return T{p...};
}

int main()
{
  std::cout << factory<std::string>("Hello!") << std::endl;
  auto p = factory<std::vector<int>>(1, 2, 3);
}
```

Template parameter packs can be expanded alongside function parameter packs, for example, during the initialization of base classes with derived class constructor parameters:

```cpp
#include <iostream>
#include <string>

struct A
{
  A() = default;
  A(int) {}
};

template <typename ...P>
struct B: P...
{
  B(const P &...p): P(p)...
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
};

int main()
{
  B<>();
  B<A>(1);
  B<A, std::string>({}, "Hello!");
}
```

---

### **Recursive Processing**

Function parameter packs can be processed recursively. The trick is to define two function parameters: one for immediate processing and another as a pack for recursive calls. This way, the pack size decreases by one with each recursive call.

```cpp
#include <iostream>
#include <string>

template <typename P1, typename ...P>
void print(P1 p1, P ...p)
{
  std::cout << p1;

  if constexpr(sizeof...(P))
    print(p...);
}

int main()
{
  print("Hello", ' ', std::string("World"), " x ", 100, '\n');
}
```

---

### **Fold Expressions**

A **fold expression** (introduced in C++17) generates an expression using any **binary operator `op`** based on the pack `p`. It condenses the expression into a compact form and is processed at compile time for the given parameter pack `p`, eliminating the need for recursion. A fold expression is identified by `...` and parentheses. There are four forms: two unary and two binary, all using the same operator `op`.

#### **Unary Forms**
- **Left-fold**: `(... op expr)` → `((p1 op p2) op ...)`
- **Right-fold**: `(expr op ...)` → `(p1 op (p2 op ...))`

The example below uses a right-fold expression with the operator `,`. If the pack `p` is empty, the fold expression is empty. If `p` has one parameter, the compiler appends an additional empty argument if the operator requires two arguments (e.g., `,` uses `void()`).

```cpp
#include <iostream>
#include <string>

template <typename T, typename ...P>
void print(const T &t, const P &...p)
{
  std::cout << t;
  ((std::cout << ", " << p), ...);
}

int main()
{
  print(5, "10", std::string("15"));
  std::cout << std::endl;
}
```

#### **Binary Forms**
Binary forms require an **initializer `init`**:
- **Left-fold**: `(init op ... op expr)` → `((init op p1) op p2) op ...)`
- **Right-fold**: `(expr op ... op init)` → `(init op (p1 op (p2 op ...)))`

An example with a left-fold:

```cpp
#include <iostream>
#include <string>

template <typename ...P>
void print(const P &...p)
{
  (std::cout << ... << p);
}

int main()
{
  print("Hello", ' ', std::string("World"), " x ", 100, '\n');
}
```

---

### **Example: Object Properties**

```cpp
#include <iostream>
#include <set>

// name property
template <typename T>
struct name
{
  T m_name;
};

template <typename T>
T &get_name(name<T> &a)
{
  return a.m_name;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const name<T> &w)
{
  os << "name = " << w.m_name;
  return os;
}

// weight property
template <typename T>
struct weight
{
  T m_weight;
};

template <typename T>
T &get_weight(weight<T> &a)
{
  return a.m_weight;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const weight<T> &w)
{
  os << "weight = " << w.m_weight;
  return os;
}

// Type A
template <typename ...P>
struct A: P...
{
  A(P &&...p): P(std::forward<P>(p))...
  {}
};

template <typename P1, typename ...Ps>
std::ostream &operator<<(std::ostream &out, const A<P1, Ps...> &a)
{
  out << static_cast<const P1 &>(a);
  ((out << ", " << static_cast<const Ps &>(a)), ...);
  return out;
}

int main()
{
  using type = A<name<const char *>, weight<int>>;
  type a(name<const char *>("Hello"), weight<int>(1));
  type b = a;
  get_weight(a) = 2;
  get_name(a) = "World";

  std::cout << a << std::endl;
  std::cout << b << std::endl;
}
```

---

### **Summary**

1. Variadic templates accept any number of arguments.
2. Parameter packs are only used in **expansions**.
3. Fold expressions simplify operations over parameter packs and replace recursion in many cases.

---

### **Quiz**

1. Can a template parameter pack accept arguments of different types?
2. Can a parameter pack be empty?
3. What is a fold expression?