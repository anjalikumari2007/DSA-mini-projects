
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Student {
    int id;
    char name[50];
    char department[50];
};

struct Node {
    struct Student data;
    struct Node *left;
    struct Node *right;
};

struct Node* createNode(int id, char name[], char department[]) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));

    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->data.id = id;
    strcpy(newNode->data.name, name);
    strcpy(newNode->data.department, department);

    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

struct Node* insert(struct Node *root, int id, char name[], char department[]) {

    if (root == NULL) {
        printf("Student record inserted successfully!\n");
        return createNode(id, name, department);
    }

    if (id < root->data.id) {
        root->left = insert(root->left, id, name, department);
    }
    else if (id > root->data.id) {
        root->right = insert(root->right, id, name, department);
    }
    else {
        printf("Duplicate enrolment ID! Record not inserted.\n");
    }

    return root;
}

struct Node* search(struct Node *root, int id, int *comparisons) {

    if (root == NULL)
        return NULL;

    (*comparisons)++;

    if (id == root->data.id)
        return root;

    if (id < root->data.id)
        return search(root->left, id, comparisons);

    return search(root->right, id, comparisons);
}

struct Node* findMin(struct Node *root) {

    while (root != NULL && root->left != NULL) {
        root = root->left;
    }

    return root;
}

struct Node* deleteNode(struct Node *root, int id) {

    if (root == NULL) {
        return NULL;
    }

    if (id < root->data.id) {
        root->left = deleteNode(root->left, id);
    }
    else if (id > root->data.id) {
        root->right = deleteNode(root->right, id);
    }
    else {

        if (root->left == NULL && root->right == NULL) {
            free(root);
            printf("Student record deleted successfully!\n");
            return NULL;
        }

        else if (root->left == NULL) {
            struct Node *temp = root->right;
            free(root);
            printf("Student record deleted successfully!\n");
            return temp;
        }
        else if (root->right == NULL) {
            struct Node *temp = root->left;
            free(root);
            printf("Student record deleted successfully!\n");
            return temp;
        }

        else {
            struct Node *temp = findMin(root->right);

            root->data = temp->data;

            root->right = deleteNode(root->right, temp->data.id);
        }
    }

    return root;
}

void inorder(struct Node *root) {

    if (root != NULL) {
        inorder(root->left);

        printf("%-10d %-20s %-20s\n",
               root->data.id,
               root->data.name,
               root->data.department);

        inorder(root->right);
    }
}

void preorder(struct Node *root) {

    if (root != NULL) {
        printf("%d ", root->data.id);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct Node *root) {

    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data.id);
    }
}

void displayStudent(struct Node *student) {

    if (student == NULL) {
        printf("Student record not found!\n");
        return;
    }

    printf("\nStudent Details\n");
    printf("-------------------------\n");
    printf("Enrolment ID : %d\n", student->data.id);
    printf("Name         : %s\n", student->data.name);
    printf("Department   : %s\n", student->data.department);
}

void loadSamples(struct Node **root) {
	int i;

    int ids[] = {105, 103, 107, 101, 104,
                 106, 109, 102, 108, 110};

    char names[10][50] = {
        "Aarav", "Priya", "Rahul", "Ananya", "Rohan",
        "Neha", "Karan", "Sneha", "Arjun", "Meera"
    };

    char departments[10][50] = {
        "CSE", "IT", "ECE", "CSE", "IT",
        "ECE", "CSE", "IT", "ECE", "CSE"
    };

    for (i = 0; i < 10; i++) {
        *root = insert(*root, ids[i], names[i], departments[i]);
    }

    printf("\n10 sample records loaded successfully!\n");
}

void freeTree(struct Node *root) {

    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {

    struct Node *root = NULL;
    struct Node *result;

    int choice, id, comparisons;
    char name[50], department[50];

    do {

        printf("\n====================================\n");
        printf("   STUDENT RECORD SEARCH SYSTEM\n");
        printf("       USING BINARY SEARCH TREE\n");
        printf("====================================\n");

        printf("1. Insert Student Record\n");
        printf("2. Search Student Record\n");
        printf("3. Delete Student Record\n");
        printf("4. Display Inorder Traversal\n");
        printf("5. Display Preorder Traversal\n");
        printf("6. Display Postorder Traversal\n");
        printf("7. Load 10 Sample Records\n");
        printf("8. Exit\n");

        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Enter a number.\n");

            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);
            continue;
        }

        switch (choice) {

            case 1:
                printf("Enter Enrolment ID: ");
                if (scanf("%d", &id) != 1) {
                    printf("Invalid ID!\n");
                    while (getchar() != '\n');
                    break;
                }

                printf("Enter Student Name: ");
                scanf(" %49[^\n]", name);

                printf("Enter Department: ");
                scanf(" %49[^\n]", department);

                root = insert(root, id, name, department);
                break;

            case 2:
                printf("Enter Enrolment ID to search: ");

                if (scanf("%d", &id) != 1) {
                    printf("Invalid ID!\n");
                    while (getchar() != '\n');
                    break;
                }

                comparisons = 0;
                result = search(root, id, &comparisons);

                displayStudent(result);

                printf("Number of comparisons: %d\n", comparisons);
                break;

            case 3:
                printf("Enter Enrolment ID to delete: ");

                if (scanf("%d", &id) != 1) {
                    printf("Invalid ID!\n");
                    while (getchar() != '\n');
                    break;
                }

                comparisons = 0;
                result = search(root, id, &comparisons);

                if (result == NULL) {
                    printf("Student record not found!\n");
                }
                else {
                    root = deleteNode(root, id);
                }
                break;

            case 4:
                printf("\nSTUDENT RECORDS (SORTED BY ID)\n");
                printf("-----------------------------------------------\n");
                printf("%-10s %-20s %-20s\n",
                       "ID", "NAME", "DEPARTMENT");
                inorder(root);
                break;

            case 5:
                printf("\nPreorder Traversal: ");
                preorder(root);
                printf("\n");
                break;

            case 6:
                printf("\nPostorder Traversal: ");
                postorder(root);
                printf("\n");
                break;

            case 7:
                loadSamples(&root);
                break;

            case 8:
                printf("\nExiting Student Record System...\n");
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }

    } while (choice != 8);

    freeTree(root);

    return 0;
}
