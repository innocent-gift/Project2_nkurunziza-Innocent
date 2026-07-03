#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUDENT_ID_HEADER "54321"

typedef struct {
    int id;
    char name[50];
    float grade;
} Student;

// Function prototypes for operations
void add_students(Student *arr, int *count, int max);
void display_students(Student *arr, int count);
void sort_students(Student *arr, int count);
void calculate_average(Student *arr, int count);
void find_top_student(Student *arr, int count);
void run_custom_analysis(Student *arr, int count); // Custom: Performance Classification

int main() {
    int max_students = 15;
    int current_count = 0;
    
    // Dynamic Memory Allocation
    Student *student_array = (Student *)malloc(max_students * sizeof(Student));
    if (!student_array) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Seed initial dataset (10 students) as required
    Student initial_data[10] = {
        {101, "Alice Smith", 88.5}, {102, "Bob Jones", 92.0},
        {103, "Charlie Brown", 71.5}, {104, "Diana Prince", 95.5},
        {105, "Evan Wright", 64.0}, {106, "Fiona Gallagher", 83.0},
        {107, "George Brooks", 77.5}, {108, "Hannah Abbott", 91.0},
        {109, "Ian Malcolm", 55.0}, {110, "Julia Roberts", 89.0}
    };
    
    Student *ptr = student_array;
    for(int i = 0; i < 10; i++) {
        *ptr = initial_data[i];
        ptr++;
        current_count++;
    }

    // Function Pointer Array for Menu Operations
    void (*operations[])(Student*, int*) = {
        (void (*)(Student*, int*))display_students,
        (void (*)(Student*, int*))sort_students,
        (void (*)(Student*, int*))calculate_average,
        (void (*)(Student*, int*))find_top_student,
        (void (*)(Student*, int*))run_custom_analysis
    };

    int choice;
    do {
        printf("\n====================================\n");
        printf("STUDENT ID: %s\n", STUDENT_ID_HEADER);
        printf("====================================\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Sort Students (By Grade Descending)\n");
        printf("4. Calculate Average Grade\n");
        printf("5. Find Top Student\n");
        printf("6. Run Custom Analysis (Performance Classification)\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            add_students(student_array, &current_count, max_students);
        } else if (choice >= 2 && choice <= 6) {
            if (current_count == 0) {
                printf("No student records available.\n");
            } else {
                // Invoking operations via function pointers
                operations[choice - 2](student_array, (int *)(long)current_count);
            }
        }
    } while (choice != 7);

    free(student_array);
    return 0;
}

void add_students(Student *arr, int *count, int max) {
    if (*count >= max) {
        printf("Engine capacity full!\n");
        return;
    }
    // Pointer traversal to find insertion slot
    Student *target = arr + *count; 
    printf("Enter ID: ");
    scanf("%d", &target->id);
    printf("Enter Name: ");
    getchar(); // Clear buffer
    fgets(target->name, sizeof(target->name), stdin);
    target->name[strcspn(target->name, "\n")] = 0; // Strip newline
    printf("Enter Grade: ");
    scanf("%f", &target->grade);
    (*count)++;
    printf("Student added successfully.\n");
}

void display_students(Student *arr, int count) {
    printf("\n%-5s %-20s %-5s\n", "ID", "Name", "Grade");
    printf("----------------------------------------\n");
    // Pointer traversal
    for (Student *ptr = arr; ptr < arr + count; ptr++) {
        printf("%-5d %-20s %-5.2f\n", ptr->id, ptr->name, ptr->grade);
    }
}

void sort_students(Student *arr, int count) {
    // Bubble sort using pure pointer manipulation
    for (Student *i = arr; i < arr + count - 1; i++) {
        for (Student *j = arr; j < arr + count - 1 - (i - arr); j++) {
            if (j->grade < (j + 1)->grade) {
                Student temp = *j;
                *j = *(j + 1);
                *(j + 1) = temp;
            }
        }
    }
    printf("Students sorted by grade successfully.\n");
    display_students(arr, count);
}

void calculate_average(Student *arr, int count) {
    float sum = 0;
    for (Student *ptr = arr; ptr < arr + count; ptr++) {
        sum += ptr->grade;
    }
    printf("\nAverage Grade of Class: %.2f\n", sum / count);
}

void find_top_student(Student *arr, int count) {
    Student *top = arr;
    for (Student *ptr = arr + 1; ptr < arr + count; ptr++) {
        if (ptr->grade > top->grade) {
            top = ptr;
        }
    }
    printf("\nTop Performing Student: %s (ID: %d) with Grade: %.2f\n", top->name, top->id, top->grade);
}

// Custom Analysis Function: Performance Classification
void run_custom_analysis(Student *arr, int count) {
    printf("\nCustom Analysis: Performance Classification\n");
    printf("----------------------------------------\n");
    for (Student *ptr = arr; ptr < arr + count; ptr++) {
        char rating;
        if (ptr->grade >= 90) rating = 'A';
        else if (ptr->grade >= 80) rating = 'B';
        else if (ptr->grade >= 70) rating = 'C';
        else if (ptr->grade >= 60) rating = 'D';
        else rating = 'F';
        
        printf("ID: %d | %-20s | Grade: %-5.2f | Status: Standing [%c]\n", ptr->id, ptr->name, ptr->grade, rating);
    }
}
