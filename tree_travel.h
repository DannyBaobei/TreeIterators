#ifndef TREE_TRAVEL_H
#define TREE_TRAVEL_H

#include "tree.h"

//#if 1
#define DATA_type char
struct TreeNode_s {
	DATA_type data;
	struct TreeNode_s *parent, *lchild, *rchild;
	TreeNode_s( DATA_type  theData);
	static void ConstructTree( TreeNode_p_t &theTree, TreeNode_p_t parentTree,  char* &theKeyWds);
};
//#else
//#endif

void Trav_inorder_goto(TreeNode_p_t root, funcVisitor fn);
void Trav_preorder_goto(TreeNode_p_t root, funcVisitor fn);
void Trav_postorder_goto(TreeNode_p_t root, funcVisitor fn);

void Trav_inorder_recur(TreeNode_p_t root, funcVisitor fn);
void Trav_preorder_recur(TreeNode_p_t root, funcVisitor fn);
void Trav_postorder_recur(TreeNode_p_t root, funcVisitor fn);

void Trav_inorder_loop(TreeNode_p_t root, funcVisitor fn);
void Trav_preorder_loop(TreeNode_p_t root, funcVisitor fn);
void Trav_postorder_loop(TreeNode_p_t root, funcVisitor fn);

typedef struct TraverseHandler_s{
	TRAVEL_type_t type;
	funcTravel fn;
}TraverseHandler_t;





















#endif
