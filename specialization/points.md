

#### **1. Can a function template be partially specialized?**
**Answer:**
No, a **function template cannot be partially specialized**. Only type templates (class or struct templates) can be partially specialized. Function templates can only have **complete specializations**.

---

#### **2. When resolving overloads, does the compiler prefer a function template or a regular function overload?**
**Answer:**
The **compiler prefers a regular function overload** over a function template or its specialization. Regular functions are considered more specific, while templates are more generic.

---

#### **3. Does the specialization of a type template inherit from the primary type template?**
**Answer:**
No, **specializations of type templates do not inherit from the primary template** unless explicitly defined to do so. Each specialization is a standalone definition and may have an entirely different structure or implementation.

---

### **Most Important Points**
1. **Complete specialization is allowed for both function and type templates**, but only type templates can be **partially specialized**.
2. When **overloading**, the compiler prioritizes **regular functions over templates**, making templates a fallback mechanism for less specific cases.
3. Template specializations allow **custom behavior for specific types** while maintaining the generality of the primary template.
4. **Type template specializations** (partial or complete) do not automatically inherit from the primary template; they are separate implementations.

