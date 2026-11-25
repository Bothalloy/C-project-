# Student Grade and Result Analyzer (C Language)

A complete, beginner-friendly **Student Grade and Result Analyzer** created in **pure C** for first-year B.Tech / engineering students.

---

## 📌 Project Overview
This project is designed as an introductory C mini-project. It helps faculty and students manage semester marks, calculate percentages and grades, identify class toppers, evaluate subject-wise performance (highest, lowest, average, pass rate), and save records persistently to a file.

---

## 🚀 Key Features

1. **Add Students**: Add single or multiple students with validation (duplicate roll number check, marks range 0–100).
2. **Display All Marksheets**: Displays a neat tabular report showing roll number, student name, marks in 5 subjects, total, percentage, grade, and pass/fail status.
3. **Search by Roll Number**: Quickly find and print an individual student's detailed report card.
4. **Class Topper**: Automatically identifies the student with the highest percentage.
5. **Subject-Wise Analysis**: Computes the highest score, lowest score, average score, and pass percentage for every individual subject.
6. **Overall Class Performance**: Generates a summary report with class average, pass/fail percentage, and grade distribution (A+, A, B, C, D, E, F).
7. **File Persistence**: Automatically saves records to `students_records.txt` and reloads them when the application starts.

---

## 📚 1st Year Engineering Subjects Included
- Mathematics
- Physics
- Basic Electrical
- Programming in C
- English

---

## 🎯 Grading System
- **Minimum Passing Marks**: 40 marks per subject. If a student scores less than 40 in any subject, they are declared **FAIL** with grade **F**.
- **Grade Scale (for Passed Students)**:
  - **A+** : $\ge 90\%$
  - **A**  : $80\% - 89.99\%$
  - **B**  : $70\% - 79.99\%$
  - **C**  : $60\% - 69.99\%$
  - **D**  : $50\% - 59.99\%$
  - **E**  : $40\% - 49.99\%$
  - **F**  : $< 40\%$ or failed in any subject

---

## 🛠️ Concepts of C Used
This project uses standard first-year C programming concepts:
1. **Structures (`struct Student`)**: Groups multiple attributes (roll number, name, marks array, total, grade) into one user-defined data type.
2. **Arrays**: 1D arrays for subject marks and array of structures (`students[MAX_STUDENTS]`).
3. **Functions & Pointers**: Pass-by-reference (`struct Student *s`) for modifying student records and pass-by-value/array pointers for display.
4. **Loops & Decision Making**: `do-while`, `for`, `if-else`, and `switch-case` for menu-driven flow.
5. **String Handling**: `<string.h>` functions like `strcpy()` and `strcmp()`.
6. **File I/O (`<stdio.h>`)**: File pointers (`FILE *`), `fopen()`, `fprintf()`, `fscanf()`, and `fclose()`.

---

## 💻 How to Compile and Run

### Step 1: Open Terminal / Command Prompt
Navigate to the project folder:
```bash
cd /path/to/C-project-
```

### Step 2: Compile the Code
Using GCC:
```bash
gcc -Wall -Wextra main.c -o analyzer
```

### Step 3: Run the Program
On macOS / Linux:
```bash
./analyzer
```
On Windows:
```cmd
analyzer.exe
```

---

## 💡 Quick Viva / Presentation Q&A for Students

**Q1: Why did you use `struct` instead of separate arrays for names, roll numbers, and marks?**  
> *Answer:* A structure allows us to group related variables of different data types under a single name (`Student`). This makes the program modular, cleaner, and easy to manage rather than maintaining 5 or 6 separate parallel arrays.

**Q2: How does the program ensure data is saved when you close the program?**  
> *Answer:* We use file handling functions (`fopen`, `fprintf`, and `fclose`). When we choose the save option or exit the menu, the student records are written to a text file named `students_records.txt`. When the program restarts, it checks if this file exists and automatically loads the data using `fscanf`.

**Q3: How does the pass/fail logic work?**  
> *Answer:* To pass, a student must score at least 40 marks in every single subject. If any subject score is below 40, the student is marked as "FAIL" with grade "F", regardless of their overall percentage.

**Q4: How do you handle student names that contain spaces (e.g., "Rahul Sharma")?**  
> *Answer:* We use `scanf(" %49[^\n]", s.name);` instead of `scanf("%s", ...)`. The `%[^\n]` format specifier reads characters until a newline is pressed, allowing spaces in names.
