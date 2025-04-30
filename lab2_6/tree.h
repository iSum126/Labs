#ifndef TREE_H
#define TREE_H

typedef struct TreeNode {
    int key;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode* create_node(int key);
TreeNode* insert_node(TreeNode *root, int key);
TreeNode* delete_node(TreeNode *root, int key);
void free_tree(TreeNode *root);

void inorder_traversal(TreeNode *root, int arr[], int *index);
int count_nodes(TreeNode *root);

TreeNode* build_balanced_tree_from_sorted(int arr[], int start, int end);

int tree_height(TreeNode *root);
void print_tree_top_down(TreeNode *root);

#endif
