#include "tree_definition.h"
#include <functional>
#include <cstddef>
using namespace std;

struct List{
	function <TreeNode_p_t()> first;
	function <List_p_t()>     rest;
};

TreeNode_p_t first(List_p_t list1)
{
	return list1 == NULL? NULL : list1->first();
}

List_p_t rest(List_p_t list1)
{
	return list1 == NULL? NULL:list1->rest();
}

List_p_t Empty() {
	return NULL;
};

List_p_t Singleton(TreeNode_p_t e) {
	List *node = new List();
	node->first = [=]()mutable{
		return e;
	};

	node->rest = [=]()mutable{
		return (List_p_t)NULL;
	};
	return node;
}

List_p_t Append(List_p_t list1, List_p_t list2)
{
	if(NULL == list1) return list2;
	if(NULL == list2) return list1;

	List *node = new List();
	node->first = [=]()mutable{
		return first(list1);
	};

	node->rest = [=]()mutable{
		return Append(rest(list1), list2);
	};
	return node;
}


List_p_t make_inorder_tree_iterator(TreeNode_p_t node) 
{
    if(!node)
        return NULL;
	List_p_t listNode = new List();
	listNode->first = [node]()mutable {
		return NULL != node->lchild ? first(make_inorder_tree_iterator(node->lchild)) : node;
	};
	listNode->rest = [node]()mutable {
		List_p_t left_it = (NULL == node->lchild ? NULL : make_inorder_tree_iterator(node->lchild));
		List_p_t root_it = Singleton(node);
		List_p_t right_it = (NULL == node->rchild ? NULL : make_inorder_tree_iterator(node->rchild));
		List_p_t it = Append(Append(left_it, root_it), right_it);
		return rest(it);
	};
	return listNode;
}

List_p_t make_preorder_tree_iterator(TreeNode_p_t node) 
{
    if(!node)
        return NULL;
	List_p_t listNode = new List();
	listNode->first = [node]()mutable {
		return node;
	};
	listNode->rest = [node]()mutable {
		List_p_t left_it = (NULL == node->lchild ? NULL : make_preorder_tree_iterator(node->lchild));
		List_p_t root_it = Singleton(node);
		List_p_t right_it = (NULL == node->rchild ? NULL : make_preorder_tree_iterator(node->rchild));
		List_p_t it = Append(Append(root_it,left_it), right_it);
		return rest(it);
	};
	return listNode;
}

List_p_t make_postorder_tree_iterator(TreeNode_p_t node) 
{
    if(!node)
        return NULL;
	List_p_t listNode = new List();
	listNode->first = [node]()mutable {
        if(NULL == node->lchild  &&  NULL == node->rchild)
            return node;
		return NULL != node->lchild ? first(make_postorder_tree_iterator(node->lchild)) : first(make_postorder_tree_iterator(node->rchild)) ;
	};
	listNode->rest = [node]()mutable {
		List_p_t left_it = (NULL == node->lchild ? NULL : make_postorder_tree_iterator(node->lchild));
		List_p_t root_it = Singleton(node);
		List_p_t right_it = (NULL == node->rchild ? NULL : make_postorder_tree_iterator(node->rchild));
		List_p_t it = Append(Append(left_it, right_it), root_it);
		return rest(it);
	};
	return listNode;
}
