#include "tree_definition.h"
#include <functional>
#include <iostream>
#include <utility>
#include <cstddef>
#include <stack>
using namespace std;


struct List
{
function <TreeNode_p_t()>  first;
function <struct List*()>     rest;
};

TreeNode_p_t first(List* list1)
{
    return list1 == NULL? NULL : list1->first();
}

List* rest(List* list1)
{
    return list1 == NULL? NULL:list1->rest();
}

List* Empty() {
    return NULL;
};

List* Singleton(TreeNode_p_t e) {
    List *node = new List();
    node->first = [=]()mutable{
        return e;
    };

    node->rest = [=]()mutable{
        return (List*)NULL;
    };
    return node;
}

List* Append(List* list1, List* list2)
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

List* make_binary_tree_iterator(TreeNode_p_t node) 
{
    List* listNode = new List();
    listNode->first = [=]()mutable {
        return NULL != node->lchild ? first(make_binary_tree_iterator(node->lchild)) : node;
    };
    listNode->rest = [=]()mutable {
        List* left_it = (NULL == node->lchild ? NULL : make_binary_tree_iterator(node->lchild));
        List* root_it = Singleton(node);
        List* right_it = (NULL == node->rchild ? NULL : make_binary_tree_iterator(node->rchild));
        List* it = Append(Append(left_it, root_it), right_it);
        return rest(it);
    };
    return listNode;
}


