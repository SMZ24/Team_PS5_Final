# **Student Grade Monitoring System**

## **1. Project Overview**

The **Student Grade Monitoring System** is a command-line application designed to efficiently manage and monitor student grades. It supports adding, updating, searching, deleting, and displaying student records in a sorted manner.

To ensure high performance even with large datasets, the system uses an **AVL Tree** (a self-balancing Binary Search Tree). This guarantees that essential operations: **insertion, deletion, search, and update**, run in **O(log n)** time, preventing the slowdowns common in unbalanced BSTs.

---

## **2. Features**

The system uses a menu-driven interface with the following capabilities:

* **Add Student**
  Insert a new student record containing ID, Name, Course, and Grade. GPA is auto-calculated.

* **Update Student Grade**
  Modify an existing record’s grade and GPA.

* **Search Student**
  Search by **Student ID** and **Course**.

* **Delete Student**
  Remove a student record or a specific course entry.

* **Display All Students**
  Shows all records sorted by Student ID in ascending order using in-order traversal.

* **Save to File**
  Exports all records to a CSV file.

* **Load from File**
  Rebuilds the AVL tree from a CSV file.

---

## **3. Technical Details**

* **Language:** C++
* **Data Structure:** AVL Tree
* **Storage Format:** CSV
* **Files:**

  * `main.cpp` – User interface, input handling, and main loop
  * `AVLTree.cpp / AVLTree.h` – AVL logic, rotations, balancing, file I/O
  * `AVLNode.cpp / AVLNode.h` – Node structure and student record definition
  * `studentrecord1.csv` – Default persistent data file

---

## **4. Algorithmic Sources**

Standard AVL Tree algorithms were referenced during development.

### **Insertion & Balancing**

* *“Insertion in an AVL Tree”* — GeeksforGeeks (July 23, 2025)
  [https://www.geeksforgeeks.org/dsa/insertion-in-an-avl-tree/](https://www.geeksforgeeks.org/dsa/insertion-in-an-avl-tree/)

### **Search Operation**

* *“Search in an AVL Tree”* — GeeksforGeeks (July 23, 2025)
  [https://www.geeksforgeeks.org/dsa/avl-trees-containing-a-parent-node-pointer/](https://www.geeksforgeeks.org/dsa/avl-trees-containing-a-parent-node-pointer/)

### **Deletion**

* *“Deletion in an AVL Tree”* — GeeksforGeeks (June 19, 2025)
  [https://www.geeksforgeeks.org/dsa/deletion-in-an-avl-tree/](https://www.geeksforgeeks.org/dsa/deletion-in-an-avl-tree/)

### **Display (In-Order Traversal)**

* *“Inorder Traversal of Binary Tree”* — GeeksforGeeks (March 3, 2023)
  [https://www.geeksforgeeks.org/dsa/inorder-traversal-of-binary-tree/](https://www.geeksforgeeks.org/dsa/inorder-traversal-of-binary-tree/)

---

## **5. How to Build and Run**

### **Prerequisites**

* A C++ compiler (G++ recommended)

---

### **Compilation**

Open your terminal/command prompt in the project folder:

```bash
g++ main.cpp AVLTree.cpp AVLNode.cpp -o grade_system
```

---

### **Execution**

#### **Windows**

```bash
grade_system.exe
```

#### **Linux / macOS**

```bash
./grade_system
```

---

## **6. About**

* **Author:** PS5
* **Course:** CSC 307 – Data Structures and Algorithm Analysis
* **Semester:** Fall 2025
* **License:** MIT License

This program was developed as a semester project to demonstrate the practical application of self-balancing binary search trees using AVL tree in data management systems.

---

## End of Documentation

---
