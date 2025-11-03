#include <stdio.h>
#include <string.h>

#define MAX 100

struct Student {
    int rollNo;
    char name[50];
    float marks;
};

struct Student students[MAX];
int count = 0;

void createStudent() {
    if (count >= MAX) {
        printf("Cannot add more students.\n");
        return;
    }

    printf("Enter roll number: ");
    scanf("%d", &students[count].rollNo);
    printf("Enter name: ");
    scanf(" %[^\n]s", students[count].name);
    printf("Enter marks: ");
    scanf("%f", &students[count].marks);

    printf("Student added successfully.\n");
    count++;
}

void displayStudents() {
    if (count == 0) {
        printf("No students to display.\n");
        return;
    }

    printf("\n--- Student Records ---\n");
    for (int i = 0; i < count; i++) {
        printf("Roll No: %d, Name: %s, Marks: %.2f\n",
               students[i].rollNo, students[i].name, students[i].marks);
    }
}

void updateStudent() {
    int roll, found = 0;
    printf("Enter roll number to update: ");
    scanf("%d", &roll);

    for (int i = 0; i < count; i++) {
        if (students[i].rollNo == roll) {
            printf("Enter new name: ");
            scanf(" %[^\n]s", students[i].name);
            printf("Enter new marks: ");
            scanf("%f", &students[i].marks);
            printf("Student updated successfully.\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student with roll number %d not found.\n", roll);
}

void deleteStudent() {
    int roll, found = 0;
    printf("Enter roll number to delete: ");
    scanf("%d", &roll);

    for (int i = 0; i < count; i++) {
        if (students[i].rollNo == roll) {
            for (int j = i; j < count - 1; j++) {
                students[j] = students[j + 1];
            }
            count--;
            printf("Student deleted successfully.\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student with roll number %d not found.\n", roll);
}

void reflectOnDataTypes() {
    printf("\n--- Data Type Reflection ---\n");
    printf("Primitive Data Types:\n");
    printf("Examples: int, float, char\n");
    printf("They store a single piece of data.\n\n");

    printf("Abstract Data Types (ADTs):\n");
    printf("Examples: Student, Book, Employee (modeled using struct)\n");
    printf("They combine multiple data items into one logical unit.\n");
    printf("They support operations like create, update, delete, etc.\n");
}

int main() {
    int choice;

    do {
        printf("\n-- Student Management Menu --\n");
        printf("1. Create Student\n");
        printf("2. Display Students\n");
        printf("3. Update Student\n");
        printf("4. Delete Student\n");
        printf("5. Show Data Type Differences\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createStudent(); break;
            case 2: displayStudents(); break;
            case 3: updateStudent(); break;
            case 4: deleteStudent(); break;
            case 5: reflectOnDataTypes(); break;
            case 6: printf("Exiting program.\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 6);

    return 0;
}
