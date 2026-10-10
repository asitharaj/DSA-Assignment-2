#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Structure for expression tree node
struct Node {
    char data;
    struct Node *left;
    struct Node *right;
};

// Stack for tree nodes
struct Node *treeStack[MAX];
int top = -1;

// Create a new node
struct Node* createNode(char data) {
    struct Node *newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Push tree node
void push(struct Node *node) {
    treeStack[++top] = node;
}

// Pop tree node
struct Node* pop() {
    return treeStack[top--];
}

// Construct expression tree from postfix
struct Node* constructTree(char postfix[]) {
    int i;
    char symbol;
    struct Node *node;
    struct Node *left;
    struct Node *right;

    for (i = 0; postfix[i] != '\0'; i++) {

        symbol = postfix[i];

        if (symbol == ' ')
            continue;

        // If operand
        if (isdigit(symbol)) {
            node = createNode(symbol);
            push(node);
        }

        // If operator
        else {
            node = createNode(symbol);

            right = pop();
            left = pop();

            node->left = left;
            node->right = right;

            push(node);
        }
    }

    return pop();
}

// Inorder traversal
void inorder(struct Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%c ", root->data);
        inorder(root->right);
    }
}

// Preorder traversal
void preorder(struct Node *root) {
    if (root != NULL) {
        printf("%c ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// Postorder traversal
void postorder(struct Node *root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%c ", root->data);
    }
}

// Perform operation
int operation(int a, int b, char op) {
    switch (op) {
        case '+':
            return a + b;

        case '-':
            return a - b;

        case '*':
            return a * b;

        case '/':
            return a / b;
    }

    return 0;
}

// Evaluate expression tree
int evaluateTree(struct Node *root) {

    int leftValue;
    int rightValue;

    if (root == NULL)
        return 0;

    // If operand
    if (isdigit(root->data))
        return root->data - '0';

    leftValue = evaluateTree(root->left);
    rightValue = evaluateTree(root->right);

    return operation(leftValue, rightValue, root->data);
}

// Evaluate postfix using stack
int evaluatePostfix(char postfix[]) {

    int stack[MAX];
    int top = -1;

    int i;
    int a, b, result;
    char symbol;

    for (i = 0; postfix[i] != '\0'; i++) {

        symbol = postfix[i];

        if (symbol == ' ')
            continue;

        // If operand
        if (isdigit(symbol)) {
            stack[++top] = symbol - '0';
        }

        // If operator
        else {
            b = stack[top--];
            a = stack[top--];

            result = operation(a, b, symbol);

            stack[++top] = result;
        }
    }

    return stack[top];
}

// Main function
int main() {

    char postfix[] = "8 3 2 * + 6 2 / -";

    struct Node *root;

    root = constructTree(postfix);

    printf("Postfix Expression: %s\n", postfix);

    printf("\nInorder Traversal: ");
    inorder(root);

    printf("\nPreorder Traversal: ");
    preorder(root);

    printf("\nPostorder Traversal: ");
    postorder(root);

    printf("\n\nStack-based Postfix Evaluation: %d",
           evaluatePostfix(postfix));

    printf("\nExpression Tree Evaluation: %d\n",
           evaluateTree(root));

    return 0;
}