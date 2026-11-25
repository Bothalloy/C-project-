# Student Grade Analyzer

A simple, menu-driven *Student Grade Analyzer* written in basic 1st-semester C. It stores up to 100 student records in memory, validates SAP IDs and subject marks, calculates totals/percentages/grades, and generates rankings and class statistics.

## Features

1.⁠ ⁠*Add Student*
   - Validates 9-digit *SAP IDs* starting with ⁠ 5900 ⁠ (⁠ 590000000 ⁠–⁠ 590099999 ⁠, e.g., ⁠ 590032680 ⁠).
   - Prevents duplicate SAP IDs.
   - Accepts marks (⁠ 0 ⁠–⁠ 100 ⁠) for 5 subjects: *Maths, **Physics, **Chemistry, **English, and **Computer*.
   - Automatically calculates *Total, **Percentage, and **Grade*.

2.⁠ ⁠*Display All Students*
   - Prints a table with *SAP ID, **Name, **Total, **Percent, **Grade, and **Result* (⁠ PASS ⁠ / ⁠ FAIL ⁠).

3.⁠ ⁠*Search by SAP ID*
   - Finds a student using linear search (⁠ findSap ⁠) and displays their Total, Percentage, and Grade.

4.⁠ ⁠*Rank & Class Summary*
   - Sorts students in descending order of percentage using *Bubble Sort* to display a *Rank List*.
   - Shows *Class Average, **Topper, **Lowest* scorer, and *Passed* count (⁠ X/Y ⁠).
   - Prints a ⁠ * ⁠ *Grade Chart* for grades ⁠ A ⁠–⁠ F ⁠.
   - Prints a *Failing List* for students scoring below ⁠ 40% ⁠ (grade ⁠ F ⁠).

5.⁠ ⁠*Delete Student*
   - Removes a student record by SAP ID and shifts the remaining array elements.

## Grading Scale

| Percentage | Grade | Result |
| :--- | :---: | :---: |
| ⁠ 90% – 100% ⁠ | A | PASS |
| ⁠ 75% – 89.99% ⁠ | B | PASS |
| ⁠ 60% – 74.99% ⁠ | C | PASS |
| ⁠ 40% – 59.99% ⁠ | D | PASS |
| ⁠ Below 40% ⁠ | F | FAIL |

## C Concepts Used

•⁠  ⁠⁠ struct ⁠ (⁠ struct Student ⁠)
•⁠  ⁠1D & 2D arrays (⁠ st[100] ⁠, ⁠ marks[5] ⁠, ⁠ subjects[5][15] ⁠)
•⁠  ⁠Functions (⁠ findSap ⁠, ⁠ addStudent ⁠, ⁠ displayAll ⁠, ⁠ searchStudent ⁠, ⁠ deleteStudent ⁠, ⁠ rankAndSummary ⁠, ⁠ main ⁠)
•⁠  ⁠Loops (⁠ for ⁠, ⁠ do-while ⁠) and conditionals (⁠ if / else if / else ⁠, ⁠ switch ⁠)
•⁠  ⁠Basic algorithms: *Linear Search* and *Bubble Sort*

## How to Compile and Run

Using GCC on Windows:

⁠ powershell
gcc main.c -o main.exe
.\main.exe
 ⁠

On Linux / macOS:

⁠ bash
gcc main.c -o main
./main
 ⁠

	⁠*Note:* Enter single-word names (first name only, without spaces) when adding a student, as ⁠ scanf("%s", s.name) ⁠ is used.
