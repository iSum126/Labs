#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

TreeNode* create_node(int key) {
    TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
    if (!node) {
        printf("Ошибка выделения памяти для нового узла.\n");
        exit(EXIT_FAILURE);
    }
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

TreeNode* insert_node(TreeNode *root, int key) {
    if (root == NULL)
        return create_node(key);
    if (key < root->key)
        root->left = insert_node(root->left, key);
    else if (key > root->key)
        root->right = insert_node(root->right, key);
    else 
        printf("Элемент %d уже присутствует в дереве.\n", key);
    return root;
}

static TreeNode* find_min(TreeNode *root) {
    while (root && root->left)
        root = root->left;
    return root;
}

TreeNode* delete_node(TreeNode *root, int key) {
    if (root == NULL)
        return NULL;
    if (key < root->key)
        root->left = delete_node(root->left, key);
    else if (key > root->key)
        root->right = delete_node(root->right, key);
    else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        } else if (root->left == NULL) {
            TreeNode *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNode *temp = root->left;
            free(root);
            return temp;
        } else {
            TreeNode *temp = find_min(root->right);
            root->key = temp->key;
            root->right = delete_node(root->right, temp->key);
        }
    }
    return root;
}

void free_tree(TreeNode *root) {
    if (root == NULL)
        return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

void inorder_traversal(TreeNode *root, int arr[], int *index) {
    if (root == NULL)
        return;
    inorder_traversal(root->left, arr, index);
    arr[(*index)++] = root->key;
    inorder_traversal(root->right, arr, index);
}

int count_nodes(TreeNode *root) {
    if (root == NULL)
        return 0;
    return 1 + count_nodes(root->left) + count_nodes(root->right);
}

TreeNode* build_balanced_tree_from_sorted(int arr[], int start, int end) {
    if (start > end)
        return NULL;
    int mid = (start + end) / 2;
    TreeNode *root = create_node(arr[mid]);
    root->left = build_balanced_tree_from_sorted(arr, start, mid - 1);
    root->right = build_balanced_tree_from_sorted(arr, mid + 1, end);
    return root;
}

int tree_height(TreeNode *root) {
    if (root == NULL)
        return 0;
    int leftH = tree_height(root->left);
    int rightH = tree_height(root->right);
    return (leftH > rightH ? leftH : rightH) + 1;
}

static void fill_output(TreeNode *node, int level, int left, int right, char **output, int cellWidth) {
    if (node == NULL || left > right)
        return;
    int mid = (left + right) / 2;
    

    char buf[16];
    sprintf(buf, "%4d", node->key);
    
    int start = mid - cellWidth / 2;
    if (start < left)
        start = left;
    for (int i = 0; i < cellWidth; i++) {
        if (start + i < right + 1)
            output[level * 2][start + i] = buf[i];
    }
    
    if (node->left) {
        int child_mid = (left + mid - 1) / 2;
        int conn_col = (child_mid + mid) / 2;
        output[level * 2 + 1][conn_col] = '/';
        fill_output(node->left, level + 1, left, mid - 1, output, cellWidth);
    }
    
    if (node->right) {
        int child_mid = (mid + 1 + right) / 2;
        int conn_col = (mid + child_mid) / 2;
        output[level * 2 + 1][conn_col] = '\\';
        fill_output(node->right, level + 1, mid + 1, right, output, cellWidth);
    }
}

void print_tree_top_down(TreeNode *root) {
    if (root == NULL) {
        printf("Дерево пустое.\n");
        return;
    }
    int h = tree_height(root);
    int cellWidth = 4;
    int cols = ((1 << h) * cellWidth) - 1;
    int rows = h * 2 - 1;
    
    char **output = (char**)malloc(rows * sizeof(char *));
    if (!output) {
        printf("Ошибка выделения памяти для визуализации дерева.\n");
        return;
    }
    for (int i = 0; i < rows; i++) {
        output[i] = (char*)malloc((cols + 1) * sizeof(char));
        if (!output[i]) {
            printf("Ошибка выделения памяти для строки буфера.\n");
            for (int j = 0; j < i; j++)
                free(output[j]);
            free(output);
            return;
        }
        for (int j = 0; j < cols; j++)
            output[i][j] = ' ';
        output[i][cols] = '\0';
    }
    
    fill_output(root, 0, 0, cols - 1, output, cellWidth);
    
    for (int i = 0; i < rows; i++) {
        printf("%s\n", output[i]);
        free(output[i]);
    }
    free(output);
}
