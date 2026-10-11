// Lab 4 — Student management module: IMPLEMENTATION
// Task: implement the functions marked TODO. Run "make test" to check.
#include <stdlib.h>
#include <string.h>
#include "student.h"

// ===================== 4.1 Struct =====================

// Create a Student. Names longer than MAX_NAME - 1 characters are truncated
// (hint: strncpy then set '\0' at the end yourself, or use snprintf).
Student make_student(int id, const char *name, float gpa) {
    Student s = {0};
    s.id = id;
    snprintf(s.name, MAX_NAME, "%s", name);
    s.gpa = gpa;
    return s;
}

// Print one line in the form:  "  1001  Nguyen Van An                  3.45"
void print_student(const Student *s) {
    printf("%6d  %-30s %.2f\n", s->id, s->name, s->gpa);
}

// ===================== 4.2 Linked list =====================

// Insert at the front of the list, return the new head

Node *list_push_front(Node *head, Student s) {
    Node *new_head = malloc(sizeof(*new_head));
    if (new_head == NULL) {
        DEBUG_PRINT("list_push_front: malloc error");
        return head;
    }

    new_head->data = make_student(s.id, s.name, s.gpa);
    new_head->next = head;

    DEBUG_PRINT("push_front id=%d", s.id);
    return new_head;
}

// Insert at the end of the list, return head (changes if the list was empty)
Node *list_push_back(Node *head, Student s) {
    Node *tmp = malloc(sizeof *tmp);
    if (tmp == NULL) {
        DEBUG_PRINT("list_push_back: malloc error");
        return head;
    }

    tmp->data = make_student(s.id, s.name, s.gpa);
    tmp->next = NULL;

    if (head == NULL) {
        head = tmp;
        return head;
    }

    Node *buf = head;

    while (buf->next != NULL) buf = buf->next;

    buf->next = tmp;
    
    DEBUG_PRINT("push_back id=%d", s.id);
    return head;
}

// Number of elements
int list_length(const Node *head) {
    int i = 0;

    for (; head != NULL; i++) 
        head = head->next;

    return i;
}

// Find by id; return a pointer to the Student in the list (so it can be modified), or NULL
Student *list_find(Node *head, int id) {
    if (head == NULL) return NULL;

    do {
        if (head->data.id == id) {
            Student *p = &(head->data);
            return p;
        }

        head = head->next;
    } while (head != NULL);

    return NULL;
}

// Remove the first node with the matching id (remember to free it), return the new head.
// If the id is not found, leave the list unchanged.
Node *list_remove(Node *head, int id) {
    if(head == NULL) return NULL;

    if (head->data.id == id) {
        Node *tmp = head->next;
        free(head);
        return tmp;
    }

    Node *buf = head;
    
    do {
        if (buf->next->data.id == id) {
            Node *tmp = buf->next;
            buf->next = buf->next->next;
            
            free(tmp);
            break;
        }

        buf = buf->next;
    } while (buf->next != NULL);

    return head;
}

// Print the whole list
void list_print(const Node *head) {
    for (const Node *p = head; p != NULL; p = p->next)
        print_student(&p->data);
}

// Free the whole list
void list_free(Node *head) {
    while (head != NULL) {
        Node *tmp = head->next;
        free(head);
        head = tmp;
    }
}

// ===================== 4.3 Function pointers =====================

// Comparison functions for qsort: a, b are pointers to Student.
// Return < 0 if a comes before b, 0 if equal, > 0 if a comes after b.

int compare_by_id(const void *a, const void *b) {
    const Student *x = a, *y = b;
    return x->id - y->id; // example
}

int compare_by_name(const void *a, const void *b) {
    const Student *x = a, *y = b;
    return strcmp(x->name, y->name);
}

// GPA in descending order (higher GPA first). Careful: gpa is a float, do not return x->gpa - y->gpa!
int compare_by_gpa_desc(const void *a, const void *b) {
    const Student *x = a, *y = b;
    if (x->gpa > y->gpa) return -1;
    else if(x->gpa == y->gpa) return 0;
    else return 1;
}

// Copy at most max elements of the list into the array out, return the number copied
int list_to_array(const Node *head, Student out[], int max) {
    if (head == NULL) return 0;

    int i = 0;
    for (; i < max && head != NULL; i++) {
        out[i] = make_student(head->data.id, head->data.name, head->data.gpa);
        head = head->next;
    }

    return i;
}

