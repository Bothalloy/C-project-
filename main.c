/* 
 * Student Grade and Result Analyzer
 * Simple C Project for 1st Year B.Tech Students
 * Features: Add, View Marksheet, Topper, Subject Average, Delete, File Save
 */

#include <stdio.h>

// Structure to store student data
struct Student {
    long long sapid;    // Student SAP ID (e.g., 500012345)
    char name[30];
    float marks[3];     // 3 subjects: Maths, Physics, C Programming
    float total;
    float percentage;
    char grade;
};

// Function to save student array to a text file
void saveToFile(struct Student s[], int n) {
    FILE *fp = fopen("students.txt", "w");
    if (fp == NULL) {
        printf("Error opening file for saving!\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(fp, "%lld %s %.1f %.1f %.1f\n",
                s[i].sapid, s[i].name, s[i].marks[0], s[i].marks[1], s[i].marks[2]);
    }

    fclose(fp);
}

int main() {
    struct Student s[100];
    int n = 0;          // Total number of students currently stored
    int choice;
    int i, j;

    // Load previously saved students from file on program start
    FILE *fp = fopen("students.txt", "r");
    if (fp != NULL) {
        while (fscanf(fp, "%lld %s %f %f %f",
                      &s[n].sapid, s[n].name,
                      &s[n].marks[0], &s[n].marks[1], &s[n].marks[2]) == 5) {
            
            // Calculate total, percentage, and grade for each loaded student
            s[n].total = s[n].marks[0] + s[n].marks[1] + s[n].marks[2];
            s[n].percentage = s[n].total / 3.0;

            if (s[n].percentage >= 90) {
                s[n].grade = 'A';
            } else if (s[n].percentage >= 75) {
                s[n].grade = 'B';
            } else if (s[n].percentage >= 60) {
                s[n].grade = 'C';
            } else if (s[n].percentage >= 40) {
                s[n].grade = 'D';
            } else {
                s[n].grade = 'F';
            }

            n++;
        }
        fclose(fp);
        if (n > 0) {
            printf("\n--> Loaded %d existing student record(s) from 'students.txt'.\n", n);
        }
    }

    while (1) {
        printf("\n=================================\n");
        printf("  STUDENT GRADE & RESULT ANALYZER\n");
        printf("=================================\n");
        printf("1. Add New Student(s)\n");
        printf("2. Display Marksheet Table\n");
        printf("3. Find Class Topper\n");
        printf("4. Subject-wise Average Marks\n");
        printf("5. Delete a Student Record\n");
        printf("6. Exit\n");
        printf("---------------------------------\n");
        printf("Enter your choice (1-6): ");
        scanf("%d", &choice);

        // 1. Add students (appends to existing data)
        if (choice == 1) {
            int count;
            printf("\nHow many students do you want to add? ");
            scanf("%d", &count);

            for (i = 0; i < count; i++) {
                printf("\n--- Student %d ---\n", n + 1);
                printf("Enter SAP ID: ");
                scanf("%lld", &s[n].sapid);

                printf("Enter Name (single word): ");
                scanf("%s", s[n].name);

                printf("Enter marks for 3 subjects (out of 100):\n");
                printf("  1. Mathematics : ");
                scanf("%f", &s[n].marks[0]);
                printf("  2. Physics     : ");
                scanf("%f", &s[n].marks[1]);
                printf("  3. C Language  : ");
                scanf("%f", &s[n].marks[2]);

                // Calculate total and percentage
                s[n].total = s[n].marks[0] + s[n].marks[1] + s[n].marks[2];
                s[n].percentage = s[n].total / 3.0;

                // Grade calculation
                if (s[n].percentage >= 90) {
                    s[n].grade = 'A';
                } else if (s[n].percentage >= 75) {
                    s[n].grade = 'B';
                } else if (s[n].percentage >= 60) {
                    s[n].grade = 'C';
                } else if (s[n].percentage >= 40) {
                    s[n].grade = 'D';
                } else {
                    s[n].grade = 'F';
                }

                n++; // Increase student count
                printf("Student added successfully!\n");
            }

            // Save to file automatically after adding
            saveToFile(s, n);
            printf("--> All data saved to 'students.txt'!\n");
        }

        // 2. Display all results in a marksheet table
        else if (choice == 2) {
            if (n == 0) {
                printf("\nNo student records found! Please add students first.\n");
            } else {
                printf("\n----------------------------------------------------------------------------\n");
                printf("%-12s %-12s %-8s %-8s %-8s %-8s %-8s %-5s\n",
                       "SAP ID", "Name", "Maths", "Phy", "C-Lang", "Total", "%age", "Grade");
                printf("----------------------------------------------------------------------------\n");
                for (i = 0; i < n; i++) {
                    printf("%-12lld %-12s %-8.1f %-8.1f %-8.1f %-8.1f %-8.1f %-5c\n",
                           s[i].sapid, s[i].name, s[i].marks[0], s[i].marks[1],
                           s[i].marks[2], s[i].total, s[i].percentage, s[i].grade);
                }
                printf("----------------------------------------------------------------------------\n");
                printf("Total Students: %d\n", n);
            }
        }

        // 3. Find class topper
        else if (choice == 3) {
            if (n == 0) {
                printf("\nNo data found! Please add students first.\n");
            } else {
                int topper = 0;
                for (i = 1; i < n; i++) {
                    if (s[i].percentage > s[topper].percentage) {
                        topper = i;
                    }
                }

                printf("\n********* CLASS TOPPER *********\n");
                printf("SAP ID      : %lld\n", s[topper].sapid);
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

        // 5. Delete a student record by SAP ID
        else if (choice == 5) {
            if (n == 0) {
                printf("\nNo records available to delete!\n");
            } else {
                long long delSapid;
                int found = 0;

                printf("\nEnter SAP ID of student to delete: ");
                scanf("%lld", &delSapid);

                for (i = 0; i < n; i++) {
                    if (s[i].sapid == delSapid) {
                        found = 1;

                        // Shift all remaining students one step to the left
                        for (j = i; j < n - 1; j++) {
                            s[j] = s[j + 1];
                        }

                        n--; // Decrease student count

                        // Save updated array to file
                        saveToFile(s, n);

                        printf("Student with SAP ID %lld deleted successfully!\n", delSapid);
                        printf("--> Updated records saved to 'students.txt'.\n");
                        break;
                    }
                }

                if (!found) {
                    printf("Student with SAP ID %lld not found!\n", delSapid);
                }
            }
        }

        // 6. Exit
        else if (choice == 6) {
            printf("\nExiting program. Thank you!\n");
            break;
        }

        // Invalid choice
        else {
            printf("\nInvalid choice! Please enter a number from 1 to 6.\n");
        }
    }

    return 0;
}
