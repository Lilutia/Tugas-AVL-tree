#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* left;
    struct node* right;
    int ht; // height of node
};
struct node* root = NULL;

// Function to calculate the height of a node
int height(struct node* root) {
    int lh, rh;

    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL) {
        lh = 0;
    } else {
        lh = 1 + root->left->ht;
    }
    if (root->right == NULL) {
        rh = 0;
    } else {
        rh = 1 + root->right->ht;
    }
    if (lh > rh) {
        return lh;
    }
    return rh;
}

struct node* rotate_left(struct node* root) {
    struct node* right_child = root->right;
    root->right = right_child->left;
    right_child->left = root;

    // update the heights of the nodes
    root->ht = height(root);
    right_child->ht = height(right_child);

    // return the new node after rotation
    return right_child;
}

struct node* rotate_right(struct node* root) {
    struct node* left_child = root->left;
    root->left = left_child->right;
    left_child->right = root;

    // update the heights of the nodes
    root->ht = height(root);
    left_child->ht = height(left_child);

    // return the new node after rotation
    return left_child;
}

int balance_factor(struct node* root) {
    int lh, rh;

    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL) {
        lh = 0;
    } else {
        lh = 1 + root->left->ht;
    }
    if (root->right == NULL) {
        rh = 0;
    } else {
        rh = 1 + root->right->ht;
    }
    return lh - rh;
}

struct node* create_node(int data) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->right = NULL;
    new_node->left = NULL;
    new_node->ht = 1;
    return new_node;
}

struct node* insert(struct node* root, int data) {
    if (root == NULL) {
        root = create_node(data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);

        // if unbalanced, rotate!
        if (balance_factor(root) == -2) {
            if (data > root->right->data) { // case RR
                root = rotate_left(root);
            } else { // case RL
                root->right = rotate_right(root->right);
                root = rotate_left(root);
            }
        }
    } else {
        root->left = insert(root->left, data);

        if (balance_factor(root) == 2) {
            if (data < root->left->data) { // case LL
                root = rotate_right(root);
            } else { // case LR
                root->left = rotate_left(root->left);
                root = rotate_right(root);
            }
        }
    }

    // update height of node
    root->ht = height(root);
    return root;
}

// find the minimum node in the right subtree
struct node* min_value_node(struct node* node) {
    struct node* current = node;

    // find the leftmost leaf
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

// delete node in AVL tree
struct node* delete_node(struct node* root, int data) {
    if (root == NULL) {
        return root;
    }

    if (data < root->data) {
        root->left = delete_node(root->left, data);
    }
    else if (data > root->data) {
        root->right = delete_node(root->right, data);
    }
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            struct node* temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else { // one child case
                *root = *temp; // copy the contents of the non-empty child
            }
            free(temp);
        } else {
            struct node* temp = min_value_node(root->right);

            root->data = temp->data;

            root->right = delete_node(root->right, temp->data);
        }
    }

    if (root == NULL) {
        return root;
    }

    root->ht = height(root);

    int balance = balance_factor(root);

    // balance the tree
    if (balance > 1) {
        // case LL
        if (balance_factor(root->left) >= 0) {
            return rotate_right(root);
        }
        // case LR
        else {
            root->left = rotate_left(root->left);
            return rotate_right(root);
        }
    }
    if (balance < -1) {
        // case RR
        if (balance_factor(root->right) <= 0) {
            return rotate_left(root);
        }
        // case RL
        else {
            root->right = rotate_right(root->right);
            return rotate_left(root);
        }
    }

    return root;
}

// search node function
struct node* search(struct node* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }
    if (data < root->data) {
        return search(root->left, data);
    }
    return search(root->right, data);
}

// Search multiple node function
void search_multiple(struct node* root, int keys[], int num_keys) {
    for (int i = 0; i < num_keys; i++) {
        struct node* found = search(root, keys[i]);
        if (found != NULL) {
            printf("Node %d was found in the AVL tree.\n", keys[i]);
        } else {
            printf("Node %d was not found in the AVL tree.\n", keys[i]);
        }
    }
}

// inorder traversal of the tree
void inorder(struct node* root) {
    if (root == NULL) {
        return;
    }

    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

// preorder traversal of the tree
void preorder(struct node* root) {
    if (root == NULL) {
        return;
    }

    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

// postorder traversal of the tree
void postorder(struct node* root) {
    if (root == NULL) {
        return;
    }

    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

int main() {
    root = insert(root, 10);
    root = insert(root, 15);
    root = insert(root, 20);
    root = insert(root, 9);
    root = insert(root, 5);
    root = insert(root, 16);
    root = insert(root, 17);
    root = insert(root, 8);
    root = insert(root, 6);

    printf("Preorder traversal of the AVL tree:\n");
    preorder(root);
    printf("\n");
    printf("\n");

    root = delete_node(root, 16);
    root = delete_node(root, 9);

    printf("Preorder traversal of the AVL tree after deletion:\n");
    preorder(root);
    printf("\n");
    printf("\n");
    
	printf("Single searching:\n");
    // searching
    int search_key = 15;
    struct node* found = search(root, search_key);
    if (found != NULL) {
        printf("Node %d found in the AVL tree.\n", search_key);
    } else {
        printf("Node %d not found in the AVL tree.\n", search_key);
    }
    printf("\n");
    
    
    printf("Multiple Searches:\n");
    int search_keys[] = {7, 20, 8};
    int num_keys = sizeof(search_keys) / sizeof(search_keys[0]);

    search_multiple(root, search_keys, num_keys);

    return 0;
}

