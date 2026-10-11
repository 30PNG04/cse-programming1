#include "student.h"
#include <string.h>

void display_menu();
void add_student(Node **head);
void remove_student(Node **head);
void find_by_id(Node *head);
void update_gpa(Node *head);
void print_list(const Node *head);
void count_excellent(const Node *head);


int main() {
    Node *list = load_csv("data.csv");
    int choice;
    do {
        display_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            add_student(&list);
            break;
        case 2:
            remove_student(&list);
            break;
        case 3:
            find_by_id(list);
            break;
        case 4:
            update_gpa(list);
            break;
        case 5:
            print_list(list);
            break;
        case 6:
            count_excellent(list);
            break;
        case 0:
            printf("Exiting the library system.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 0);

    save_csv(list, "data.csv");
    list_free(list);
    return 0;
}

void display_menu() {
    printf("\nLibrary Management System\n");
    printf("1. Add student\n");
    printf("2. Remove student by ID\n");
    printf("3. Find student by ID\n");
    printf("4. Update GPA\n");
    printf("5. Print list (sorted by: id / name / GPA)\n");
    printf("6. Count excellent students\n");
    printf("0. Exit\n");
}

void add_student(Node **head) {
    printf("\nAdd student\n");

    int id;
    printf("ID: ");
    scanf("%d", &id);

    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    char name[MAX_NAME];
    printf("Name: ");
    fgets(name, MAX_NAME, stdin);
    name[strcspn(name, "\n")] = '\0';

    float gpa;
    printf("GPA: ");
    scanf("%f", &gpa);

    printf("\nAdding...\n");
    *head = list_push_back(*head, make_student(id, name, gpa));
}

void remove_student(Node **head) {
    printf("\nRemove student by ID\n");

    int id;
    printf("ID: ");
    scanf("%d", &id);

    printf("\nRemoving...\n");
    *head = list_remove(*head, id);
}

void find_by_id(Node *head) {
    printf("\nFind student by ID\n");

    int id;
    printf("ID: ");
    scanf("%d", &id);

    printf("\nFinding...\n");

    Student *s = list_find(head, id);

    if (s == NULL) {
        printf("Exitting...\n");
        return;
    }

    print_student(s);
}

void update_gpa(Node *head) {
    printf("\nUpdate GPA\n");
    
    int id;
    printf("ID: ");
    scanf("%d", &id);

    Student *p = list_find(head, id);
    if (p == NULL) {
        printf("\nReturning...\n");
        return;
    }

    printf("GPA: ");
    scanf("%f", &(p->gpa));

    printf("\nUpdating...\n");
}

void print_list(const Node *head) {
    int choice;

    do {
        printf("\nPrint list by\n");
        printf("0. ID\n");
        printf("1. Name\n");
        printf("2. GPA\n");

        printf("Choice: ");
        scanf("%d", &choice);
    } while (choice != 0 && choice != 1 && choice != 2);

    int max = list_length(head);
    Student arr[max];
    int n = list_to_array(head, arr, max);
    StudentCompare cmp[] = {compare_by_id, compare_by_name, compare_by_gpa_desc};

    sort_students(arr, n, cmp[choice]);

    printf("\nPrinting\n");
    for (int i = 0; i < n; i++) {
        print_student(&arr[i]);
    }
}

void count_excellent(const Node *head) {
    printf("\nCount excellent students\n");
    printf("%d excellent student(s)", count_if(head, is_excellent));
}