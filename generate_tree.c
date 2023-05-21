// AVL tree implementation in C
#include <stdio.h>
#include <stdlib.h>
#include "helper_functions.h"

// Create Node
struct Node {
  Customer *customer;
  struct Node *left;
  struct Node *right;
  int height;
};

int max(int a, int b);

// Calculate height
int height(struct Node *N) 
{
  if (N == NULL)
    return 0;
  return N->height;
}

int max(int a, int b) 
{
  return (a > b) ? a : b;
}

// Create a node
struct Node *newNode(Customer *customer) 
{
  struct Node *node = (struct Node *)malloc(sizeof(struct Node));
  node->customer = customer;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return (node);
}

// Right rotate
struct Node *rightRotate(struct Node *y) 
{
  struct Node *x = y->left;
  struct Node *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  return x;
}

// Left rotate
struct Node *leftRotate(struct Node *x) 
{
  struct Node *y = x->right;
  struct Node *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  return y;
}

// Get the balance factor
int getBalance(struct Node *N) 
{
  if (N == NULL)
    return 0;
  return height(N->left) - height(N->right);
}

// Insert node
struct Node *insertNode(struct Node *node, Customer *customer, COMPARE(cust, pivot)) 
{
  // Find the correct position to insertNode the node and insertNode it
  if (node == NULL)
    return (newNode(customer));

  if (comp_function(customer, node->customer) == customer)
    node->left = insertNode(node->left, customer, comp_function);
  else if (comp_function(customer, node->customer) == node->customer)
    node->right = insertNode(node->right, customer, comp_function);
  else
    return node;

  // Update the balance factor of each node and
  // Balance the tree
  node->height = 1 + max(height(node->left),
               height(node->right));

  int balance = getBalance(node);
  if (balance > 1 && comp_function(node->left->customer, customer) == customer)
    return rightRotate(node);

  if (balance < -1 && comp_function(customer, node->right->customer) == node->right->customer)
    return leftRotate(node);

  if (balance > 1 && comp_function(customer, node->left->customer) == node->left->customer) 
  {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  if (balance < -1 && comp_function(node->right->customer, customer) == customer) 
  {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

struct Node *minValueNode(struct Node *node) 
{
  struct Node *current = node;

  while (current->left != NULL)
    current = current->left;

  return current;
}

// Delete a nodes
struct Node *Delete(struct Node *root, Customer *customer, COMPARE(cust, pivot)) 
{
  // Find the node and delete it
  if (root == NULL)
    return root;

  if (comp_function(customer, root->customer) == customer)
    root->left = Delete(root->left, customer, comp_function);

  else if (comp_function(root->customer, customer) == root->customer)
    root->right = Delete(root->right, customer, comp_function);

  else {
    if ((root->left == NULL) || (root->right == NULL)) {
      struct Node *temp = root->left ? root->left : root->right;

      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else
        *root = *temp;
      free(temp);
    } else {
      struct Node *temp = minValueNode(root->right);

      root->customer = temp->customer;

      root->right = Delete(root->right, temp->customer, comp_function);
    }
  }

  if (root == NULL)
    return root;

  // Update the balance factor of each node and
  // balance the tree
  root->height = 1 + max(height(root->left),
               height(root->right));

  int balance = getBalance(root);
  if (balance > 1 && getBalance(root->left) >= 0)
    return rightRotate(root);

  if (balance > 1 && getBalance(root->left) < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  if (balance < -1 && getBalance(root->right) <= 0)
    return leftRotate(root);

  if (balance < -1 && getBalance(root->right) > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}

// Print the tree
void Print(struct Node *root) 
{
  if (root != NULL) 
  {
    Print(root->left);
    printf("%d ", root->customer->debt);
    Print(root->right);
  }
}

int main() 
{
    struct Node *root = NULL;

    Customer *c1 = calloc(1, sizeof(Customer));
    c1->debt = 100;
    Customer *c2 = calloc(1, sizeof(Customer));
    c2->debt = 200;
    Customer *c3 = calloc(1, sizeof(Customer));
    c3->debt = -100;
    Customer *c4 = calloc(1, sizeof(Customer));
    c4->debt = -200;
    Customer *c5 = calloc(1, sizeof(Customer));
    c5->debt = 0;
    Customer *c6 = calloc(1, sizeof(Customer));
    c6->debt = 101;

    root = insertNode(root, c1, compare_debt);
    root = insertNode(root, c2, compare_debt);
    root = insertNode(root, c3, compare_debt);
    root = insertNode(root, c4, compare_debt);
    root = insertNode(root, c5, compare_debt);
    root = insertNode(root, c5, compare_debt);
    root = insertNode(root, c6, compare_debt);

    Print(root);

    root = Delete(root, c1, compare_debt);

    printf("\nAfter deletion: ");
    Print(root);

    return 0;
}