// Sort the array using the comparison function cmp
void sort_students(Student arr[], int n, StudentCompare cmp) {
    qsort(arr, n, sizeof(*arr), cmp);
}

// Excellent student: gpa >= 3.6
int is_excellent(const Student *s) {
    return s->gpa >= 3.6;
}

// Count the students that satisfy pred

/*FOR CSV HANDLING*/
int count_if(const Node *head, StudentPredicate pred) {
    int i = 0;
    while (head != NULL) {
        i += pred(&(head->data));
        head = head->next;
    }

    return i;
}

int save_csv(const Node *head, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) return 0;

    while (head != NULL) {
        fprintf(file, "%d,%s,%0.2f\n", head->data.id, head->data.name, head->data.gpa);
        head = head->next;
    }

    fclose(file);
    return 1;
}

Node *load_csv(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) return NULL;

    Node *list = NULL;
    Student s;

    while (fscanf(file, "%d,%49[^,],%f",
                &s.id, s.name, &s.gpa) == 3) {
        list = list_push_back(list, s);
    }

    fclose(file);
    return list;
}

/*Re-implement for binary tree*/
Node_t *tree_add (Node_t *tree, Student s) {
    Node_t *node = calloc(1, sizeof(*node));
    Node_t **buf = &tree;
    if (node == NULL) {
        DEBUG_PRINT("tree_add: malloc error");
        return tree;
    }

    node->data = make_student(s.id, s.name, s.gpa);

    while (*buf != NULL) {
        if((*buf)->data.id == node->data.id) break;
        buf = (*buf)->data.id < node->data.id ? &((*buf)->right) : &((*buf)->left);
    }
    
    *buf = node;

    DEBUG_PRINT("tree_add id=%d", s.id);
    return tree;
}

// Number of elements
int tree_size(const Node_t *tree) {
    int count = 0;
    if(tree != NULL) {
        count++;
        count += tree_length(tree->left);
        count += tree_length(tree->right);
    }

    return count;
}

// Find by id; return a pointer to the Student in the list (so it can be modified), or NULL
Student *tree_find(Node_t *tree, int id) {
    if(tree == NULL) return NULL;

    Student *p;
    if(tree->data.id == id) {
        p = &(tree->data);
        return p;
    } else if ((p = tree_find(tree->right, id)) == NULL) {
        p = tree_find(tree->left, id);
    }

    return p;
}

// Remove the first node with the matching id (remember to free it), return the new head.
// If the id is not found, leave the list unchanged.

Node_t *tree_remove(Node_t *tree, int id) {
    if(tree == NULL) return NULL;

    Node_t *buf = NULL;
    if(tree->data.id == id) {
        Node_t *tmp = tree->right;


        buf = tree->left;

        if(buf == NULL) {
            free(tree);
            return tmp;
        }

        while (buf->right != NULL) buf = buf->right;
        buf->right = tmp;

        free(tree);
        return buf;
    } else if (id < tree->data.id) tree->left = tree_remove(tree->left, id);
    else tree->right = tree_remove(tree->right, id);

    return tree;
}

// Print the whole list
void tree_print(const Node_t *tree) {
    if(tree == NULL) return;
    print_student(&(tree->data));
    tree_print(tree->left);
    tree_print(tree->right);
}

// Free the whole list
void tree_free(Node_t *tree) {
    if(tree == NULL) return;
    tree_free(tree->left);
    tree_free(tree->right);
    free(tree);
}

//TODO continue
int list_to_array(const Node_t *tree, Student out[], int max) {
    if (tree == NULL) return 0;

    int i = 0;
    for (; i < max && head != NULL; i++) {
        out[i] = make_student(head->data.id, head->data.name, head->data.gpa);
        head = head->next;
    }

    return i;
}

int count_if(const Node *head, StudentPredicate pred) {
    int i = 0;
    while (head != NULL) {
        i += pred(&(head->data));
        head = head->next;
    }

    return i;
}

int save_csv(const Node *head, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) return 0;

    while (head != NULL) {
        fprintf(file, "%d,%s,%0.2f\n", head->data.id, head->data.name, head->data.gpa);
        head = head->next;
    }

    fclose(file);
    return 1;
}