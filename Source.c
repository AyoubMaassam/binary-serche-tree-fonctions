#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct node {
    int nmb;
    struct node* left;
    struct node* right;
};
struct node* creatnode(int nmb);


int Check_bst(struct node* root, int* min, int* max);

void Destroy_tree(struct node* root);

void Node_number(struct node* root, int* a);

void Display_tree(struct node* root);

void Display_tree2(struct node* root);

int Compare(struct node* first_tree, struct node* second_tree);

struct node* Insert(struct node* root, int valeur);

int* Find_node(struct node* root, int V);

int Check_bst(struct node* root, int* min, int* max);

struct node* Delete(struct node* root, int val);

int main() {
    struct node* root = creatnode(50);
    root->left = creatnode(30);
    root->right = creatnode(70);
    root->left->left = creatnode(20);
    root->left->right = creatnode(30);
    root->right->left = creatnode(60);
    root->right->right = creatnode(80);
    int min = INT_MAX;
    int max = INT_MIN;

    if (Check_bst(root, &min, &max)) {
        printf("The tree is a Binary Search Tree.\n");
        printf("min = %d max = %d \n", min, max);
    }
    else {
        printf("The tree is not a Binary Search Tree.\n");
    }
    int count = 0;
    Node_number(root, &count);
    printf("Number of nodes: %d\n", count);
    printf("\n");
    Display_tree(root);
    printf("\n");
    Display_tree2(root);
    printf("\n");
    int value_to_find = 40;
    int* result = Find_node(root, value_to_find);

    if (result != NULL) {
        printf("Value %d found at address %p\n", value_to_find, (void*)result);
    }
    else {
        printf("Value %d not found\n", value_to_find);
    }

    return 0;
}
struct node* creatnode(int nmb) {
    struct node* NewNode = (struct node*)malloc(sizeof(struct node));
    if (NewNode == NULL) {
        printf("Memory allocation error");
        exit(1);
    }
    NewNode->nmb = nmb;
    NewNode->left = NULL;
    NewNode->right = NULL;
    return NewNode;
}
void Destroy_tree(struct node* root) {
    if (root == NULL) {
        return;
    }
    Destroy_tree(root->left);
    Destroy_tree(root->right);
    free(root);
}
void Node_number(struct node* root, int* a) {
    if (root == NULL) {
        return;
    }
    else {
        *a = *a + 1;
        Node_number(root->left, a);
        Node_number(root->right, a);
    }
}
void Display_tree(struct node* root) {
    if (root != NULL) {
        Display_tree(root->left);
        printf("%d ", root->nmb);
        Display_tree(root->right);
    }
}
void Display_tree2(struct node* root) {
    if (root == NULL) {
        printf("{}");
        return;
    }

    printf("{");
    Display_tree2(root->left);
    printf(" , %d, ", root->nmb);
    Display_tree2(root->right);
    printf("}");
}
int Compare(struct node* first_tree, struct node* second_tree) {
    if (first_tree == NULL && second_tree == NULL) {
        return 0;
    }

    if (first_tree != NULL && second_tree != NULL) {
        if (first_tree->nmb == second_tree->nmb) {
            return Compare(first_tree->left, second_tree->left) &&
                Compare(first_tree->right, second_tree->right);
        }
        else {
            return 1;
        }
    }
    else {
        return 1;
    }
}
struct node* Insert(struct node* root, int valeur) {
    if (root == NULL) {
        return creatnode(valeur);
    }
    if (valeur <= root->nmb) {
        root->left = Insert(root->left, valeur);
    }
    else {
        root->right = Insert(root->right, valeur);
    }
    return root;
}
int* Find_node(struct node* root,int V) {
    if (root == NULL) {
        return NULL;
    }
    if (root->nmb == V) {
        return &root->nmb;
    }
    else {
        if (root->nmb < V) {
            return Find_node(root->left, V);
    }
    else {
            return Find_node(root->right, V);
    }
    }
}
int Check_bst(struct node* root, int* min, int* max) {
    if (root == NULL) {
        return 1;
    }

    if (root->nmb < *min) {
        *min = root->nmb;
    }

    if (root->nmb > *max) {
        *max = root->nmb;
    }

    return Check_bst(root->left, min, max) && Check_bst(root->right, min, max);
}
struct node* Delete(struct node* root, int val) {
    if (root == NULL) {
        return root;
    }

    if (val < root->nmb) {
        root->left = Delete(root->left, val);
    }
    else if (val > root->nmb) {
        root->right = Delete(root->right, val);
    }
    else {
 
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }

        struct node* temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }

        root->nmb = temp->nmb;
        root->right = Delete(root->right, temp->nmb);
    }
    return root;
}