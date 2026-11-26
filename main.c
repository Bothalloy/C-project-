#include <stdio.h>
struct Student {
    long sap;
    char name[50], grade;
    float marks[5], total, percent;
} st[100];
int n = 0; char sub[5][10] = {"Math", "Phy", "Chem", "Eng", "Comp"};
void addStudent() {
    struct Student s = {0};
    if (n >= 100) { printf("List is full!\n"); return; }
    do {
        printf("Enter SAP ID (e.g. 590032680): ");
        scanf("%ld", &s.sap);
    } while (s.sap < 590000000 || s.sap > 590099999);
    for (int i = 0; i < n; i++)
        if (st[i].sap == s.sap) { printf("SAP ID already exists!\n"); return; }
    printf("Enter name: ");
    scanf("%s", s.name);
    for (int i = 0; i < 5; i++) {
        do {
            printf("%s marks (0-100): ", sub[i]);
            scanf("%f", &s.marks[i]);
        } while (s.marks[i] < 0 || s.marks[i] > 100);
        s.total = s.total + s.marks[i];
    }
    s.percent = s.total / 5;
    s.grade = (s.percent >= 90) ? 'A' : (s.percent >= 75) ? 'B' : (s.percent >= 60) ? 'C' : (s.percent >= 40) ? 'D' : 'F';
    st[n] = s;
    n = n + 1;
    printf("Added! Percentage: %.2f%%, Grade: %c\n", s.percent, s.grade);
}

void displayAll() {
    if (n == 0) { printf("No records found.\n"); return; }
    printf("\nSAP ID\t\tName\tTotal\tPercent\tGrade\tResult\n");
    for (int i = 0; i < n; i++)
        printf("%ld\t%s\t%.1f\t%.2f%%\t%c\t%s\n", st[i].sap, st[i].name, st[i].total, st[i].percent, st[i].grade, st[i].grade == 'F' ? "FAIL" : "PASS");
}

void searchStudent() {
    long id;
    printf("Enter SAP ID: ");
    scanf("%ld", &id);
    for (int i = 0; i < n; i++)
        if (st[i].sap == id) {
            printf("Found: %s | Total: %.1f | Percent: %.2f%% | Grade: %c\n", st[i].name, st[i].total, st[i].percent, st[i].grade);
            return;
        }
    printf("Student not found.\n");
}

void deleteStudent() {
    long id;
    printf("Enter SAP ID to delete: ");
    scanf("%ld", &id);
    for (int i = 0; i < n; i++)
        if (st[i].sap == id) {
            for (int j = i; j < n - 1; j++) st[j] = st[j + 1];
            n = n - 1;
            printf("Record deleted.\n");
            return;
        }
    printf("Student not found.\n");
}

void rankAndSummary() {
    if (n == 0) { printf("No records found.\n"); return; }
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (st[j].percent < st[j + 1].percent) {
                struct Student temp = st[j]; st[j] = st[j + 1]; st[j + 1] = temp;
            }
    float sum = 0;
    int pass = 0;
    printf("\n--- Rank List ---\n");
    for (int i = 0; i < n; i++) {
        printf("%d. %s (%ld) - %.2f%% [%c]\n", i + 1, st[i].name, st[i].sap, st[i].percent, st[i].grade);
        sum = sum + st[i].percent;
        if (st[i].grade != 'F') pass = pass + 1;
    }
    printf("\nClass Average: %.2f%%\nTopper: %s (%.2f%%)\nLowest: %s (%.2f%%)\nPassed: %d out of %d\n", sum / n, st[0].name, st[0].percent, st[n - 1].name, st[n - 1].percent, pass, n);
}

int main() {
    int choice;
    do {
        printf("\n1. Add Student\n2. Display All\n3. Search\n4. Rank & Summary\n5. Delete Student\n6. Exit\nEnter choice: ");
        scanf("%d", &choice);
        if (choice == 1) addStudent();
        else if (choice == 2) displayAll();
        else if (choice == 3) searchStudent();
        else if (choice == 4) rankAndSummary();
        else if (choice == 5) deleteStudent();
        else if (choice == 6) printf("Goodbye!\n");
        else printf("Invalid choice!\n");
    } while (choice != 6);
    return 0;
}
