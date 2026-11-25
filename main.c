#include <stdio.h>

struct Student {
    long sap;
    char name[50];
    float marks[5];
    float total;
    float percent;
    char grade;
};

struct Student st[100];
int n = 0;
char subjects[5][15] = {"Maths", "Physics", "Chemistry", "English", "Computer"};

void addStudent() {
    struct Student s;
    int i;
    if (n >= 100) {
        printf("List is full!\n");
        return;
    }
    s.total = 0;

    do {
        printf("Enter SAP ID (e.g. 590032680): ");
        scanf("%ld", &s.sap);
        if (s.sap < 590000000 || s.sap > 590099999) {
            printf("Invalid SAP ID! Must start with 5900 and have 5 more digits.\n");
        }
    } while (s.sap < 590000000 || s.sap > 590099999);

    for (i = 0; i < n; i++) {
        if (st[i].sap == s.sap) {
            printf("SAP ID already exists!\n");
            return;
        }
    }

    printf("Enter first name: ");
    scanf("%s", s.name);

    for (i = 0; i < 5; i++) {
        do {
            printf("Marks in %s (0-100): ", subjects[i]);
            scanf("%f", &s.marks[i]);
        } while (s.marks[i] < 0 || s.marks[i] > 100);
        s.total = s.total + s.marks[i];
    }

    s.percent = s.total / 5;

    if (s.percent >= 90)
        s.grade = 'A';
    else if (s.percent >= 75)
        s.grade = 'B';
    else if (s.percent >= 60)
        s.grade = 'C';
    else if (s.percent >= 40)
        s.grade = 'D';
    else
        s.grade = 'F';

    st[n] = s;
    n++;
    printf("Added! Percentage: %.2f%%, Grade: %c\n", s.percent, s.grade);
}

void displayAll() {
    int i;
    if (n == 0) {
        printf("No records found.\n");
        return;
    }
    printf("\nSAP ID\t\tName\tTotal\tPercent\tGrade\tResult\n");
    for (i = 0; i < n; i++) {
        printf("%ld\t%s\t%.1f\t%.2f%%\t%c\t",
               st[i].sap, st[i].name, st[i].total, st[i].percent, st[i].grade);
        if (st[i].grade == 'F')
            printf("FAIL\n");
        else
            printf("PASS\n");
    }
}

void searchStudent() {
    long id;
    int i;
    printf("Enter SAP ID: ");
    scanf("%ld", &id);

    for (i = 0; i < n; i++) {
        if (st[i].sap == id) {
            printf("Found: %s | Total: %.1f | Percent: %.2f%% | Grade: %c\n",
                   st[i].name, st[i].total, st[i].percent, st[i].grade);
            return;
        }
    }
    printf("Student not found.\n");
}

void deleteStudent() {
    long id;
    int i, j;
    printf("Enter SAP ID to delete: ");
    scanf("%ld", &id);

    for (i = 0; i < n; i++) {
        if (st[i].sap == id) {
            for (j = i; j < n - 1; j++)
                st[j] = st[j + 1];
            n--;
            printf("Record deleted.\n");
            return;
        }
    }
    printf("Student not found.\n");
}

void rankAndSummary() {
    int i, j, pass = 0;
    int gradeCount[5] = {0};
    char grades[5] = {'A', 'B', 'C', 'D', 'F'};
    float sum = 0;
    struct Student temp;

    if (n == 0) {
        printf("No records found.\n");
        return;
    }

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (st[j].percent < st[j + 1].percent) {
                temp = st[j];
                st[j] = st[j + 1];
                st[j + 1] = temp;
            }
        }
    }

    printf("\n--- Rank List ---\n");
    for (i = 0; i < n; i++) {
        printf("%d. %s (SAP ID: %ld) - %.2f%% [%c]\n",
               i + 1, st[i].name, st[i].sap, st[i].percent, st[i].grade);
        sum = sum + st[i].percent;
        if (st[i].grade != 'F')
            pass++;

        switch (st[i].grade) {
            case 'A': gradeCount[0]++; break;
            case 'B': gradeCount[1]++; break;
            case 'C': gradeCount[2]++; break;
            case 'D': gradeCount[3]++; break;
            default:  gradeCount[4]++; break;
        }
    }

    printf("\nClass Average: %.2f%%\n", sum / n);
    printf("Topper: %s (%.2f%%)\n", st[0].name, st[0].percent);
    printf("Lowest: %s (%.2f%%)\n", st[n - 1].name, st[n - 1].percent);
    printf("Passed: %d out of %d\n", pass, n);

    printf("\nGrade Chart:\n");
    for (i = 0; i < 5; i++) {
        printf("%c | ", grades[i]);
        for (j = 0; j < gradeCount[i]; j++)
            printf("*");
        printf(" (%d)\n", gradeCount[i]);
    }

    printf("\nFailing List (below 40%%):\n");
    if (pass == n) {
        printf("None!\n");
    } else {
        for (i = 0; i < n; i++) {
            if (st[i].grade == 'F')
                printf("- %s (SAP ID: %ld): %.2f%%\n", st[i].name, st[i].sap, st[i].percent);
        }
    }
}

int main() {
    int choice;

    do {
        printf("\n1. Add Student\n2. Display All\n3. Search\n4. Rank & Summary\n5. Delete Student\n6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayAll(); break;
            case 3: searchStudent(); break;
            case 4: rankAndSummary(); break;
            case 5: deleteStudent(); break;
            case 6: printf("Goodbye!\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 6);

    return 0;
}
