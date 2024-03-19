#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void insertByOrder(int *arr, int *n, int key);
void deleteByPosition(int *arr, int *n, int pos);
void searchByKey(int *arr, int *n, int key);
void reverse(int *arr, int *n);
void printArray(int *arr, int *n);

// Function to insert an element in sorted order
void insertByOrder(int *arr, int *n, int key) {
    int i = *n - 1;
    // Shift elements to make space for new element
    while (i >= 0 && arr[i] > key) {
        arr[i + 1] = arr[i];
        i--;
    }
    // Insert the new element
    arr[i + 1] = key;
    (*n)++;
}

// Function to delete an element by position
void deleteByPosition(int *arr, int *n, int pos) {
    if (pos < 1 || pos > *n) {
        printf("Invalid position\n");
        return;
    }
    // Shift elements to overwrite the deleted element
    for (int i = pos - 1; i < *n - 1; i++) {
        arr[i] = arr[i + 1];
    }
    (*n)--;
}

// Function to search for an element by its value
void searchByKey(int *arr, int *n, int key) {
    for (int i = 0; i < *n; i++) {
        if (arr[i] == key) {
            printf("Key %d found at position %d\n", key, i + 1);
            return;
        }
    }
    printf("Key %d not found\n", key);
}

// Function to reverse the elements of the array
void reverse(int *arr, int *n) {
    for (int i = 0; i < *n / 2; i++) {
        int temp = arr[i];
        arr[i] = arr[*n - i - 1];
        arr[*n - i - 1] = temp;
    }
}

// Function to print the elements of the array
void printArray(int *arr, int *n) {
    printf("Current array: ");
    for (int i = 0; i < *n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int *arr, n, c, choice;
    int pos, key;
    // Input capacity and size of the array
    printf("Enter the capacity and size of the array: ");
    scanf("%d %d", &c, &n);
    arr = (int *)malloc(c * sizeof(int));
    // Input elements of the array in sorted order
    printf("Enter %d elements of the array in sorted order:\n", n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    // Menu-driven program loop
    do {
        printf("\nMenu: \n");
        printf("1. Insert by order.\n");
        printf("2. Delete by position.\n");
        printf("3. Search by key.\n");
        printf("4. Reverse the content.\n");
        printf("5. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter the element to insert: ");
                scanf("%d", &key);
                insertByOrder(arr, &n, key);
                break;
            case 2:
                printf("Enter the position to delete: ");
                scanf("%d", &pos);
                deleteByPosition(arr, &n, pos);
                break;
            case 3:
                printf("Enter the key to search: ");
                scanf("%d", &key);
                searchByKey(arr, &n, key);
                break;
            case 4:
                printf("The contents of the array after reversing are:\n");
                reverse(arr, &n);
                break;
            case 5:
                printf("Exiting the program\n");
                free(arr);
                return 0;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
        printArray(arr, &n);
    } while (choice != 5);
    return 0;
}
