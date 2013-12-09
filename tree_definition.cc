#include "tree.h"
#include "stdio.h"
#include <assert.h>

TreeNode_s::TreeNode_s( DATA_type  theData)
	: data(theData) 
	, parent(NULL) 
	, lchild(NULL) 
	, rchild(NULL) 
{ 
}
void TreeNode_s::ConstructTree( struct TreeNode_s* &theTree, struct TreeNode_s * parentTree,  char* &theKeyWds)
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

		if(++theKeyWds == NULL)
			return;
		ConstructTree(theTree->lchild, theTree, theKeyWds);
		if(++theKeyWds == NULL)
			return;
		ConstructTree(theTree->rchild, theTree, theKeyWds);
	}
}





