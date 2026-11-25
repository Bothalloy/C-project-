/* 
 * Student Grade and Result Analyzer
 * Simple C Project for 1st Year B.Tech Students
 */

#include <stdio.h>

// Structure to store student data
struct Student {
    int roll;
    char name[30];
    float marks[3];     // 3 subjects: Maths, Physics, C Programming
    float total;
    float percentage;
    char grade;
};

int main() {
    struct Student s[50];
    int n = 0;
    int choice;
    int i, j;

    while (1) {
        printf("\n=================================\n");
        printf("  STUDENT GRADE & RESULT ANALYZER\n");
        printf("=================================\n");
        printf("1. Enter Student Details\n");
        printf("2. Display Marksheet Table\n");
        printf("3. Find Class Topper\n");
        printf("4. Subject-wise Average Marks\n");
        printf("5. Exit\n");
        printf("---------------------------------\n");
        printf("Enter your choice (1-5): ");
        scanf("%d", &choice);

        // 1. Input student details
        if (choice == 1) {
            printf("\nHow many students do you want to enter? ");
            scanf("%d", &n);

            for (i = 0; i < n; i++) {
                printf("\n--- Student %d ---\n", i + 1);
                printf("Enter Roll Number: ");
                scanf("%d", &s[i].roll);

                printf("Enter Name (single word): ");
                scanf("%s", s[i].name);

                s[i].total = 0;
                printf("Enter marks for 3 subjects (out of 100):\n");
                printf("  1. Mathematics : ");
                scanf("%f", &s[i].marks[0]);
                printf("  2. Physics     : ");
                scanf("%f", &s[i].marks[1]);
                printf("  3. C Language  : ");
                scanf("%f", &s[i].marks[2]);

                // Calculate total and percentage
                s[i].total = s[i].marks[0] + s[i].marks[1] + s[i].marks[2];
                s[i].percentage = s[i].total / 3.0;

                // Simple grade calculation
                if (s[i].percentage >= 90) {
                    s[i].grade = 'A';
                } else if (s[i].percentage >= 75) {
                    s[i].grade = 'B';
                } else if (s[i].percentage >= 60) {
                    s[i].grade = 'C';
                } else if (s[i].percentage >= 40) {
                    s[i].grade = 'D';
                } else {
                    s[i].grade = 'F';
                }

                printf("Student added successfully!\n");
            }
        }

        // 2. Display all results in a marksheet table
        else if (choice == 2) {
            if (n == 0) {
                printf("\nNo data found! Please enter student details first (Option 1).\n");
            } else {
                printf("\n--------------------------------------------------------------------\n");
                printf("Roll\tName\t\tMaths\tPhy\tC-Lang\tTotal\t%%\tGrade\n");
                printf("--------------------------------------------------------------------\n");
                for (i = 0; i < n; i++) {
                    printf("%d\t%-10s\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%c\n",
                           s[i].roll, s[i].name, s[i].marks[0], s[i].marks[1],
                           s[i].marks[2], s[i].total, s[i].percentage, s[i].grade);
                }
                printf("--------------------------------------------------------------------\n");
            }
        }

        // 3. Find class topper
        else if (choice == 3) {
            if (n == 0) {
                printf("\nNo data found! Please enter student details first.\n");
            } else {
                int topper = 0;
                for (i = 1; i < n; i++) {
                    if (s[i].percentage > s[topper].percentage) {
                        topper = i;
                    }
                }

                printf("\n********* CLASS TOPPER *********\n");
                printf("Roll Number : %d\n", s[topper].roll);
                printf("Name        : %s\n", s[topper].name);
                printf("Total Marks : %.1f / 300\n", s[topper].total);
                printf("Percentage  : %.2f%%\n", s[topper].percentage);
                printf("Grade       : %c\n", s[topper].grade);
                printf("********************************\n");
            }
        }

        // 4. Subject-wise average analysis
        else if (choice == 4) {
            if (n == 0) {
                printf("\nNo data found! Please enter student details first.\n");
            } else {
                char subjects[3][20] = {"Mathematics", "Physics", "C Language"};

                printf("\n--- SUBJECT-WISE AVERAGE MARKS ---\n");
                for (j = 0; j < 3; j++) {
                    float sum = 0;
                    for (i = 0; i < n; i++) {
                        sum += s[i].marks[j];
                    }
                    printf("%-15s Average : %.2f / 100\n", subjects[j], sum / n);
                }
            }
        }

        // 5. Exit
        else if (choice == 5) {
            printf("\nExiting program. Thank you!\n");
            break;
        }

        // Invalid choice
        else {
            printf("\nInvalid choice! Please enter a number from 1 to 5.\n");
        }
    }

    return 0;
}
