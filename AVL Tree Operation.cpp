#include <stdio.h>
#include <stdlib.h>


struct Node {
    int data;
    char color;
    struct Node *left, *right, *parent;
};


struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->color = 'R';
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}


void leftRotate(struct Node **root, struct Node *x) {
    struct Node *y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        (*root) = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}


void rightRotate(struct Node **root, struct Node *y) {
    struct Node *x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == NULL)
        (*root) = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}


void fixViolation(struct Node **root, struct Node *pt) {
    struct Node *parent_pt = NULL;
    struct Node *grand_parent_pt = NULL;
    while ((pt != (*root)) && (pt->color != 'B') && (pt->parent->color == 'R')) {
        parent_pt = pt->parent;
        grand_parent_pt = pt->parent->parent;
        if (parent_pt == grand_parent_pt->left) {
            struct Node *uncle_pt = grand_parent_pt->right;
            if (uncle_pt != NULL && uncle_pt->color == 'R') {
                grand_parent_pt->color = 'R';
                parent_pt->color = 'B';
                uncle_pt->color = 'B';
                pt = grand_parent_pt;
            } else {
                if (pt == parent_pt->right) {
                    leftRotate(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }
                rightRotate(root, grand_parent_pt);
                char temp = parent_pt->color;
                parent_pt->color = grand_parent_pt->color;
                grand_parent_pt->color = temp;
                pt = parent_pt;
            }
        }
        else {
            struct Node *uncle_pt = grand_parent_pt->left;
            if ((uncle_pt != NULL) && (uncle_pt->color == 'R')) {
                grand_parent_pt->color = 'R';
                parent_pt->color = 'B';
                uncle_pt->color = 'B';
                pt = grand_parent_pt;
            } else {
                if (pt == parent_pt->left) {
                    rightRotate(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }
                leftRotate(root, grand_parent_pt);
                char temp = parent_pt->color;
                parent_pt->color = grand_parent_pt->color;
                grand_parent_pt->color = temp;
                pt = parent_pt;
            }
        }
    }
    (*root)->color = 'B';
}

struct Node* insert(struct Node* root, int data) {
    struct Node* newNode = createNode(data);
    struct Node* current = root;
    struct Node* parent = NULL;
    while (current != NULL) {
        parent = current;
        if (data < current->data)
            current = current->left;
        else
            current = current->right;
    }
    newNode->parent = parent;
    if (parent == NULL)
        root = newNode;
    else if (data < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;
    fixViolation(&root, newNode);
    return root;
}


void inOrderTraversal(struct Node* root) {
    if (root == NULL)
        return;
    inOrderTraversal(root->left);
    printf("%d ", root->data);
    inOrderTraversal(root->right);
}


int main() {
    struct Node* root = NULL;
    root = insert(root, 41);
    root = insert(root, 22);
    root = insert(root, 5);
    root = insert(root, 51);
    root = insert(root, 48);
    root = insert(root, 29);
    root = insert(root, 18);
    root = insert(root, 21);
    root = insert(root, 45);
    root = insert(root, 3);

    printf("InOrder Traversal: \n");
    inOrderTraversal(root);
    printf("\n");

    return 0;
}

