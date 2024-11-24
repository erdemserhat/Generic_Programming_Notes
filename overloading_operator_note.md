
# Overloading `<<` Operator in C++

To override the print behavior of a custom type in C++, overload the `<<` operator for `std::ostream`. This allows objects of your class to be printed using `std::cout`.

## **Steps to Overload `<<`**
1. Define a **free function** for `operator<<`.
2. Take `std::ostream&` as the first parameter and a `const` reference to your type as the second.
3. Implement the print logic and return the `std::ostream&`.

## **Example**
```cpp
#include <iostream>
#include <string>

class Person {
private:
    std::string name;
    int age;

public:
    Person(const std::string& name, int age) : name(name), age(age) {}

    // Overloading << operator
    friend std::ostream& operator<<(std::ostream& os, const Person& person) {
        os << "Person(Name: " << person.name << ", Age: " << person.age << ")";
        return os;
    }
};

int main() {
    Person p("Alice", 30);
    std::cout << p << std::endl;  // Outputs: Person(Name: Alice, Age: 30)
    return 0;
}
```

## **Key Points**
- **Free Function:** Define `operator<<` as a non-member function to allow flexibility.
- **Friend Access:** Use `friend` to access private members if needed.
- **Return `std::ostream&`:** Enable chaining of output operations (e.g., `std::cout << p1 << p2`).

## **Advanced Example**
For more complex types like matrices, customize the logic inside `operator<<`:
```cpp
friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    for (const auto& row : matrix.data) {
        for (const auto& val : row) {
            os << val << " ";
        }
        os << "\n";
    }
    return os;
}
```

---

