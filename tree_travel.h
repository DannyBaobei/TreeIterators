#ifndef TREE_TRAVEL_H
#define TREE_TRAVEL_H

#include "tree.h"

void Trav_inorder_goto(TreeNode_p_t root, funcVisitor fn);
void Trav_preorder_goto(TreeNode_p_t root, funcVisitor fn);
void Trav_postorder_goto(TreeNode_p_t root, funcVisitor fn);

void Trav_inorder_recur(TreeNode_p_t root, funcVisitor fn);
void Trav_preorder_recur(TreeNode_p_t root, funcVisitor fn);
void Trav_postorder_recur(TreeNode_p_t root, funcVisitor fn);

void Trav_inorder_loop(TreeNode_p_t root, funcVisitor fn);
void Trav_preorder_loop(TreeNode_p_t root, funcVisitor fn);
void Trav_postorder_loop(TreeNode_p_t root, funcVisitor fn);

struct {
	TRAVEL_type_t type;
	funcTravel fn;
}TraverseHandler_s;





















#endif
