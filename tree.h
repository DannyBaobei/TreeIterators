#ifndef TREE_H
#define TREE_H

#define DATA_type char

typedef struct TreeNode_s {
	DATA_type data;
	struct TreeNode_s *parent, *lchild, *rchild;
	TreeNode_s( DATA_type  theData);
	static void ConstructTree( struct TreeNode_s* &theTree, struct TreeNode_s * parentTree,  char* &theKeyWds);
}TreeNode_t, *TreeNode_p_t;


typedef enum TRAVEL_type_e {
	TRAVEL_R_PRE_ORDER =0,
	TRAVEL_R_IN_ORDER  ,
	TRAVEL_R_POST_ORDER,
	TRAVEL_G_PRE_ORDER,
	TRAVEL_G_IN_ORDER ,
	TRAVEL_G_POST_ORDER, 
	TRAVEL_L_PRE_ORDER,
	TRAVEL_L_IN_ORDER ,
	TRAVEL_L_POST_ORDER 
}TRAVEL_type_t;

typedef void (*funcVisitor) ( TreeNode_p_t node);
typedef void (*funcTravel) ( TreeNode_p_t root, funcVisitor fn);

extern void TREE_traverse(TRAVEL_type_t mode, TreeNode_p_t root, funcVisitor fn);





















#endif
