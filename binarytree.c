#include <stdio.h>
#include <stdlib.h>
#include "binarytree.h"

/* Alloc a new node with given data. */
struct TreeNode* createNode(int data)
{
	struct TreeNode *root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	root->data = data;

	root->left = NULL;
	root->right = NULL;

	return root;
}

/* Insert data at appropriate place in BST, return new tree root. */
struct TreeNode* insertBST(struct TreeNode* root, int data)
{
	if(root == NULL)
	{
		return createNode(data);
	}
	else
	{
		if (data <= root->data)
		{
			root->left = insertBST(root->left, data);
		}
		else
		{
			root->right = insertBST(root->right, data);
		}
		return root;
	}
}

/* Remove data from BST pointed to by rootRef, changing root if necessary.
 * For simplicity's sake, always choose node's in-order
 *   successor in the two-child case.
 * Memory for removed node should be freed.
 * Return 1 if data was present, 0 if not found. */
int removeBST(struct TreeNode** rootRef, int data)
{
  if (*rootRef == NULL) return 0;
  if (data < (*rootRef)->data) 
  {
	removeBST(&(*rootRef)->left, data);
  }
  else if (data > (*rootRef)->data)
  {
	removeBST(&(*rootRef)->right, data);
  }
  else if (data == (*rootRef)->data) //delete
  {
	if ((*rootRef)->left == NULL && (*rootRef)->right == NULL)
	{
	  free((*rootRef));
	  (*rootRef) = NULL;
	}
	else if ((*rootRef)->right == NULL)
	{
	  struct TreeNode *temp = (*rootRef)->left;
	  free(*rootRef);
	  *rootRef = temp;
	}
	else if ((*rootRef)->left == NULL)
	{
	  struct TreeNode *temp = (*rootRef)->right; 
	  free(*rootRef);
	  *rootRef = temp;
	}
	else
	{
	  struct TreeNode **successor = getInOrderSuccessor(&(*rootRef)->right);
	  (*rootRef)->data = (*successor)->data;
	  removeBST(successor, (*successor)->data);
	}
	return 1;
  }
  return 0;
}

/*Returns the in order successor of a given tree node. */
struct TreeNode** getInOrderSuccessor(struct TreeNode **node)
{
	struct TreeNode **temp = node;
	while ((*temp)->left != NULL)
	{
	  temp = &(*temp)->left;
	}
	return temp;
}
/* Return minimum value in non-empty binary search tree. */
int minValueBST(struct TreeNode* root)
{
	struct TreeNode* current = root;

	while (current->left != NULL)
	{
		current = current->left;
	}
	return(current->data);
}
/* Return maximum value in non-empty binary search tree. */
int maxValueBST(struct TreeNode* root)
{
	struct TreeNode* current = root;

	while (current->right != NULL)
	{
		current = current->right;
	}
	return(current->data);
}

/* Return maximum depth of tree. Empty tree has depth 0. */
int maxDepth(struct TreeNode* root)
{
	if(root == NULL) return 0;
	else
	{
		int leftDepth = maxDepth(root->left);
		int rightDepth = maxDepth(root->right);

		if (rightDepth > leftDepth)
		{
			return rightDepth+1;
		}
		else
		{
			return leftDepth+1;
		}
	}
}
/* A tree is balanced if both subtrees are balanced and
 * the difference in height between the subtrees is no more than 1.
 * Return 1 if tree is balanced, 0 if not. */
int isBalanced(struct TreeNode* root)
{
	int leftHeight;
	int rightHeight;

	if (root == NULL) return 1;

	leftHeight = maxDepth(root->left);
	rightHeight = maxDepth(root->right);

	if (abs(leftHeight-rightHeight) <= 1
		&& isBalanced(root->left)
		&& isBalanced(root->right))
	{
		return 1;
	}
	return 0;
}

/* Return 1 if tree is a binary search tree, 0 if not. */
int isBST(struct TreeNode* root)
{
	if(root == NULL) return 1;

	if(root->left != NULL && maxValueBST(root->left) > root->data) return 0;

	if(root->right != NULL && minValueBST(root->right) < root->data) return 0;

	if(!isBST(root->left) || !isBST(root->right)) return 0;

	return 1;
}

/* Print data for inorder tree traversal on single line,
 * separated with spaces, ending with newline. */
void printTree(struct TreeNode* root)
{
	if(root != NULL)
	{
		printTree(root->left);
		printf("%d ", root->data);
		printTree(root->right);
	}
}

/* Print data for leaves on single line,
 * separated with spaces, ending with newline.*/
void printLeaves(struct TreeNode* root)
{
	if(root == NULL)
	{
		printf("");
	}
	else if(root->left == NULL && root->right == NULL)
	{
		printf("%d ", root->data);
	}
	else
	{
		if(root->left != NULL)
		{
			printLeaves(root->left);
		}
		if(root->right != NULL)
		{
			printLeaves(root->right);
		}
	}
}

void newLine(int data);

/* Free memory used by the tree. */
void freeTree(struct TreeNode* root)
{
  if(root != NULL)
  {
  	freeTree(root->left);
  	freeTree(root->right);
  	free(root);
  }
}