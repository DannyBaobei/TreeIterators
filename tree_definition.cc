#include "tree_definition.h"
#include <cstddef>
#include <assert.h>

TreeNode_s::TreeNode_s( DATA_type  theData)
	: data(theData) 
	, parent(NULL) 
	, lchild(NULL) 
	, rchild(NULL) 
#ifdef RB_TREE
	, color(true) 
#endif
{ 
}
void TreeNode_s::ConstructTree( TreeNode_p_t &theTree, TreeNode_p_t parentTree,  char* &theKeyWds)
{
	if(!theKeyWds)
		return;
	if(*theKeyWds == '#')
		theTree = NULL;
	else
	{
		theTree = new TreeNode_s(*theKeyWds); 
		theTree->parent = parentTree;
		assert(theTree);
        ++theKeyWds;
        if(!theKeyWds || *theKeyWds == '\0')
			return;
		ConstructTree(theTree->lchild, theTree, theKeyWds);
        ++theKeyWds;
		if(!theKeyWds|| *theKeyWds == '\0')
			return;
		ConstructTree(theTree->rchild, theTree, theKeyWds);
	}
}



void TREE_constuct( TreeNode_p_t &theTree, TreeNode_p_t parentTree,  char* &theKeyWds)
{
    return TreeNode_s::ConstructTree(theTree, parentTree, theKeyWds);
}

void TREE_get_node_value( TreeNode_p_t &theTree, const void** data )
{
    if(!theTree)
        return ;
    *data = &theTree->data;
}

