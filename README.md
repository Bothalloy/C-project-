# Student Record & Grade Management System

A menu-driven console application written in C for managing student academic records, calculating percentages and letter grades across five core subjects, and generating class-wide performance summaries.

---

## Features

1. **Add Student (`addStudent`)**
   - Supports up to **100** student records in memory.
   - Validates SAP IDs within the range `590000000` – `590099999` and prevents duplicate IDs.
   - Validates subject marks (`0` – `100`) across five subjects: **Math, Phy, Chem, Eng, and Comp**.
   - Automatically calculates total marks, percentage, and letter grade.

2. **Display All Records (`displayAll`)**
   - Outputs a formatted table showing SAP ID, Name, Total Marks, Percentage, Grade, and Pass/Fail status.

3. **Search Student (`searchStudent`)**
   - Looks up a specific student record using their unique SAP ID.

4. **Rank & Class Summary (`rankAndSummary`)**
   - Sorts students in descending order of percentage using **Bubble Sort**.
   - Displays a ranked leaderboard alongside the **Class Average**, **Topper**, **Lowest Scorer**, and **Total Pass Count**.

5. **Delete Student (`deleteStudent`)**
   - Removes a record by SAP ID and shifts remaining array elements left to maintain contiguous storage.

---

## Grading Criteria

Grades are assigned automatically based on the student's overall percentage:

| Percentage Range | Grade | Status |
| :--- | :---: | :---: |
| $\ge 90\%$ | `A` | PASS |
| $75\% - 89.99\%$ | `B` | PASS |
| $60\% - 74.99\%$ | `C` | PASS |
| $40\% - 59.99\%$ | `D` | PASS |
| $< 40\%$ | `F` | FAIL |

---

## Data Architecture

```c
struct Student {
    long sap;
    char name[50], grade;
    float marks[5], total, percent;
} st[100];
```

* **`st[100]`**: Global array storing up to 100 `Student` structures.
* **`n`**: Global integer tracking the active number of student records.
* **`sub[5][10]`**: 2D character array storing the five subject names.

---

## Compilation & Usage

### Prerequisites
* A C compiler such as `gcc` or `clang`.

### Build and Run
```bash
gcc main.c -o student_system
./student_system
```

---

## Known Limitations

* **Volatile Storage:** Records are stored in RAM and are cleared when the program exits.
* **Single-Word Names:** Uses `scanf("%s", s.name)`, so names containing spaces are truncated at the first whitespace.
* **In-Place Sorting:** Running **Rank & Summary** reorders the main `st` array permanently for subsequent **Display All** calls.
* **Numeric Input Handling:** Entering non-numeric characters at numeric prompts can cause unexpected input buffer behavior.
