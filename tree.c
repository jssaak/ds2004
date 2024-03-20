#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct node {
    struct node *llink;
    struct node *rlink;
    int data;
};

typedef struct node *NODE;

NODE getNode(int data) {
    NODE n = (NODE)malloc(sizeof(struct node));
    n->data = data;
    n->llink = NULL;
    n->rlink = NULL;
    return n;
}

NODE insert(NODE root, int data) {
    if (root == NULL) {
        NODE temp = getNode(data);
        return temp;
    }
    if (data < root->data) {
        root->llink = insert(root->llink, data);
    } else
        root->rlink = insert(root->rlink, data);
    return root;
}

void preorder(NODE root) {
    if (root == NULL) {
        return;
    }
    printf("%d\t", root->data);
    preorder(root->llink);
    preorder(root->rlink);
}

void inorder(NODE root) {
    if (root == NULL) {
        return;
    }
    inorder(root->llink);
    printf("%d\t", root->data);
    inorder(root->rlink);
}

void postorder(NODE root) {
    if (root == NULL) {
        return;
    }
    postorder(root->llink);
    postorder(root->rlink);
    printf("%d\t", root->data);
}

NODE searchByKey(NODE prev, NODE root, int key, int *exist) {
    if (root == NULL) {
        return NULL;
    }

    if (root->data == key) {
        *exist = 1;
        return prev;
    }
    NODE x;
    if (key < root->data) {
        x = searchByKey(root, root->llink, key, exist);
    } else {
        x = searchByKey(root, root->rlink, key, exist);
    }

    return x;
}

int countNodes(NODE root) {
    if (root == NULL) {
        return 0;
    }
    // Count current node + nodes in left subtree + nodes in right subtree
    return 1 + countNodes(root->llink) + countNodes(root->rlink);
}

int height(NODE root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + fmax(height(root->llink), height(root->rlink));
}

NODE findMax(NODE root, NODE *parent) {
    //  parent = NULL;
    NODE temp = root;
    if (temp == NULL) {
        return NULL;
    }
    while (temp->rlink != NULL) {
        *parent = temp;
        temp = temp->rlink;
    }
    return temp;
}

NODE findInorderSuccessor(NODE root) {
    while (root->llink != NULL) {
        root = root->llink;
    }
    return root;
}

NODE deleteNode(NODE root, int key) {
    if (root == NULL) {
        printf("Node not found\n");
        return NULL;
    }
    if (root->data < key) {
        root->rlink = deleteNode(root->rlink, key);
    } else if (root->data > key) {
        root->llink = deleteNode(root->llink, key);
    } else {
        // case -1 ->no child node
        if (root->llink == NULL && root->rlink == NULL) {
            return NULL;
        }
        // case 2-> 1 child node
        if (root->llink == NULL) {
            return root->rlink;
        }
        if (root->rlink == NULL)
            return root->llink;
        // case 3-> 2 child nodes
        NODE IS = findInorderSuccessor(root->rlink);
        root->data = IS->data;
        root->rlink = deleteNode(root->rlink, IS->data);
    }
    return root;
}

void main() {
    NODE root = NULL;
    int arr[] = {6, 2, 10, 4, 5, 7, 8, 3, 1, 9};
    /*          6
              /  \
             2   10
            / \  /
           1  4  7
             / \  \
            3  5   8
                    \
                     9
    */
    for (int i = 0; i < 10; i++) {
        root = insert(root, arr[i]);
    }
    NODE parent;
    NODE maxNode;
    int ch;
    printf("Enter 1. insert\n2. preorder\n3. inorder\n4. postorder\n5. search node by key\n6. count nodes\n7. find height\n8. max value\n9. delete a node by key\n10. Exit");
    while (1) {
        printf("\nEnter choice :");
        scanf("%d", &ch);
        switch (ch) {
        case 1:
            printf("Enter the value of node to be inserted : ");
            int x;
            scanf("%d", &x);
            root = insert(root, x);
            break;
        case 2:
            preorder(root);
            break;
        case 3:
            inorder(root);
            break;
        case 4:
            postorder(root);
            break;
        case 5:
            printf("Enter the data to be searched : ");
            int y;
            scanf("%d", &y);

            int exist;
            NODE temp = searchByKey(NULL, root, y, &exist);
            if (exist == 1) {
                if (temp == NULL)
                    printf("Key found at Root node !\n");
                else {
                    printf("Key found !\n");
                    printf("Parent -> %d\n", temp->data);
                }
            } else {
                printf("Key not found !\n");
            }
            break;
        case 6:
            printf("No. of Nodes are : %d\n", countNodes(root));
        case 7:
            printf(" Height of the BST is : %d", height(root));
            break;
        case 8: // Finding maxnode and printing parent node details
            parent = NULL;
            maxNode = findMax(root, &parent);
            if (maxNode == NULL) {
                printf("BST is Empty");
            } else {
                if (parent == NULL) {
                    printf("Root node has the maximum value -> %d", maxNode->data);
                } else {
                    printf("Value of \nmaximum node is %d \nParent node is %d", maxNode->data, parent->data);
                }
            }
            break;
        case 9:
            printf("Enter the node value to be deleted : ");
            scanf("%d", &x);
            root = deleteNode(root, x);
            inorder(root);
            break;
        case 10:
            exit(0);
        default:
            printf("Invalid choice!");
            break;
        }
    }
}