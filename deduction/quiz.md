### **Summary**
1. **Template Argument Deduced or Provided**:  
   A template argument can be:
    - **Deduced**: The compiler automatically determines it based on the arguments provided in the function call.
    - **Provided**: Explicitly specified by the programmer or through default template arguments.

2. **What Deduction Depends On**:  
   Template argument deduction depends on:
    - The **type of the function parameter** (e.g., regular, pointer, or reference types).
    - The **type of the function call argument** passed by the caller.

3. **Types of Deduced Arguments**:  
   Deduced arguments can be:
    - **Pointer types** (e.g., `int*`).
    - **Reference types** (e.g., `int&` or `const int&`).
    - **Constant types** (e.g., `const int`).
    - **Array types** (e.g., `int[]` or `int[5]`).

---

### **Quiz Questions**

1. **What is template argument deduction based on?**
    - Template argument deduction is based on the types of the function parameters and the types of the arguments provided in the function call.

2. **Does deduction consider the return type of the function?**
    - No, deduction is only based on the function parameters and arguments. The return type does not affect deduction.

3. **What is the decay of an array?**
    - Decay of an array refers to the automatic conversion of an array's name into a pointer to its first element when passed as a function argument (e.g., `int arr[]` becomes `int*`). This process is why functions often receive arrays as pointers.