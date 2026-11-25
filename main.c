/*
 * Project: Student Grade and Result Analyzer
 * Language: C
 * Description: A menu-driven program to manage student marks, calculate
 *              grades, find toppers, analyze subject-wise performance,
 *              and save/load records from a file.
 * Level: First Year B.Tech Mini Project
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NUM_SUBJECTS 5
#define PASSING_MARKS 40.0f

// Subject names for 1st Year Engineering
const char SUBJECT_NAMES[NUM_SUBJECTS][30] = {
    "Mathematics",
    "Physics",
    "Basic Electrical",
    "Programming in C",
    "English"
};

// Structure to store all information of a single student
struct Student {
    int rollNumber;
    char name[50];
    float marks[NUM_SUBJECTS];
    float totalMarks;
    float percentage;
    char grade[3];          // e.g., "A+", "A", "B", "C", "D", "F"
    char status[10];        // "PASS" or "FAIL"
};

// Function prototypes
void clearInputBuffer();
void calculateStudentResults(struct Student *s);
void addStudents(struct Student students[], int *count);
void displayAllStudents(const struct Student students[], int count);
void searchStudentByRoll(const struct Student students[], int count);
void findClassTopper(const struct Student students[], int count);
void subjectWiseAnalysis(const struct Student students[], int count);
void classPerformanceReport(const struct Student students[], int count);
void saveToFile(const struct Student students[], int count);
void loadFromFile(struct Student students[], int *count);

// Helper function to flush standard input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Function to calculate total, percentage, pass/fail status, and grade
void calculateStudentResults(struct Student *s) {
    int hasFailed = 0;
    s->totalMarks = 0.0f;

    for (int i = 0; i < NUM_SUBJECTS; i++) {
        s->totalMarks += s->marks[i];
        if (s->marks[i] < PASSING_MARKS) {
            hasFailed = 1; // Student failed in at least one subject
        }
    }

    s->percentage = s->totalMarks / NUM_SUBJECTS;

    // Determine status and grade
    if (hasFailed) {
        strcpy(s->status, "FAIL");
        strcpy(s->grade, "F");
    } else {
        strcpy(s->status, "PASS");

        if (s->percentage >= 90.0f) {
            strcpy(s->grade, "A+");
        } else if (s->percentage >= 80.0f) {
            strcpy(s->grade, "A");
        } else if (s->percentage >= 70.0f) {
            strcpy(s->grade, "B");
        } else if (s->percentage >= 60.0f) {
            strcpy(s->grade, "C");
        } else if (s->percentage >= 50.0f) {
            strcpy(s->grade, "D");
        } else {
            strcpy(s->grade, "E");
        }
    }
}

// Function to add new student records
void addStudents(struct Student students[], int *count) {
    int n;
    printf("\nHow many students do you want to add? ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input. Please enter a positive number.\n");
        clearInputBuffer();
        return;
    }

    if (*count + n > MAX_STUDENTS) {
        printf("Error: Cannot add %d students. Maximum capacity is %d.\n", n, MAX_STUDENTS);
        return;
    }

    for (int i = 0; i < n; i++) {
        struct Student s;
        printf("\n--- Enter Details for Student %d ---\n", *count + 1);

        // Check for duplicate roll number
        int duplicate;
        do {
            duplicate = 0;
            printf("Enter Roll Number: ");
            scanf("%d", &s.rollNumber);
            clearInputBuffer();

            if (s.rollNumber <= 0) {
                printf("Roll number must be positive. Try again.\n");
                duplicate = 1;
                continue;
            }

            for (int j = 0; j < *count; j++) {
                if (students[j].rollNumber == s.rollNumber) {
                    printf("Error: Roll number %d already exists! Enter a unique roll number.\n", s.rollNumber);
                    duplicate = 1;
                    break;
                }
            }
        } while (duplicate);

        printf("Enter Student Name: ");
        scanf(" %49[^\n]", s.name);

        printf("\nEnter marks out of 100 for each subject:\n");
        for (int j = 0; j < NUM_SUBJECTS; j++) {
            do {
                printf("  %s: ", SUBJECT_NAMES[j]);
                if (scanf("%f", &s.marks[j]) != 1 || s.marks[j] < 0.0f || s.marks[j] > 100.0f) {
                    printf("  Invalid marks! Please enter between 0 and 100.\n");
                    clearInputBuffer();
                    s.marks[j] = -1.0f;
                }
            } while (s.marks[j] < 0.0f || s.marks[j] > 100.0f);
        }

        // Calculate results
        calculateStudentResults(&s);

        // Store into array
        students[*count] = s;
        (*count)++;

        printf("Student record added successfully!\n");
    }
}

// Function to display all students in a neat tabular format
void displayAllStudents(const struct Student students[], int count) {
    if (count == 0) {
        printf("\nNo student records available. Please add some first.\n");
        return;
    }

    printf("\n========================================================================================\n");
    printf("                              STUDENT MARKSHEET REPORT                                  \n");
    printf("========================================================================================\n");
    printf("%-8s %-20s %-8s %-8s %-8s %-8s %-8s %-8s %-7s %-6s %-6s\n",
           "Roll", "Name", "Math", "Phy", "Elec", "Prog", "Eng", "Total", "%age", "Grade", "Status");
    printf("----------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-8d %-20s %-8.1f %-8.1f %-8.1f %-8.1f %-8.1f %-8.1f %-7.2f %-6s %-6s\n",
               students[i].rollNumber,
               students[i].name,
               students[i].marks[0],
               students[i].marks[1],
               students[i].marks[2],
               students[i].marks[3],
               students[i].marks[4],
               students[i].totalMarks,
               students[i].percentage,
               students[i].grade,
               students[i].status);
    }
    printf("========================================================================================\n");
    printf("Total records: %d\n", count);
}

// Function to search student record by roll number
void searchStudentByRoll(const struct Student students[], int count) {
    if (count == 0) {
        printf("\nNo records available to search.\n");
        return;
    }

    int searchRoll;
    printf("\nEnter Roll Number to search: ");
    if (scanf("%d", &searchRoll) != 1) {
        printf("Invalid roll number.\n");
        clearInputBuffer();
        return;
    }

    int foundIndex = -1;
    for (int i = 0; i < count; i++) {
        if (students[i].rollNumber == searchRoll) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        const struct Student *s = &students[foundIndex];
        printf("\n====================================\n");
        printf("         STUDENT REPORT CARD        \n");
        printf("====================================\n");
        printf(" Roll Number : %d\n", s->rollNumber);
        printf(" Name        : %s\n", s->name);
        printf("------------------------------------\n");
        printf(" Subject-wise Marks:\n");
        for (int j = 0; j < NUM_SUBJECTS; j++) {
            printf("   %-18s : %6.2f / 100\n", SUBJECT_NAMES[j], s->marks[j]);
        }
        printf("------------------------------------\n");
        printf(" Total Marks : %.2f / %d\n", s->totalMarks, NUM_SUBJECTS * 100);
        printf(" Percentage  : %.2f%%\n", s->percentage);
        printf(" Grade       : %s\n", s->grade);
        printf(" Status      : %s\n", s->status);
        printf("====================================\n");
    } else {
        printf("\nStudent with Roll Number %d was NOT found.\n", searchRoll);
    }
}

// Function to find topper (highest percentage)
void findClassTopper(const struct Student students[], int count) {
    if (count == 0) {
        printf("\nNo student records available.\n");
        return;
    }

    int topperIdx = 0;
    for (int i = 1; i < count; i++) {
        if (students[i].percentage > students[topperIdx].percentage) {
            topperIdx = i;
        }
    }

    printf("\n=========================================\n");
    printf("             CLASS TOPPER                \n");
    printf("=========================================\n");
    printf(" Name        : %s\n", students[topperIdx].name);
    printf(" Roll Number : %d\n", students[topperIdx].rollNumber);
    printf(" Total Marks : %.2f / %d\n", students[topperIdx].totalMarks, NUM_SUBJECTS * 100);
    printf(" Percentage  : %.2f%%\n", students[topperIdx].percentage);
    printf(" Grade       : %s\n", students[topperIdx].grade);
    printf("=========================================\n");
}

// Function to analyze subject-wise performance (Highest, Lowest, Average)
void subjectWiseAnalysis(const struct Student students[], int count) {
    if (count == 0) {
        printf("\nNo student records available for analysis.\n");
        return;
    }

    printf("\n=========================================================================\n");
    printf("                        SUBJECT-WISE PERFORMANCE ANALYSIS                \n");
    printf("=========================================================================\n");
    printf("%-20s %-12s %-12s %-12s %-10s\n",
           "Subject", "Highest", "Lowest", "Average", "Pass Rate");
    printf("-------------------------------------------------------------------------\n");

    for (int j = 0; j < NUM_SUBJECTS; j++) {
        float highest = students[0].marks[j];
        float lowest = students[0].marks[j];
        float sum = 0.0f;
        int passCount = 0;

        for (int i = 0; i < count; i++) {
            float m = students[i].marks[j];
            if (m > highest) highest = m;
            if (m < lowest) lowest = m;
            sum += m;
            if (m >= PASSING_MARKS) passCount++;
        }

        float avg = sum / count;
        float passRate = ((float)passCount / count) * 100.0f;

        printf("%-20s %-12.2f %-12.2f %-12.2f %6.1f%%\n",
               SUBJECT_NAMES[j], highest, lowest, avg, passRate);
    }
    printf("=========================================================================\n");
}

// Function to show overall class summary (Pass %, Fail %, Grade counts)
void classPerformanceReport(const struct Student students[], int count) {
    if (count == 0) {
        printf("\nNo student records available.\n");
        return;
    }

    int passCount = 0;
    int failCount = 0;
    int gradeCountA_Plus = 0;
    int gradeCountA = 0;
    int gradeCountB = 0;
    int gradeCountC = 0;
    int gradeCountD = 0;
    int gradeCountE = 0;
    int gradeCountF = 0;
    float totalClassPercentage = 0.0f;

    for (int i = 0; i < count; i++) {
        totalClassPercentage += students[i].percentage;

        if (strcmp(students[i].status, "PASS") == 0) {
            passCount++;
        } else {
            failCount++;
        }

        if (strcmp(students[i].grade, "A+") == 0) gradeCountA_Plus++;
        else if (strcmp(students[i].grade, "A") == 0) gradeCountA++;
        else if (strcmp(students[i].grade, "B") == 0) gradeCountB++;
        else if (strcmp(students[i].grade, "C") == 0) gradeCountC++;
        else if (strcmp(students[i].grade, "D") == 0) gradeCountD++;
        else if (strcmp(students[i].grade, "E") == 0) gradeCountE++;
        else gradeCountF++;
    }

    printf("\n==========================================\n");
    printf("       OVERALL CLASS PERFORMANCE REPORT   \n");
    printf("==========================================\n");
    printf(" Total Students       : %d\n", count);
    printf(" Class Average        : %.2f%%\n", totalClassPercentage / count);
    printf(" Passed Students      : %d (%.2f%%)\n", passCount, ((float)passCount / count) * 100.0f);
    printf(" Failed Students      : %d (%.2f%%)\n", failCount, ((float)failCount / count) * 100.0f);
    printf("------------------------------------------\n");
    printf(" Grade Distribution:\n");
    printf("   A+ (>= 90%%)        : %d student(s)\n", gradeCountA_Plus);
    printf("   A  (80%% - 89%%)     : %d student(s)\n", gradeCountA);
    printf("   B  (70%% - 79%%)     : %d student(s)\n", gradeCountB);
    printf("   C  (60%% - 69%%)     : %d student(s)\n", gradeCountC);
    printf("   D  (50%% - 59%%)     : %d student(s)\n", gradeCountD);
    printf("   E  (40%% - 49%%)     : %d student(s)\n", gradeCountE);
    printf("   F  (Fail < 40%%)    : %d student(s)\n", gradeCountF);
    printf("==========================================\n");
}

// Function to save student data to a text file
void saveToFile(const struct Student students[], int count) {
    if (count == 0) {
        printf("\nNo data to save.\n");
        return;
    }

    FILE *fp = fopen("students_records.txt", "w");
    if (fp == NULL) {
        printf("\nError opening file for saving!\n");
        return;
    }

    // Write number of students first
    fprintf(fp, "%d\n", count);

    for (int i = 0; i < count; i++) {
        // Save: roll, name, marks0, marks1, marks2, marks3, marks4
        fprintf(fp, "%d,%s,%.2f,%.2f,%.2f,%.2f,%.2f\n",
                students[i].rollNumber,
                students[i].name,
                students[i].marks[0],
                students[i].marks[1],
                students[i].marks[2],
                students[i].marks[3],
                students[i].marks[4]);
    }

    fclose(fp);
    printf("\nSuccessfully saved %d records to 'students_records.txt'.\n", count);
}

// Function to load student data from a text file
void loadFromFile(struct Student students[], int *count) {
    FILE *fp = fopen("students_records.txt", "r");
    if (fp == NULL) {
        printf("\nFile 'students_records.txt' not found or could not be opened.\n");
        return;
    }

    int savedCount = 0;
    if (fscanf(fp, "%d\n", &savedCount) != 1) {
        printf("\nError reading file format.\n");
        fclose(fp);
        return;
    }

    int loaded = 0;
    for (int i = 0; i < savedCount && i < MAX_STUDENTS; i++) {
        struct Student s;
        // Read CSV line: roll,name,m0,m1,m2,m3,m4
        if (fscanf(fp, "%d,%49[^,],%f,%f,%f,%f,%f\n",
                   &s.rollNumber,
                   s.name,
                   &s.marks[0],
                   &s.marks[1],
                   &s.marks[2],
                   &s.marks[3],
                   &s.marks[4]) == 7) {
            calculateStudentResults(&s);
            students[i] = s;
            loaded++;
        }
    }

    *count = loaded;
    fclose(fp);
    printf("\nSuccessfully loaded %d records from 'students_records.txt'.\n", loaded);
}

// Main function: Driver program with interactive menu
int main() {
    struct Student students[MAX_STUDENTS];
    int count = 0;
    int choice;

    printf("\n********************************************************\n");
    printf("*   WELCOME TO STUDENT GRADE & RESULT ANALYZER (C)     *\n");
    printf("*        B.Tech 1st Year Engineering Project           *\n");
    printf("********************************************************\n");

    // Try auto-loading existing records on startup
    FILE *checkFile = fopen("students_records.txt", "r");
    if (checkFile != NULL) {
        fclose(checkFile);
        printf("\nFound existing 'students_records.txt'. Loading data...\n");
        loadFromFile(students, &count);
    }

    do {
        printf("\n==================== MAIN MENU ====================\n");
        printf(" 1. Add New Student(s)\n");
        printf(" 2. Display All Student Marksheets\n");
        printf(" 3. Search Student by Roll Number\n");
        printf(" 4. Find Class Topper\n");
        printf(" 5. Subject-Wise Analysis (High/Low/Avg)\n");
        printf(" 6. Overall Class Performance & Grade Distribution\n");
        printf(" 7. Save Records to File\n");
        printf(" 8. Load Records from File\n");
        printf(" 9. Exit\n");
        printf("===================================================\n");
        printf("Enter your choice (1-9): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number between 1 and 9.\n");
            clearInputBuffer();
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1:
                addStudents(students, &count);
                break;
            case 2:
                displayAllStudents(students, count);
                break;
            case 3:
                searchStudentByRoll(students, count);
                break;
            case 4:
                findClassTopper(students, count);
                break;
            case 5:
                subjectWiseAnalysis(students, count);
                break;
            case 6:
                classPerformanceReport(students, count);
                break;
            case 7:
                saveToFile(students, count);
                break;
            case 8:
                loadFromFile(students, &count);
                break;
            case 9:
                printf("\nSaving your records before exiting...\n");
                if (count > 0) {
                    saveToFile(students, count);
                }
                printf("Thank you for using Student Grade and Result Analyzer! Goodbye.\n\n");
                break;
            default:
                printf("Invalid choice! Please choose an option between 1 and 9.\n");
        }
    } while (choice != 9);

    return 0;
}
