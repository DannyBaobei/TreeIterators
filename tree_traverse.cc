#include "tree_travel.h"
#include <assert.h>

funcTravel fns[] = {
	Trav_preorder_goto,
	Trav_inorder_goto,
	Trav_postorder_goto,
	Trav_preorder_recur,
	Trav_inorder_recur,
	Trav_postorder_recur,
	Trav_preorder_loop,
	Trav_inorder_loop,
	Trav_postorder_loop
};

void Trav_inorder_recur(TreeNode_p_t node, funcVisitor fn)
{
	if(!node)
		return;
	Trav_preorder_recur(node->lchild, fn);
	fn(node);
	Trav_preorder_recur(node->rchild, fn);
}
void Trav_preorder_recur(TreeNode_p_t node, funcVisitor fn)
{
	if(!node)
		return;
	fn(node);
	Trav_preorder_recur(node->lchild, fn);
	Trav_preorder_recur(node->rchild, fn);
}
void Trav_postorder_recur(TreeNode_p_t node, funcVisitor fn)
{
	if(!node)
		return;
	Trav_preorder_recur(node->lchild, fn);
	Trav_preorder_recur(node->rchild, fn);
	fn(node);
}

void Trav_inorder_loop(TreeNode_p_t root, funcVisitor fn)
{

}
void Trav_preorder_loop(TreeNode_p_t root, funcVisitor fn)
{

}
void Trav_postorder_loop(TreeNode_p_t root, funcVisitor fn)
{

}

void Trav_inorder_goto(TreeNode_p_t root, funcVisitor fn)
{
	if(!root)
		return;
	TreeNode_p_t curr = root;

	trval_start:
	while (curr->lchild)
		curr = curr->lchild;
	leaf_return:
	assert(curr);
	fn(curr);

	if(curr->rchild)
	{
		curr = curr->rchild;
		goto trval_start;
	}
	else
	{
	leaf_find_unvisited:
		if(curr == root || curr == NULL)
			goto trval_end;

		//curr is leaf
		bool isVisited = curr == curr->parent->rchild;
		curr = curr->parent;
		if (isVisited)
			goto leaf_find_unvisited ;
		goto leaf_return;
	}
trval_end:  return;
}

void Trav_preorder_goto(TreeNode_p_t root, funcVisitor fn)
{
	if(!root)
		return;
	TreeNode_p_t curr = root;

	trval_start:
	assert(curr);
	fn(curr);
	if (curr->lchild) {
		curr = curr->lchild;
		goto trval_start;
	}

	if(curr->rchild)
	{
		curr = curr->rchild;
		goto trval_start;
	}
	else
	{
	leaf_find_unvisited:
		if(curr == root || curr == NULL)
			goto trval_end;

		bool isRLeaf = curr == curr->parent->rchild;
		if(isRLeaf && root  == curr->parent)
			goto trval_end;

		TreeNode_p_t next = isRLeaf? curr->parent->parent->rchild : curr->parent->rchild;

		if (next){
			curr = next;
			goto trval_start;
		}
		curr = curr->parent;
		goto leaf_find_unvisited;
	}
trval_end:  return;
}

void Trav_postorder_goto(TreeNode_p_t root, funcVisitor fn)
{
	if(!root)
		return;
	TreeNode_p_t curr = root;

	trval_start:
	while (curr->lchild)
		curr = curr->lchild;
	leaf_return:
	assert(curr);

	if(curr->rchild)
	{
		curr = curr->rchild;
		goto trval_start;
	}
	else
	{
	    leaf_find_unvisited:
		fn(curr);
		if(curr == root){
			goto trval_end;
		}

		bool isRLeaf = curr == curr->parent->rchild;
		TreeNode_p_t next = isRLeaf? curr->parent : curr->parent->rchild;
		if (!isRLeaf && next){
			curr = next;
			goto trval_start;
		}
		curr = curr->parent;
		goto leaf_find_unvisited;
	}
trval_end:  return;

}

void TREE_traverse(TRAVEL_type_t mode, TreeNode_p_t root, funcVisitor fnVisit)
{
	return fns[mode](root, fnVisit);

}

